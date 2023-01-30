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
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string string, Expr* e)=0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr* e);
};

class Add : public Expr {
public:
    Expr *lhs; Expr *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr* e);
};

class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr* e);
};

class Variable : public Expr {
public:
    std::string name;
    Variable(std::string varName);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(std::string string, Expr* e);
};
