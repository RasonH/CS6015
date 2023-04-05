//
//  expr.h
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

/**
 * \file expr.h
 * \brief expression class
 *
 * Contains the blueprint of the superclass - Expr,
 *                        with its subclass - Num, Add, Mult, Variable
 */
#pragma include once

#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include "pointer.h"

class Val;

typedef enum {
	prec_none,       // = 0, NumExpr, VarExpr, BoolExpr, CallExpr
	prec_add,        // = 1
	prec_mult,       // = 2
	prec_keywords,   // = 3, LetExpr, IfExpr
	prec_eq,         // = 4, EqExpr TODO: still need to modify the precedence for print related

} precedence_t;

/*! \brief Abstract expression class\n
 * (pure abstract class)
 */
class Expr {
 public:
	/**
	 * \brief Judge if this Expr class object equals to another object
	 * \param e an Expr pointer to object waited to be compared
	 * \return returns a boolean, true if two object equals, otherwise false
	 */
	virtual bool equals(PTR(Expr)e) = 0;

	/**
	 * \brief Interpret Expr object to an integer value
	 * \return returns the actual integer value of the Expr, if it contains
	 * Variable, throw an exception
	 */
	virtual PTR(Val)interp() = 0;

	/**
	 * \brief Substitute the Variable inside Expr object with another Expr
	 * \param string first argument, a target string that is waited to be
	 * substituted \param e second argument, an Expr pointer to object that is
	 * going to substitute the Variable inside expression \return returns the new
	 * Expr pointer to object after substitution, return the original object if
	 * string Variable not found
	 */
	virtual PTR(Expr)subst(std::string string, PTR(Expr)e) = 0;

	// TODO: do we need to handle with negative expression?
	/**
	 * \brief print the expression into most basic format (with parentheses, no
	 * space) \param ostream deliver string through this output stream
	 */
	virtual void print(std::ostream &ostream) = 0;

	/**
	 * \brief helper function for pretty_print(std::ostream &ostream)
	 * \param ostream deliver string through this output stream
	 * \param lastReturnSeen tracking the position of last '\\n' seen (generated
	 * by Let) by passing reference \param lastLvlLeft tracking where did the last
	 * binding came from, return true if it is the left hand side of the upper
	 * level Add expression
	 */
	virtual void pretty_print_at(std::ostream &ostream,
								 std::streampos &lastReturnSeen,
								 bool lastLeftAndAdd) = 0;

	/**
	 * \brief implementation helper function of pretty_print_at for classifying
	 * case \return precedence_t type enum
	 */
	virtual precedence_t get_prec() = 0;

	/**
	 * \brief print the expression into a pretty format (avoids unnecessary
	 * parentheses, with space around + / *) \param ostream deliver string through
	 * this output stream
	 */
	void pretty_print(std::ostream &ostream);

	/**
	 * \brief  converting expression to string with basic format
	 */
	std::string to_string();

	/**
	 * \brief  converting expression to string with a pretty format
	 */
	std::string to_pretty_string(); // if not required - only for test use

	// judge if at least with someone's lhs
	//    bool isOnAnyLhs(bool &onLhs);
};

/*! \brief Num class inherits from Expr class, representing pure number
 */
class NumExpr : public Expr {
 public:
	int val_; //!< the integer value of the Num object

	/**
	 * \brief Constructor for Num object
	 * \param val integer value of Num
	 */
	explicit NumExpr(int val);

	/**
	 * \brief Judge if this Num class object equals to another object
	 * \param e an Expr pointer to Expr object waited to be compared
	 * \return returns a boolean, true if two object equals, otherwise false
	 */
	bool equals(PTR(Expr)e) override;

	/**
	 * \brief Interpret Num object to an integer value
	 * \return returns the actual integer value of the Num
	 */
	PTR(Val)interp() override;

	/**
	 * \brief Substitute the Variable inside Num object with another Expr
	 * \param string first argument, a target string that is waited to be
	 * substituted \param e second argument, an Expr pointer to object that is
	 * going to substitute the Variable inside expression \return returns this
	 * object, since there is no Variable in Num object
	 */
	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

/*! \brief Var class inherits from Expr class, representing pure variable
 */
class VarExpr : public Expr {
 public:
	std::string string_; //!< the string name that makes up the Var object

	/**
	 * \brief Constructor for Var object
	 * \param varName a string that can be seen as the label of the Var
	 */
	explicit VarExpr(std::string varName);

	/**
	 * \brief Judge if this Var class object equals to another object, overrides
	 * function in superclass. \param e an Expr pointer to Expr object waited to
	 * be compared \return returns a boolean, true if two object equals, otherwise
	 * false
	 */
	bool equals(PTR(Expr)e) override;

	/**
	 * \brief Interpret Var object to an integer value
	 * \return A Var doesn't have specific integer value, throw an exception
	 */
	PTR(Val)interp() override;

	/**
	 * \brief Substitute the Var object with another Expr
	 * \param string first argument, a target string that is waited to be
	 * substituted \param e second argument, an Expr pointer to object that is
	 * going to substitute the Var inside expression \return returns the new Expr
	 * pointer to object after substitution, return the original object if string
	 * variable not found
	 */
	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

/*! \brief Add class inherits from Expr class, representing addition for two
 * expressions
 */
class AddExpr : public Expr {
 public:
	PTR(Expr)lhs_; //!< the Expr object that makes up the left hand side of the Add
	//!< object
	PTR(Expr)rhs_; //!< the Expr object that makes up the right hand side of the Add
	//!< object

	/**
	 * \brief Constructor for Add object
	 * \param lhs an Expr object on the left hand side
	 * \param rhs an Expr object on the right hand side
	 */
	AddExpr(PTR(Expr)lhs, PTR(Expr)rhs);

	/**
	 * \brief Judge if this Add class object equals to another object
	 * \param e an Expr pointer to Expr object waited to be compared
	 * \return returns a boolean, true if two object equals, otherwise false
	 */
	bool equals(PTR(Expr)e) override;

	/**
	 * \brief Interpret Add object to an integer value
	 * \return returns the actual integer value (lhs + rhs) of the Add, if it
	 * contains Var, throw an exception
	 */
	PTR(Val)interp() override;

	/**
	 * \brief Substitute the Var inside Add object with another Expr
	 * \param string first argument, a target string that is waited to be
	 * substituted \param e second argument, an Expr pointer to object that is
	 * going to substitute the Var inside expression \return returns the new Expr
	 * pointer to object after substitution, return the original object if string
	 * variable not found
	 */
	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

/*! \brief Mult class inherits from Expr class, representing multiplication for
 * two expressions
 */
class MultExpr : public Expr {
 public:
	PTR(Expr)lhs_; //!< the Expr object that makes up the left hand side of the Mult
	//!< object
	PTR(Expr)rhs_; //!< the Expr object that makes up the right hand side of the Mult
	//!< object

	/**
	 * \brief Constructor for Mult object
	 * \param lhs an Expr object on the left hand side
	 * \param rhs an Expr object on the right hand side
	 */
	MultExpr(PTR(Expr)lhs, PTR(Expr)rhs);

	/**
	 * \brief Judge if this Mult class object equals to another object
	 * \param e an Expr pointer to Expr object waited to be compared
	 * \return returns a boolean, true if two object equals, otherwise false
	 */
	bool equals(PTR(Expr)e) override;

	/**
	 * \brief Interpret Mult object to an integer value
	 * \return returns the actual integer value (lhs * rhs) of the Mult, if it
	 * contains Var, throw an exception
	 */
	PTR(Val)interp() override;

	/**
	 * \brief Substitute the Var inside Mult object with another Expr
	 * \param string first argument, a target string that is waited to be
	 * substituted \param e second argument, an Expr pointer to object that is
	 * going to substitute the Var inside expression \return returns the new Expr
	 * pointer to object after substitution, return the original object if string
	 * variable not found
	 */
	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

/*! \brief Let class inherits from Expr class, representing setting values for
 * some expressions if applicable
 */
class LetExpr : public Expr {
 public:
	std::string lhs_; //!< the expression that is waiting to be set with value
	PTR(Expr)rhs_;       //!< the setting value
	PTR(Expr)body_;      //!< in which expression the variable is set with the value

	/**
	 * \brief Constructor for Let object
	 * \param lhs string that represents the variable waiting to be set
	 * \param rhs an Expr with some value passing to the lhs expression
	 * \param body in which expression the variable is set with the value
	 */
	LetExpr(std::string lhs, PTR(Expr)rhs, PTR(Expr)body);

	/**
	 * \brief Judge if this Let class object equals to another object
	 * \param e an Expr pointer to Expr object waited to be compared
	 * \return returns a boolean, true if two object equals, otherwise false
	 */
	bool equals(PTR(Expr)e) override;

	/**
	 * \brief Interpret Let object to an integer value
	 * \return returns the actual integer value of the Num
	 */
	PTR(Val)interp() override;

	/**
	 * \brief Substitute the Var inside Let object with another Expr
	 * \param string first argument, a target string that is waited to be
	 * substituted \param e second argument, an Expr pointer to object that is
	 * going to substitute the Var inside expression \return returns this object,
	 * since there is no Var in Let object
	 */
	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

class BoolExpr : public Expr {
 public:
	bool val_;

	explicit BoolExpr(bool val);

	bool equals(PTR(Expr)e) override;

	PTR(Val)interp() override;

	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

class EqExpr : public Expr { // equal class
 public:
	PTR(Expr)lhs_;
	PTR(Expr)rhs_;

	EqExpr(PTR(Expr)lhs, PTR(Expr)rhs);

	bool equals(PTR(Expr)e) override;

	PTR(Val)interp() override;

	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

class IfExpr : public Expr {
 public:
	PTR(Expr)test_part_; // if condition
	PTR(Expr)then_part_;
	PTR(Expr)else_part_;

	IfExpr(PTR(Expr)testPart, PTR(Expr)thenPart, PTR(Expr)elsePart);

	bool equals(PTR(Expr)e) override;

	Val *interp() override;

	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

class FunExpr : public Expr {
 public:
	std::string formal_arg_; // _fun (x)
	PTR(Expr)body_; // return expression

	FunExpr(std::string formalArg, PTR(Expr)body);

	bool equals(PTR(Expr)e) override;

	Val *interp() override;

	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};

class CallExpr : public Expr {
 public:
	PTR(Expr)to_be_called_;
	PTR(Expr)actual_arg_;

	CallExpr(PTR(Expr)toBeCalled, PTR(Expr)actualArg);

	bool equals(PTR(Expr)e) override;

	Val *interp() override;

	PTR(Expr)subst(std::string string, PTR(Expr)e) override;

	void print(std::ostream &ostream) override;

	void pretty_print_at(std::ostream &ostream, std::streampos &lastReturnSeen,
						 bool lastLeftAndAdd) override;

	precedence_t get_prec() override;
};