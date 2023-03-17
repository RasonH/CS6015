//
// Created by Rason Hung on 3/13/23.
//

#pragma include once

#include <string>

class Expr;

class Val {
public:
    virtual bool equals(Val *rep) = 0;

    virtual Expr *to_expr() = 0;

    virtual std::string to_string() = 0;

    virtual Val *add_to(Val *rep) = 0;

    virtual Val *mult_with(Val *rep) = 0;
};

class NumVal : public Val {
public:
    int rep_;

    NumVal(int rep);

    bool equals(Val *val) override;

    Expr *to_expr() override;

    std::string to_string() override;

    Val *add_to(Val *otherVal) override;

    Val *mult_with(Val *otherVal) override;
};

class BoolVal : public Val {
public:
    bool rep_;

    BoolVal(bool rep);

    bool equals(Val *val) override;

    Expr *to_expr() override;

    std::string to_string() override;

    Val *add_to(Val *otherVal) override;

    Val *mult_with(Val *otherVal) override;
};