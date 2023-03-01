//
// Created by Rason Hung on 1/29/23.
//

#pragma include once
//#include "expr.h"
#include "catch.h"
#include "parse.h"

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
            CHECK((new Num(1))->equals(new Var("x")) == false);
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
            CHECK((new Add(new Num(1), new Num(2)))->equals(new Var("x")) == false);
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
            CHECK((new Mult(new Num(1), new Num(2)))->equals(new Var("x")) == false);
        }
    }

    SECTION("Variable_equals"){
        SECTION("Normal_cases"){
            CHECK((new Var("x"))->equals(new Var("x")) == true);
            CHECK((new Var("x"))->equals(new Var("X")) == false);
            CHECK((new Var("x"))->equals(new Var("y")) == false);
            CHECK((new Var("x"))->equals(new Var("xa")) == false);
        }
        SECTION("Edge_cases"){ //from diffenrt classes
            CHECK((new Var("x"))->equals(new Num(1)) == false);
            CHECK((new Var("x"))->equals(new Add(new Num(1), new Num(2))) == false);
            CHECK((new Var("x"))->equals(new Mult(new Num(1), new Num(2))) == false);
        }
    }

    SECTION("Let_equals"){
        SECTION("Normal_cases"){
            CHECK((new Let("x", new Num(2), new Add(new Var("x"), new Num(3))))
                  ->equals(new Let("x", new Num(2), new Add(new Var("x"), new Num(3))))
                  == true);
            CHECK((new Let("x", new Num(2), new Add(new Var("x"), new Num(3))))
                  ->equals(new Let("y", new Num(2), new Add(new Var("x"), new Num(3))))
                  == false);
            CHECK((new Let("x", new Num(3), new Add(new Var("x"), new Num(3))))
                  ->equals(new Let("x", new Num(2), new Add(new Var("x"), new Num(3))))
                  == false);
            CHECK((new Let("x", new Num(2), new Add(new Var("x"), new Num(3))))
                  ->equals(new Let("x", new Num(2), new Mult(new Var("x"), new Num(3))))
                  == false);
        }
        SECTION("Edge_cases"){ //from diffenrt classes
            CHECK((new Let("x",
                           new Num(2),
                           new Add(new Var("x"), new Num(3))))
                      ->equals(new Num(2))
                      == false);
            CHECK((new Let("x",
                           new Num(2),
                           new Add(new Var("x"), new Num(3))))
                      ->equals(new Add(new Var("x"), new Num(3)))
                      == false);
            CHECK((new Let("x",
                           new Num(2),
                           new Add(new Var("x"), new Num(3))))
                      ->equals(new Mult(new Var("x"), new Num(3)))
                      == false);
            CHECK((new Let("x",
                           new Num(2),
                           new Add(new Var("x"), new Num(3))))
                      ->equals(new Var("x"))
                      == false);

        }
    }

    SECTION("Mixed_equals"){
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Var("x")))->equals(new Add(new Mult(new Num(1), new Num(2)), new Var("x"))) == true);
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Var("x")))->equals(new Add(new Var("x"), new Mult(new Num(1), new Num(2)))) == false);

        //changed some of the components but not order
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Var("x")))->equals(new Add(new Mult(new Num(1), new Num(2)), new Var("y"))) == false);
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Var("x")))->equals(new Add(new Mult(new Num(2), new Num(2)), new Var("x"))) == false);
        CHECK((new Add(new Mult(new Num(1), new Num(2)), new Var("x")))->equals(new Mult(new Add(new Num(1), new Num(2)), new Var("x"))) == false);

        //changed expression order
        CHECK((new Mult(new Add(new Num(1), new Num(2)), new Var("x")))->equals(new Mult(new Add(new Num(1), new Num(2)), new Var("x"))) == true);
    }
    SECTION("Invalid_argument_equals"){
        SECTION("Nullptr"){
            CHECK((new Num(2))->equals(new Add(new Num(1), new Num(2))) == false);
            CHECK((new Add(new Num(1), new Num(2)))->equals(nullptr) == false);
            CHECK((new Mult(new Num(1), new Num(2)))->equals(nullptr) == false);
            CHECK((new Let("x", new Num(1), new Num(2)))->equals(nullptr) == false);
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
        CHECK_THROWS_WITH((new Var("x"))->interp(), "no value for variable" );
        CHECK_THROWS_WITH((new Var("abc"))->interp(), "no value for variable" );
    }

    SECTION("Let_interpret"){
        CHECK((new Let("x",
                       new Num(2),
                       new Add(new Var("x"), new Num(3))))
                    ->interp() == 5);
        CHECK((new Let("x",
                       new Num(2),
                       new Mult(new Add(new Var("x"), new Num(1)), new Num(3))))
                    ->interp() == 9);
        CHECK((new Let("x",
                       new Num(2),
                       new Add(new Num(3), new Num(3))))
                    ->interp() == 6);
        CHECK((new Let("x",
                       new Num(5),
                       new Add(new Let("y",
                                               new Num(3),
                                               new Add(new Var("y"),
                                                            new Num(2))),
                                    new Var("x"))))
                    ->interp() == 10);
        CHECK((new Add(new Mult(new Num(5),
                                    new Let("x",
                                                new Num(5),
                                                new Var("x"))),
                            new Num(1)))
                ->interp() == 26);
        CHECK_THROWS_WITH((new Let("x",
                                   new Num(2),
                                   new Add(new Var("y"), new Num(3))))
                                ->interp(), "no value for variable" );
    }

    SECTION("Mixed_interpret"){
        CHECK((new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp() == 65);
        CHECK_THROWS_WITH((new Add(new Add(new Var("x"), new Num(15)), new Add(new Num(20), new Num(20))))->interp(), "no value for variable");
        CHECK_THROWS_WITH((new Add(new Mult(new Var("x"), new Num(15)), new Add(new Num(20), new Num(20))))->interp(), "no value for variable");
        CHECK_THROWS_WITH((new Add(new Add(new Num(15), new Var("x")), new Add(new Num(20), new Num(20))))->interp(), "no value for variable");
        CHECK_THROWS_WITH((new Add(new Mult(new Num(15), new Var("x")), new Add(new Num(20), new Num(20))))->interp(), "no value for variable");
    }
}

TEST_CASE("Has_variable"){
    SECTION("Variable_has_variable"){
        CHECK((new Var("x"))->has_variable() == true);
        CHECK((new Var("y"))->has_variable() == true);
    }

    SECTION("Others_has_variable"){
        CHECK((new Num(1))->has_variable() == false);
        CHECK((new Num(0))->has_variable() == false);
        CHECK((new Add(new Num(1), new Num(2)))->has_variable() == false);
        CHECK((new Add(new Var("x"), new Num(2)))->has_variable() == true);
        CHECK((new Add(new Num(1), new Var("x")))->has_variable() == true);
        CHECK((new Mult(new Num(1), new Num(2)))->has_variable() == false);
        CHECK((new Mult(new Num(1), new Var("x")))->has_variable() == true);
        CHECK((new Let("x",
                       new Num(2),
                       new Add(new Var("y"), new Num(3))))
                    ->has_variable() == true);
        CHECK((new Let("x",
                       new Num(2),
                       new Add(new Var("x"), new Num(3))))
                    ->has_variable() == false);
    }

    SECTION("Mixed_has_variable"){
        CHECK((new Add(new Num(1), new Var("x")))->has_variable() == true);
        CHECK((new Mult(new Var("y"), new Num(2)))->has_variable() == true);
        CHECK((new Mult(new Add(new Num(10), new Num(15)),new Mult(new Num(20),new Num(20))))->has_variable() == false);
    }
}

TEST_CASE("Substitute"){
    CHECK((new Add(new Var("x"), new Num(7)))
                   ->subst("x", new Var("y"))
                   ->equals(new Add(new Var("y"), new Num(7))));
    CHECK((new Var("x"))
                   ->subst("x", new Add(new Var("y"), new Num(7)))
                   ->equals(new Add(new Var("y"), new Num(7))) );
    // x * (y * (x + 1)) => x = -2 => -2 * (y * (-2 + 1))
    CHECK((new Mult(new Var("x"), new Mult(new Var("y"), new Add(new Var("x"), new Num(1)))))
                  ->subst("x", new Num(-2))
                  ->equals(new Mult(new Num(-2), new Mult(new Var("y"), new Add(new Num(-2), new Num(1))))));
    SECTION("Other_substitute"){
        CHECK(((new Var("x"))->subst("x", new Num(2)))->interp() == 2);
        CHECK(((new Var("x"))->subst("x", new Mult(new Num(2), new Var("y")))->equals(new Mult(new Num(2), new Var("y")))));
        CHECK(((new Var("x"))->subst("y", new Num(2)))->equals(new Var("x")));
    }
    SECTION("Let_substitute"){
        CHECK((new Let("x",
                       new Add(new Var("x"), new Var("y")),
                       new Mult(new Var("x"), new Var("y"))))
                    ->subst("x",new Num(2))
                    ->equals(new Let("x", new Add(new Num(2), new Var("y")), new Mult(new Var("x"), new Var("y")))) == true);
        CHECK((new Let("x", new Add(new Var("x"), new Var("y")), new Mult(new Var("x"), new Var("y"))))
                  ->subst("y",new Num(3))
                  ->equals(new Let("x", new Add(new Var("x"), new Num(3)), new Mult(new Var("x"), new Num(3)))) == true);
    }
}

TEST_CASE("Precedence"){
    SECTION("Get_prec"){
        CHECK((new Num(1))->get_prec() == prec_none);
        CHECK((new Var("x"))->get_prec() == prec_none);
        CHECK((new Add(new Num(1), new Var("x")))->get_prec() == prec_add);
        CHECK((new Mult(new Num(1), new Var("x")))->get_prec() == prec_mult);
        CHECK((new Let("x",
                    new Add(new Var("x"), new Var("y")),
                   new Mult(new Var("x"), new Var("y"))))
                        ->get_prec() == prec_let);
    }
}


TEST_CASE("To_string"){
    SECTION("Print"){
        SECTION("Num_print"){
            CHECK((new Num(10))->to_string() == "10");
            CHECK((new Num(-10))->to_string() == "-10");
        }
        SECTION("Variable_print"){
            CHECK((new Var("x"))->to_string() == "x");
            CHECK((new Var("MAX"))->to_string() == "MAX");
        }
        SECTION("Add_print"){
            CHECK((new Add(new Num(10),new Num(12)))->to_string() == "(10+12)");
            CHECK((new Add(new Num(-10),new Num(-12)))->to_string() == "(-10+-12)");
            CHECK((new Add(new Num(10),new Var("x")))->to_string() == "(10+x)");
        }
        SECTION("Mult_print"){
            CHECK((new Mult(new Num(10),new Num(12)))->to_string() == "(10*12)");
            CHECK((new Mult(new Num(-10),new Num(-12)))->to_string() == "(-10*-12)");
            CHECK((new Mult(new Num(10),new Var("x")))->to_string() == "(10*x)");
        }
        SECTION("Mixed_print"){
            CHECK((new Mult(new Num(10),new Add(new Var("x"), new Num(12))))->to_string() == "(10*(x+12))");
        }
        SECTION("Let_print"){
            CHECK((new Let("x",
                           new Num(5),
                           new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                       ->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
            CHECK((new Add(new Mult(new Num(5), new Let("x",
                                                        new Num(5),
                                                        new Var("x"))), new Num(1)))
                          ->to_string() == "((5*(_let x=5 _in x))+1)");
            CHECK((new Mult(new Num(1234),
                            new Let("x", new Let("z",
                                                            new Num(2),
                                                            new Add(new Var("z"), new Num(5))),
                            new Add(new Let("y",
                                        new Num(3),
                                        new Add(new Var("y"), new Num(2))), new Var("x")))))
                        ->to_string() == "(1234*(_let x=(_let z=2 _in (z+5)) _in ((_let y=3 _in (y+2))+x)))");
        }

    }SECTION("Pretty_print"){
        SECTION("Num_pretty_print"){
            CHECK((new Num(10))->to_pretty_string() == "10");
            CHECK((new Num(-10))->to_pretty_string() == "-10");
        }
        SECTION("Variable_pretty_print"){
            CHECK((new Var("x"))->to_pretty_string() == "x");
            CHECK((new Var("MAX"))->to_pretty_string() == "MAX");
        }
        SECTION("Add_pretty_print"){
            CHECK((new Add(new Num(10),new Num(12)))->to_pretty_string() == "10 + 12");
            CHECK((new Add(new Num(-10),new Num(-12)))->to_pretty_string() == "-10 + -12");
            CHECK((new Add(new Num(10),new Var("x")))->to_pretty_string() == "10 + x");
        }
        SECTION("Mult_pretty_print"){
            CHECK((new Mult(new Num(10),new Num(12)))->to_pretty_string() == "10 * 12");
            CHECK((new Mult(new Num(-10),new Num(-12)))->to_pretty_string() == "-10 * -12");
            CHECK((new Mult(new Num(10),new Var("x")))->to_pretty_string() == "10 * x");
        }
        SECTION("Mixed_pretty_print"){
            SECTION("Add_in_between"){
                SECTION("None_add_none"){
                    CHECK((new Add(new Num(10),new Num(12)))->to_pretty_string() == "10 + 12");
                }
                SECTION("None_add_add"){
                    CHECK((new Add(new Num(10),new Add(new Num(12), new Var("x"))))->to_pretty_string() == "10 + 12 + x");
                }
                SECTION("None_add_mult"){
                    CHECK((new Add(new Num(10),new Mult(new Num(12), new Var("x"))))->to_pretty_string() == "10 + 12 * x");
                }
                SECTION("Add_add_none"){
                    CHECK((new Add(new Add(new Num(12), new Var("x")), new Num(10)))->to_pretty_string() == "(12 + x) + 10");
                }
                SECTION("Add_add_add"){
                    CHECK((new Add(new Add(new Num(12), new Var("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "(12 + x) + 10 + 1");
                }
                SECTION("Add_add_mult"){
                    CHECK((new Add(new Add(new Num(12), new Var("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "(12 + x) + 10 * 1");
                }
                SECTION("Mult_add_none"){
                    CHECK((new Add(new Mult(new Num(12), new Var("x")), new Num(10)))->to_pretty_string() == "12 * x + 10");
                }
                SECTION("Mult_add_add"){
                    CHECK((new Add(new Mult(new Num(12), new Var("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "12 * x + 10 + 1");
                }
                SECTION("Mult_add_mult"){
                    CHECK((new Add(new Mult(new Num(12), new Var("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "12 * x + 10 * 1");
                }
            }
            SECTION("Mult_in_between"){
                SECTION("None_mult_none"){
                    CHECK((new Mult(new Num(10),new Num(12)))->to_pretty_string() == "10 * 12");
                }
                SECTION("None_mult_add"){
                    CHECK((new Mult(new Num(10),new Add(new Num(12), new Var("x"))))->to_pretty_string() == "10 * (12 + x)");
                }
                SECTION("None_mult_mult"){
                    CHECK((new Mult(new Num(10),new Mult(new Num(12), new Var("x"))))->to_pretty_string() == "10 * 12 * x");
                }
                SECTION("Add_mult_none"){
                    CHECK((new Mult(new Add(new Num(12), new Var("x")), new Num(10)))->to_pretty_string() == "(12 + x) * 10");
                }
                SECTION("Add_mult_add"){
                    CHECK((new Mult(new Add(new Num(12), new Var("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "(12 + x) * (10 + 1)");
                }
                SECTION("Add_mult_mult"){
                    CHECK((new Mult(new Add(new Num(12), new Var("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "(12 + x) * 10 * 1");
                }
                SECTION("Mult_mult_none"){
                    CHECK((new Mult(new Mult(new Num(12), new Var("x")), new Num(10)))->to_pretty_string() == "(12 * x) * 10");
                }
                SECTION("Mult_mult_add"){
                    CHECK((new Mult(new Mult(new Num(12), new Var("x")), new Add(new Num(10), new Num(1))))->to_pretty_string() == "(12 * x) * (10 + 1)");
                }
                SECTION("Mult_mult_mult"){
                    CHECK((new Mult(new Mult(new Num(12), new Var("x")), new Mult(new Num(10), new Num(1))))->to_pretty_string() == "(12 * x) * 10 * 1");
                }
                SECTION("William")
                {
                    CHECK((new Mult( new Mult(new Num(10), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10))))->to_pretty_string()  == "(10 * (10 * 10) * 10) * 10 * 10");
                }
            }
        }
        SECTION("Let_pretty_print"){
            CHECK((new Let("x",
                           new Num(5),
                           new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                          ->to_pretty_string() == "_let x = 5\n"
                                                  "_in  (_let y = 3\n"
                                                  "      _in  y + 2) + x");
            CHECK((new Add(new Mult(new Num(5),
                                        new Let("x",
                                                    new Num(5),
                                                    new Var("x"))),
                            new Num(1)))
                          ->to_pretty_string() == "5 * (_let x = 5\n"
                                                  "     _in  x) + 1");
            CHECK((new Mult(new Num(1234),
                            new Let("x",
                                        new Let("z",
                                                     new Num(2),
                                                     new Add(new Var("z"),
                                                                        new Num(5))),
                                        new Add(new Let("y",
                                                                new Num(3),
                                                                new Add(new Var("y"),
                                                                                new Num(2))),
                                                        new Var("x")))))
                          ->to_pretty_string() == "1234 * _let x = _let z = 2\n"
                                                  "                _in  z + 5\n"
                                                  "       _in  (_let y = 3\n"
                                                  "             _in  y + 2) + x");
            CHECK((new Add(new Num(3),
                           new Add(new Num (2),
                                   new Add(new Let("x" ,
                                                   new Num(5),
                                                   new Var("x")),
                                           new Num(4)))))
                       ->to_pretty_string() == "3 + 2 + (_let x = 5\n"
                                               "         _in  x) + 4");
            CHECK((new Mult(new Num(5),
                            new Let("x",
                                        new Num(5),
                                        new Add(new Var("x"),
                                                        new Num(1)))))
                ->to_pretty_string() == "5 * _let x = 5\n"
                                        "    _in  x + 1");
            CHECK((new Add(new Num(3),
                           new Add(new Num (2),
                                   new Let("x" ,
                                           new Num(5),
                                           new Var("x")))))
                   ->to_pretty_string() == "3 + 2 + _let x = 5\n"
                                           "        _in  x");
            CHECK((new Add(new Add(new Num (2),
                                   new Let("x" ,
                                           new Num(5),
                                           new Var("x"))),
                           new Num(1)))
                       ->to_pretty_string() == "(2 + _let x = 5\n"
                                               "     _in  x) + 1");
            CHECK((new Add(new Mult(new Num(1234),
                                    new Let("x",
                                            new Let("z",
                                                    new Num(2),
                                                    new Add(new Var("z"),
                                                            new Num(5))),
                                            new Let("y",
                                                    new Num(3),
                                                    new Add(new Var("y"),
                                                            new Num(2)))
                                    )),new Var("x")))
                    ->to_pretty_string() == "1234 * (_let x = _let z = 2\n"
                                            "                 _in  z + 5\n"
                                            "        _in  _let y = 3\n"
                                            "             _in  y + 2) + x");
        }
    }

}


// TESTS from Kevin and William
TEST_CASE("TESTS from Kevin and William"){
    SECTION("Tests from examples"){
        std::stringstream out("");
        (new Let("x", new Num(5), new Add(new Var("x"), new Num(1))))->pretty_print(out);
        CHECK(out.str() == "_let x = 5\n"
                           "_in  x + 1");
        out.str(std::string());
        (new Add(new Let("x", new Num(5), new Var("x")), new Num(1)))->pretty_print(out);
        CHECK(out.str() == "(_let x = 5\n"
                           " _in  x) + 1");
        out.str(std::string());
        (new Mult(new Num(5), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))))->pretty_print(out);
        CHECK(out.str() == "5 * _let x = 5\n"
                           "    _in  x + 1");
        out.str(std::string());
        (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->pretty_print(out);
        CHECK(out.str() == "5 * (_let x = 5\n"
                           "     _in  x) + 1");
        out.str(std::string());
        (new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                ->pretty_print(out);

        CHECK(out.str() == "_let x = 5\n"
                           "_in  (_let y = 3\n"
                           "      _in  y + 2) + x");
        out.str(std::string());
        (new Let("x", new Let("y", new Num(6), new Mult(new Var("y"), new Num(2))),
                 new Add(new Var("x"), new Num(1))))->pretty_print(out);
        CHECK(out.str() == "_let x = _let y = 6\n"
                           "         _in  y * 2\n"
                           "_in  x + 1");
    }
    SECTION("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
        Let* tripleNestedLet = new Let("x", new Num(1),
                                       new Let("y", new Num(1),
                                               new Mult(new Add(new Var("x"), new Var("y")), new Var("z"))));
        Let* tripleNestedLet2 = new Let("x", new Num(1),
                                        new Let("y", new Num(1),
                                                new Let("z", new Add(new Var("x"), new Num(1)),
                                                        new Add(new Add(new Var("x"), new Var("y")), new Var("z")))));
        Let* tripleNestedLet3 = new Let("x", new Num(1),
                                        new Let("y", new Num(1),
                                                new Let("z", new Add(new Var("x"), new Num(1)),
                                                        new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))));


        CHECK(tripleNestedLet -> to_pretty_string() ==
              "_let x = 1\n"
              "_in  _let y = 1\n"
              "     _in  (x + y) * z"
        );
        CHECK(tripleNestedLet2 -> to_pretty_string() ==
              "_let x = 1\n"
              "_in  _let y = 1\n"
              "     _in  _let z = x + 1\n"
              "          _in  (x + y) + z"
        );
        CHECK(tripleNestedLet3 -> to_pretty_string() ==
              "_let x = 1\n"
              "_in  _let y = 1\n"
              "     _in  _let z = x + 1\n"
              "          _in  (x + y) * z"
        );
        Let* tripleNestedLet4 =new Let("x", new Num(5),
                                       new Let("y", new Num(3),
                                               new Add(new Var("y"), new Num(2))));
        Let* tripleNestedLet5 =new Let("x", new Num(5),
                                       new Add(new Let("y", new Num(3),
                                                       new Add(new Var("y"), new Num(2))), new Var("x")));
        std::stringstream out("");
        out.str("");
        tripleNestedLet4->pretty_print(out);
        CHECK(out.str() ==
              "_let x = 5\n"
              "_in  _let y = 3\n"
              "     _in  y + 2"
        );

        CHECK(tripleNestedLet5 -> to_pretty_string() == "_let x = 5\n"
                                                        "_in  (_let y = 3\n"
                                                        "      _in  y + 2) + x");
        SECTION("assignment_examples") {
            CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))-> to_pretty_string()
                   == "5 * (_let x = 5\n"
                      "     _in  x) + 1");
            CHECK( (new Mult(new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") ,new  Num(1)) )), new Num(3) )) -> to_pretty_string()
                   == "(2 * _let x = 5\n"
                      "     _in  x + 1) * 3");
            CHECK( (new Add(new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") ,new  Num(1)) )), new Num(3) )) -> to_pretty_string()
                   == "2 * (_let x = 5\n"
                      "     _in  x + 1) + 3");
        }
            // A _let needs parentheses when it is nested immediately as the right argument of an unparenthesized *
            // where _let would have needed parentheses in the surrounding context
            // (that is, if the _let used in place of the whole * would need parentheses,
            // then it still needs parentheses within the right-hand size of *).
        SECTION("new_edge") {
            CHECK( (new Mult(new Num (2), new Let("x", new Num(5), new Add(new Var("x") ,new  Num(1)) ) )) -> to_pretty_string()
                   == "2 * _let x = 5\n"
                      "    _in  x + 1");
            CHECK( (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1)))-> to_pretty_string()
                   == "5 * (_let x = 5\n"
                      "     _in  x * 2) + 1");
            CHECK( (new Mult((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1))), new Num(7)))-> to_pretty_string()
                   == "(5 * (_let x = 5\n"
                      "      _in  x * 2) + 1) * 7");
            CHECK( (new Let("x", new Num(10), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10)))))
                           ->to_pretty_string()  == "_let x = 10\n"
                                                    "_in  (x * (10 * 10) * 10) * 10 * 10");
            CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Num(10), new Num(10)))))
                           -> to_pretty_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * 10 * 10" );
            CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Var("y"), new Num(10)))))
                           -> to_pretty_string() == "_let x = 1\n"
                                                    "_in  (x * (10 * 10) * x) * y * 10" );
        }
    }
    SECTION("Let_equals_mine") {
        SECTION("Values_same") {
            REQUIRE( (new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) )));
        }
        SECTION("Values_same_different_rhs") {
            REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("x", new Num(5), new Add(new Num(2), new Var("x")) )));
        }
        SECTION("Values_same_different_lhs") {
            REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("y", new Num(4), new Add(new Num(2), new Var("x")) )));
        }
        SECTION("Values_same_different_body") {
            REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals(new Let("x", new Num(4), new Mult(new Num(3), new Var("y")) )));
        }
        SECTION("different_types") {
            REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->equals( new Mult(new Num(3), new Var("y")) ));
        }
    }
    SECTION("Let_has_variable_mine") {
        SECTION("has") {
            REQUIRE( (new Let("x", new Num(4), new Add(new Num(2), new Var("x")) ))->has_variable() == false);
        }
        SECTION("does_not_has") {
            REQUIRE( !(new Let("x", new Num(4), new Add(new Num(2), new Num(4)) ))->has_variable());
        }
    }
    SECTION("Let_print_mine") {
        CHECK( (new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x")))) -> to_string()
               == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK( (new Let("x", new Num(1),
                        new Let("y", new Num(1),
                                new Let("z", new Add(new Var("x"), new Num(1)),
                                        new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))))) -> to_string()
               == "(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
    }
    SECTION ("Let_interp_mine") {
        SECTION("hw_examples") {
            CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1))) -> interp() == 26);
            CHECK((new Mult(new Num(5), new Let("x", new Num(5), new Add(new Var("x"), new Num(1))))) -> interp() == 30);
        }
        SECTION("from_pretty_print_edge") {
            CHECK( (new Let("x", new Num(1),
                            new Let("y", new Num(1),
                                    new Let("z", new Add(new Var("x"), new Num(1)),
                                            new Mult(new Add(new Var("x"), new Var("y")), new Var("z")))))) -> interp() == 4);
            CHECK( (new Mult((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Mult(new Var("x"), new Num(2)))), new Num(1))), new Num(7))) -> interp() == 357); // 51 * 7
            CHECK( (new Let("x", new Num(10), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Num(10))), new Mult(new Num(10), new Num(10)))))
                           ->interp()  == 1000000);
            CHECK( (new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Num(10), new Num(10)))))
                           ->interp()  == 10000);
            CHECK_THROWS_WITH( ((new Let("x", new Num(1), new Mult( new Mult(new Var("x"), new Mult(new Mult(new Num(10), new Num(10)), new Var("x"))), new Mult(new Var("y"), new Num(10)))))
                                        -> interp() == 10000), "no value for variable");
        }
        SECTION("bypass_middle_let") {
            CHECK ((new Let("x", new Num(2), new Let("z", new Num(4), new Add(new Var("x"), new Num(10)))))
                           -> interp() == 12);
        }
    }

    SECTION("Pretty Print based on Matthew Flatt's examples"){
        std::stringstream out("");
        (new Let("x", new Num(5), new Add(new Var("x"), new Num(1))))->pretty_print(out);
        CHECK(out.str() == "_let x = 5\n"
                           "_in  x + 1");
        out.str(std::string());
        (new Add(new Let("x", new Num(5), new Var("x")), new Num(1)))->pretty_print(out);
        CHECK(out.str() == "(_let x = 5\n"
                           " _in  x) + 1");
        out.str(std::string());
        (new Mult(new Num(5), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))))->pretty_print(out);
        CHECK(out.str() == "5 * _let x = 5\n"
                           "    _in  x + 1");
        out.str(std::string());
        (new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->pretty_print(out);
        CHECK(out.str() == "5 * (_let x = 5\n"
                           "     _in  x) + 1");
        out.str(std::string());
        (new Let("x", new Num(5), new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                ->pretty_print(out);
        CHECK(out.str() == "_let x = 5\n"
                           "_in  (_let y = 3\n"
                           "      _in  y + 2) + x");
        out.str(std::string());
        (new Let("x", new Let("y", new Num(6), new Mult(new Var("y"), new Num(2))), new Add(new Var("x"), new Num(1))))->pretty_print(out);
        CHECK(out.str() == "_let x = _let y = 6\n"
                           "         _in  y * 2\n"
                           "_in  x + 1");
    }
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "invalid input" );

    CHECK( parse_str("(1)")->equals(new Num(1)) );
    CHECK( parse_str("(((1)))")->equals(new Num(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "invalid input" );

    CHECK( parse_str("1")->equals(new Num(1)) );
    CHECK( parse_str("10")->equals(new Num(10)) );
    CHECK( parse_str("-3")->equals(new Num(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("(((-1))"), "invalid input" );

    CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
    CHECK( parse_str("x")->equals(new Var("x")) );
    CHECK( parse_str("xyz")->equals(new Var("xyz")) );
    CHECK( parse_str("xYz")->equals(new Var("xYz")) );

    CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("1 2"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("1 x"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("1)"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("1+1)"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("1+1 2)"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("3+1-2)"), "invalid input" );
    CHECK_THROWS_WITH( parse_str("x!y"), "invalid input" );


    CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );
    CHECK( parse_str("x     + y")->equals(new Add(new Var("x"), new Var("y"))) );
    CHECK( parse_str("    x     + y ")->equals(new Add(new Var("x"), new Var("y"))) );
    CHECK( parse_str("x+y")->equals(new Add(new Var("x"), new Var("y"))) );
    CHECK( parse_str("(x+y)")->equals(new Add(new Var("x"), new Var("y"))) );

    CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                                    new Var("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(new Mult(new Var("z"),
                                     new Add(new Var("x"), new Var("y"))) ));

    CHECK(parse_str("3222") -> equals (new Num(3222)));
    CHECK(parse_str(" 1211") -> equals (new Num(1211)));
    CHECK(parse_str("-19 ") -> equals (new Num(-19)));
    CHECK(parse_str("( -3    )") -> equals (new Num(-3)));
    CHECK_THROWS_WITH(parse_str("(99"), "invalid input");

    CHECK(parse_str("2 + 1") -> equals (new Add(new Num(2), new Num(1))));
    CHECK(parse_str("-7 + 6") -> equals (new Add(new Num(-7), new Num(6))));
    CHECK(parse_str("(3 + 2)") -> equals (new Add(new Num(3), new Num(2))));
    CHECK(parse_str("   5+1") -> equals (new Add(new Num(5), new Num(1))));
    CHECK_THROWS_WITH(parse_str("(9 +"), "invalid input");
    CHECK_THROWS_WITH(parse_str("(9 +1"), "invalid input");
    CHECK_THROWS_WITH(parse_str("9 +)"), "invalid input");

    CHECK(parse_str("6 * 12") -> equals (new Mult(new Num(6), new Num(12))));
    CHECK(parse_str("-1*2") -> equals (new Mult(new Num(-1), new Num(2))));
    CHECK(parse_str("(-8)*  4") -> equals (new Mult(new Num(-8), new Num(4))));
    CHECK(parse_str("(2  * 1)") -> equals (new Mult(new Num(2), new Num(1))));
    CHECK_THROWS_WITH(parse_str("(2  * 1"), "invalid input");
    CHECK_THROWS_WITH(parse_str("2  * 1)"), "invalid input");

    CHECK(parse_str("cat") -> equals (new Var("cat")));
    CHECK(parse_str("  dog") -> equals (new Var("dog")));
    CHECK(parse_str("OWLS") -> equals (new Var("OWLS")));
    CHECK_THROWS_WITH(parse_str("mo.ngo"), "invalid input");

    CHECK(parse_str("_let x = 5 _in x+2") -> equals
            (new Let("x", new Num(5),
                      new Add(new Var("x"), new Num(2)))));
    CHECK(parse_str("_let x = (x+2) _in      (x+-3)") -> equals
            (new Let("x", new Add(new Var("x"), new Num(2)),
                      new Add(new Var("x"), new Num(-3)))));
    CHECK_THROWS_WITH(parse_str("_let x = 1    _i"), "variable _in is required");


    CHECK(parse_str("6 + (2 * -7)") -> equals(new Add(new Num(6),
                                                  new Mult(new Num(2), new Num(-7)))));
    CHECK(parse_str("(-3)  +  4 * (_let x = 2 _in x+1)") -> equals(
            new Add(new Num(-3), new Mult(new Num(4),
                                          new Let("x", new Num(2),
                                                   new Add(new Var("x"), new Num(1)))))));
    CHECK(parse_str("(1234*((_let x=1_in x+-2)+7))") -> equals(
            new Mult(new Num(1234),
                     new Add(new Let("x", new Num(1),
                                      new Add(new Var("x"), new Num(-2))),
                             new Num(7)))));
    //TODO
    // don't know the standard for parsing negative number/ minus : 3+1-2 (valid or not?)
}

