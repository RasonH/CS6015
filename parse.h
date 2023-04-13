//
// Created by Rason Hung on 2/21/23.
//

#pragma include once

#include <cstdio>
#include <istream>
#include "pointer.h"

class Expr;

void consume(std::istream &in, int nextChar);

void skip_space(std::istream &in);

PTR(Expr) parse_str(const std::string &s);

PTR(Expr) parse_str(std::istream &in);

PTR(Expr) parse_num(std::istream &in);

PTR(Expr) parse_var(std::istream &in);

std::string parse_keyword(std::istream &in);

PTR(Expr) parse_let(std::istream &in);

PTR(Expr) parse_if(std::istream &in);

PTR(Expr) parse_expr(std::istream &in);

PTR(Expr) parse_comparg(std::istream &in);

PTR(Expr) parse_addend(std::istream &in);

PTR(Expr) parse_multicand(std::istream &in);

PTR(Expr) parse_inner(std::istream &in);

PTR(Expr) parse_fun(std::istream &in);
