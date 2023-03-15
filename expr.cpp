//
//  expr.cpp
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

#pragma include once
#include "val.h"
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

NumExpr::NumExpr(int val){
    this->val_ = val;
}

bool NumExpr::equals(Expr *e){
    NumExpr *pNum = dynamic_cast<NumExpr*>(e);
    if(pNum == nullptr){
        return false;
    }else{
        return this->val_ == pNum->val_;
    }
}

Val * NumExpr::interp(){
    return new NumVal(this->val_);
}

bool NumExpr::has_variable(){
    return false;
}

Expr* NumExpr::subst(std::string string, Expr* e){
    return this;
}

void NumExpr::print(std::ostream &ostream){
    ostream << std::to_string(this->val_);
}

void NumExpr::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
    this->print(ostream);
}

precedence_t NumExpr::get_prec(){
    return prec_none;
}




/*---------------------------------------
 Variable class
 ---------------------------------------*/

VarExpr::VarExpr(std::string varName){
    this->string_ = std::move(varName);
}

bool VarExpr::equals(Expr *e){
    VarExpr *pVar = dynamic_cast<VarExpr*>(e);
    if(pVar == nullptr){
        return false;
    }else{
        return (this->string_ == pVar->string_);
    }
}

Val * VarExpr::interp(){
    throw std::runtime_error("no value for variable");
//    throw std::runtime_error("invalid input");
//    throw std::runtime_error("");
}

bool VarExpr::has_variable(){
    return true;
}

Expr* VarExpr::subst(std::string string, Expr* e){
    if(this->string_ == string){ // TODO: what if the string is ""
        return e;
    }
    return this;
}

void VarExpr::print(std::ostream &ostream){
    ostream << this->string_;
}

void VarExpr::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
    this->print(ostream);
}

precedence_t VarExpr::get_prec(){
    return prec_none;
}




/*---------------------------------------
 Add class
 ---------------------------------------*/

AddExpr::AddExpr(Expr *lhs, Expr *rhs) {
    this->lhs_ = lhs;
    this->rhs_ = rhs;
}

bool AddExpr::equals(Expr *e){
    AddExpr *pAdd = dynamic_cast<AddExpr*>(e);
    if(pAdd == nullptr){
        return false;
    }else{
        return  (this->lhs_->equals(pAdd->lhs_))
                && (this->rhs_->equals(pAdd->rhs_));
    }
}

Val * AddExpr::interp(){
    return (this->lhs_->interp())->add_to(this->rhs_->interp());
}

bool AddExpr::has_variable(){
    return  this->lhs_->has_variable()
            || this->rhs_->has_variable();
}

Expr* AddExpr::subst(std::string string, Expr* e){
    return new AddExpr(this->lhs_->subst(string, e),
                       this->rhs_->subst(string, e));
}

void AddExpr::print(std::ostream &ostream){
    ostream << "(";
    this->lhs_->print(ostream);
    ostream << "+";
    this->rhs_->print(ostream);
    ostream << ")";
}

void AddExpr::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
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

precedence_t AddExpr::get_prec(){
    return prec_add;
}




/*---------------------------------------
 Multiplication class
 ---------------------------------------*/

MultExpr::MultExpr(Expr *lhs, Expr *rhs) {
    this->lhs_ = lhs;
    this->rhs_ = rhs;
}

bool MultExpr::equals(Expr *e){
    MultExpr *pMult = dynamic_cast<MultExpr*>(e);
    if(pMult == nullptr){
        return false;
    }else{
        return  (this->lhs_->equals(pMult->lhs_))
                && (this->rhs_->equals(pMult->rhs_));
    }
}

Val * MultExpr::interp(){
    return this->lhs_->interp()->mult_with(this->rhs_->interp()) ;
}

bool MultExpr::has_variable(){
    return  this->lhs_->has_variable()
            || this->rhs_->has_variable();
}

Expr* MultExpr::subst(std::string string, Expr* e){
    return new MultExpr(this->lhs_->subst(string, e),
                        this->rhs_->subst(string, e));
}

void MultExpr::print(std::ostream &ostream){
    ostream << "(";
    this->lhs_->print(ostream);
    ostream << "*";
    this->rhs_->print(ostream);
    ostream << ")";
}


void MultExpr::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) {
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

precedence_t MultExpr::get_prec(){
    return prec_mult;
}


/*---------------------------------------
 Let class
 ---------------------------------------*/

LetExpr::LetExpr(std::string lhs, Expr *rhs, Expr *body) {
    this->lhs_ = std::move(lhs);
    this->rhs_ = rhs;
    this->body_ = body;
}

bool LetExpr::equals(Expr *e){
    LetExpr *pLet = dynamic_cast<LetExpr*>(e);
    if(pLet == nullptr){
        return false;
    }else{
        return  (this->lhs_ == pLet->lhs_)
                && (this->rhs_->equals(pLet->rhs_))
                && (this->body_->equals(pLet->body_));
    }
}

Val * LetExpr::interp(){
    return  this->body_
            ->subst(lhs_, rhs_->interp()->to_expr())
            ->interp();
}

bool LetExpr::has_variable(){
    return  this->body_->subst(lhs_, rhs_)->has_variable(); // after substitution still have variable, then true
}

Expr* LetExpr::subst(std::string string, Expr* e){
    if(string == this->lhs_){
        return new LetExpr(this->lhs_,
                           this->rhs_->subst(string, e),
                           this->body_);
    }else{
        return new LetExpr(this->lhs_,
                           this->rhs_->subst(string, e),
                           this->body_->subst(string, e));
    }
}

void LetExpr::print(std::ostream &ostream){
    ostream << "(_let " << this->lhs_ << "=";
    this->rhs_->print(ostream);
    ostream << " _in ";
    this->body_->print(ostream);
    ostream << ")";
}

void LetExpr::pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen, bool lastLeftAndAdd) { // still need to deal with cases that doesn't have but need to have
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

precedence_t LetExpr::get_prec(){
    return prec_let;
}







