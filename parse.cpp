//
// Created by Rason Hung on 2/21/23.
//

#include <istream>
#include <sstream>
#include "parse.h"

//helper function consume
void consume(std::istream &in, int expect){
    int c = in.get();
    if (c != expect)
        throw std::runtime_error("consume mismatch");
}

//helper function check space
void skip_whitespace(std::istream &in){
    while (1){
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);
    }
}

//helper function for testing
Expr *parse_str(std::string s){
    bool exprParsed = false;
    std::stringstream in(s);
    Expr* e = parse_expr(in);
    skip_whitespace(in);
    if(isgraph(in.peek())){ // if there is still character at the end after parsing a whole expression
        throw std::runtime_error("invalid input");
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

    while (1){
        int c = in.peek();
        if (isdigit(c)) {
            if(numSeen == false){
                numSeen = true;
            }
            consume(in, c);
            n = n * 10 + (c - '0');
        }else
            break;
    }
    if (negative)
        n = -n;
    if (numSeen == false){
        throw std::runtime_error("invalid input");
    }
    return new Num(n);
}

// parse variable
Expr *parse_var(std::istream &in){
    std::string s;
    while(1){
        char c = in.peek();
        if (isalpha(c)){
            consume(in, c);
            s = s + c;
        }else
            break;
    }
//    if()
    return new Var(s);
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
    skip_whitespace(in);
    return keyword;
}

//parse _let
Expr *parse_let(std::istream &in){
    skip_whitespace(in);
    std::string lhs = parse_var(in) -> to_string();
    skip_whitespace(in);
    int c = in.peek();
    if (c == '='){
        consume(in, '=');
    }else{
        throw std::runtime_error("variable '=' is required");
    }
    skip_whitespace(in);
    Expr *rhs = parse_expr(in);
    skip_whitespace(in);
    if (parse_keyword(in) != "_in"){
        throw std::runtime_error("variable _in is required");
    }
    skip_whitespace(in);
    Expr *body = parse_expr(in);
    return new Let(lhs,rhs,body);
}

/* <expr> = <addend>
          | <addend> + <expr>
**/

Expr *parse_expr(std::istream &in){
    Expr *e;

    e = parse_addend(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '+'){
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new Add(e,rhs);
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
    skip_whitespace(in);

    int c = in.peek();
    if (c == '*'){
        consume(in, '*');
        Expr *rhs = parse_addend(in);
        return new Mult(e,rhs);
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
    skip_whitespace(in);

    int c = in.peek();
    // grammar <number>
    if ((c == '-') || isdigit(c)) {
        return parse_num(in);
    }
        //grammar ( <expr> )
    else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);// parse parenthesized
        skip_whitespace(in);
        c = in.get();
        if (c != ')')
            throw std::runtime_error("missing close parenthesis");
        return e;
    }
        //grammar <variable>
    else if (isalpha(c)) {
        return parse_var(in);
    }
        //grammar _let
    else if (c == '_') {
        std::string keyword = parse_keyword(in);
        if (keyword == "_let") {
            return parse_let(in);
        }
    }

    else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}
