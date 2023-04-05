//
//  expr.cpp
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

#pragma include once

#include "expr.h"
#include "val.h"
#include <utility>

/*--------------------------------------------------------------------------------------------
	oooooooooooo
	`888'     `8
	 888         oooo    ooo oo.ooooo.  oooo d8b
	 888oooo8     `88b..8P'   888' `88b `888""8P
	 888    "       Y888'     888   888  888
	 888       o  .o8"'88b    888   888  888
	o888ooooood8 o88'   888o  888bod8P' d888b
							  888
							 o888o
--------------------------------------------------------------------------------------------*/

std::string Expr::to_string() {
	std::stringstream st("");
	this->print(st);
	return st.str();
}

void Expr::pretty_print(std::ostream &ostream) {
	std::streampos init = ostream.tellp();
	this->pretty_print_at(ostream, init, false);
}

std::string Expr::to_pretty_string() {
	std::stringstream st("");
	this->pretty_print(st);
	return st.str();
}

/*--------------------------------------------------------------------------------------------
	ooooo      ooo                               oooooooooooo
	`888b.     `8'                               `888'     `8
	 8 `88b.    8  oooo  oooo  ooo. .oo.  .oo.    888         oooo    ooo oo.ooooo.  oooo d8b
	 8   `88b.  8  `888  `888  `888P"Y88bP"Y88b   888oooo8     `88b..8P'   888' `88b `888""8P
	 8     `88b.8   888   888   888   888   888   888    "       Y888'     888   888  888
	 8       `888   888   888   888   888   888   888       o  .o8"'88b    888   888  888
	o8o        `8   `V88V"V8P' o888o o888o o888o o888ooooood8 o88'   888o  888bod8P' d888b
																		   888
																		  o888o
--------------------------------------------------------------------------------------------*/

NumExpr::NumExpr(int val) { this->val_ = val; }

bool NumExpr::equals(PTR(Expr)e) {
	PTR(NumExpr)pNum = CAST(NumExpr)(e);
	if (pNum == nullptr) {
		return false;
	} else {
		return this->val_ == pNum->val_;
	}
}

PTR(Val)NumExpr::interp() { return new NumVal(this->val_); }

PTR(Expr)NumExpr::subst(std::string string, PTR(Expr)e) { return this; }

void NumExpr::print(std::ostream &ostream) {
	ostream << std::to_string(this->val_);
}

void NumExpr::pretty_print_at(std::ostream &ostream,
							  std::streampos &lastReturnSeen,
							  bool lastLeftAndAdd) {
	this->print(ostream);
}

precedence_t NumExpr::get_prec() { return prec_none; }

/*--------------------------------------------------------------------------------------------
	oooooo     oooo                    oooooooooooo
	 `888.     .8'                     `888'     `8
	  `888.   .8'    .oooo.   oooo d8b  888         oooo    ooo oo.ooooo.  oooo d8b
	   `888. .8'    `P  )88b  `888""8P  888oooo8     `88b..8P'   888' `88b `888""8P
		`888.8'      .oP"888   888      888    "       Y888'     888   888  888
		 `888'      d8(  888   888      888       o  .o8"'88b    888   888  888
		  `8'       `Y888""8o d888b    o888ooooood8 o88'   888o  888bod8P' d888b
																 888
																o888o
--------------------------------------------------------------------------------------------*/

VarExpr::VarExpr(std::string varName) { this->string_ = std::move(varName); }

bool VarExpr::equals(PTR(Expr)e) {
	PTR(VarExpr)pVar = CAST(VarExpr)(e);
	if (pVar == nullptr) {
		return false;
	} else {
		return (this->string_ == pVar->string_);
	}
}

PTR(Val)VarExpr::interp() {
	throw std::runtime_error("no value for variable");
	//    throw std::runtime_error("invalid input");
	//    throw std::runtime_error("");
}

PTR(Expr)VarExpr::subst(std::string string, PTR(Expr)e) {
	if (this->string_ == string) { // TODO: what if the string is ""
		return e;
	}
	return this;
}

void VarExpr::print(std::ostream &ostream) { ostream << this->string_; }

void VarExpr::pretty_print_at(std::ostream &ostream,
							  std::streampos &lastReturnSeen,
							  bool lastLeftAndAdd) {
	this->print(ostream);
}

precedence_t VarExpr::get_prec() { return prec_none; }

/*--------------------------------------------------------------------------------------------
		  .o.             .o8        .o8  oooooooooooo
		 .888.           "888       "888  `888'     `8
		.8"888.      .oooo888   .oooo888   888         oooo    ooo oo.ooooo.  oooo d8b
	   .8' `888.    d88' `888  d88' `888   888oooo8     `88b..8P'   888' `88b `888""8P
	  .88ooo8888.   888   888  888   888   888    "       Y888'     888   888  888
	 .8'     `888.  888   888  888   888   888       o  .o8"'88b    888   888  888
	o88o     o8888o `Y8bod88P" `Y8bod88P" o888ooooood8 o88'   888o  888bod8P' d888b
																	888
																   o888o
--------------------------------------------------------------------------------------------*/

AddExpr::AddExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
	this->lhs_ = lhs;
	this->rhs_ = rhs;
}

bool AddExpr::equals(PTR(Expr)e) {
	PTR(AddExpr)pAdd = CAST(AddExpr)(e);
	if (pAdd == nullptr) {
		return false;
	} else {
		return (this->lhs_->equals(pAdd->lhs_)) && (this->rhs_->equals(pAdd->rhs_));
	}
}

PTR(Val)AddExpr::interp() {
	return (this->lhs_->interp())->add_to(this->rhs_->interp());
}

PTR(Expr)AddExpr::subst(std::string string, PTR(Expr)e) {
	return new AddExpr(this->lhs_->subst(string, e),
					   this->rhs_->subst(string, e));
}

void AddExpr::print(std::ostream &ostream) {
	ostream << "(";
	this->lhs_->print(ostream);
	ostream << "+";
	this->rhs_->print(ostream);
	ostream << ")";
}

void AddExpr::pretty_print_at(std::ostream &ostream,
							  std::streampos &lastReturnSeen,
							  bool lastLeftAndAdd) {
	if (this->lhs_->get_prec() == prec_add ||
		this->lhs_->get_prec() == prec_keywords ||
		this->lhs_->get_prec() == prec_eq) {
		ostream << "(";
		this->lhs_->pretty_print_at(ostream, lastReturnSeen, true);
		ostream << ")";
	} else {
		this->lhs_->pretty_print_at(ostream, lastReturnSeen, true);
	}
	ostream << " + ";
	this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
}

precedence_t AddExpr::get_prec() { return prec_add; }

/*--------------------------------------------------------------------------------------------
	ooo        ooooo             oooo      .   oooooooooooo
	`88.       .888'             `888    .o8   `888'     `8
	 888b     d'888  oooo  oooo   888  .o888oo  888         oooo    ooo oo.ooooo.  oooo d8b
	 8 Y88. .P  888  `888  `888   888    888    888oooo8     `88b..8P'   888' `88b `888""8P
	 8  `888'   888   888   888   888    888    888    "       Y888'     888   888  888
	 8    Y     888   888   888   888    888 .  888       o  .o8"'88b    888   888  888
	o8o        o888o  `V88V"V8P' o888o   "888" o888ooooood8 o88'   888o  888bod8P' d888b
																		 888
																		o888o
--------------------------------------------------------------------------------------------*/

MultExpr::MultExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
	this->lhs_ = lhs;
	this->rhs_ = rhs;
}

bool MultExpr::equals(PTR(Expr)e) {
	PTR(MultExpr)pMult = CAST(MultExpr)(e);
	if (pMult == nullptr) {
		return false;
	} else {
		return (this->lhs_->equals(pMult->lhs_)) &&
			(this->rhs_->equals(pMult->rhs_));
	}
}

PTR(Val)MultExpr::interp() {
	return this->lhs_->interp()->mult_with(this->rhs_->interp());
}

PTR(Expr)MultExpr::subst(std::string string, PTR(Expr)e) {
	return new MultExpr(this->lhs_->subst(string, e),
						this->rhs_->subst(string, e));
}

void MultExpr::print(std::ostream &ostream) {
	ostream << "(";
	this->lhs_->print(ostream);
	ostream << "*";
	this->rhs_->print(ostream);
	ostream << ")";
}

void MultExpr::pretty_print_at(std::ostream &ostream,
							   std::streampos &lastReturnSeen,
							   bool lastLeftAndAdd) {
	if (this->lhs_->get_prec() != prec_none) {
		ostream << "(";
		this->lhs_->pretty_print_at(ostream, lastReturnSeen, false);
		ostream << ")";
	} else {
		this->lhs_->pretty_print_at(ostream, lastReturnSeen, false);
	}

	ostream << " * ";

	if (this->rhs_->get_prec() == prec_add ||
		this->rhs_->get_prec() == prec_eq ||
		((this->rhs_->get_prec() == prec_keywords) && lastLeftAndAdd)) {
		ostream << "(";
		this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
		ostream << ")";
	} else {
		this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
	}
}

precedence_t MultExpr::get_prec() { return prec_mult; }

/*--------------------------------------------------------------------------------------------
	ooooo                      .   oooooooooooo
	`888'                    .o8   `888'     `8
	 888          .ooooo.  .o888oo  888         oooo    ooo oo.ooooo.  oooo d8b
	 888         d88' `88b   888    888oooo8     `88b..8P'   888' `88b `888""8P
	 888         888ooo888   888    888    "       Y888'     888   888  888
	 888       o 888    .o   888 .  888       o  .o8"'88b    888   888  888
	o888ooooood8 `Y8bod8P'   "888" o888ooooood8 o88'   888o  888bod8P' d888b
															 888
															o888o
--------------------------------------------------------------------------------------------*/

LetExpr::LetExpr(std::string lhs, PTR(Expr)rhs, PTR(Expr)body) {
	this->lhs_ = std::move(lhs);
	this->rhs_ = rhs;
	this->body_ = body;
}

bool LetExpr::equals(PTR(Expr)e) {
	PTR(LetExpr)pLet = CAST(LetExpr)(e);
	if (pLet == nullptr) {
		return false;
	} else {
		return (this->lhs_ == pLet->lhs_) &&
			(this->rhs_->equals(pLet->rhs_)) &&
			(this->body_->equals(pLet->body_));
	}
}

PTR(Val)LetExpr::interp() {
	return this->body_->subst(lhs_, rhs_->interp()->to_expr())->interp();
}

PTR(Expr)LetExpr::subst(std::string string, PTR(Expr)e) {
	if (string == this->lhs_) {
		return new LetExpr(this->lhs_,
						   this->rhs_->subst(string, e),
						   this->body_);
	} else {
		return new LetExpr(this->lhs_,
						   this->rhs_->subst(string, e),
						   this->body_->subst(string, e));
	}
}

void LetExpr::print(std::ostream &ostream) {
	ostream << "(_let " << this->lhs_ << "=";
	this->rhs_->print(ostream);
	ostream << " _in ";
	this->body_->print(ostream);
	ostream << ")";
}

void LetExpr::pretty_print_at(std::ostream &ostream,
							  std::streampos &lastReturnSeen,
							  bool lastLeftAndAdd) {
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

precedence_t LetExpr::get_prec() { return prec_keywords; }

/*--------------------------------------------------------------------------------------------
oooooooooo.                      oooo  oooooooooooo
`888'   `Y8b                     `888  `888'     `8
 888     888  .ooooo.   .ooooo.   888   888         oooo    ooo oo.ooooo.  oooo d8b
 888oooo888' d88' `88b d88' `88b  888   888oooo8     `88b..8P'   888' `88b `888""8P
 888    `88b 888   888 888   888  888   888    "       Y888'     888   888  888
 888    .88P 888   888 888   888  888   888       o  .o8"'88b    888   888  888
o888bood8P'  `Y8bod8P' `Y8bod8P' o888o o888ooooood8 o88'   888o  888bod8P' d888b
                                                                 888
                                                                o888o
--------------------------------------------------------------------------------------------*/

BoolExpr::BoolExpr(bool val) { this->val_ = val; }

bool BoolExpr::equals(PTR(Expr)e) {
	PTR(BoolExpr)pBoolExpr = CAST(BoolExpr)(e);
	if (pBoolExpr == nullptr) {
		return false;
	} else {
		return (this->val_ == pBoolExpr->val_);
	}
}

PTR(Val)BoolExpr::interp() { return new BoolVal(this->val_); }

PTR(Expr)BoolExpr::subst(std::string string, PTR(Expr)e) {
	return this;
}

void BoolExpr::print(std::ostream &ostream) {
	if (this->val_ == true) {
		ostream << "_true";
	} else {
		ostream << "_false";
	}
}

void BoolExpr::pretty_print_at(std::ostream &ostream,
							   std::streampos &lastReturnSeen,
							   bool lastLeftAndAdd) {
	this->print(ostream);
}

precedence_t BoolExpr::get_prec() { return prec_none; }

/*--------------------------------------------------------------------------------------------
	oooooooooooo            oooooooooooo
	`888'     `8            `888'     `8
	 888          .ooooo oo  888         oooo    ooo oo.ooooo.  oooo d8b
	 888oooo8    d88' `888   888oooo8     `88b..8P'   888' `88b `888""8P
	 888    "    888   888   888    "       Y888'     888   888  888
	 888       o 888   888   888       o  .o8"'88b    888   888  888
	o888ooooood8 `V8bod888  o888ooooood8 o88'   888o  888bod8P' d888b
					   888.                           888
					   8P'                           o888o
					   "
--------------------------------------------------------------------------------------------*/

EqExpr::EqExpr(PTR(Expr)lhs, PTR(Expr)rhs) {
	this->lhs_ = lhs;
	this->rhs_ = rhs;
}

bool EqExpr::equals(PTR(Expr)e) {
	PTR(EqExpr)pEqExpr = CAST(EqExpr)(e);
	if (pEqExpr == nullptr) {
		return false;
	} else {
		return this->lhs_->equals(pEqExpr->lhs_) &&
			this->rhs_->equals(pEqExpr->rhs_);
	}
}

PTR(Val)EqExpr::interp() {
	return new BoolVal(this->lhs_->interp()->equals(this->rhs_->interp()));
}

PTR(Expr)EqExpr::subst(std::string string, PTR(Expr)e) {
	return new EqExpr(this->lhs_->subst(string, e), this->rhs_->subst(string, e));
}

void EqExpr::print(std::ostream &ostream) {
	ostream << "(";
	this->lhs_->print(ostream);
	ostream << "==";
	this->rhs_->print(ostream);
	ostream << ")";
}

void EqExpr::pretty_print_at(std::ostream &ostream,
							 std::streampos &lastReturnSeen,
							 bool lastLeftAndAdd) {
	if (this->lhs_->get_prec() != prec_none) {
		ostream << "(";
		this->lhs_->pretty_print_at(ostream, lastReturnSeen, false);
		ostream << ")";
	} else {
		this->lhs_->pretty_print_at(ostream, lastReturnSeen, false);
	}
	ostream << " == ";
	if (this->rhs_->get_prec() != prec_none) {
		ostream << "(";
		this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
		ostream << ")";
	} else {
		this->rhs_->pretty_print_at(ostream, lastReturnSeen, false);
	}
}

precedence_t EqExpr::get_prec() {
	return prec_eq;
}

/*--------------------------------------------------------------------------------------------
	ooooo  .o88o. oooooooooooo
	`888'  888 `" `888'     `8
	 888  o888oo   888         oooo    ooo oo.ooooo.  oooo d8b
	 888   888     888oooo8     `88b..8P'   888' `88b `888""8P
	 888   888     888    "       Y888'     888   888  888
	 888   888     888       o  .o8"'88b    888   888  888
	o888o o888o   o888ooooood8 o88'   888o  888bod8P' d888b
											888
										   o888o
--------------------------------------------------------------------------------------------*/

IfExpr::IfExpr(PTR(Expr)testPart, PTR(Expr)thenPart, PTR(Expr)elsePart) {
	this->test_part_ = testPart;
	this->then_part_ = thenPart;
	this->else_part_ = elsePart;
}

bool IfExpr::equals(PTR(Expr)e) {
	PTR(IfExpr)pIfExpr = CAST(IfExpr)(e);
	if (pIfExpr == nullptr) {
		return false;
	} else {
		return this->test_part_->equals(pIfExpr->test_part_) &&
			this->then_part_->equals(pIfExpr->then_part_) &&
			this->else_part_->equals(pIfExpr->else_part_);
	}
}

PTR(Val)IfExpr::interp() {
	PTR(Val)test = this->test_part_->interp();
	PTR(NumVal)pTestVal = CAST(NumVal)(test);
	if (pTestVal == nullptr) { // can't interp to BoolVal
		throw std::runtime_error("IfExpr's condition isn't BoolVal");
	} else if (pTestVal->rep_ == true) { // condition true
		return this->then_part_->interp();
	} else {    // condition false
		return this->else_part_->interp();
	}
}

PTR(Expr)IfExpr::subst(std::string string, PTR(Expr)e) {
	return new IfExpr(this->test_part_->subst(string, e),
					  this->then_part_->subst(string, e),
					  this->else_part_->subst(string, e));
}

void IfExpr::print(std::ostream &ostream) {
	ostream << "(_if ";
	this->test_part_->print(ostream);
	ostream << " _then ";
	this->then_part_->print(ostream);
	ostream << " _else ";
	this->else_part_->print(ostream);
	ostream << ")";
}

void IfExpr::pretty_print_at(std::ostream &ostream,
							 std::streampos &lastReturnSeen,
							 bool lastLeftAndAdd) { // TODO: still need to check
	std::streampos oldLastReturn = lastReturnSeen;
	std::streampos currentStart = ostream.tellp();
	ostream << "_if ";
	this->test_part_->pretty_print_at(ostream, lastReturnSeen, false);
	ostream << "\n";
	lastReturnSeen = ostream.tellp(); //update to this position
	ostream << std::string(currentStart - oldLastReturn, ' ');
	ostream << "_then ";
	this->then_part_->pretty_print_at(ostream, lastReturnSeen, false);
	ostream << "\n";
	lastReturnSeen = ostream.tellp(); // update to this position
	ostream << std::string(currentStart - oldLastReturn, ' ');
	ostream << "_else ";
	this->else_part_->pretty_print_at(ostream, lastReturnSeen, false);
}

precedence_t IfExpr::get_prec() {
	return prec_keywords;
}

/*--------------------------------------------------------------------------------------------
	oooooooooooo                         oooooooooooo
	`888'     `8                         `888'     `8
	 888         oooo  oooo  ooo. .oo.    888         oooo    ooo oo.ooooo.  oooo d8b
	 888oooo8    `888  `888  `888P"Y88b   888oooo8     `88b..8P'   888' `88b `888""8P
	 888    "     888   888   888   888   888    "       Y888'     888   888  888
	 888          888   888   888   888   888       o  .o8"'88b    888   888  888
	o888o         `V88V"V8P' o888o o888o o888ooooood8 o88'   888o  888bod8P' d888b
																   888
																  o888o
--------------------------------------------------------------------------------------------*/

FunExpr::FunExpr(std::string formalArg, PTR(Expr)body) {
	this->formal_arg_ = formalArg;
	this->body_ = body;
}

bool FunExpr::equals(PTR(Expr)e) {
	PTR(FunExpr)pFunExpr = CAST(FunExpr)(e);
	if (pFunExpr == nullptr) {
		return false;
	} else {
		return (this->formal_arg_ == pFunExpr->formal_arg_) &&
			(this->body_->equals(pFunExpr->body_));
	}
}

PTR(Val)FunExpr::interp() {
	return new FunVal(this->formal_arg_, this->body_);
}

PTR(Expr)FunExpr::subst(std::string string, PTR(Expr)e) {
	if (string == this->formal_arg_) {
		return this;
	} else {
		return new FunExpr(this->formal_arg_, this->body_->subst(string, e));
	}
}

void FunExpr::print(std::ostream &ostream) {
	ostream << "(_fun (" << this->formal_arg_ << ") ";
	this->body_->print(ostream);
	ostream << ")";
}

void FunExpr::pretty_print_at(std::ostream &ostream,
							  std::streampos &lastReturnSeen,
							  bool lastLeftAndAdd) { // TODO: still need to check
	std::streampos oldLastReturn = lastReturnSeen;
	std::streampos currentStart = ostream.tellp();
	ostream << "_fun (" << formal_arg_ << ")\n";
	lastReturnSeen = ostream.tellp(); //update to this position
	ostream << std::string(currentStart - oldLastReturn + 2, ' '); //indent the body 2 more space
	this->body_->pretty_print_at(ostream, lastReturnSeen, false);
}

precedence_t FunExpr::get_prec() {
	return prec_keywords;
}

/*--------------------------------------------------------------------------------------------
	  .oooooo.             oooo  oooo  oooooooooooo
	 d8P'  `Y8b            `888  `888  `888'     `8
	888           .oooo.    888   888   888         oooo    ooo oo.ooooo.  oooo d8b
	888          `P  )88b   888   888   888oooo8     `88b..8P'   888' `88b `888""8P
	888           .oP"888   888   888   888    "       Y888'     888   888  888
	`88b    ooo  d8(  888   888   888   888       o  .o8"'88b    888   888  888
	 `Y8bood8P'  `Y888""8o o888o o888o o888ooooood8 o88'   888o  888bod8P' d888b
																 888
																o888o
--------------------------------------------------------------------------------------------*/

CallExpr::CallExpr(PTR(Expr)toBeCalled, PTR(Expr)actualArg) {
	this->to_be_called_ = toBeCalled;
	this->actual_arg_ = actualArg;
}

bool CallExpr::equals(PTR(Expr)e) {
	PTR(CallExpr)pCallExpr = CAST(CallExpr)(e);
	if (pCallExpr == nullptr) {
		return false;
	} else {
		return (this->to_be_called_->equals(pCallExpr->to_be_called_)) &&
			(this->actual_arg_->equals(pCallExpr->actual_arg_));
	}
}

PTR(Val)CallExpr::interp() {
	return this->to_be_called_->interp()->call(actual_arg_->interp());
}

Expr *CallExpr::subst(std::string string, Expr *e) {
	return new CallExpr(this->to_be_called_->subst(string, e), this->actual_arg_->subst(string, e));
}

void CallExpr::print(std::ostream &ostream) {
	this->to_be_called_->print(ostream);
	ostream << "(";
	this->actual_arg_->print(ostream);
	ostream << ")";
}

void CallExpr::pretty_print_at(std::ostream &ostream,
							   std::streampos &lastReturnSeen,
							   bool lastLeftAndAdd) { // TODO: still need to check
	std::streampos oldLastReturn = lastReturnSeen;
	std::streampos currentStart = ostream.tellp();
	this->to_be_called_->pretty_print_at(ostream, lastReturnSeen, false);
	ostream << "(";
	this->actual_arg_->pretty_print_at(ostream, lastReturnSeen, false);
	ostream << ")";
}

precedence_t CallExpr::get_prec() {
	return prec_none;
}