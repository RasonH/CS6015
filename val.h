//
// Created by Rason Hung on 3/13/23.
//

#pragma include once
#include <string>
#include "pointer.h"
class Expr;

CLASS (Val) {
 public:
	virtual bool equals(PTR(Val)rep) = 0;

	virtual PTR(Expr)to_expr() = 0;

	virtual std::string to_string() = 0;

	virtual PTR(Val)add_to(PTR(Val)rep) = 0;

	virtual PTR(Val)mult_with(PTR(Val)rep) = 0;

	virtual PTR(Val)call(PTR(Val)actualArg) = 0;
};

class NumVal : public Val {
 public:
	int rep_;

	NumVal(int rep);

	bool equals(PTR(Val)val) override;

	PTR(Expr)to_expr() override;

	std::string to_string() override;

	PTR(Val)add_to(PTR(Val)otherVal) override;

	PTR(Val)mult_with(PTR(Val)otherVal) override;

	PTR(Val)call(PTR(Val)actualArg) override;
};

class BoolVal : public Val {
 public:
	bool rep_;

	BoolVal(bool rep);

	bool equals(PTR(Val)val) override;

	PTR(Expr)to_expr() override;

	std::string to_string() override;

	PTR(Val)add_to(PTR(Val)otherVal) override;

	PTR(Val)mult_with(PTR(Val)otherVal) override;

	PTR(Val)call(PTR(Val)actualArg) override;
};

class FunVal : public Val {
 public:
	std::string formal_arg_;
	PTR(Expr)body_;

	FunVal(std::string formalArg, PTR(Expr)body);

	bool equals(PTR(Val)val) override;

	PTR(Expr)to_expr() override;

	std::string to_string() override;

	PTR(Val)add_to(PTR(Val)otherVal) override;

	PTR(Val)mult_with(PTR(Val)otherVal) override;

	PTR(Val)call(PTR(Val)actualArg) override;
};