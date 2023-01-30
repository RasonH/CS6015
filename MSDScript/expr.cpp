//
//  expr.cpp
//  ExpressionClasses
//
//  Created by Rason Hung on 1/22/23.
//

#pragma include once
#include "expr.h"
#include "catch.h"

Num::Num(int val){
    this->val = val;
}

bool Num::equals(Expr *e){
    Num *n = dynamic_cast<Num*>(e);
    if(n == NULL){
        return false;
    }else{
        return this->val == n->val;
    }
}

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr *e){
    Add *a = dynamic_cast<Add*>(e);
    if(a == NULL){
        return false;
    }else{
        return (this->lhs->equals(a->lhs) && this->rhs->equals(a->rhs));
    }
}

Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *e){
    Mult *m = dynamic_cast<Mult*>(e);
    if(m == NULL){
        return false;
    }else{
        return (this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs));
    }
}

Variable::Variable(std::string varName){
    this->name = varName;
}

bool Variable::equals(Expr *e){
    Variable *m = dynamic_cast<Variable*>(e);
    if(m == NULL){
        return false;
    }else{
        return (this->name == m->name);
    }
}


TEST_CASE("Num_equals","[num]"){
    SECTION("Normal_cases"){
        REQUIRE((new Num(1))->equals(new Num(1)) == true);
        REQUIRE((new Num(1))->equals(new Num(2)) == false);
        REQUIRE((new Num(1))->equals(new Num(-1)) == false);
        REQUIRE((new Num(1))->equals(new Num(0)) == false);
    }
    SECTION("Edge_cases"){ //from diffenrt classes
        REQUIRE((new Num(1))->equals(new Add(new Num(1), new Num(1))) == false);
        REQUIRE((new Num(1))->equals(new Mult(new Num(1), new Num(1))) == false);
        REQUIRE((new Num(1))->equals(new Variable("x")) == false);
    }
}

TEST_CASE("Add_equals","[add]"){
    SECTION("Normal_cases"){
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == true);
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(2), new Num(2))) == false);
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(3))) == false);
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(2), new Num(1))) == false);
        REQUIRE((new Add(new Num(1), (new Add(new Num(2), new Num(3)))))->equals(new Add(new Num(1), (new Add(new Num(2), new Num(3))))) == true);
    }
    SECTION("Edge_cases"){ //from diffenrt classes
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Num(2)) == false);
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(2))) == false);
        REQUIRE((new Add(new Num(1), new Num(2)))->equals(new Variable("x")) == false);
    }
}

TEST_CASE("Mult_equals","[mult]"){
    SECTION("Normal_cases"){
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(2))) == true);
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(2), new Num(2))) == false);
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(3))) == false);
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(2), new Num(1))) == false);
        REQUIRE((new Mult(new Num(1), (new Mult(new Num(2), new Num(3)))))->equals(new Mult(new Num(1), (new Mult(new Num(2), new Num(3))))) == true);
    }
    SECTION("Edge_cases"){ //from diffenrt classes
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Num(2)) == false);
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == false);
        REQUIRE((new Mult(new Num(1), new Num(2)))->equals(new Variable("x")) == false);
    }
}

TEST_CASE("Variable_equals","[var]"){
    SECTION("Normal_cases"){
        REQUIRE((new Variable("x"))->equals(new Variable("x")) == true);
        REQUIRE((new Variable("x"))->equals(new Variable("X")) == false);
        REQUIRE((new Variable("x"))->equals(new Variable("y")) == false);
        REQUIRE((new Variable("x"))->equals(new Variable("xa")) == false);
    }
    SECTION("Edge_cases"){ //from diffenrt classes
        REQUIRE((new Variable("x"))->equals(new Num(1)) == false);
        REQUIRE((new Variable("x"))->equals(new Add(new Num(1), new Num(2))) == false);
        REQUIRE((new Variable("x"))->equals(new Mult(new Num(1), new Num(2))) == false);
    }
}

TEST_CASE("Mixed_equals","[mix]"){
    REQUIRE((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Mult(new Num(1), new Num(2)), new Variable("x"))) == true);
    REQUIRE((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Variable("x"), new Mult(new Num(1), new Num(2)))) == false);
    
    //changed some of the components but not order
    REQUIRE((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Mult(new Num(1), new Num(2)), new Variable("y"))) == false);
    REQUIRE((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Mult(new Num(2), new Num(2)), new Variable("x"))) == false);
    REQUIRE((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Mult(new Add(new Num(1), new Num(2)), new Variable("x"))) == false);
    
    //changed expression order
    REQUIRE((new Mult(new Add(new Num(1), new Num(2)), new Variable("x")))->equals(new Mult(new Add(new Num(1), new Num(2)), new Variable("x"))) == true);
}
