//
// Created by Rason Hung on 2/21/23.
//

#pragma include once
#include <cstdio>
#include <istream>
class Expr;

void consume(std::istream &in, int nextChar);
void skip_space(std::istream &in);
Expr *parse_str(const std::string& s);
Expr *parse_str(std::istream &in);

Expr *parse_num(std::istream &in);
Expr *parse_var(std::istream &in);
std::string parse_keyword(std::istream &in);
Expr *parse_let(std::istream &in);

Expr *parse_expr(std::istream &in);
Expr *parse_addend(std::istream &in);
Expr *parse_multicand(std::istream &in);