//
// Created by Rason Hung on 3/13/23.
//

#include "val.h"
#include "expr.h"

/*--------------------------------------------------------------------------------------------
	ooooo      ooo                               oooooo     oooo           oooo
	`888b.     `8'                                `888.     .8'            `888
	 8 `88b.    8  oooo  oooo  ooo. .oo.  .oo.     `888.   .8'    .oooo.    888
	 8   `88b.  8  `888  `888  `888P"Y88bP"Y88b     `888. .8'    `P  )88b   888
	 8     `88b.8   888   888   888   888   888      `888.8'      .oP"888   888
	 8       `888   888   888   888   888   888       `888'      d8(  888   888
	o8o        `8   `V88V"V8P' o888o o888o o888o       `8'       `Y888""8o o888o
--------------------------------------------------------------------------------------------*/

NumVal::NumVal(int rep) { this->rep_ = rep; }

bool NumVal::equals(PTR(Val)val) {
	PTR(NumVal)pNumVal = CAST(NumVal)(val);
	if (pNumVal == nullptr) {
		return false;
	} else {
		return this->rep_ == pNumVal->rep_;
	}
}

PTR(Val)NumVal::add_to(PTR(Val)otherVal) {
	PTR(NumVal)otherNum = CAST(NumVal)(otherVal);
	if (otherNum == nullptr) {
		throw std::runtime_error("add of non-number");
	} else {
		return NEW(NumVal)((unsigned)this->rep_ + (unsigned)otherNum->rep_);
	}
}

PTR(Val)NumVal::mult_with(PTR(Val)otherVal) {
	PTR(NumVal)otherNum = CAST(NumVal)(otherVal);
	if (otherNum == nullptr) {
		throw std::runtime_error("mult of non-number");
	} else {
		return NEW(NumVal)((unsigned)this->rep_ * (unsigned)otherNum->rep_);
	}
}

//PTR(Expr)NumVal::to_expr() { return NEW(NumExpr)(this->rep_); }

std::string NumVal::to_string() { return std::to_string(this->rep_); }

PTR(Val)NumVal::call(PTR(Val)actualArg) {
	throw std::runtime_error("Can not call on NumVal");
}

/*--------------------------------------------------------------------------------------------
	oooooooooo.                      oooo  oooooo     oooo           oooo
	`888'   `Y8b                     `888   `888.     .8'            `888
	888     888  .ooooo.   .ooooo.   888    `888.   .8'    .oooo.    888
	888oooo888' d88' `88b d88' `88b  888     `888. .8'    `P  )88b   888
	888    `88b 888   888 888   888  888      `888.8'      .oP"888   888
	888    .88P 888   888 888   888  888       `888'      d8(  888   888
	o888bood8P'  `Y8bod8P' `Y8bod8P' o888o       `8'       `Y888""8o o888o
--------------------------------------------------------------------------------------------*/

BoolVal::BoolVal(bool rep) { this->rep_ = rep; }

bool BoolVal::equals(PTR(Val)val) {
	PTR(BoolVal)pBoolVal = CAST(BoolVal)(val);
	if (pBoolVal == nullptr) {
		return false;
	} else {
		return this->rep_ == pBoolVal->rep_;
	}
}

//PTR(Expr)BoolVal::to_expr() { return NEW(BoolExpr)(this->rep_); }

PTR(Val)BoolVal::add_to(PTR(Val)otherVal) {
	throw std::runtime_error("add of non-number");
}

PTR(Val)BoolVal::mult_with(PTR(Val)otherVal) {
	throw std::runtime_error("mult of non-number");
}

std::string BoolVal::to_string() {
	if (this->rep_ == true) {
		return "_true";
	} else {
		return "_false";
	}
}

PTR(Val)BoolVal::call(PTR(Val)actualArg) {
	throw std::runtime_error("Can not call on BoolVal");
}

/*--------------------------------------------------------------------------------------------
	oooooooooooo                         oooooo     oooo           oooo
	`888'     `8                          `888.     .8'            `888
	888         oooo  oooo  ooo. .oo.     `888.   .8'    .oooo.    888
	888oooo8    `888  `888  `888P"Y88b     `888. .8'    `P  )88b   888
	888    "     888   888   888   888      `888.8'      .oP"888   888
	888          888   888   888   888       `888'      d8(  888   888
	o888o         `V88V"V8P' o888o o888o       `8'       `Y888""8o o888o
--------------------------------------------------------------------------------------------*/

FunVal::FunVal(std::string formalArg, PTR(Expr)body, PTR(Env)env) {
	formal_arg_ = formalArg;
	body_ = body;
	env_ = env;
}

bool FunVal::equals(PTR(Val)val) {
	PTR(FunVal)pFunVal = CAST(FunVal)(val);
	if (pFunVal == nullptr) {
		return false;
	} else {
		return (this->formal_arg_ == pFunVal->formal_arg_) &&
			(this->body_->equals(pFunVal->body_));
	}
}

//PTR(Expr)FunVal::to_expr() { return NEW(FunExpr)(this->formal_arg_, this->body_); }

PTR(Val)FunVal::add_to(PTR(Val)otherVal) {
	throw std::runtime_error("add of non-number");
}

PTR(Val)FunVal::mult_with(PTR(Val)otherVal) {
	throw std::runtime_error("mult of non-number");
}

std::string FunVal::to_string() {
	return ("_fun (" + this->formal_arg_ + ") " + this->body_->to_string());
}

PTR(Val)FunVal::call(PTR(Val)actualArg) {
	return this->body_->interp(NEW(ExtendedEnv)(this->formal_arg_, actualArg, this->env_));
//	return (NEW(LetExpr)(this->formal_arg_, actualArg->to_expr(), this->body_))->interp();
}