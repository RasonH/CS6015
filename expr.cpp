//
//  expr.cpp
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

#include "expr.h"

/*---------------------------------------
 Expression class
 ---------------------------------------*/
std::string Expr::to_string() {
    std::stringstream st("");
    this->print(st);
    return st.str();
}

std::string Expr::to_pretty_string() {
    std::stringstream st("");
    this->pretty_print(st);
    return st.str();
}



/*---------------------------------------
 Number class
 ---------------------------------------*/

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

void Num::print(std::ostream &ostream){
    ostream << std::to_string(this->val);
}

void Num::pretty_print(std::ostream &ostream) {
    Num::print(ostream);
}

precedence_t Num::pretty_print_at(){
    return prec_none;
}




/*---------------------------------------
 Variable class
 ---------------------------------------*/

Variable::Variable(std::string varName){
    this->name = std::move(varName);
}

bool Variable::equals(Expr *e){
    Variable *v = dynamic_cast<Variable*>(e);
    if(v == nullptr){
        return false;
    }else{
        return (this->name == v->name);
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

void Variable::print(std::ostream &ostream){
    ostream << this->name;
}

void Variable::pretty_print(std::ostream &ostream) {
    Variable::print(ostream);
}

precedence_t Variable::pretty_print_at(){
    return prec_none;
}




/*---------------------------------------
 Add class
 ---------------------------------------*/

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

void Add::print(std::ostream &ostream){
    ostream << "(";
    this->lhs->print(ostream);
    ostream << "+";
    this->rhs->print(ostream);
    ostream << ")";
}

void Add::pretty_print(std::ostream &ostream) {
    if(this->lhs->pretty_print_at() == prec_add){
        ostream << "(";
        this->lhs->pretty_print(ostream);
        ostream << ")";
    }else{
        this->lhs->pretty_print(ostream);
    }
    ostream << " + ";
    this->rhs->pretty_print(ostream);
}

precedence_t Add::pretty_print_at(){
    return prec_add;
}




/*---------------------------------------
 Multiplication class
 ---------------------------------------*/

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

void Mult::print(std::ostream &ostream){
    ostream << "(";
    this->lhs->print(ostream);
    ostream << "*";
    this->rhs->print(ostream);
    ostream << ")";
}

void Mult::pretty_print(std::ostream &ostream) {
    // if any of lhs or rhs is Add, then put parenthesis to it
    if(this->lhs->pretty_print_at() != prec_none){
        ostream << "(";
        this->lhs->pretty_print(ostream);
        ostream << ")";
    }else{
        this->lhs->pretty_print(ostream);
    }

    ostream << " * ";

    if(this->rhs->pretty_print_at() == prec_add){
        ostream << "(";
        this->rhs->pretty_print(ostream);
        ostream << ")";
    }else{
        this->rhs->pretty_print(ostream);
    }
}

precedence_t Mult::pretty_print_at(){
    return prec_mult;
}








