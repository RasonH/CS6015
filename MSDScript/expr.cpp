//
//  expr.cpp
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

#include <stdexcept>
#include <utility>
#include "expr.h"


/*
 Number class
 */

Num::Num(int val){
    this->val = val;
}

bool Num::equals(Expr *e){
    Num *n = dynamic_cast<Num*>(e);
    if(n == nullptr){
        return false;
    }else{
        return this->val == n->val;
    }
}

int Num::interp(){
    return this->val;
}

bool Num::has_variable(){
    return false;
}

Expr* Num::subst(std::string string, Expr* e){
    return this;
}


/*
 Add class
 */

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr *e){
    Add *a = dynamic_cast<Add*>(e);
    if(a == nullptr){
        return false;
    }else{
        return (this->lhs->equals(a->lhs) && this->rhs->equals(a->rhs));
    }
}

int Add::interp(){
    return this->lhs->interp() + this->rhs->interp();
}

bool Add::has_variable(){
    return this->lhs->has_variable() || this->rhs->has_variable();
}

Expr* Add::subst(std::string string, Expr* e){
    return new Add(this->lhs->subst(string, e),
                    this->rhs->subst(string, e));
}


/*
 Multiplication class
 */

Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *e){
    Mult *m = dynamic_cast<Mult*>(e);
    if(m == nullptr){
        return false;
    }else{
        return (this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs));
    }
}

int Mult::interp(){
    return this->lhs->interp() * this->rhs->interp();
}

bool Mult::has_variable(){
    return this->lhs->has_variable() || this->rhs->has_variable();
}

Expr* Mult::subst(std::string string, Expr* e){
    return new Mult(this->lhs->subst(string, e),
                    this->rhs->subst(string, e));
}


/*
 Variable class
 */

Variable::Variable(std::string varName){
    this->name = std::move(varName);
}

bool Variable::equals(Expr *e){
    Variable *m = dynamic_cast<Variable*>(e);
    if(m == nullptr){
        return false;
    }else{
        return (this->name == m->name);
    }
}

int Variable::interp(){
    throw std::runtime_error("no value for variable");
}

bool Variable::has_variable(){
    return true;
}

Expr* Variable::subst(std::string string, Expr* e){
    if(this->name == string){ // TODO: what if the string is ""
        return e;
    }
    return this;
}



