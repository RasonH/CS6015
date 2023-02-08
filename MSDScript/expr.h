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
#include <string>


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
    virtual bool equals(Expr *e) = 0;

    /**
    * \brief Interpret Expr object to an integer value
    * \return returns the actual integer value of the Expr, if it contains Variable, throw an exception
    */
    virtual int interp() = 0;

    /**
    * \brief Judge if the Expr object contains any Variable
    * \return returns a boolean, true if the Expr object contains any Variable, otherwise false
    */
    virtual bool has_variable() = 0;

    /**
    * \brief Substitute the Variable inside Expr object with another Expr
    * \param string first argument, a target string that is waited to be substituted
    * \param e second argument, an Expr pointer to object that is going to substitute the Variable inside expression
    * \return returns the new Expr pointer to object after substitution, return the original object if string Variable not found
    */
    virtual Expr* subst(std::string string, Expr* e)=0;
};

/*! \brief Num class inherits from Expr class, representing pure number
 */
class Num : public Expr {
public:
    int val; //!< the integer value of the Num object

    /**
    * \brief Constructor for Num object
    * \param val integer value of Num
    */
    explicit Num(int val);

    /**
    * \brief Judge if this Num class object equals to another object
    * \param e an Expr pointer to Expr object waited to be compared
    * \return returns a boolean, true if two object equals, otherwise false
    */
    bool equals(Expr *e) override;

    /**
    * \brief Interpret Num object to an integer value
    * \return returns the actual integer value of the Num
    */
    int interp() override;

    /**
    * \brief Judge if the Num object contains any Variable
    * \return returns a boolean, always return false
    */
    bool has_variable() override;

    /**
    * \brief Substitute the Variable inside Num object with another Expr
    * \param string first argument, a target string that is waited to be substituted
    * \param e second argument, an Expr pointer to object that is going to substitute the Variable inside expression
    * \return returns this object, since there is no Variable in Num object
    */
    Expr* subst(std::string string, Expr* e) override;
};


/*! \brief Add class inherits from Expr class, representing addition for two expressions
 */
class Add : public Expr {
public:
    Expr *lhs; //!< the Expr object that makes up the left hand side of the Add object
    Expr *rhs; //!< the Expr object that makes up the right hand side of the Add object

    /**
   * \brief Constructor for Add object
   * \param lhs an Expr object on the left hand side
   * \param rhs an Expr object on the right hand side
   */
    Add(Expr *lhs, Expr *rhs);

    /**
    * \brief Judge if this Add class object equals to another object
    * \param e an Expr pointer to Expr object waited to be compared
    * \return returns a boolean, true if two object equals, otherwise false
    */
    bool equals(Expr *e) override;

    /**
    * \brief Interpret Add object to an integer value
    * \return returns the actual integer value (lhs + rhs) of the Add, if it contains Variable, throw an exception
    */
    int interp() override;

    /**
    * \brief Judge if the Add object contains any Variable
    * \return returns a boolean, true if the Expr object contains any Variable, otherwise false
    */
    bool has_variable() override;

    /**
    * \brief Substitute the Variable inside Add object with another Expr
    * \param string first argument, a target string that is waited to be substituted
    * \param e second argument, an Expr pointer to object that is going to substitute the Variable inside expression
    * \return returns the new Expr pointer to object after substitution, return the original object if string Variable not found
    */
    Expr* subst(std::string string, Expr* e) override;
};

/*! \brief Mult class inherits from Expr class, representing multiplication for two expressions
 */
class Mult : public Expr {
public:
    Expr *lhs; //!< the Expr object that makes up the left hand side of the Mult object
    Expr *rhs; //!< the Expr object that makes up the right hand side of the Mult object

    /**
   * \brief Constructor for Mult object
   * \param lhs an Expr object on the left hand side
   * \param rhs an Expr object on the right hand side
   */
    Mult(Expr *lhs, Expr *rhs);

    /**
    * \brief Judge if this Mult class object equals to another object
    * \param e an Expr pointer to Expr object waited to be compared
    * \return returns a boolean, true if two object equals, otherwise false
    */
    bool equals(Expr *e) override;

    /**
    * \brief Interpret Mult object to an integer value
    * \return returns the actual integer value (lhs * rhs) of the Mult, if it contains Variable, throw an exception
    */
    int interp() override;

    /**
    * \brief Judge if the Mult object contains any Variable
    * \return returns a boolean, true if the Expr object contains any Variable, otherwise false
    */
    bool has_variable() override;

    /**
    * \brief Substitute the Variable inside Mult object with another Expr
    * \param string first argument, a target string that is waited to be substituted
    * \param e second argument, an Expr pointer to object that is going to substitute the Variable inside expression
    * \return returns the new Expr pointer to object after substitution, return the original object if string Variable not found
    */
    Expr* subst(std::string string, Expr* e) override;
};

/*! \brief Variable class inherits from Expr class, representing pure variable
 */
class Variable : public Expr {
public:
    std::string name;  //!< the string name that makes up the Variable object

    /**
    * \brief Constructor for Variable object
    * \param varName a string that can be seen as the label of the Variable
    */
    explicit Variable(std::string varName);

    /**
    * \brief Judge if this Variable class object equals to another object, overrides function in superclass.
    * \param e an Expr pointer to Expr object waited to be compared
    * \return returns a boolean, true if two object equals, otherwise false
    */
    bool equals(Expr *e) override;

    /**
    * \brief Interpret Variable object to an integer value
    * \return A Variable doesn't have specific integer value, throw an exception
    */
    int interp() override;

    /**
    * \brief Judge if the Variable object contains any Variable
    * \return returns a boolean, always return true
    */
    bool has_variable() override;

    /**
    * \brief Substitute the Variable object with another Expr
    * \param string first argument, a target string that is waited to be substituted
    * \param e second argument, an Expr pointer to object that is going to substitute the Variable inside expression
    * \return returns the new Expr pointer to object after substitution, return the original object if string Variable not found
    */
    Expr* subst(std::string string, Expr* e) override;
};
