//
// Created by Rason Hung on 3/13/23.
//

#pragma include once
#include <string>
class Expr;

class Val {
public:
    virtual bool equals(Val *val) = 0;
    virtual Expr *to_expr() = 0;
    virtual std::string to_string() = 0;
    virtual Val *add_to(Val *val) = 0;
    virtual Val *mult_with(Val *val) = 0;
};

class NumVal : public Val{
public:
    int val;
    NumVal (int val);

    bool equals(Val *val) override;
    Expr *to_expr() override;
    std::string to_string() override;
    Val *add_to(Val *val) override;
    Val *mult_with(Val *other_val) override;
};

class BoolVal : public Val{
public:
    bool val;
    BoolVal (bool val);

    bool equals(Val *val) override;
    Expr *to_expr() override;
    std::string to_string() override;
    Val *add_to(Val *val) override;
    Val *mult_with(Val *val) override;
};