//
//  expr.h
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//


#pragma include once
#include <cstdio>
#include <string>


//abstract class Expression
class Expr {
public:
    //equals is required to be implemented in the sub classes
    virtual bool equals(Expr *e) = 0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
};

class Add : public Expr {
public:
    Expr *lhs; Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
};

class Variable : public Expr {
public:
    std::string name;
    Variable(std::string varName);
    bool equals(Expr *e);
};
