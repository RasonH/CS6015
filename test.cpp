//
// Created by Rason Hung on 1/29/23.
//

#pragma include once

#include "catch.h"
#include "expr.h"
#include "parse.h"
#include "val.h"

TEST_CASE("Equals") {
	SECTION("Num_equals") {
		SECTION("Normal_cases") {
			CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true);
			CHECK((new NumExpr(1))->equals(new NumExpr(2)) == false);
			CHECK((new NumExpr(1))->equals(new NumExpr(-1)) == false);
			CHECK((new NumExpr(1))->equals(new NumExpr(0)) == false);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((new NumExpr(1))
					  ->equals(new AddExpr(new NumExpr(1), new NumExpr(1))) == false);
			CHECK((new NumExpr(1))
					  ->equals(new MultExpr(new NumExpr(1), new NumExpr(1))) ==
				false);
			CHECK((new NumExpr(1))->equals(new VarExpr("x")) == false);
		}
	}

	SECTION("Add_equals") {
		SECTION("Normal_cases") {
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) == true);
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new AddExpr(new NumExpr(2), new NumExpr(2))) == false);
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new AddExpr(new NumExpr(1), new NumExpr(3))) == false);
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new AddExpr(new NumExpr(2), new NumExpr(1))) == false);
			CHECK((new AddExpr(new NumExpr(1),
							   (new AddExpr(new NumExpr(2), new NumExpr(3)))))
					  ->equals(new AddExpr(
						  new NumExpr(1),
						  (new AddExpr(new NumExpr(2), new NumExpr(3))))) == true);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new NumExpr(2)) == false);
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new MultExpr(new NumExpr(1), new NumExpr(2))) ==
				false);
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new VarExpr("x")) == false);
		}
	}

	SECTION("Mult_equals") {
		SECTION("Normal_cases") {
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new MultExpr(new NumExpr(1), new NumExpr(2))) == true);
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new MultExpr(new NumExpr(2), new NumExpr(2))) ==
				false);
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new MultExpr(new NumExpr(1), new NumExpr(3))) ==
				false);
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new MultExpr(new NumExpr(2), new NumExpr(1))) ==
				false);
			CHECK((new MultExpr(new NumExpr(1),
								(new MultExpr(new NumExpr(2), new NumExpr(3)))))
					  ->equals(new MultExpr(
						  new NumExpr(1),
						  (new MultExpr(new NumExpr(2), new NumExpr(3))))) == true);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new NumExpr(2)) == false);
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) == false);
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))
					  ->equals(new VarExpr("x")) == false);
		}
	}

	SECTION("Variable_equals") {
		SECTION("Normal_cases") {
			CHECK((new VarExpr("x"))->equals(new VarExpr("x")) == true);
			CHECK((new VarExpr("x"))->equals(new VarExpr("X")) == false);
			CHECK((new VarExpr("x"))->equals(new VarExpr("y")) == false);
			CHECK((new VarExpr("x"))->equals(new VarExpr("xa")) == false);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((new VarExpr("x"))->equals(new NumExpr(1)) == false);
			CHECK((new VarExpr("x"))
					  ->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) == false);
			CHECK((new VarExpr("x"))
					  ->equals(new MultExpr(new NumExpr(1), new NumExpr(2))) ==
				false);
		}
	}

	SECTION("Let_equals") {
		SECTION("Normal_cases") {
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new LetExpr(
						  "x", new NumExpr(2),
						  new AddExpr(new VarExpr("x"), new NumExpr(3)))) == true);
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new LetExpr(
						  "y", new NumExpr(2),
						  new AddExpr(new VarExpr("x"), new NumExpr(3)))) == false);
			CHECK((new LetExpr("x", new NumExpr(3),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new LetExpr(
						  "x", new NumExpr(2),
						  new AddExpr(new VarExpr("x"), new NumExpr(3)))) == false);
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new LetExpr(
						  "x", new NumExpr(2),
						  new MultExpr(new VarExpr("x"), new NumExpr(3)))) == false);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new NumExpr(2)) == false);
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new AddExpr(new VarExpr("x"), new NumExpr(3))) ==
				false);
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new MultExpr(new VarExpr("x"), new NumExpr(3))) ==
				false);
			CHECK((new LetExpr("x", new NumExpr(2),
							   new AddExpr(new VarExpr("x"), new NumExpr(3))))
					  ->equals(new VarExpr("x")) == false);
		}
	}

	SECTION("Mixed_equals") {
		CHECK((new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
						   new VarExpr("x")))
				  ->equals(new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
									   new VarExpr("x"))) == true);
		CHECK((new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
						   new VarExpr("x")))
				  ->equals(new AddExpr(
					  new VarExpr("x"),
					  new MultExpr(new NumExpr(1), new NumExpr(2)))) == false);

		// changed some components but not order
		CHECK((new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
						   new VarExpr("x")))
				  ->equals(new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
									   new VarExpr("y"))) == false);
		CHECK((new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
						   new VarExpr("x")))
				  ->equals(new AddExpr(new MultExpr(new NumExpr(2), new NumExpr(2)),
									   new VarExpr("x"))) == false);
		CHECK((new AddExpr(new MultExpr(new NumExpr(1), new NumExpr(2)),
						   new VarExpr("x")))
				  ->equals(new MultExpr(new AddExpr(new NumExpr(1), new NumExpr(2)),
										new VarExpr("x"))) == false);

		// changed expression order
		CHECK((new MultExpr(new AddExpr(new NumExpr(1), new NumExpr(2)),
							new VarExpr("x")))
				  ->equals(new MultExpr(new AddExpr(new NumExpr(1), new NumExpr(2)),
										new VarExpr("x"))) == true);
	}SECTION("Invalid_argument_equals") {
		SECTION("Nullptr") {
			CHECK((new NumExpr(2))
					  ->equals(new AddExpr(new NumExpr(1), new NumExpr(2))) == false);
			CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->equals(nullptr) ==
				false);
			CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->equals(nullptr) ==
				false);
			CHECK(
				(new LetExpr("x", new NumExpr(1), new NumExpr(2)))->equals(nullptr) ==
					false);
		}
	}
}

TEST_CASE("Interpret") {
	SECTION("Num_interpret") {
		CHECK((new NumExpr(1))->interp()->equals(new NumVal(1)));
		CHECK((new NumExpr(0))->interp()->equals(new NumVal(0)));
		CHECK((new NumExpr(-1))->interp()->equals(new NumVal(-1)));
	}

	SECTION("Add_interpret") {
		CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
				  ->interp()
				  ->equals(new NumVal(3)));
		CHECK((new AddExpr(new NumExpr(1), new NumExpr(-1)))
				  ->interp()
				  ->equals(new NumVal(0)));
		CHECK((new AddExpr(new NumExpr(-5), new NumExpr(-1)))
				  ->interp()
				  ->equals(new NumVal(-6)));
	}

	SECTION("Mult_interpret") {
		CHECK((new MultExpr(new NumExpr(3), new NumExpr(2)))
				  ->interp()
				  ->equals(new NumVal(6)));
		CHECK((new MultExpr(new NumExpr(3), new NumExpr(0)))
				  ->interp()
				  ->equals(new NumVal(0)));
		CHECK((new MultExpr(new NumExpr(5), new NumExpr(2)))
				  ->interp()
				  ->equals(new NumVal(10)));
		CHECK((new MultExpr(new NumExpr(-5), new NumExpr(2)))
				  ->interp()
				  ->equals(new NumVal(-10)));
	}

	SECTION("Variable_interpret") {
		CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "no value for variable");
		CHECK_THROWS_WITH((new VarExpr("abc"))->interp(), "no value for variable");
	}

	SECTION("Let_interpret") {
		CHECK((new LetExpr("x", new NumExpr(2),
						   new AddExpr(new VarExpr("x"), new NumExpr(3))))
				  ->interp()
				  ->equals(new NumVal(5)));
		CHECK(
			(new LetExpr("x", new NumExpr(2),
						 new MultExpr(new AddExpr(new VarExpr("x"), new NumExpr(1)),
									  new NumExpr(3))))
				->interp()
				->equals(new NumVal(9)));
		CHECK((new LetExpr("x", new NumExpr(2),
						   new AddExpr(new NumExpr(3), new NumExpr(3))))
				  ->interp()
				  ->equals(new NumVal(6)));
		CHECK((new LetExpr("x", new NumExpr(5),
						   new AddExpr(new LetExpr("y", new NumExpr(3),
												   new AddExpr(new VarExpr("y"),
															   new NumExpr(2))),
									   new VarExpr("x"))))
				  ->interp()
				  ->equals(new NumVal(10)));
		CHECK((new AddExpr(
			new MultExpr(new NumExpr(5),
						 new LetExpr("x", new NumExpr(5), new VarExpr("x"))),
			new NumExpr(1)))
				  ->interp()
				  ->equals(new NumVal(26)));
		CHECK_THROWS_WITH(
			(new LetExpr("x", new NumExpr(2),
						 new AddExpr(new VarExpr("y"), new NumExpr(3))))
				->interp(),
			"no value for variable");
	}

	SECTION("Mixed_interpret") {
		CHECK((new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),
						   new AddExpr(new NumExpr(20), new NumExpr(20))))
				  ->interp()
				  ->equals(new NumVal(65)));
		CHECK_THROWS_WITH(
			(new AddExpr(new AddExpr(new VarExpr("x"), new NumExpr(15)),
						 new AddExpr(new NumExpr(20), new NumExpr(20))))
				->interp(),
			"no value for variable");
		CHECK_THROWS_WITH(
			(new AddExpr(new MultExpr(new VarExpr("x"), new NumExpr(15)),
						 new AddExpr(new NumExpr(20), new NumExpr(20))))
				->interp(),
			"no value for variable");
		CHECK_THROWS_WITH(
			(new AddExpr(new AddExpr(new NumExpr(15), new VarExpr("x")),
						 new AddExpr(new NumExpr(20), new NumExpr(20))))
				->interp(),
			"no value for variable");
		CHECK_THROWS_WITH(
			(new AddExpr(new MultExpr(new NumExpr(15), new VarExpr("x")),
						 new AddExpr(new NumExpr(20), new NumExpr(20))))
				->interp(),
			"no value for variable");
	}
}

//TEST_CASE("Has_variable") {
//	SECTION("Variable_has_variable") {
//		CHECK((new VarExpr("x"))->has_variable() == true);
//		CHECK((new VarExpr("y"))->has_variable() == true);
//	}
//
//	SECTION("Others_has_variable") {
//		CHECK((new NumExpr(1))->has_variable() == false);
//		CHECK((new NumExpr(0))->has_variable() == false);
//		CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))->has_variable() ==
//			false);
//		CHECK((new AddExpr(new VarExpr("x"), new NumExpr(2)))->has_variable() ==
//			true);
//		CHECK((new AddExpr(new NumExpr(1), new VarExpr("x")))->has_variable() ==
//			true);
//		CHECK((new MultExpr(new NumExpr(1), new NumExpr(2)))->has_variable() ==
//			false);
//		CHECK((new MultExpr(new NumExpr(1), new VarExpr("x")))->has_variable() ==
//			true);
//		CHECK((new LetExpr("x", new NumExpr(2),
//						   new AddExpr(new VarExpr("y"), new NumExpr(3))))
//				  ->has_variable() == true);
//		CHECK((new LetExpr("x", new NumExpr(2),
//						   new AddExpr(new VarExpr("x"), new NumExpr(3))))
//				  ->has_variable() == false);
//	}
//
//	SECTION("Mixed_has_variable") {
//		CHECK((new AddExpr(new NumExpr(1), new VarExpr("x")))->has_variable() ==
//			true);
//		CHECK((new MultExpr(new VarExpr("y"), new NumExpr(2)))->has_variable() ==
//			true);
//		CHECK((new MultExpr(new AddExpr(new NumExpr(10), new NumExpr(15)),
//							new MultExpr(new NumExpr(20), new NumExpr(20))))
//				  ->has_variable() == false);
//	}
//}

TEST_CASE("Substitute") {
	CHECK((new AddExpr(new VarExpr("x"), new NumExpr(7)))
			  ->subst("x", new VarExpr("y"))
			  ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
	CHECK((new VarExpr("x"))
			  ->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
			  ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
	// x * (y * (x + 1)) => x = -2 => -2 * (y * (-2 + 1))
	CHECK((new MultExpr(
		new VarExpr("x"),
		new MultExpr(new VarExpr("y"),
					 new AddExpr(new VarExpr("x"), new NumExpr(1)))))
			  ->subst("x", new NumExpr(-2))
			  ->equals(new MultExpr(
				  new NumExpr(-2),
				  new MultExpr(new VarExpr("y"),
							   new AddExpr(new NumExpr(-2), new NumExpr(1))))));
	SECTION("Other_substitute") {
		CHECK(((new VarExpr("x"))->subst("x", new NumExpr(2)))
				  ->interp()
				  ->equals(new NumVal(2)));
		CHECK(((new VarExpr("x"))
			->subst("x", new MultExpr(new NumExpr(2), new VarExpr("y")))
			->equals(new MultExpr(new NumExpr(2), new VarExpr("y")))));
		CHECK(((new VarExpr("x"))->subst("y", new NumExpr(2)))
				  ->equals(new VarExpr("x")));
	}SECTION("Let_substitute") {
		CHECK((new LetExpr("x", new AddExpr(new VarExpr("x"), new VarExpr("y")),
						   new MultExpr(new VarExpr("x"), new VarExpr("y"))))
				  ->subst("x", new NumExpr(2))
				  ->equals(new LetExpr(
					  "x", new AddExpr(new NumExpr(2), new VarExpr("y")),
					  new MultExpr(new VarExpr("x"), new VarExpr("y")))) == true);
		CHECK((new LetExpr("x", new AddExpr(new VarExpr("x"), new VarExpr("y")),
						   new MultExpr(new VarExpr("x"), new VarExpr("y"))))
				  ->subst("y", new NumExpr(3))
				  ->equals(new LetExpr(
					  "x", new AddExpr(new VarExpr("x"), new NumExpr(3)),
					  new MultExpr(new VarExpr("x"), new NumExpr(3)))) == true);
	}
}

TEST_CASE("Precedence") {
	SECTION("Get_prec") {
		CHECK((new NumExpr(1))->get_prec() == prec_none);
		CHECK((new VarExpr("x"))->get_prec() == prec_none);
		CHECK((new AddExpr(new NumExpr(1), new VarExpr("x")))->get_prec() ==
			prec_add);
		CHECK((new MultExpr(new NumExpr(1), new VarExpr("x")))->get_prec() ==
			prec_mult);
		CHECK((new LetExpr("x", new AddExpr(new VarExpr("x"), new VarExpr("y")),
						   new MultExpr(new VarExpr("x"), new VarExpr("y"))))
				  ->get_prec() == prec_keywords);
	}
}

TEST_CASE("To_string") {
	SECTION("Print") {
		SECTION("Num_print") {
			CHECK((new NumExpr(10))->to_string() == "10");
			CHECK((new NumExpr(-10))->to_string() == "-10");
		}SECTION("Variable_print") {
			CHECK((new VarExpr("x"))->to_string() == "x");
			CHECK((new VarExpr("MAX"))->to_string() == "MAX");
		}SECTION("Add_print") {
			CHECK((new AddExpr(new NumExpr(10), new NumExpr(12)))->to_string() ==
				"(10+12)");
			CHECK((new AddExpr(new NumExpr(-10), new NumExpr(-12)))->to_string() ==
				"(-10+-12)");
			CHECK((new AddExpr(new NumExpr(10), new VarExpr("x")))->to_string() ==
				"(10+x)");
		}SECTION("Mult_print") {
			CHECK((new MultExpr(new NumExpr(10), new NumExpr(12)))->to_string() ==
				"(10*12)");
			CHECK((new MultExpr(new NumExpr(-10), new NumExpr(-12)))->to_string() ==
				"(-10*-12)");
			CHECK((new MultExpr(new NumExpr(10), new VarExpr("x")))->to_string() ==
				"(10*x)");
		}SECTION("Mixed_print") {
			CHECK((new MultExpr(new NumExpr(10),
								new AddExpr(new VarExpr("x"), new NumExpr(12))))
					  ->to_string() == "(10*(x+12))");
		}SECTION("Let_print") {
			CHECK((new LetExpr("x", new NumExpr(5),
							   new AddExpr(new LetExpr("y", new NumExpr(3),
													   new AddExpr(new VarExpr("y"),
																   new NumExpr(2))),
										   new VarExpr("x"))))
					  ->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
			CHECK((new AddExpr(
				new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
														 new VarExpr("x"))),
				new NumExpr(1)))
					  ->to_string() == "((5*(_let x=5 _in x))+1)");
			CHECK(
				(new MultExpr(
					new NumExpr(1234),
					new LetExpr(
						"x",
						new LetExpr("z", new NumExpr(2),
									new AddExpr(new VarExpr("z"), new NumExpr(5))),
						new AddExpr(new LetExpr("y", new NumExpr(3),
												new AddExpr(new VarExpr("y"),
															new NumExpr(2))),
									new VarExpr("x")))))
					->to_string() ==
					"(1234*(_let x=(_let z=2 _in (z+5)) _in ((_let y=3 _in (y+2))+x)))");
		}
	}SECTION("Pretty_print") {
		SECTION("Num_pretty_print") {
			CHECK((new NumExpr(10))->to_pretty_string() == "10");
			CHECK((new NumExpr(-10))->to_pretty_string() == "-10");
		}SECTION("Variable_pretty_print") {
			CHECK((new VarExpr("x"))->to_pretty_string() == "x");
			CHECK((new VarExpr("MAX"))->to_pretty_string() == "MAX");
		}SECTION("Add_pretty_print") {
			CHECK(
				(new AddExpr(new NumExpr(10), new NumExpr(12)))->to_pretty_string() ==
					"10 + 12");
			CHECK((new AddExpr(new NumExpr(-10), new NumExpr(-12)))
					  ->to_pretty_string() == "-10 + -12");
			CHECK((new AddExpr(new NumExpr(10), new VarExpr("x")))
					  ->to_pretty_string() == "10 + x");
		}SECTION("Mult_pretty_print") {
			CHECK((new MultExpr(new NumExpr(10), new NumExpr(12)))
					  ->to_pretty_string() == "10 * 12");
			CHECK((new MultExpr(new NumExpr(-10), new NumExpr(-12)))
					  ->to_pretty_string() == "-10 * -12");
			CHECK((new MultExpr(new NumExpr(10), new VarExpr("x")))
					  ->to_pretty_string() == "10 * x");
		}SECTION("Mixed_pretty_print") {
			SECTION("Add_in_between") {
				SECTION("None_add_none") {
					CHECK((new AddExpr(new NumExpr(10), new NumExpr(12)))
							  ->to_pretty_string() == "10 + 12");
				}SECTION("None_add_add") {
					CHECK((new AddExpr(new NumExpr(10),
									   new AddExpr(new NumExpr(12), new VarExpr("x"))))
							  ->to_pretty_string() == "10 + 12 + x");
				}SECTION("None_add_mult") {
					CHECK((new AddExpr(new NumExpr(10),
									   new MultExpr(new NumExpr(12), new VarExpr("x"))))
							  ->to_pretty_string() == "10 + 12 * x");
				}SECTION("Add_add_none") {
					CHECK((new AddExpr(new AddExpr(new NumExpr(12), new VarExpr("x")),
									   new NumExpr(10)))
							  ->to_pretty_string() == "(12 + x) + 10");
				}SECTION("Add_add_add") {
					CHECK((new AddExpr(new AddExpr(new NumExpr(12), new VarExpr("x")),
									   new AddExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "(12 + x) + 10 + 1");
				}SECTION("Add_add_mult") {
					CHECK((new AddExpr(new AddExpr(new NumExpr(12), new VarExpr("x")),
									   new MultExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "(12 + x) + 10 * 1");
				}SECTION("Mult_add_none") {
					CHECK((new AddExpr(new MultExpr(new NumExpr(12), new VarExpr("x")),
									   new NumExpr(10)))
							  ->to_pretty_string() == "12 * x + 10");
				}SECTION("Mult_add_add") {
					CHECK((new AddExpr(new MultExpr(new NumExpr(12), new VarExpr("x")),
									   new AddExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "12 * x + 10 + 1");
				}SECTION("Mult_add_mult") {
					CHECK((new AddExpr(new MultExpr(new NumExpr(12), new VarExpr("x")),
									   new MultExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "12 * x + 10 * 1");
				}
			}SECTION("Mult_in_between") {
				SECTION("None_mult_none") {
					CHECK((new MultExpr(new NumExpr(10), new NumExpr(12)))
							  ->to_pretty_string() == "10 * 12");
				}SECTION("None_mult_add") {
					CHECK((new MultExpr(new NumExpr(10),
										new AddExpr(new NumExpr(12), new VarExpr("x"))))
							  ->to_pretty_string() == "10 * (12 + x)");
				}SECTION("None_mult_mult") {
					CHECK((new MultExpr(new NumExpr(10),
										new MultExpr(new NumExpr(12), new VarExpr("x"))))
							  ->to_pretty_string() == "10 * 12 * x");
				}SECTION("Add_mult_none") {
					CHECK((new MultExpr(new AddExpr(new NumExpr(12), new VarExpr("x")),
										new NumExpr(10)))
							  ->to_pretty_string() == "(12 + x) * 10");
				}SECTION("Add_mult_add") {
					CHECK((new MultExpr(new AddExpr(new NumExpr(12), new VarExpr("x")),
										new AddExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "(12 + x) * (10 + 1)");
				}SECTION("Add_mult_mult") {
					CHECK((new MultExpr(new AddExpr(new NumExpr(12), new VarExpr("x")),
										new MultExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "(12 + x) * 10 * 1");
				}SECTION("Mult_mult_none") {
					CHECK((new MultExpr(new MultExpr(new NumExpr(12), new VarExpr("x")),
										new NumExpr(10)))
							  ->to_pretty_string() == "(12 * x) * 10");
				}SECTION("Mult_mult_add") {
					CHECK((new MultExpr(new MultExpr(new NumExpr(12), new VarExpr("x")),
										new AddExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "(12 * x) * (10 + 1)");
				}SECTION("Mult_mult_mult") {
					CHECK((new MultExpr(new MultExpr(new NumExpr(12), new VarExpr("x")),
										new MultExpr(new NumExpr(10), new NumExpr(1))))
							  ->to_pretty_string() == "(12 * x) * 10 * 1");
				}SECTION("William") {
					CHECK((new MultExpr(
						new MultExpr(new NumExpr(10),
									 new MultExpr(new MultExpr(new NumExpr(10),
															   new NumExpr(10)),
												  new NumExpr(10))),
						new MultExpr(new NumExpr(10), new NumExpr(10))))
							  ->to_pretty_string() == "(10 * (10 * 10) * 10) * 10 * 10");
				}
			}
		}SECTION("Let_pretty_print") {
			CHECK((new LetExpr("x", new NumExpr(5),
							   new AddExpr(new LetExpr("y", new NumExpr(3),
													   new AddExpr(new VarExpr("y"),
																   new NumExpr(2))),
										   new VarExpr("x"))))
					  ->to_pretty_string() == "_let x = 5\n"
											  "_in  (_let y = 3\n"
											  "      _in  y + 2) + x");
			CHECK((new AddExpr(
				new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
														 new VarExpr("x"))),
				new NumExpr(1)))
					  ->to_pretty_string() == "5 * (_let x = 5\n"
											  "     _in  x) + 1");
			CHECK((new MultExpr(
				new NumExpr(1234),
				new LetExpr(
					"x",
					new LetExpr("z", new NumExpr(2),
								new AddExpr(new VarExpr("z"), new NumExpr(5))),
					new AddExpr(new LetExpr("y", new NumExpr(3),
											new AddExpr(new VarExpr("y"),
														new NumExpr(2))),
								new VarExpr("x")))))
					  ->to_pretty_string() == "1234 * _let x = _let z = 2\n"
											  "                _in  z + 5\n"
											  "       _in  (_let y = 3\n"
											  "             _in  y + 2) + x");
			CHECK(
				(new AddExpr(new NumExpr(3),
							 new AddExpr(new NumExpr(2),
										 new AddExpr(new LetExpr("x", new NumExpr(5),
																 new VarExpr("x")),
													 new NumExpr(4)))))
					->to_pretty_string() == "3 + 2 + (_let x = 5\n"
											"         _in  x) + 4");
			CHECK((new MultExpr(
				new NumExpr(5),
				new LetExpr("x", new NumExpr(5),
							new AddExpr(new VarExpr("x"), new NumExpr(1)))))
					  ->to_pretty_string() == "5 * _let x = 5\n"
											  "    _in  x + 1");
			CHECK((new AddExpr(
				new NumExpr(3),
				new AddExpr(new NumExpr(2), new LetExpr("x", new NumExpr(5),
														new VarExpr("x")))))
					  ->to_pretty_string() == "3 + 2 + _let x = 5\n"
											  "        _in  x");
			CHECK((new AddExpr(
				new AddExpr(new NumExpr(2), new LetExpr("x", new NumExpr(5),
														new VarExpr("x"))),
				new NumExpr(1)))
					  ->to_pretty_string() == "(2 + _let x = 5\n"
											  "     _in  x) + 1");
			CHECK((new AddExpr(
				new MultExpr(
					new NumExpr(1234),
					new LetExpr("x",
								new LetExpr("z", new NumExpr(2),
											new AddExpr(new VarExpr("z"),
														new NumExpr(5))),
								new LetExpr("y", new NumExpr(3),
											new AddExpr(new VarExpr("y"),
														new NumExpr(2))))),
				new VarExpr("x")))
					  ->to_pretty_string() == "1234 * (_let x = _let z = 2\n"
											  "                 _in  z + 5\n"
											  "        _in  _let y = 3\n"
											  "             _in  y + 2) + x");
		}
	}
}

// TESTS from Kevin and William
TEST_CASE("TESTS from Kevin and William") {
	SECTION("Tests from examples") {
		std::stringstream out("");
		(new LetExpr("x", new NumExpr(5),
					 new AddExpr(new VarExpr("x"), new NumExpr(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  x + 1");
		out.str(std::string());
		(new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")),
					 new NumExpr(1)))
			->pretty_print(out);
		CHECK(out.str() == "(_let x = 5\n"
						   " _in  x) + 1");
		out.str(std::string());
		(new MultExpr(new NumExpr(5),
					  new LetExpr("x", new NumExpr(5),
								  new AddExpr(new VarExpr("x"), new NumExpr(1)))))
			->pretty_print(out);
		CHECK(out.str() == "5 * _let x = 5\n"
						   "    _in  x + 1");
		out.str(std::string());
		(new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
															  new VarExpr("x"))),
					 new NumExpr(1)))
			->pretty_print(out);
		CHECK(out.str() == "5 * (_let x = 5\n"
						   "     _in  x) + 1");
		out.str(std::string());
		(new LetExpr(
			"x", new NumExpr(5),
			new AddExpr(new LetExpr("y", new NumExpr(3),
									new AddExpr(new VarExpr("y"), new NumExpr(2))),
						new VarExpr("x"))))
			->pretty_print(out);

		CHECK(out.str() == "_let x = 5\n"
						   "_in  (_let y = 3\n"
						   "      _in  y + 2) + x");
		out.str(std::string());
		(new LetExpr("x",
					 new LetExpr("y", new NumExpr(6),
								 new MultExpr(new VarExpr("y"), new NumExpr(2))),
					 new AddExpr(new VarExpr("x"), new NumExpr(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = _let y = 6\n"
						   "         _in  y * 2\n"
						   "_in  x + 1");
	}SECTION("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
		LetExpr *tripleNestedLet =
			new LetExpr("x", new NumExpr(1),
						new LetExpr("y", new NumExpr(1),
									new MultExpr(new AddExpr(new VarExpr("x"),
															 new VarExpr("y")),
												 new VarExpr("z"))));
		LetExpr *tripleNestedLet2 = new LetExpr(
			"x", new NumExpr(1),
			new LetExpr(
				"y", new NumExpr(1),
				new LetExpr(
					"z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
					new AddExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")),
								new VarExpr("z")))));
		LetExpr *tripleNestedLet3 = new LetExpr(
			"x", new NumExpr(1),
			new LetExpr(
				"y", new NumExpr(1),
				new LetExpr(
					"z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
					new MultExpr(new AddExpr(new VarExpr("x"), new VarExpr("y")),
								 new VarExpr("z")))));

		CHECK(tripleNestedLet->to_pretty_string() == "_let x = 1\n"
													 "_in  _let y = 1\n"
													 "     _in  (x + y) * z");
		CHECK(tripleNestedLet2->to_pretty_string() == "_let x = 1\n"
													  "_in  _let y = 1\n"
													  "     _in  _let z = x + 1\n"
													  "          _in  (x + y) + z");
		CHECK(tripleNestedLet3->to_pretty_string() == "_let x = 1\n"
													  "_in  _let y = 1\n"
													  "     _in  _let z = x + 1\n"
													  "          _in  (x + y) * z");
		LetExpr *tripleNestedLet4 =
			new LetExpr("x", new NumExpr(5),
						new LetExpr("y", new NumExpr(3),
									new AddExpr(new VarExpr("y"), new NumExpr(2))));
		LetExpr *tripleNestedLet5 = new LetExpr(
			"x", new NumExpr(5),
			new AddExpr(new LetExpr("y", new NumExpr(3),
									new AddExpr(new VarExpr("y"), new NumExpr(2))),
						new VarExpr("x")));
		std::stringstream out("");
		out.str("");
		tripleNestedLet4->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  _let y = 3\n"
						   "     _in  y + 2");

		CHECK(tripleNestedLet5->to_pretty_string() == "_let x = 5\n"
													  "_in  (_let y = 3\n"
													  "      _in  y + 2) + x");
		SECTION("assignment_examples") {
			CHECK((new AddExpr(
				new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
														 new VarExpr("x"))),
				new NumExpr(1)))
					  ->to_pretty_string() == "5 * (_let x = 5\n"
											  "     _in  x) + 1");
			CHECK(
				(new MultExpr(new MultExpr(new NumExpr(2),
										   new LetExpr("x", new NumExpr(5),
													   new AddExpr(new VarExpr("x"),
																   new NumExpr(1)))),
							  new NumExpr(3)))
					->to_pretty_string() == "(2 * _let x = 5\n"
											"     _in  x + 1) * 3");
			CHECK((new AddExpr(new MultExpr(new NumExpr(2),
											new LetExpr("x", new NumExpr(5),
														new AddExpr(new VarExpr("x"),
																	new NumExpr(1)))),
							   new NumExpr(3)))
					  ->to_pretty_string() == "2 * (_let x = 5\n"
											  "     _in  x + 1) + 3");
		}
			// A _let needs parentheses when it is nested immediately as the right
			// argument of an unparenthesized * where _let would have needed parentheses
			// in the surrounding context (that is, if the _let used in place of the
			// whole * would need parentheses, then it still needs parentheses within
			// the right-hand size of *).
		SECTION("new_edge") {
			CHECK((new MultExpr(
				new NumExpr(2),
				new LetExpr("x", new NumExpr(5),
							new AddExpr(new VarExpr("x"), new NumExpr(1)))))
					  ->to_pretty_string() == "2 * _let x = 5\n"
											  "    _in  x + 1");
			CHECK(
				(new AddExpr(new MultExpr(new NumExpr(5),
										  new LetExpr("x", new NumExpr(5),
													  new MultExpr(new VarExpr("x"),
																   new NumExpr(2)))),
							 new NumExpr(1)))
					->to_pretty_string() == "5 * (_let x = 5\n"
											"     _in  x * 2) + 1");
			CHECK((new MultExpr(
				(new AddExpr(
					new MultExpr(new NumExpr(5),
								 new LetExpr("x", new NumExpr(5),
											 new MultExpr(new VarExpr("x"),
														  new NumExpr(2)))),
					new NumExpr(1))),
				new NumExpr(7)))
					  ->to_pretty_string() == "(5 * (_let x = 5\n"
											  "      _in  x * 2) + 1) * 7");
			CHECK((new LetExpr(
				"x", new NumExpr(10),
				new MultExpr(
					new MultExpr(new VarExpr("x"),
								 new MultExpr(new MultExpr(new NumExpr(10),
														   new NumExpr(10)),
											  new NumExpr(10))),
					new MultExpr(new NumExpr(10), new NumExpr(10)))))
					  ->to_pretty_string() == "_let x = 10\n"
											  "_in  (x * (10 * 10) * 10) * 10 * 10");
			CHECK((new LetExpr(
				"x", new NumExpr(1),
				new MultExpr(
					new MultExpr(new VarExpr("x"),
								 new MultExpr(new MultExpr(new NumExpr(10),
														   new NumExpr(10)),
											  new VarExpr("x"))),
					new MultExpr(new NumExpr(10), new NumExpr(10)))))
					  ->to_pretty_string() == "_let x = 1\n"
											  "_in  (x * (10 * 10) * x) * 10 * 10");
			CHECK((new LetExpr(
				"x", new NumExpr(1),
				new MultExpr(
					new MultExpr(new VarExpr("x"),
								 new MultExpr(new MultExpr(new NumExpr(10),
														   new NumExpr(10)),
											  new VarExpr("x"))),
					new MultExpr(new VarExpr("y"), new NumExpr(10)))))
					  ->to_pretty_string() == "_let x = 1\n"
											  "_in  (x * (10 * 10) * x) * y * 10");
		}
	}SECTION("Let_equals_mine") {
		SECTION("Values_same") {
			REQUIRE((new LetExpr("x", new NumExpr(4),
								 new AddExpr(new NumExpr(2), new VarExpr("x"))))
						->equals(new LetExpr(
							"x", new NumExpr(4),
							new AddExpr(new NumExpr(2), new VarExpr("x")))));
		}SECTION("Values_same_different_rhs") {
			REQUIRE(!(new LetExpr("x", new NumExpr(4),
								  new AddExpr(new NumExpr(2), new VarExpr("x"))))
				->equals(new LetExpr(
					"x", new NumExpr(5),
					new AddExpr(new NumExpr(2), new VarExpr("x")))));
		}SECTION("Values_same_different_lhs") {
			REQUIRE(!(new LetExpr("x", new NumExpr(4),
								  new AddExpr(new NumExpr(2), new VarExpr("x"))))
				->equals(new LetExpr(
					"y", new NumExpr(4),
					new AddExpr(new NumExpr(2), new VarExpr("x")))));
		}SECTION("Values_same_different_body") {
			REQUIRE(!(new LetExpr("x", new NumExpr(4),
								  new AddExpr(new NumExpr(2), new VarExpr("x"))))
				->equals(new LetExpr(
					"x", new NumExpr(4),
					new MultExpr(new NumExpr(3), new VarExpr("y")))));
		}SECTION("different_types") {
			REQUIRE(!(new LetExpr("x", new NumExpr(4),
								  new AddExpr(new NumExpr(2), new VarExpr("x"))))
				->equals(new MultExpr(new NumExpr(3), new VarExpr("y"))));
		}
	}
//	SECTION("Let_has_variable_mine") {
//		SECTION("has") {
//			REQUIRE((new LetExpr("x", new NumExpr(4),
//								 new AddExpr(new NumExpr(2), new VarExpr("x"))))
//						->has_variable() == false);
//		}SECTION("does_not_has") {
//			REQUIRE(!(new LetExpr("x", new NumExpr(4),
//								  new AddExpr(new NumExpr(2), new NumExpr(4))))
//				->has_variable());
//		}
//	}
	SECTION("Let_print_mine") {
		CHECK((new LetExpr("x", new NumExpr(5),
						   new AddExpr(new LetExpr("y", new NumExpr(3),
												   new AddExpr(new VarExpr("y"),
															   new NumExpr(2))),
									   new VarExpr("x"))))
				  ->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
		CHECK(
			(new LetExpr(
				"x", new NumExpr(1),
				new LetExpr(
					"y", new NumExpr(1),
					new LetExpr("z", new AddExpr(new VarExpr("x"), new NumExpr(1)),
								new MultExpr(new AddExpr(new VarExpr("x"),
														 new VarExpr("y")),
											 new VarExpr("z"))))))
				->to_string() ==
				"(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
	}SECTION("Let_interp_mine") {
		SECTION("hw_examples") {
			CHECK((new AddExpr(
				new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
														 new VarExpr("x"))),
				new NumExpr(1)))
					  ->interp()
					  ->equals(new NumVal(26)));
			CHECK((new MultExpr(
				new NumExpr(5),
				new LetExpr("x", new NumExpr(5),
							new AddExpr(new VarExpr("x"), new NumExpr(1)))))
					  ->interp()
					  ->equals(new NumVal(30)));
		}SECTION("from_pretty_print_edge") {
			CHECK((new LetExpr(
				"x", new NumExpr(1),
				new LetExpr(
					"y", new NumExpr(1),
					new LetExpr("z",
								new AddExpr(new VarExpr("x"), new NumExpr(1)),
								new MultExpr(new AddExpr(new VarExpr("x"),
														 new VarExpr("y")),
											 new VarExpr("z"))))))
					  ->interp()
					  ->equals(new NumVal(4)));
			CHECK((new MultExpr(
				(new AddExpr(
					new MultExpr(new NumExpr(5),
								 new LetExpr("x", new NumExpr(5),
											 new MultExpr(new VarExpr("x"),
														  new NumExpr(2)))),
					new NumExpr(1))),
				new NumExpr(7)))
					  ->interp()
					  ->equals(new NumVal(357))); // 51 * 7
			CHECK((new LetExpr(
				"x", new NumExpr(10),
				new MultExpr(
					new MultExpr(new VarExpr("x"),
								 new MultExpr(new MultExpr(new NumExpr(10),
														   new NumExpr(10)),
											  new NumExpr(10))),
					new MultExpr(new NumExpr(10), new NumExpr(10)))))
					  ->interp()
					  ->equals(new NumVal(1000000)));
			CHECK((new LetExpr(
				"x", new NumExpr(1),
				new MultExpr(
					new MultExpr(new VarExpr("x"),
								 new MultExpr(new MultExpr(new NumExpr(10),
														   new NumExpr(10)),
											  new VarExpr("x"))),
					new MultExpr(new NumExpr(10), new NumExpr(10)))))
					  ->interp()
					  ->equals(new NumVal(10000)));
			CHECK_THROWS_WITH(
				((new LetExpr(
					"x", new NumExpr(1),
					new MultExpr(
						new MultExpr(new VarExpr("x"),
									 new MultExpr(new MultExpr(new NumExpr(10),
															   new NumExpr(10)),
												  new VarExpr("x"))),
						new MultExpr(new VarExpr("y"), new NumExpr(10)))))
					->interp()
					->equals(new NumVal(10000))),
				"no value for variable");
		}SECTION("bypass_middle_let") {
			CHECK((new LetExpr(
				"x", new NumExpr(2),
				new LetExpr("z", new NumExpr(4),
							new AddExpr(new VarExpr("x"), new NumExpr(10)))))
					  ->interp()
					  ->equals(new NumVal(12)));
		}
	}

	SECTION("Pretty Print based on Matthew Flatt's examples") {
		std::stringstream out("");
		(new LetExpr("x", new NumExpr(5),
					 new AddExpr(new VarExpr("x"), new NumExpr(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  x + 1");
		out.str(std::string());
		(new AddExpr(new LetExpr("x", new NumExpr(5), new VarExpr("x")),
					 new NumExpr(1)))
			->pretty_print(out);
		CHECK(out.str() == "(_let x = 5\n"
						   " _in  x) + 1");
		out.str(std::string());
		(new MultExpr(new NumExpr(5),
					  new LetExpr("x", new NumExpr(5),
								  new AddExpr(new VarExpr("x"), new NumExpr(1)))))
			->pretty_print(out);
		CHECK(out.str() == "5 * _let x = 5\n"
						   "    _in  x + 1");
		out.str(std::string());
		(new AddExpr(new MultExpr(new NumExpr(5), new LetExpr("x", new NumExpr(5),
															  new VarExpr("x"))),
					 new NumExpr(1)))
			->pretty_print(out);
		CHECK(out.str() == "5 * (_let x = 5\n"
						   "     _in  x) + 1");
		out.str(std::string());
		(new LetExpr(
			"x", new NumExpr(5),
			new AddExpr(new LetExpr("y", new NumExpr(3),
									new AddExpr(new VarExpr("y"), new NumExpr(2))),
						new VarExpr("x"))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  (_let y = 3\n"
						   "      _in  y + 2) + x");
		out.str(std::string());
		(new LetExpr("x",
					 new LetExpr("y", new NumExpr(6),
								 new MultExpr(new VarExpr("y"), new NumExpr(2))),
					 new AddExpr(new VarExpr("x"), new NumExpr(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = _let y = 6\n"
						   "         _in  y * 2\n"
						   "_in  x + 1");
	}
}

TEST_CASE("Parse") {
	CHECK_THROWS_WITH(parse_str("()"), "invalid input - not included condition");

	CHECK(parse_str("(1)")->equals(new NumExpr(1)));
	CHECK(parse_str("(((1)))")->equals(new NumExpr(1)));

	CHECK_THROWS_WITH(parse_str("(1"), "invalid input - missing ')' - parse_inner");

	CHECK(parse_str("1")->equals(new NumExpr(1)));
	CHECK(parse_str("10")->equals(new NumExpr(10)));
	CHECK(parse_str("-3")->equals(new NumExpr(-3)));
	CHECK(parse_str("  \n 5  ")->equals(new NumExpr(5)));
	CHECK_THROWS_WITH(parse_str("-"), "invalid input - no number seen");
	CHECK_THROWS_WITH(parse_str("(((-1))"), "invalid input - missing ')' - parse_inner");

	CHECK_THROWS_WITH(parse_str(" -   5  "), "invalid input - no number seen");
	CHECK(parse_str("x")->equals(new VarExpr("x")));
	CHECK(parse_str("xyz")->equals(new VarExpr("xyz")));
	CHECK(parse_str("xYz")->equals(new VarExpr("xYz")));

	CHECK_THROWS_WITH(parse_str("x_z"),
					  "invalid input - still have character after parsing the whole expression"); // invalid variable name
	CHECK_THROWS_WITH(parse_str("1 2"), "invalid input - still have character after parsing the whole expression");
	CHECK_THROWS_WITH(parse_str("1 x"), "invalid input - still have character after parsing the whole expression");
	CHECK_THROWS_WITH(parse_str("1)"), "invalid input - still have character after parsing the whole expression");
	CHECK_THROWS_WITH(parse_str("1+1)"), "invalid input - still have character after parsing the whole expression");
	CHECK_THROWS_WITH(parse_str("1+1 2)"), "invalid input - still have character after parsing the whole expression");
	CHECK_THROWS_WITH(parse_str("3+1-2)"), "invalid input - still have character after parsing the whole expression");
	CHECK_THROWS_WITH(parse_str("x!y"), "invalid input - still have character after parsing the whole expression");

	CHECK(parse_str("x + y")->equals(
		new AddExpr(new VarExpr("x"), new VarExpr("y"))));
	CHECK(parse_str("x     + y")
			  ->equals(new AddExpr(new VarExpr("x"), new VarExpr("y"))));
	CHECK(parse_str("    x     + y ")
			  ->equals(new AddExpr(new VarExpr("x"), new VarExpr("y"))));
	CHECK(parse_str("x+y")->equals(
		new AddExpr(new VarExpr("x"), new VarExpr("y"))));
	CHECK(parse_str("(x+y)")->equals(
		new AddExpr(new VarExpr("x"), new VarExpr("y"))));

	CHECK(parse_str("x * y")->equals(
		new MultExpr(new VarExpr("x"), new VarExpr("y"))));

	CHECK(
		parse_str("z * x + y")
			->equals(new AddExpr(new MultExpr(new VarExpr("z"), new VarExpr("x")),
								 new VarExpr("y"))));

	CHECK(parse_str("z * (x + y)")
			  ->equals(
				  new MultExpr(new VarExpr("z"),
							   new AddExpr(new VarExpr("x"), new VarExpr("y")))));

	CHECK(parse_str("3222")->equals(new NumExpr(3222)));
	CHECK(parse_str(" 1211")->equals(new NumExpr(1211)));
	CHECK(parse_str("-19 ")->equals(new NumExpr(-19)));
	CHECK(parse_str("( -3    )")->equals(new NumExpr(-3)));
	CHECK_THROWS_WITH(parse_str("(99"), "invalid input - missing ')' - parse_inner");

	CHECK(
		parse_str("2 + 1")->equals(new AddExpr(new NumExpr(2), new NumExpr(1))));
	CHECK(parse_str("-7 + 6")->equals(
		new AddExpr(new NumExpr(-7), new NumExpr(6))));
	CHECK(parse_str("(3 + 2)")->equals(
		new AddExpr(new NumExpr(3), new NumExpr(2))));
	CHECK(
		parse_str("   5+1")->equals(new AddExpr(new NumExpr(5), new NumExpr(1))));
	CHECK_THROWS_WITH(parse_str("(9 +"), "invalid input - not included condition");
	CHECK_THROWS_WITH(parse_str("(9 +1"), "invalid input - missing ')' - parse_inner");
	CHECK_THROWS_WITH(parse_str("9 +)"), "invalid input - not included condition");

	CHECK(parse_str("6 * 12")->equals(
		new MultExpr(new NumExpr(6), new NumExpr(12))));
	CHECK(
		parse_str("-1*2")->equals(new MultExpr(new NumExpr(-1), new NumExpr(2))));
	CHECK(parse_str("(-8)*  4")
			  ->equals(new MultExpr(new NumExpr(-8), new NumExpr(4))));
	CHECK(parse_str("(2  * 1)")
			  ->equals(new MultExpr(new NumExpr(2), new NumExpr(1))));
	CHECK_THROWS_WITH(parse_str("(2  * 1"), "invalid input - missing ')' - parse_inner");
	CHECK_THROWS_WITH(parse_str("2  * 1)"), "invalid input - still have character after parsing the whole expression");

	CHECK(parse_str("cat")->equals(new VarExpr("cat")));
	CHECK(parse_str("  dog")->equals(new VarExpr("dog")));
	CHECK(parse_str("OWLS")->equals(new VarExpr("OWLS")));
	CHECK_THROWS_WITH(parse_str("mo.ngo"), "invalid input - still have character after parsing the whole expression");

	CHECK(
		parse_str("_let x = 5 _in x+2")
			->equals(new LetExpr("x", new NumExpr(5),
								 new AddExpr(new VarExpr("x"), new NumExpr(2)))));
	CHECK(parse_str("_let x = (x+2) _in      (x+-3)")
			  ->equals(
				  new LetExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(2)),
							  new AddExpr(new VarExpr("x"), new NumExpr(-3)))));
	CHECK_THROWS_WITH(parse_str("_let x = 1    _i"), "'_in' is required in _let");

	CHECK(
		parse_str("6 + (2 * -7)")
			->equals(new AddExpr(new NumExpr(6),
								 new MultExpr(new NumExpr(2), new NumExpr(-7)))));
	CHECK(parse_str("(-3)  +  4 * (_let x = 2 _in x+1)")
			  ->equals(new AddExpr(
				  new NumExpr(-3),
				  new MultExpr(new NumExpr(4),
							   new LetExpr("x", new NumExpr(2),
										   new AddExpr(new VarExpr("x"),
													   new NumExpr(1)))))));
	CHECK(parse_str("(1234*((_let x=1_in x+-2)+7))")
			  ->equals(new MultExpr(
				  new NumExpr(1234),
				  new AddExpr(
					  new LetExpr("x", new NumExpr(1),
								  new AddExpr(new VarExpr("x"), new NumExpr(-2))),
					  new NumExpr(7)))));
}

static std::string run(std::string s) {
	return parse_str(s)->interp()->to_string();
}

TEST_CASE("Refactor") { // TODO: add more tests on refactored since bool, and need to check if pretty print works
	SECTION("NumVal") {
		CHECK((new NumVal(3))->equals(new NumVal(3)) == true);
		CHECK((new NumVal(3))->equals(new NumVal(-3)) == false);
		CHECK((new NumVal(3))->equals(nullptr) == false);
		CHECK((new AddExpr(new NumExpr(1), new NumExpr(2)))
				  ->interp()
				  ->equals(new NumVal(3)));
		CHECK(parse_str("2 + 1")->interp()->equals(new NumVal(3)));
		CHECK(parse_str("2 + 1")->interp()->to_string() == "3");
		CHECK(run("1 + 2") == "3");
		CHECK((new LetExpr("x", new AddExpr(new NumExpr(2), new NumExpr(3)),
						   new MultExpr(new VarExpr("x"), new VarExpr("x"))))
				  ->interp()
				  ->equals(new NumVal(25)));
	}SECTION("BoolVal") {
		CHECK((new BoolVal(true))->equals(new BoolVal(true)) == true);
		CHECK((new BoolVal(true))->equals(new BoolVal(false)) == false);
		CHECK((new BoolVal(true))->equals(nullptr) == false);
		CHECK((new EqExpr(new NumExpr(1), new NumExpr(2)))->interp()
				  ->equals(new BoolVal(false)));
		CHECK(parse_str("1 == 2")->interp()->equals(new BoolVal(false)));
		CHECK(parse_str("1 == 2")->interp()->to_string() == "_false");
		CHECK(run("1 == 2") == "_false");
	} SECTION("from quiz") {
		CHECK((new EqExpr(new NumExpr(3), new NumExpr(3)))->interp()->equals(new BoolVal(true)) == true);
		CHECK((new EqExpr(new NumExpr(3), new AddExpr(new NumExpr(1), new NumExpr(2))))->interp()
				  ->equals(new BoolVal(true)) == true);
		CHECK((parse_str("_if 1 == 2 _then 5 _else 6"))->
			equals(new IfExpr(new EqExpr(new NumExpr(1), new NumExpr(2)), new NumExpr(5), new NumExpr(6))));

		CHECK((((parse_str("_if 1 == 2 _then 5 _else 6"))->interp())->to_string()) == "6");
		CHECK((((parse_str("1 == 2"))->interp())->to_string()) == "_false");
		CHECK((((parse_str("(1 + 2) == (3 + 0)"))->interp())->to_string()) == "_true");
		CHECK((((parse_str("1 + 2 == 3 + 0"))->interp())->to_string()) == "_true");
		CHECK_THROWS_WITH(((((parse_str("(1 == 2) + 3 "))->interp())->to_string()) == "_true"), "add of non-number");
		CHECK((((parse_str("1==2+3"))->interp())->to_string()) == "_false");
		CHECK((((parse_str("_if _false\n"
						   "_then 5\n"
						   "_else 6"))->interp())->to_string()) == "6");
		CHECK((((parse_str("_if _false\n"
						   "_then _false\n"
						   "_else _true"))->interp())->to_string()) == "_true");
		CHECK((((parse_str("_if _false\n"
						   "_then 5\n"
						   "_else _false"))->interp())->to_string()) == "_false");
		CHECK_THROWS_WITH(((((parse_str("_true + _false"))->interp())->to_string()) == "_false"), "add of non-number");
		CHECK_THROWS_WITH(((((parse_str("_true + 1"))->interp())->to_string()) == "_false"), "add of non-number");
		CHECK((((parse_str("_true == _true"))->interp())->to_string()) == "_true");
		CHECK((((parse_str("1 == _true"))->interp())->to_string()) == "_false");
		CHECK_THROWS_WITH(((((parse_str("_if 1 + 2\n"
										"_then _false\n"
										"_else _true"))->interp())->to_string()) == "_false"),
						  "IfExpr's condition isn't BoolVal");
		CHECK((((parse_str("_if _true\n"
						   "_then 5\n"
						   "_else _true + 1"))->interp())->to_string()) == "5");
		CHECK_THROWS_WITH(((((parse_str("_if _false\n"
										"_then 5\n"
										"_else _true + 1"))->interp())->to_string()) == "_false"), "add of non-number");
		CHECK_THROWS_WITH(((((parse_str("_let x = _true + 1\n"
										"_in  _if _true\n"
										"     _then 5\n"
										"     _else x"))->interp())->to_string()) == "_false"), "add of non-number");
		CHECK_THROWS_WITH(((((parse_str("_let x = _true + 1\n"
										"_in  _if _true\n"
										"     _then 5\n"
										"     _else x"))->interp())->to_string()) == "_false"), "add of non-number");
		CHECK((((parse_str("(_if _true\n"
						   " _then 5\n"
						   " _else _true) + 1"))->interp())->to_string()) == "6");
		CHECK((((parse_str("_if (_if 1 == 2\n"
						   "     _then _false\n"
						   "     _else _true)\n"
						   "_then 5\n"
						   "_else 6"))->interp())->to_string()) == "5");
		CHECK((((parse_str("_if (_if 1 == 2\n"
						   "     _then _true\n"
						   "      _else _false)\n"
						   "_then 5\n"
						   "_else 6"))->interp())->to_string()) == "6");
	}
}

TEST_CASE("Function") {
	SECTION("Tests_from_quiz") {
		// 1
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in f(5) ")->interp()->equals(new NumVal(6)));

		// 2
		CHECK(parse_str("_let f = _fun (x)\n"
						"           7\n"
						"_in f(5)")->interp()->equals(new NumVal(7)));

		// 3
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _true\n"
						"_in f(5) ")->interp()->equals(new BoolVal(true)));

		// 4
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x)\n"
									"           x + _true\n"
									"_in f(5) ")->interp(), "add of non-number");

		// 5
		CHECK(parse_str("_let f = _fun (x)\n"
						"           x + _true\n"
						"_in 5 + 1 ")->interp()->equals(new NumVal(6)));

		// 6
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x)\n"
									"           7\n"
									"_in  f(5 + _true)")->interp(), "add of non-number");

		// 7
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x) x+ 1\n"
									"_in f + 5")->interp(), "add of non-number");

		// 8
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _if _false\n"
						"    _then f(5)\n"
						"    _else f(6)")->interp()->equals(new NumVal(7)));

		// 9
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y) y+ 2 \n"
						"_in _if _true\n"
						"    _then f(5)\n"
						"    _else g(5)")->interp()->equals(new NumVal(6)));

		// 10
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y) y+ 2 \n"
						"_in f(g(5)) ")->interp()->equals(new NumVal(8)));

		// 11
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y)\n"
						"              f(y + 2)\n"
						"_in g(5) ")->interp()->equals(new NumVal(8)));
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y)\n"
						"              f(y + 2)\n"
						"_in g(5) ")
				  ->equals(new LetExpr("f", new FunExpr("x", new AddExpr(new VarExpr("x"), new NumExpr(1))),
									   new LetExpr("g",
												   new FunExpr("y",
															   new CallExpr(new VarExpr("f"),
																			new AddExpr(new VarExpr("y"),
																						new NumExpr(2)))),
												   new CallExpr(new VarExpr("g"), new NumExpr(5))))) == true);

		// 12
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (x)\n"
						"              f(2) + x\n"
						"_in g(5) ")->interp()->equals(new NumVal(8)));

		// 13
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x) x+ 1 \n"
									"_in f 5 ")->interp(),
						  "invalid input - still have character after parsing the whole expression");

		// 14
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in (f)(5) ")->interp()->equals(new NumVal(6)));

		// 15
		auto *add_x_1 = new AddExpr(new VarExpr("x"), new NumExpr(1));
		auto *fun_val_x_add_x_1 = new FunVal("x", add_x_1);
		CHECK(parse_str("_fun (x) x+ 1 ")->interp()->equals(fun_val_x_add_x_1));

		//16
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in f ")->interp()->equals(fun_val_x_add_x_1));

		// 17
		CHECK(parse_str("(_fun (x)\n"
						"   x + 1)(5)")->interp()->equals(new NumVal(6)));

		// 18
		CHECK(parse_str("_let f = _if _false\n"
						"            _then _fun (x)  \n"
						"                        x+ 1 \n"
						"           _else _fun (x)\n"
						"                       x+ 2\n"
						"_in f(5)")->interp()->equals(new NumVal(7)));

		// 19
		CHECK(parse_str("(_if _false \n"
						"  _then _fun (x)\n"
						"            x+ 1\n"
						"   _else _fun (x)\n"
						"                x + 2)(5)")->interp()->equals(new NumVal(7)));

		// 20
		CHECK(parse_str("_let f = _fun (g)\n"
						"           g(5)\n"
						"_in _let g = _fun (y)  \n"
						"             y + 2\n"
						"_in f(g) ")->interp()->equals(new NumVal(7)));

		// 21
		CHECK(parse_str("_let f = _fun (g)\n"
						"           g(5)\n"
						"_in f(_fun (y)\n"
						"        y + 2)")->interp()->equals(new NumVal(7)));

		// 22
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (y)\n"
						"x+ y _in (f(5))(1) ")->interp()->equals(new NumVal(6)));

		// 23
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (y)\n"
						"x+ y _in f(5)(1) ")->interp()->equals(new NumVal(6)));
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (y)\n"
						"x+ y _in f(5)(1) ")->equals(new LetExpr("f",
																 new FunExpr("x",
																			 new FunExpr("y",
																						 new AddExpr(new VarExpr("x"),
																									 new VarExpr("y")))),
																 new CallExpr(new CallExpr(new VarExpr("f"),
																						   new NumExpr(5)),
																			  new NumExpr(1)))));

		// 24
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (g)\n"
						"             g(x + 1)\n"
						"_in _let g = _fun (y)\n"
						"              y+ 2 \n"
						"_in (f(5))(g) ")->interp()->equals(new NumVal(8)));

		// 25
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (g)\n"
						"             g(x + 1)\n"
						"_in _let g = _fun (y)\n"
						"y+ 2 _in f(5)(g)")->interp()->equals(new NumVal(8)));

		// 26
		CHECK(parse_str("_let f = _fun (f)\n"
						"           _fun (x)\n"
						"             _if x == 0\n"
						"             _then 0\n"
						"             _else x + f(f)(x + -1)\n"
						"_in f(f)(3)")->interp()->equals(new NumVal(6)));
	} SECTION("factorial function recusion test") {
		Expr *factrl_expr = new LetExpr(
			"factrl",
			new FunExpr(
				"factrl",
				new FunExpr(
					"x",
					new IfExpr(
						new EqExpr(
							new VarExpr("x"),
							new NumExpr(1)
						),
						new NumExpr(1),
						new MultExpr(
							new VarExpr("x"),
							new CallExpr(
								new CallExpr(
									new VarExpr("factrl"),
									new VarExpr("factrl")
								),
								new AddExpr(
									new VarExpr("x"),
									new NumExpr(-1)
								)
							)
						)
					)
				)
			),
			new CallExpr(
				new CallExpr(
					new VarExpr("factrl"),
					new VarExpr("factrl")
				),
				new NumExpr(10)
			)
		);

		CHECK(factrl_expr->to_pretty_string() == "_let factrl = _fun (factrl)\n"
												 "                _fun (x)\n"
												 "                  _if x == 1\n"
												 "                  _then 1\n"
												 "                  _else x * factrl(factrl)(x + -1)\n"
												 "_in  factrl(factrl)(10)");

		CHECK(factrl_expr->interp()->equals(new NumVal(3628800)));
		std::string test_str = "_let factrl = _fun (factrl)\n"
							   "                _fun (x)\n"
							   "                  _if x == 1\n"
							   "                  _then 1\n"
							   "                  _else x * factrl(factrl)(x + -1)\n"
							   "_in  factrl(factrl)(10)";

		auto *parsed_expr = parse_str(test_str);
		auto parsed_expr_pretty_str = parsed_expr->to_pretty_string();
		auto parsed_expr_str = parsed_expr->to_string();
		CHECK(parsed_expr_pretty_str == test_str);
		CHECK(parsed_expr->equals(parse_str(parsed_expr_pretty_str)));
		CHECK(parsed_expr->equals(parse_str(parsed_expr_str)));
		CHECK(parsed_expr->interp()->equals(new NumVal(3628800)));
	}
}