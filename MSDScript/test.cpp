//
// Created by Rason Hung on 1/29/23.
//

#pragma include once
#include "expr.h"
#include "test.h"

TEST_CASE("Equals"){
    SECTION("Num_equals"){
        SECTION("Normal_cases"){
            CHECK((new Num(1))->equals(new Num(1)) == true);
            CHECK((new Num(1))->equals(new Num(2)) == false);
            CHECK((new Num(1))->equals(new Num(-1)) == false);
            CHECK((new Num(1))->equals(new Num(0)) == false);
        }
        SECTION("Edge_cases"){ //from diffenrt classes
            CHECK((new Num(1))->equals(new Add(new Num(1), new Num(1))) == false);
            CHECK((new Num(1))->equals(new Mult(new Num(1), new Num(1))) == false);
            CHECK((new Num(1))->equals(new Variable("x")) == false);
        }
    }

    SECTION("Add_equals"){
        SECTION("Normal_cases"){
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == true);
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(2), new Num(2))) == false);
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(3))) == false);
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Add(new Num(2), new Num(1))) == false);
            CHECK((new Add(new Num(1), (new Add(new Num(2), new Num(3)))))->equals(new Add(new Num(1), (new Add(new Num(2), new Num(3))))) == true);
        }
        SECTION("Edge_cases"){ //from diffenrt classes
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Num(2)) == false);
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(2))) == false);
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Variable("x")) == false);
        }
    }

    SECTION("Mult_equals"){
        SECTION("Normal_cases"){
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(2))) == true);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(2), new Num(2))) == false);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(3))) == false);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Mult(new Num(2), new Num(1))) == false);
            CHECK((new Mult(new Num(1), (new Mult(new Num(2), new Num(3)))))->equals(new Mult(new Num(1), (new Mult(new Num(2), new Num(3))))) == true);
        }
        SECTION("Edge_cases"){ //from diffenrt classes
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Num(2)) == false);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == false);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Variable("x")) == false);
        }
    }

    SECTION("Variable_equals"){
        SECTION("Normal_cases"){
            CHECK((new Variable("x"))->equals(new Variable("x")) == true);
            CHECK((new Variable("x"))->equals(new Variable("X")) == false);
            CHECK((new Variable("x"))->equals(new Variable("y")) == false);
            CHECK((new Variable("x"))->equals(new Variable("xa")) == false);
        }
        SECTION("Edge_cases"){ //from diffenrt classes
            CHECK((new Variable("x"))->equals(new Num(1)) == false);
            CHECK((new Variable("x"))->equals(new Add(new Num(1), new Num(2))) == false);
            CHECK((new Variable("x"))->equals(new Mult(new Num(1), new Num(2))) == false);
        }
    }

    SECTION("Mixed_equals"){
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Mult(new Num(1), new Num(2)), new Variable("x"))) == true);
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Variable("x"), new Mult(new Num(1), new Num(2)))) == false);

        //changed some of the components but not order
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Mult(new Num(1), new Num(2)), new Variable("y"))) == false);
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Add(new Mult(new Num(2), new Num(2)), new Variable("x"))) == false);
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Variable("x")))->equals(new Mult(new Add(new Num(1), new Num(2)), new Variable("x"))) == false);

        //changed expression order
        CHECK((new Mult(new Add(new Num(1), new Num(2)), new Variable("x")))->equals(new Mult(new Add(new Num(1), new Num(2)), new Variable("x"))) == true);
    }
    SECTION("Invalid_argument_equals"){
        SECTION("Nullptr"){
            CHECK((new Num(2))->equals(new Add(new Num(1), new Num(2))) == false);
            CHECK((new Add(new Num(1), new Num(2)))->equals(nullptr) == false);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(nullptr) == false);
        }
    }
}

TEST_CASE("Interpret"){
    SECTION("Num_interpret"){
        CHECK((new Num(1))->interp() == 1);
        CHECK((new Num(0))->interp() == 0);
        CHECK((new Num(-1))->interp() == -1);
    }

    SECTION("Add_interpret"){
        CHECK((new Add(new Num(1), new Num(2)))->interp() == 3);
        CHECK((new Add(new Num(1), new Num(-1)))->interp() == 0);
        CHECK((new Add(new Num(-5), new Num(-1)))->interp() == -6);
    }

    SECTION("Mult_interpret"){
        CHECK((new Mult(new Num(3), new Num(2)))->interp() == 6);
        CHECK((new Mult(new Num(3), new Num(0)))->interp() == 0);
        CHECK((new Mult(new Num(5), new Num(2)))->interp() == 10);
        CHECK((new Mult(new Num(-5), new Num(2)))->interp() == -10);
    }

    SECTION("Variable_interpret"){
        CHECK_THROWS_WITH( (new Variable("x"))->interp(), "no value for variable" );
        CHECK_THROWS_WITH( (new Variable("abc"))->interp(), "no value for variable" );
    }

    SECTION("Mixed_interpret"){
        CHECK((new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp() == 65);
        CHECK_THROWS_WITH((new Add(new Add(new Variable("x"), new Num(15)),new Add(new Num(20),new Num(20))))->interp(), "no value for variable");
        CHECK_THROWS_WITH((new Add(new Mult(new Variable("x"), new Num(15)),new Add(new Num(20),new Num(20))))->interp(), "no value for variable");
        CHECK_THROWS_WITH((new Add(new Add(new Num(15), new Variable("x")),new Add(new Num(20),new Num(20))))->interp(), "no value for variable");
        CHECK_THROWS_WITH((new Add(new Mult(new Num(15), new Variable("x")),new Add(new Num(20),new Num(20))))->interp(), "no value for variable");
    }
}

TEST_CASE("Has_variable"){
    SECTION("Variable_has_variable"){
        CHECK((new Variable("x"))->has_variable() == true);
        CHECK((new Variable("y"))->has_variable() == true);
    }

    SECTION("Others_has_variable"){
        CHECK((new Num(1))->has_variable() == false);
        CHECK((new Num(0))->has_variable() == false);
        CHECK((new Add(new Num(1), new Num(2)))->has_variable() == false);
        CHECK((new Add(new Variable("x"), new Num(2)))->has_variable() == true);
        CHECK((new Add(new Num(1), new Variable("x")))->has_variable() == true);
        CHECK((new Mult(new Num(1), new Num(2)))->has_variable() == false);
        CHECK((new Mult(new Num(1), new Variable("x")))->has_variable() == true);
    }

    SECTION("Mixed_has_variable"){
        CHECK((new Add(new Num(1), new Variable("x")))->has_variable() == true);
        CHECK((new Mult(new Variable("y"), new Num(2)))->has_variable() == true);
        CHECK((new Mult(new Add(new Num(10), new Num(15)),new Mult(new Num(20),new Num(20))))->has_variable() == false);
    }
}

TEST_CASE("Substitute"){
    CHECK((new Add(new Variable("x"), new Num(7)))
                   ->subst("x", new Variable("y"))
                   ->equals(new Add(new Variable("y"), new Num(7))));
    CHECK((new Variable("x"))
                   ->subst("x", new Add(new Variable("y"),new Num(7)))
                   ->equals(new Add(new Variable("y"),new Num(7))) );
    // x * (y * (x + 1)) => x = -2 => -2 * (y * (-2 + 1))
    CHECK((new Mult(new Variable("x"), new Mult(new Variable("y"), new Add(new Variable("x"), new Num(1)))))
                  ->subst("x", new Num(-2))
                  ->equals(new Mult(new Num(-2), new Mult(new Variable("y"), new Add(new Num(-2), new Num(1))))));
    SECTION("Other_substitute"){
        CHECK(((new Variable("x"))->subst("x",new Num(2)))->interp() == 2);
        CHECK(((new Variable("x"))->subst("x",new Mult(new Num(2), new Variable("y")))->equals(new Mult(new Num(2), new Variable("y")))));
        CHECK(((new Variable("x"))->subst("y",new Num(2)))->equals(new Variable("x")));
    }
}

TEST_CASE("Precedence"){
    SECTION("Pretty_print_at"){
        CHECK((new Num(1))->pretty_print_at() == prec_none);
        CHECK((new Variable("x"))->pretty_print_at() == prec_none);
        CHECK((new Add(new Num(1), new Variable("x")))->pretty_print_at() == prec_add);
        CHECK((new Mult(new Num(1), new Variable("x")))->pretty_print_at() == prec_mult);

    }
}


TEST_CASE("To_string"){
    SECTION("Print"){
        SECTION("Num_print"){
            CHECK((new Num(10))->to_string() == "10");
            CHECK((new Num(-10))->to_string() == "-10");
        }
        SECTION("Variable_print"){
            CHECK((new Variable("x"))->to_string() == "x");
            CHECK((new Variable("MAX"))->to_string() == "MAX");
        }
        SECTION("Add_print"){
            CHECK((new Add(new Num(10),new Num(12)))->to_string() == "(10+12)");
            CHECK((new Add(new Num(-10),new Num(-12)))->to_string() == "(-10+-12)");
            CHECK((new Add(new Num(10),new Variable("x")))->to_string() == "(10+x)");
        }
        SECTION("Mult_print"){
            CHECK((new Mult(new Num(10),new Num(12)))->to_string() == "(10*12)");
            CHECK((new Mult(new Num(-10),new Num(-12)))->to_string() == "(-10*-12)");
            CHECK((new Mult(new Num(10),new Variable("x")))->to_string() == "(10*x)");
        }
        SECTION("Mixed_print"){
            CHECK((new Mult(new Num(10),new Add(new Variable("x"), new Num(12))))->to_string() == "(10*(x+12))");
        }

    }SECTION("Pretty_print"){
        SECTION("Num_pretty_print"){
            CHECK((new Num(10))->to_pretty_string() == "10");
            CHECK((new Num(-10))->to_pretty_string() == "-10");
        }
        SECTION("Variable_pretty_print"){
            CHECK((new Variable("x"))->to_pretty_string() == "x");
            CHECK((new Variable("MAX"))->to_pretty_string() == "MAX");
        }
        SECTION("Add_pretty_print"){
            CHECK((new Add(new Num(10),new Num(12)))->to_pretty_string() == "10 + 12");
            CHECK((new Add(new Num(-10),new Num(-12)))->to_pretty_string() == "-10 + -12");
            CHECK((new Add(new Num(10),new Variable("x")))->to_pretty_string() == "10 + x");
        }
        SECTION("Mult_pretty_print"){
            CHECK((new Mult(new Num(10),new Num(12)))->to_pretty_string() == "10 * 12");
            CHECK((new Mult(new Num(-10),new Num(-12)))->to_pretty_string() == "-10 * -12");
            CHECK((new Mult(new Num(10),new Variable("x")))->to_pretty_string() == "10 * x");
        }
        SECTION("Mixed_pretty_print"){
            SECTION("Add_in_between"){
                SECTION("None_add_none"){
                    CHECK((new Add(new Num(10),new Num(12)))->to_pretty_string() == "10 + 12");
                }
                SECTION("None_add_add"){
                    CHECK((new Add(new Num(10),new Add(new Num(12), new Variable("x"))))->to_pretty_string() == "10 + 12 + x");
                }
                SECTION("None_add_mult"){
                    CHECK((new Add(new Num(10),new Mult(new Num(12), new Variable("x"))))->to_pretty_string() == "10 + 12 * x");
                }
                SECTION("Add_add_none"){
                    CHECK((new Add(new Add(new Num(12), new Variable("x")), new Num(10)))->to_pretty_string() == "12 + x + 10");
                }
                SECTION("Add_add_add"){
                    CHECK((new Add(new Add(new Num(12), new Variable("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "12 + x + 10 + 1");
                }
                SECTION("Add_add_mult"){
                    CHECK((new Add(new Add(new Num(12), new Variable("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "12 + x + 10 * 1");
                }
                SECTION("Mult_add_none"){
                    CHECK((new Add(new Mult(new Num(12), new Variable("x")), new Num(10)))->to_pretty_string() == "12 * x + 10");
                }
                SECTION("Mult_add_add"){
                    CHECK((new Add(new Mult(new Num(12), new Variable("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "12 * x + 10 + 1");
                }
                SECTION("Mult_add_mult"){
                    CHECK((new Add(new Mult(new Num(12), new Variable("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "12 * x + 10 * 1");
                }
            }
            SECTION("Mult_in_between"){
                SECTION("None_mult_none"){
                    CHECK((new Mult(new Num(10),new Num(12)))->to_pretty_string() == "10 * 12");
                }
                SECTION("None_mult_add"){
                    CHECK((new Mult(new Num(10),new Add(new Num(12), new Variable("x"))))->to_pretty_string() == "10 * (12 + x)");
                }
                SECTION("None_mult_mult"){
                    CHECK((new Mult(new Num(10),new Mult(new Num(12), new Variable("x"))))->to_pretty_string() == "10 * 12 * x");
                }
                SECTION("Add_mult_none"){
                    CHECK((new Mult(new Add(new Num(12), new Variable("x")), new Num(10)))->to_pretty_string() == "(12 + x) * 10");
                }
                SECTION("Add_mult_add"){
                    CHECK((new Mult(new Add(new Num(12), new Variable("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "(12 + x) * (10 + 1)");
                }
                SECTION("Add_mult_mult"){
                    CHECK((new Mult(new Add(new Num(12), new Variable("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "(12 + x) * 10 * 1");
                }
                SECTION("Mult_mult_none"){
                    CHECK((new Mult(new Mult(new Num(12), new Variable("x")), new Num(10)))->to_pretty_string() == "12 * x * 10");
                }
                SECTION("Mult_mult_add"){
                    CHECK((new Mult(new Mult(new Num(12), new Variable("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "12 * x * (10 + 1)");
                }
                SECTION("Mult_mult_mult"){
                    CHECK((new Mult(new Mult(new Num(12), new Variable("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "12 * x * 10 * 1");
                }
            }
        }
    }

}
