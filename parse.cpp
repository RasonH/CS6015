//
// Created by Rason Hung on 2/21/23.
//

#pragma include once

#include "parse.h"
#include "expr.h"
// default design rule - skip spaces both front and end for every parse function

// helper function consume
void consume(std::istream &in, int nextChar) {
	int c = in.get();
	if (c != nextChar) {
		throw std::runtime_error("consume mismatch");
	}
}

// helper function check space
void skip_space(std::istream &in) {
	while (true) {
		int c = in.peek();
		if (!(isspace(c) || (c == '\n'))) {
			break;
		}
		consume(in, c);
	}
}

// helper function for testing
PTR(Expr)parse_str(const std::string &s) {
	std::stringstream in(s);
	return parse_str(in);
}

PTR(Expr)parse_str(std::istream &in) {
	PTR(Expr)e = parse_expr(in);
	if (!in.eof()) { // if there is still character at the end after parsing a
		// whole expression
		throw std::runtime_error("invalid input - still have character after parsing the whole expression");
		//        throw std::runtime_error("");
	} else {
		return e;
	}
}

// parse number
PTR(Expr)parse_num(std::istream &in) {
//	(called by parse_inner, already skipped space in the front), the next character is '-' or digit
//	skip_space(in); // no skipping space here, be careful with input"-   123456", rule: only "-123456" is valid to parse
	int n = 0;
	bool negative = false;
	bool numSeen = false;
	if (in.peek() == '-') {
		negative = true;
		consume(in, '-');
	}
	while (true) {
		int c = in.peek();
		if (isdigit(c)) {
			if (!numSeen) {
				numSeen = true;
			}
			consume(in, c);
			n = n * 10 + (c - '0');
		} else {
			break;
		}
	}
	if (negative) {
		n = -n;
	}
	if (!numSeen) {
		throw std::runtime_error("invalid input - no number seen");
		//        throw std::runtime_error("");
	}
	skip_space(in);
	return NEW(NumExpr)(n);
}

// parse variable
PTR(Expr)parse_var(std::istream &in) {
	skip_space(in);
	std::string s;
	while (true) {
		int c = in.peek();
		if (isalpha(c)) {
			consume(in, c);
			s += c;
		} else {
			break;
		}
	}
	skip_space(in);
	return NEW(VarExpr)(s);
}

// parse keyword
std::string parse_keyword(std::istream &in) {
	skip_space(in);
	int c = in.peek();
	std::string keyword = "";
	if (c == '_') {
		keyword += c;
		consume(in, c);
		c = in.peek();
		while (isalpha(c)) {
			keyword += c;
			consume(in, c);
			c = in.peek();
		}
	}
	skip_space(in);
	return keyword;
}

// parse _let - _let <variable> = <expr> _in <expr>
PTR(Expr)parse_let(std::istream &in) {
	// already read in _let and consumed
	skip_space(in);
	std::string lhs = parse_var(in)->to_string();
	int c = in.peek();
	if (c == '=') {
		consume(in, c);
	} else {
		throw std::runtime_error("'=' is required in _let");
	}
	PTR(Expr)rhs = parse_expr(in);
	if (parse_keyword(in) != "_in") {
		throw std::runtime_error("'_in' is required in _let");
	}
	PTR(Expr)body = parse_expr(in);
	skip_space(in);
	return NEW(LetExpr)(lhs, rhs, body);
}

// parse _if - _if <expr> _then  <expr> _else <expr>
PTR(Expr)parse_if(std::istream &in) {
	// already read in _if and consumed
	skip_space(in);
	PTR(Expr)testPart = parse_expr(in);
	if (parse_keyword(in) != "_then") {
		throw std::runtime_error("'_then' is required in _if");
	}
	PTR(Expr)thenPart = parse_expr(in);
	if (parse_keyword(in) != "_else") {
		throw std::runtime_error("'_else' is required in _if");
	}
	PTR(Expr)elsePart = parse_expr(in);
	skip_space(in);
	return NEW(IfExpr)(testPart, thenPart, elsePart);
}

// parse _fun - _fun (<variable>) <expr>
PTR(Expr)parse_fun(std::istream &in) {
	// already read in _fun and consumed
	skip_space(in);
	int c = in.peek();
	std::string formalArg;
	if (c == '(') {
		consume(in, c);
		formalArg = parse_var(in)->to_string();
	} else {
		throw std::runtime_error("'(' is required in _fun");
	}
	c = in.peek();
	if (c == ')') {
		consume(in, c);
	} else {
		throw std::runtime_error("')' is required in _fun");
	}
	PTR(Expr)body = parse_expr(in);
	skip_space(in);
	return NEW(FunExpr)(formalArg, body);
}

/*
   <inner> = <number>
		   | ( <expr> )
		   | <variable>
		   | _let <variable> = <expr> _in <expr>
		   | _true
		   | _false
		   | _if <expr> _then <expr> _else <expr>
		   | _fun ( <variable> ) <expr>
 */

PTR(Expr)parse_inner(std::istream &in) {
	skip_space(in);
	int c = in.peek();
	// <number>
	if ((c == '-') || isdigit(c)) {
		return parse_num(in);
	}
		// ( <expr> )
	else if (c == '(') {
		consume(in, '(');
		PTR(Expr)e = parse_expr(in); // parse parenthesized
		c = in.peek();
		if (c != ')') {
			throw std::runtime_error(
				"invalid input - missing ')' - parse_inner"); // missing the closing parenthesis
		} else {
			consume(in, ')');
			skip_space(in);
			return e;
		}
	}
		// <variable>
	else if (isalpha(c)) {
		return parse_var(in);
	}
		// keywords
	else if (c == '_') {
		std::string keyword = parse_keyword(in);
		if (keyword == "_let") {
			return parse_let(in);
		} else if (keyword == "_true") {
			skip_space(in);
			return NEW(BoolExpr)(true);
		} else if (keyword == "_false") {
			skip_space(in);
			return NEW(BoolExpr)(false);
		} else if (keyword == "_if") {
			return parse_if(in);
		} else if (keyword == "_fun") {
			return parse_fun(in);
		} else {
			throw std::runtime_error("invalid input - unknown keyword"); // triggered keyword parsing but unknown keyword
		}
	} else { // next character is not any of these conditions
//		consume(in, c);
		throw std::runtime_error("invalid input - not included condition");
		// other than previous possibilities
	}
}

/*
   <multicand> =  <inner>
				| <multicand> ( <expr> )
 */
PTR(Expr)parse_multicand(std::istream &in) {
	skip_space(in);
	PTR(Expr)expr = parse_inner(in);
	while (in.peek() == '(') {
		consume(in, '(');
		PTR(Expr)actualArg = parse_expr(in);
		if (in.peek() == ')') {
			consume(in, ')');
			skip_space(in); // TODO: here assume "f   (1)   (2)  " is valid input
		} else {
			throw std::runtime_error("invalid input - missing ')' - parse_multicand"); // missing closing parenthesis
		}
		expr = NEW(CallExpr)(expr, actualArg); // e.g. f(1)(2) -> can be recursively parsed
	}
	skip_space(in);
	return expr;
}

/*
   <addend> = <multicand>
            | <multicand> * <addend>
 */
PTR(Expr)parse_addend(std::istream &in) {
	skip_space(in);
	PTR(Expr)e = parse_multicand(in);
	int c = in.peek();
	if (c == '*') {
		consume(in, '*');
		PTR(Expr)rhs = parse_addend(in);
		skip_space(in);
		return NEW(MultExpr)(e, rhs);
	} else {
		skip_space(in);
		return e;
	}
}
/*
   <comparg> = <addend>
         	 | <addend> + <comparg>
 */
PTR(Expr)parse_comparg(std::istream &in) {
	skip_space(in);
	PTR(Expr)e = parse_addend(in);
	int c = in.peek();
	if (c == '+') {
		consume(in, '+');
		PTR(Expr)rhs = parse_comparg(in);
		skip_space(in);
		return NEW(AddExpr)(e, rhs);
	} else {
		skip_space(in);
		return e;
	}
}

/*
   <expr> = <comparg>
          | <comparg> == <expr>
 */
PTR(Expr)parse_expr(std::istream &in) {
	skip_space(in);
	PTR(Expr)e = parse_comparg(in);
	int c = in.peek();
	if (c == '=') {
		consume(in, '=');
		c = in.peek();
		if (c == '=') {
			consume(in, '=');
			PTR(Expr)rhs = parse_expr(in);
			skip_space(in);
			return NEW(EqExpr)(e, rhs);
		} else {
			throw std::runtime_error("'==' is required in EqExpr");
		}
	} else {
		skip_space(in);
		return e;
	}
}
