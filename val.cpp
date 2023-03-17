//
// Created by Rason Hung on 3/13/23.
//

#include "val.h"
#include "expr.h"

NumVal::NumVal(int rep) { this->rep_ = rep; }

bool NumVal::equals(Val *val) {
    NumVal *pNumVal = dynamic_cast<NumVal *>(val);
    if (pNumVal == nullptr) {
        return false;
    } else {
        return this->rep_ == pNumVal->rep_;
    }
}

Val *NumVal::add_to(Val *otherVal) {
    NumVal *otherNum = dynamic_cast<NumVal *>(otherVal);
    if (otherNum == nullptr) {
        throw std::runtime_error("addition of non-number");
    } else {
        return new NumVal(this->rep_ + otherNum->rep_);
    }
}

Val *NumVal::mult_with(Val *otherVal) {
    NumVal *otherNum = dynamic_cast<NumVal *>(otherVal);
    if (otherNum == nullptr) {
        throw std::runtime_error("multiplication of non-number");
    } else {
        return new NumVal(this->rep_ * otherNum->rep_);
    }
}

Expr *NumVal::to_expr() { return new NumExpr(this->rep_); }

std::string NumVal::to_string() { return std::to_string(this->rep_); }

// subclass boolValue
BoolVal::BoolVal(bool rep) { this->rep_ = rep; }

bool BoolVal::equals(Val *val) {
    BoolVal *pBoolVal = dynamic_cast<BoolVal *>(val);
    if (pBoolVal == nullptr) {
        return false;
    } else {
        return this->rep_ == pBoolVal->rep_;
    }
}

Expr *BoolVal::to_expr() { return new BoolExpr(this->rep_); }

Val *BoolVal::add_to(Val *otherVal) {
    throw std::runtime_error("Cannot add BooVal type.");
}

Val *BoolVal::mult_with(Val *otherVal) {
    throw std::runtime_error("Cannot multiply BooVal type.");
}

std::string BoolVal::to_string() {
    if (this->rep_ == true) {
        return "_true";
    } else {
        return "_false";
    }
}
