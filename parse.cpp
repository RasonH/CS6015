//
// Created by Rason Hung on 2/21/23.
//

#pragma include once
#include "parse.h"
#include "expr.h"

//helper function consume
void consume(std::istream &in, int nextChar){
    int c = in.get();
    if (c != nextChar)
        throw std::runtime_error("consume mismatch");
}

//helper function check space
void skip_space(std::istream &in){
    while (true){
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);
    }
}

//helper function for testing
Expr *parse_str(const std::string& s){
    std::stringstream in(s);
    Expr* e = parse_expr(in);
    skip_space(in);
    if(!in.eof()){ // if there is still character at the end after parsing a whole expression
        throw std::runtime_error("invalid input");
//        throw std::runtime_error("");
    }else{
        return e;
    }
}

Expr *parse_str(std::istream &in){
    Expr* e = parse_expr(in);
    skip_space(in);
    if(!in.eof()){ // if there is still character at the end after parsing a whole expression
        throw std::runtime_error("invalid input");
//        throw std::runtime_error("");
    }else{
        return e;
    }
}


//parse number
Expr *parse_num(std::istream &in){
    int n = 0;
    bool negative = false;
    bool numSeen = false;

    if (in.peek() == '-'){
        negative = true;
        consume(in, '-');
    }

    while (true){
        int c = in.peek();
        if (isdigit(c)) {
            if(!numSeen){
                numSeen = true;
            }
            consume(in, c);
            n = n * 10 + (c - '0');
        }else
            break;
    }
    if (negative)
        n = -n;
    if (!numSeen){
        throw std::runtime_error("invalid input");
//        throw std::runtime_error("");
    }
    return new NumExpr(n);
}

// parse variable
Expr *parse_var(std::istream &in){
    std::string s;
    while(true){
        char c = in.peek();
        if (isalpha(c)){
            consume(in, c);
            s = s + c;
        }else {
            break;
        }
    }
    return new VarExpr(s);
}

//parse keyword
std::string parse_keyword(std::istream &in){
    int c = in.peek();
    std::string keyword = "_";
    if(c == '_'){
        consume(in,c);
        c = in.peek();
        while(isalpha(c)){
            keyword += c;
            consume (in, c);
            c = in.peek();
        }
    }
    skip_space(in);
    return keyword;
}

//parse _let
Expr *parse_let(std::istream &in){
    skip_space(in);
    std::string lhs = parse_var(in) -> to_string();
    skip_space(in);
    int c = in.peek();
    if (c == '='){
        consume(in, '=');
    }else{
        throw std::runtime_error("variable '=' is required");
    }
    skip_space(in);
    Expr *rhs = parse_expr(in);
    skip_space(in);
    if (parse_keyword(in) != "_in"){
        throw std::runtime_error("variable _in is required");
    }
    skip_space(in);
    Expr *body = parse_expr(in);
    return new LetExpr(lhs, rhs, body);
}

/* <expr> = <addend>
          | <addend> + <expr>
**/

Expr *parse_expr(std::istream &in){
    Expr *e;

    e = parse_addend(in);
    skip_space(in);

    int c = in.peek();
    if (c == '+'){
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new AddExpr(e, rhs);
    }else
        return e;
}

/*
 <addend>    = <multicand>
             | <multicand> * <addend>
 **/
Expr *parse_addend(std::istream &in){
    Expr *e;

    e = parse_multicand(in);
    skip_space(in);

    int c = in.peek();
    if (c == '*'){
        consume(in, '*');
        Expr *rhs = parse_addend(in);
        return new MultExpr(e, rhs);
    }else
        return e;
}

/*
<multicand> = <number>
            | ( <expr> )
            | <variable>
            | _let <variable> = <expr> _in <expr>
 **/

Expr *parse_multicand(std::istream &in) {
    skip_space(in);

    int c = in.peek();
    // <number>
    if ((c == '-') || isdigit(c)) {
        return parse_num(in);
    }
    // ( <expr> )
    else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);// parse parenthesized
        skip_space(in);
        c = in.get();
        if (c != ')') {
            throw std::runtime_error("invalid input"); // missing the closing parenthesis
//            throw std::runtime_error(""); // missing the closing parenthesis
        }
        return e;
    }
    // <variable>
    else if (isalpha(c)) {
        return parse_var(in);
    }
    // _let
    else if (c == '_') {
        std::string keyword = parse_keyword(in);
        if (keyword == "_let") {
            return parse_let(in);
        }else{
            throw std::runtime_error("invalid input"); // unknown keyword
//            throw std::runtime_error(""); // unknown keyword
        }
    }
    else {
        consume(in, c);
        throw std::runtime_error("invalid input"); // still have things remained other than above possibilities
//        throw std::runtime_error(""); // still have things remained other than above possibilities
    }
}
