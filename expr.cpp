//
//  expr.cpp
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

#include "expr.h"
#include <utility>

/*---------------------------------------
 Expression class
 ---------------------------------------*/
std::string Expr::to_string() {
    std::stringstream st("");
    this->print(st);
    return st.str();
}

void Expr::pretty_print(std::ostream &ostream){
    std::streampos init = ostream.tellp();
    this->pretty_print_at(ostream, init, false);
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
    this->val_ = val;
}

bool Num::equals(Expr *e){
    Num *pNum = dynamic_cast<Num*>(e);
    if(pNum == nullptr){
        return false;
    }else{
        return this->val_ == pNum->val_;
    }
}

int Num::interp(){
    return this->val_;
}

bool Num::has_variable(){
    return false;
}

Expr* Num::subst(std::string string, Expr* e){
    return this;
}

void Num::print(std::ostream &ostream){
    ostream << std::to_string(this->val_);
}

void Num::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
    this->print(ostream);
}

precedence_t Num::get_prec(){
    return prec_none;
}




/*---------------------------------------
 Variable class
 ---------------------------------------*/

Var::Var(std::string varName){
    this->string_ = std::move(varName);
}

bool Var::equals(Expr *e){
    Var *pVar = dynamic_cast<Var*>(e);
    if(pVar == nullptr){
        return false;
    }else{
        return (this->string_ == pVar->string_);
    }
}

int Var::interp(){
    throw std::runtime_error("no value for variable");
}

bool Var::has_variable(){
    return true;
}

Expr* Var::subst(std::string string, Expr* e){
    if(this->string_ == string){ // TODO: what if the string is ""
        return e;
    }
    return this;
}

void Var::print(std::ostream &ostream){
    ostream << this->string_;
}

void Var::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
    this->print(ostream);
}

precedence_t Var::get_prec(){
    return prec_none;
}




/*---------------------------------------
 Add class
 ---------------------------------------*/

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs_ = lhs;
    this->rhs_ = rhs;
}

bool Add::equals(Expr *e){
    Add *pAdd = dynamic_cast<Add*>(e);
    if(pAdd == nullptr){
        return false;
    }else{
        return  (this->lhs_->equals(pAdd->lhs_))
                && (this->rhs_->equals(pAdd->rhs_));
    }
}

int Add::interp(){
    return this->lhs_->interp() + this->rhs_->interp();
}

bool Add::has_variable(){
    return  this->lhs_->has_variable()
            || this->rhs_->has_variable();
}

Expr* Add::subst(std::string string, Expr* e){
    return new Add(this->lhs_->subst(string, e),
                   this->rhs_->subst(string, e));
}

void Add::print(std::ostream &ostream){
    ostream << "(";
    this->lhs_->print(ostream);
    ostream << "+";
    this->rhs_->print(ostream);
    ostream << ")";
}

void Add::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
    if(this->lhs_->get_prec() == prec_add || this->lhs_->get_prec() == prec_let){
        ostream << "(";
        this->lhs_->pretty_print_at(ostream, lastReturnSeen, true);
        ostream << ")";
    }else{
        this->lhs_->pretty_print_at(ostream, lastReturnSeen, true);
    }
    ostream << " + ";
    this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
}

precedence_t Add::get_prec(){
    return prec_add;
}




/*---------------------------------------
 Multiplication class
 ---------------------------------------*/

Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs_ = lhs;
    this->rhs_ = rhs;
}

bool Mult::equals(Expr *e){
    Mult *pMult = dynamic_cast<Mult*>(e);
    if(pMult == nullptr){
        return false;
    }else{
        return  (this->lhs_->equals(pMult->lhs_))
                && (this->rhs_->equals(pMult->rhs_));
    }
}

int Mult::interp(){
    return this->lhs_->interp() * this->rhs_->interp();
}

bool Mult::has_variable(){
    return  this->lhs_->has_variable()
            || this->rhs_->has_variable();
}

Expr* Mult::subst(std::string string, Expr* e){
    return new Mult(this->lhs_->subst(string, e),
                    this->rhs_->subst(string, e));
}

void Mult::print(std::ostream &ostream){
    ostream << "(";
    this->lhs_->print(ostream);
    ostream << "*";
    this->rhs_->print(ostream);
    ostream << ")";
}


void Mult::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
    if(this->lhs_->get_prec() != prec_none){
        ostream << "(";
        this->lhs_->pretty_print_at(ostream, lastReturnSeen, false);
        ostream << ")";
    }else{
        this->lhs_->pretty_print_at(ostream, lastReturnSeen, false);
    }

    ostream << " * ";

    if(this->rhs_->get_prec() == prec_add || ((this->rhs_->get_prec() == prec_let) && lastLeftAndAdd)){
        ostream << "(";
        this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
        ostream << ")";
    }else{
        this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
    }
}

precedence_t Mult::get_prec(){
    return prec_mult;
}


/*---------------------------------------
 Let class
 ---------------------------------------*/

Let::Let(std::string lhs, Expr *rhs, Expr *body) {
    this->lhs_ = std::move(lhs);
    this->rhs_ = rhs;
    this->body_ = body;
}

bool Let::equals(Expr *e){
    Let *pLet = dynamic_cast<Let*>(e);
    if(pLet == nullptr){
        return false;
    }else{
        return  (this->lhs_ == pLet->lhs_)
                && (this->rhs_->equals(pLet->rhs_))
                && (this->body_->equals(pLet->body_));
    }
}

int Let::interp(){
    return  this->body_
            ->subst(lhs_, rhs_)
            ->interp();
}

bool Let::has_variable(){
    return  this->body_->subst(lhs_, rhs_)->has_variable(); // after substitution still have variable, then true
}

Expr* Let::subst(std::string string, Expr* e){
    if(string == this->lhs_){
        return new Let(this->lhs_,
                       this->rhs_->subst(string, e),
                       this->body_);
    }else{
        return new Let(this->lhs_,
                        this->rhs_->subst(string, e),
                        this->body_->subst(string, e));
    }
}

void Let::print(std::ostream &ostream){
    ostream << "(_let " << this->lhs_ << "=";
    this->rhs_->print(ostream);
    ostream << " _in ";
    this->body_->print(ostream);
    ostream << ")";
}

void Let::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) { // still need to deal with cases that doesn't have but need to have
    std::streampos oldLastReturn = lastReturnSeen;
    std::streampos currentStart = ostream.tellp();
    ostream << "_let " << this->lhs_ << " = ";
    this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
    ostream << "\n";
    lastReturnSeen = ostream.tellp(); // make sure it will be at least update to this position
    ostream << std::string(currentStart - oldLastReturn, ' ');
    ostream << "_in  ";
    this->body_->pretty_print_at(ostream, lastReturnSeen, false);
}

precedence_t Let::get_prec(){
    return prec_let;
}







