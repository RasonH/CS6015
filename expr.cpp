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

std::string Expr::to_pretty_string() {
    std::stringstream st("");
    std::streampos init = st.tellp();
    this->pretty_print(st,init);
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

void Num::pretty_print(std::ostream &ostream, std::streampos &lastReturnSeen) {
    Num::print(ostream);
}

precedence_t Num::get_prec(){
    return prec_none;
}




/*---------------------------------------
 Variable class
 ---------------------------------------*/

Variable::Variable(std::string varName){
    this->string_ = std::move(varName);
}

bool Variable::equals(Expr *e){
    Variable *pVar = dynamic_cast<Variable*>(e);
    if(pVar == nullptr){
        return false;
    }else{
        return (this->string_ == pVar->string_);
    }
}

int Variable::interp(){
    throw std::runtime_error("no value for variable");
}

bool Variable::has_variable(){
    return true;
}

Expr* Variable::subst(std::string string, Expr* e){
    if(this->string_ == string){ // TODO: what if the string is ""
        return e;
    }
    return this;
}

void Variable::print(std::ostream &ostream){
    ostream << this->string_;
}

void Variable::pretty_print(std::ostream &ostream, std::streampos &lastReturnSeen) {
    Variable::print(ostream);
}

precedence_t Variable::get_prec(){
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

void Add::pretty_print(std::ostream &ostream, std::streampos &lastReturnSeen) {
    if(this->lhs_->get_prec() == prec_add || this->lhs_->get_prec() == prec_let){
        ostream << "(";
        this->lhs_->pretty_print(ostream, lastReturnSeen);
        ostream << ")";
    }else{
        this->lhs_->pretty_print(ostream, lastReturnSeen);
    }
    ostream << " + ";
    this->rhs_->pretty_print(ostream, lastReturnSeen);
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


void Mult::pretty_print(std::ostream &ostream, std::streampos &lastReturnSeen) {
    if(this->lhs_->get_prec() != prec_none){
        ostream << "(";
        this->lhs_->pretty_print(ostream, lastReturnSeen);
        ostream << ")";
    }else{
        this->lhs_->pretty_print(ostream, lastReturnSeen);
    }

    ostream << " * ";

    if(this->rhs_->get_prec() == prec_add){
        ostream << "(";
        this->rhs_->pretty_print(ostream, lastReturnSeen);
        ostream << ")";
    }else{
        this->rhs_->pretty_print(ostream, lastReturnSeen);
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
    return  this->rhs_->has_variable()
            || this->body_->has_variable();
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

void Let::pretty_print(std::ostream &ostream, std::streampos &lastReturnSeen) {
    std::streampos oldLastReturn = lastReturnSeen;
    std::streampos currentStart = ostream.tellp();
    ostream << "_let " << this->lhs_ << " = ";
    this->rhs_->pretty_print(ostream, lastReturnSeen);
    ostream << "\n";
    lastReturnSeen = ostream.tellp(); // make sure it will be at least update to this position
    for(u_long i = 0; i < (u_long)(currentStart - oldLastReturn); i++){
        ostream << " ";
    }
    ostream << "_in ";
    this->body_->pretty_print(ostream, lastReturnSeen);
}

precedence_t Let::get_prec(){
    return prec_let;
}






