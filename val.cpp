//
// Created by Rason Hung on 3/13/23.
//

#include "val.h"
#include "expr.h"

NumVal::NumVal(int val) {
    this->val = val;
}

bool NumVal::equals(Val *val) {
    NumVal *pNumVal = dynamic_cast<NumVal *>(val);
    if (pNumVal == nullptr)
        return false;
    return this->val == pNumVal->val;
}

Val *NumVal::add_to(Val *other_val) {
    NumVal *other_num = dynamic_cast<NumVal*>(other_val);
    if (other_num == nullptr) throw std::runtime_error("addition of non-number");
    return new NumVal(this->val + other_num->val);
}

Val *NumVal::mult_with(Val *other_val) {
    NumVal *other_num = dynamic_cast<NumVal *>(other_val);
    if (other_num == nullptr)
        throw std::runtime_error("multiplication of non-number");
    return new NumVal (this->val * other_num->val);
}

Expr *NumVal::to_expr() {
    return new NumExpr(this->val);
}

std::string NumVal::to_string() {
    return std::to_string(this->val);
}


//subclass boolValue
BoolVal::BoolVal(bool val) {
    this->val = val;
}

bool BoolVal::equals(Val *val) {
    BoolVal *pBoolVal = dynamic_cast<BoolVal *>(val);
    if (pBoolVal == nullptr) {
        return false;
    }
    return this->val == pBoolVal->val;
}

Expr *BoolVal::to_expr() {
    return nullptr; // TODO: need to modify to return BoolExpr after creating the class
}

Val *BoolVal::add_to(Val *val) {
    throw std::runtime_error("Cannot add BooVal type.");
}

Val *BoolVal::mult_with(Val *val) {
    throw std::runtime_error("Cannot multiply BooVal type.");
}

std::string BoolVal::to_string() {
    if (this->val == true) {
        return "_true";
    }
    return "_false";
}
