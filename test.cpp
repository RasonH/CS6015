//
// Created by Rason Hung on 1/29/23.
//

#pragma include once

#include "catch.h"
#include "expr.h"
#include "parse.h"
#include "val.h"
//#include "env.h"

TEST_CASE("Equals") {
	SECTION("Num_equals") {
		SECTION("Normal_cases") {
			CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(1)) == true);
			CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(2)) == false);
			CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(-1)) == false);
			CHECK((NEW(NumExpr)(1))->equals(NEW(NumExpr)(0)) == false);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((NEW(NumExpr)(1))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(1))) == false);
			CHECK((NEW(NumExpr)(1))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(1))) ==
				false);
			CHECK((NEW(NumExpr)(1))->equals(NEW(VarExpr)("x")) == false);
		}
	}

	SECTION("Add_equals") {
		SECTION("Normal_cases") {
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == true);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(2))) == false);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(3))) == false);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(1))) == false);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1),
								(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))))
					  ->equals(NEW(AddExpr)(
						  NEW(NumExpr)(1),
						  (NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))) == true);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(NumExpr)(2)) == false);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) ==
				false);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(VarExpr)("x")) == false);
		}
	}

	SECTION("Mult_equals") {
		SECTION("Normal_cases") {
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == true);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(2))) ==
				false);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(3))) ==
				false);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(1))) ==
				false);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1),
								 (NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)))))
					  ->equals(NEW(MultExpr)(
						  NEW(NumExpr)(1),
						  (NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3))))) == true);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(NumExpr)(2)) == false);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == false);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
					  ->equals(NEW(VarExpr)("x")) == false);
		}
	}

	SECTION("Variable_equals") {
		SECTION("Normal_cases") {
			CHECK((NEW(VarExpr)("x"))->equals(NEW(VarExpr)("x")) == true);
			CHECK((NEW(VarExpr)("x"))->equals(NEW(VarExpr)("X")) == false);
			CHECK((NEW(VarExpr)("x"))->equals(NEW(VarExpr)("y")) == false);
			CHECK((NEW(VarExpr)("x"))->equals(NEW(VarExpr)("xa")) == false);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((NEW(VarExpr)("x"))->equals(NEW(NumExpr)(1)) == false);
			CHECK((NEW(VarExpr)("x"))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == false);
			CHECK((NEW(VarExpr)("x"))
					  ->equals(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) ==
				false);
		}
	}

	SECTION("Let_equals") {
		SECTION("Normal_cases") {
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(LetExpr)(
						  "x", NEW(NumExpr)(2),
						  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3)))) == true);
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(LetExpr)(
						  "y", NEW(NumExpr)(2),
						  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3)))) == false);
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(3),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(LetExpr)(
						  "x", NEW(NumExpr)(2),
						  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3)))) == false);
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(LetExpr)(
						  "x", NEW(NumExpr)(2),
						  NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3)))) == false);
		}SECTION("Edge_cases") { // from diffenrt classes
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(NumExpr)(2)) == false);
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))) ==
				false);
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))) ==
				false);
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
					  ->equals(NEW(VarExpr)("x")) == false);
		}
	}

	SECTION("Mixed_equals") {
		CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
							NEW(VarExpr)("x")))
				  ->equals(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
										NEW(VarExpr)("x"))) == true);
		CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
							NEW(VarExpr)("x")))
				  ->equals(NEW(AddExpr)(
					  NEW(VarExpr)("x"),
					  NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))) == false);

		// changed some components but not order
		CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
							NEW(VarExpr)("x")))
				  ->equals(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
										NEW(VarExpr)("y"))) == false);
		CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
							NEW(VarExpr)("x")))
				  ->equals(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(2)),
										NEW(VarExpr)("x"))) == false);
		CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
							NEW(VarExpr)("x")))
				  ->equals(NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
										 NEW(VarExpr)("x"))) == false);

		// changed expression order
		CHECK((NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
							 NEW(VarExpr)("x")))
				  ->equals(NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)),
										 NEW(VarExpr)("x"))) == true);
	}SECTION("Invalid_argument_equals") {
		SECTION("Nullptr") {
			CHECK((NEW(NumExpr)(2))
					  ->equals(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))) == false);
			CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->equals(nullptr) ==
				false);
			CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->equals(nullptr) ==
				false);
			CHECK(
				(NEW(LetExpr)("x", NEW(NumExpr)(1), NEW(NumExpr)(2)))->equals(nullptr) ==
					false);
		}
	}
}

TEST_CASE("Interpret") {
	SECTION("Num_interpret") {
		CHECK((NEW(NumExpr)(1))->interp(Env::empty)->equals(NEW(NumVal)(1)));
		CHECK((NEW(NumExpr)(0))->interp(Env::empty)->equals(NEW(NumVal)(0)));
		CHECK((NEW(NumExpr)(-1))->interp(Env::empty)->equals(NEW(NumVal)(-1)));
	}

	SECTION("Add_interpret") {
		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(3)));
		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(-1)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(0)));
		CHECK((NEW(AddExpr)(NEW(NumExpr)(-5), NEW(NumExpr)(-1)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(-6)));
	}

	SECTION("Mult_interpret") {
		CHECK((NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(6)));
		CHECK((NEW(MultExpr)(NEW(NumExpr)(3), NEW(NumExpr)(0)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(0)));
		CHECK((NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(2)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(10)));
		CHECK((NEW(MultExpr)(NEW(NumExpr)(-5), NEW(NumExpr)(2)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(-10)));
	}

	SECTION("Variable_interpret") {
		CHECK_THROWS_WITH((NEW(VarExpr)("x"))->interp(Env::empty), "free variable: x");
		CHECK_THROWS_WITH((NEW(VarExpr)("abc"))->interp(Env::empty), "free variable: abc");
	}

	SECTION("Let_interpret") {
		CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
							NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(5)));
		CHECK(
			(NEW(LetExpr)("x", NEW(NumExpr)(2),
						  NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
										NEW(NumExpr)(3))))
				->interp(Env::empty)
				->equals(NEW(NumVal)(9)));
		CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
							NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(3))))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(6)));
		CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
							NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
													  NEW(AddExpr)(NEW(VarExpr)("y"),
																   NEW(NumExpr)(2))),
										 NEW(VarExpr)("x"))))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(10)));
		CHECK((NEW(AddExpr)(
			NEW(MultExpr)(NEW(NumExpr)(5),
						  NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x"))),
			NEW(NumExpr)(1)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(26)));
		CHECK_THROWS_WITH(
			(NEW(LetExpr)("x", NEW(NumExpr)(2),
						  NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(3))))
				->interp(Env::empty),
			"free variable: y");
	}

	SECTION("Mixed_interpret") {
		CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(15)),
							NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(65)));
		CHECK_THROWS_WITH(
			(NEW(AddExpr)(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(15)),
						  NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
				->interp(Env::empty),
			"free variable: x");
		CHECK_THROWS_WITH(
			(NEW(AddExpr)(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(15)),
						  NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
				->interp(Env::empty),
			"free variable: x");
		CHECK_THROWS_WITH(
			(NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(15), NEW(VarExpr)("x")),
						  NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
				->interp(Env::empty),
			"free variable: x");
		CHECK_THROWS_WITH(
			(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(15), NEW(VarExpr)("x")),
						  NEW(AddExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
				->interp(Env::empty),
			"free variable: x");
	}
}

//TEST_CASE("Has_variable") {
//	SECTION("Variable_has_variable") {
//		CHECK((NEW(VarExpr)("x"))->has_variable() == true);
//		CHECK((NEW(VarExpr)("y"))->has_variable() == true);
//	}
//
//	SECTION("Others_has_variable") {
//		CHECK((NEW(NumExpr)(1))->has_variable() == false);
//		CHECK((NEW(NumExpr)(0))->has_variable() == false);
//		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->has_variable() ==
//			false);
//		CHECK((NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(2)))->has_variable() ==
//			true);
//		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x")))->has_variable() ==
//			true);
//		CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->has_variable() ==
//			false);
//		CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x")))->has_variable() ==
//			true);
//		CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
//						   NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(3))))
//				  ->has_variable() == true);
//		CHECK((NEW(LetExpr)("x", NEW(NumExpr)(2),
//						   NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3))))
//				  ->has_variable() == false);
//	}
//
//	SECTION("Mixed_has_variable") {
//		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x")))->has_variable() ==
//			true);
//		CHECK((NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2)))->has_variable() ==
//			true);
//		CHECK((NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(15)),
//							NEW(MultExpr)(NEW(NumExpr)(20), NEW(NumExpr)(20))))
//				  ->has_variable() == false);
//	}
//}

//TEST_CASE("Substitute") {
//	CHECK((NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7)))
//			  ->subst("x", NEW(VarExpr)("y"))
//			  ->equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7))));
//	CHECK((NEW(VarExpr)("x"))
//			  ->subst("x", NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7)))
//			  ->equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7))));
//	// x * (y * (x + 1)) => x = -2 => -2 * (y * (-2 + 1))
//	CHECK((NEW(MultExpr)(
//		NEW(VarExpr)("x"),
//		NEW(MultExpr)(NEW(VarExpr)("y"),
//					  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))
//			  ->subst("x", NEW(NumExpr)(-2))
//			  ->equals(NEW(MultExpr)(
//				  NEW(NumExpr)(-2),
//				  NEW(MultExpr)(NEW(VarExpr)("y"),
//								NEW(AddExpr)(NEW(NumExpr)(-2), NEW(NumExpr)(1))))));
//	SECTION("Other_substitute") {
//		CHECK(((NEW(VarExpr)("x"))->subst("x", NEW(NumExpr)(2)))
//				  ->interp(Env::empty)
//				  ->equals(NEW(NumVal)(2)));
//		CHECK(((NEW(VarExpr)("x"))
//			->subst("x", NEW(MultExpr)(NEW(NumExpr)(2), NEW(VarExpr)("y")))
//			->equals(NEW(MultExpr)(NEW(NumExpr)(2), NEW(VarExpr)("y")))));
//		CHECK(((NEW(VarExpr)("x"))->subst("y", NEW(NumExpr)(2)))
//				  ->equals(NEW(VarExpr)("x")));
//	}SECTION("Let_substitute") {
//		CHECK((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
//							NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))))
//				  ->subst("x", NEW(NumExpr)(2))
//				  ->equals(NEW(LetExpr)(
//					  "x", NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("y")),
//					  NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")))) == true);
//		CHECK((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
//							NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))))
//				  ->subst("y", NEW(NumExpr)(3))
//				  ->equals(NEW(LetExpr)(
//					  "x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3)),
//					  NEW(MultExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(3)))) == true);
//	}
//}

TEST_CASE("Precedence") {
	SECTION("Get_prec") {
		CHECK((NEW(NumExpr)(1))->get_prec() == prec_none);
		CHECK((NEW(VarExpr)("x"))->get_prec() == prec_none);
		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x")))->get_prec() ==
			prec_add);
		CHECK((NEW(MultExpr)(NEW(NumExpr)(1), NEW(VarExpr)("x")))->get_prec() ==
			prec_mult);
		CHECK((NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
							NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))))
				  ->get_prec() == prec_keywords);
	}
}

TEST_CASE("To_string") {
	SECTION("Print") {
		SECTION("Num_print") {
			CHECK((NEW(NumExpr)(10))->to_string() == "10");
			CHECK((NEW(NumExpr)(-10))->to_string() == "-10");
		}SECTION("Variable_print") {
			CHECK((NEW(VarExpr)("x"))->to_string() == "x");
			CHECK((NEW(VarExpr)("MAX"))->to_string() == "MAX");
		}SECTION("Add_print") {
			CHECK((NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(12)))->to_string() ==
				"(10+12)");
			CHECK((NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-12)))->to_string() ==
				"(-10+-12)");
			CHECK((NEW(AddExpr)(NEW(NumExpr)(10), NEW(VarExpr)("x")))->to_string() ==
				"(10+x)");
		}SECTION("Mult_print") {
			CHECK((NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(12)))->to_string() ==
				"(10*12)");
			CHECK((NEW(MultExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-12)))->to_string() ==
				"(-10*-12)");
			CHECK((NEW(MultExpr)(NEW(NumExpr)(10), NEW(VarExpr)("x")))->to_string() ==
				"(10*x)");
		}SECTION("Mixed_print") {
			CHECK((NEW(MultExpr)(NEW(NumExpr)(10),
								 NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(12))))
					  ->to_string() == "(10*(x+12))");
		}SECTION("Let_print") {
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
								NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
														  NEW(AddExpr)(NEW(VarExpr)("y"),
																	   NEW(NumExpr)(2))),
											 NEW(VarExpr)("x"))))
					  ->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
			CHECK((NEW(AddExpr)(
				NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
															NEW(VarExpr)("x"))),
				NEW(NumExpr)(1)))
					  ->to_string() == "((5*(_let x=5 _in x))+1)");
			CHECK(
				(NEW(MultExpr)(
					NEW(NumExpr)(1234),
					NEW(LetExpr)(
						"x",
						NEW(LetExpr)("z", NEW(NumExpr)(2),
									 NEW(AddExpr)(NEW(VarExpr)("z"), NEW(NumExpr)(5))),
						NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
												  NEW(AddExpr)(NEW(VarExpr)("y"),
															   NEW(NumExpr)(2))),
									 NEW(VarExpr)("x")))))
					->to_string() ==
					"(1234*(_let x=(_let z=2 _in (z+5)) _in ((_let y=3 _in (y+2))+x)))");
		}
	}SECTION("Pretty_print") {
		SECTION("Num_pretty_print") {
			CHECK((NEW(NumExpr)(10))->to_pretty_string() == "10");
			CHECK((NEW(NumExpr)(-10))->to_pretty_string() == "-10");
		}SECTION("Variable_pretty_print") {
			CHECK((NEW(VarExpr)("x"))->to_pretty_string() == "x");
			CHECK((NEW(VarExpr)("MAX"))->to_pretty_string() == "MAX");
		}SECTION("Add_pretty_print") {
			CHECK(
				(NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(12)))->to_pretty_string() ==
					"10 + 12");
			CHECK((NEW(AddExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-12)))
					  ->to_pretty_string() == "-10 + -12");
			CHECK((NEW(AddExpr)(NEW(NumExpr)(10), NEW(VarExpr)("x")))
					  ->to_pretty_string() == "10 + x");
		}SECTION("Mult_pretty_print") {
			CHECK((NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(12)))
					  ->to_pretty_string() == "10 * 12");
			CHECK((NEW(MultExpr)(NEW(NumExpr)(-10), NEW(NumExpr)(-12)))
					  ->to_pretty_string() == "-10 * -12");
			CHECK((NEW(MultExpr)(NEW(NumExpr)(10), NEW(VarExpr)("x")))
					  ->to_pretty_string() == "10 * x");
		}SECTION("Mixed_pretty_print") {
			SECTION("Add_in_between") {
				SECTION("None_add_none") {
					CHECK((NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(12)))
							  ->to_pretty_string() == "10 + 12");
				}SECTION("None_add_add") {
					CHECK((NEW(AddExpr)(NEW(NumExpr)(10),
										NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x"))))
							  ->to_pretty_string() == "10 + 12 + x");
				}SECTION("None_add_mult") {
					CHECK((NEW(AddExpr)(NEW(NumExpr)(10),
										NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x"))))
							  ->to_pretty_string() == "10 + 12 * x");
				}SECTION("Add_add_none") {
					CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										NEW(NumExpr)(10)))
							  ->to_pretty_string() == "(12 + x) + 10");
				}SECTION("Add_add_add") {
					CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "(12 + x) + 10 + 1");
				}SECTION("Add_add_mult") {
					CHECK((NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "(12 + x) + 10 * 1");
				}SECTION("Mult_add_none") {
					CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										NEW(NumExpr)(10)))
							  ->to_pretty_string() == "12 * x + 10");
				}SECTION("Mult_add_add") {
					CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "12 * x + 10 + 1");
				}SECTION("Mult_add_mult") {
					CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "12 * x + 10 * 1");
				}
			}SECTION("Mult_in_between") {
				SECTION("None_mult_none") {
					CHECK((NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(12)))
							  ->to_pretty_string() == "10 * 12");
				}SECTION("None_mult_add") {
					CHECK((NEW(MultExpr)(NEW(NumExpr)(10),
										 NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x"))))
							  ->to_pretty_string() == "10 * (12 + x)");
				}SECTION("None_mult_mult") {
					CHECK((NEW(MultExpr)(NEW(NumExpr)(10),
										 NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x"))))
							  ->to_pretty_string() == "10 * 12 * x");
				}SECTION("Add_mult_none") {
					CHECK((NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										 NEW(NumExpr)(10)))
							  ->to_pretty_string() == "(12 + x) * 10");
				}SECTION("Add_mult_add") {
					CHECK((NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										 NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "(12 + x) * (10 + 1)");
				}SECTION("Add_mult_mult") {
					CHECK((NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										 NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "(12 + x) * 10 * 1");
				}SECTION("Mult_mult_none") {
					CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										 NEW(NumExpr)(10)))
							  ->to_pretty_string() == "(12 * x) * 10");
				}SECTION("Mult_mult_add") {
					CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										 NEW(AddExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "(12 * x) * (10 + 1)");
				}SECTION("Mult_mult_mult") {
					CHECK((NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(12), NEW(VarExpr)("x")),
										 NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(1))))
							  ->to_pretty_string() == "(12 * x) * 10 * 1");
				}SECTION("William") {
					CHECK((NEW(MultExpr)(
						NEW(MultExpr)(NEW(NumExpr)(10),
									  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
																  NEW(NumExpr)(10)),
													NEW(NumExpr)(10))),
						NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10))))
							  ->to_pretty_string() == "(10 * (10 * 10) * 10) * 10 * 10");
				}
			}
		}SECTION("Let_pretty_print") {
			CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
								NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
														  NEW(AddExpr)(NEW(VarExpr)("y"),
																	   NEW(NumExpr)(2))),
											 NEW(VarExpr)("x"))))
					  ->to_pretty_string() == "_let x = 5\n"
											  "_in  (_let y = 3\n"
											  "      _in  y + 2) + x");
			CHECK((NEW(AddExpr)(
				NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
															NEW(VarExpr)("x"))),
				NEW(NumExpr)(1)))
					  ->to_pretty_string() == "5 * (_let x = 5\n"
											  "     _in  x) + 1");
			CHECK((NEW(MultExpr)(
				NEW(NumExpr)(1234),
				NEW(LetExpr)(
					"x",
					NEW(LetExpr)("z", NEW(NumExpr)(2),
								 NEW(AddExpr)(NEW(VarExpr)("z"), NEW(NumExpr)(5))),
					NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
											  NEW(AddExpr)(NEW(VarExpr)("y"),
														   NEW(NumExpr)(2))),
								 NEW(VarExpr)("x")))))
					  ->to_pretty_string() == "1234 * _let x = _let z = 2\n"
											  "                _in  z + 5\n"
											  "       _in  (_let y = 3\n"
											  "             _in  y + 2) + x");
			CHECK(
				(NEW(AddExpr)(NEW(NumExpr)(3),
							  NEW(AddExpr)(NEW(NumExpr)(2),
										   NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5),
																	 NEW(VarExpr)("x")),
														NEW(NumExpr)(4)))))
					->to_pretty_string() == "3 + 2 + (_let x = 5\n"
											"         _in  x) + 4");
			CHECK((NEW(MultExpr)(
				NEW(NumExpr)(5),
				NEW(LetExpr)("x", NEW(NumExpr)(5),
							 NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))
					  ->to_pretty_string() == "5 * _let x = 5\n"
											  "    _in  x + 1");
			CHECK((NEW(AddExpr)(
				NEW(NumExpr)(3),
				NEW(AddExpr)(NEW(NumExpr)(2), NEW(LetExpr)("x", NEW(NumExpr)(5),
														   NEW(VarExpr)("x")))))
					  ->to_pretty_string() == "3 + 2 + _let x = 5\n"
											  "        _in  x");
			CHECK((NEW(AddExpr)(
				NEW(AddExpr)(NEW(NumExpr)(2), NEW(LetExpr)("x", NEW(NumExpr)(5),
														   NEW(VarExpr)("x"))),
				NEW(NumExpr)(1)))
					  ->to_pretty_string() == "(2 + _let x = 5\n"
											  "     _in  x) + 1");
			CHECK((NEW(AddExpr)(
				NEW(MultExpr)(
					NEW(NumExpr)(1234),
					NEW(LetExpr)("x",
								 NEW(LetExpr)("z", NEW(NumExpr)(2),
											  NEW(AddExpr)(NEW(VarExpr)("z"),
														   NEW(NumExpr)(5))),
								 NEW(LetExpr)("y", NEW(NumExpr)(3),
											  NEW(AddExpr)(NEW(VarExpr)("y"),
														   NEW(NumExpr)(2))))),
				NEW(VarExpr)("x")))
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
		(NEW(LetExpr)("x", NEW(NumExpr)(5),
					  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  x + 1");
		out.str(std::string());
		(NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x")),
					  NEW(NumExpr)(1)))
			->pretty_print(out);
		CHECK(out.str() == "(_let x = 5\n"
						   " _in  x) + 1");
		out.str(std::string());
		(NEW(MultExpr)(NEW(NumExpr)(5),
					   NEW(LetExpr)("x", NEW(NumExpr)(5),
									NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))
			->pretty_print(out);
		CHECK(out.str() == "5 * _let x = 5\n"
						   "    _in  x + 1");
		out.str(std::string());
		(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
																  NEW(VarExpr)("x"))),
					  NEW(NumExpr)(1)))
			->pretty_print(out);
		CHECK(out.str() == "5 * (_let x = 5\n"
						   "     _in  x) + 1");
		out.str(std::string());
		(NEW(LetExpr)(
			"x", NEW(NumExpr)(5),
			NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
									  NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
						 NEW(VarExpr)("x"))))
			->pretty_print(out);

		CHECK(out.str() == "_let x = 5\n"
						   "_in  (_let y = 3\n"
						   "      _in  y + 2) + x");
		out.str(std::string());
		(NEW(LetExpr)("x",
					  NEW(LetExpr)("y", NEW(NumExpr)(6),
								   NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
					  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = _let y = 6\n"
						   "         _in  y * 2\n"
						   "_in  x + 1");
	}SECTION("pretty_print_let_mine_some_reuse_of_kevin_triple_nested_let") {
		PTR(LetExpr) tripleNestedLet =
			NEW(LetExpr)("x", NEW(NumExpr)(1),
						 NEW(LetExpr)("y", NEW(NumExpr)(1),
									  NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
																 NEW(VarExpr)("y")),
													NEW(VarExpr)("z"))));
		PTR(LetExpr) tripleNestedLet2 = NEW(LetExpr)(
			"x", NEW(NumExpr)(1),
			NEW(LetExpr)(
				"y", NEW(NumExpr)(1),
				NEW(LetExpr)(
					"z", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
					NEW(AddExpr)(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
								 NEW(VarExpr)("z")))));
		PTR(LetExpr) tripleNestedLet3 = NEW(LetExpr)(
			"x", NEW(NumExpr)(1),
			NEW(LetExpr)(
				"y", NEW(NumExpr)(1),
				NEW(LetExpr)(
					"z", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
					NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")),
								  NEW(VarExpr)("z")))));

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
		PTR(LetExpr) tripleNestedLet4 =
			NEW(LetExpr)("x", NEW(NumExpr)(5),
						 NEW(LetExpr)("y", NEW(NumExpr)(3),
									  NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))));
		PTR(LetExpr) tripleNestedLet5 = NEW(LetExpr)(
			"x", NEW(NumExpr)(5),
			NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
									  NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
						 NEW(VarExpr)("x")));
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
			CHECK((NEW(AddExpr)(
				NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
															NEW(VarExpr)("x"))),
				NEW(NumExpr)(1)))
					  ->to_pretty_string() == "5 * (_let x = 5\n"
											  "     _in  x) + 1");
			CHECK(
				(NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(2),
											 NEW(LetExpr)("x", NEW(NumExpr)(5),
														  NEW(AddExpr)(NEW(VarExpr)("x"),
																	   NEW(NumExpr)(1)))),
							   NEW(NumExpr)(3)))
					->to_pretty_string() == "(2 * _let x = 5\n"
											"     _in  x + 1) * 3");
			CHECK((NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(2),
											  NEW(LetExpr)("x", NEW(NumExpr)(5),
														   NEW(AddExpr)(NEW(VarExpr)("x"),
																		NEW(NumExpr)(1)))),
								NEW(NumExpr)(3)))
					  ->to_pretty_string() == "2 * (_let x = 5\n"
											  "     _in  x + 1) + 3");
		}
			// A _let needs parentheses when it is nested immediately as the right
			// argument of an unparenthesized * where _let would have needed parentheses
			// in the surrounding context (that is, if the _let used in place of the
			// whole * would need parentheses, then it still needs parentheses within
			// the right-hand size of *).
		SECTION("new_edge") {
			CHECK((NEW(MultExpr)(
				NEW(NumExpr)(2),
				NEW(LetExpr)("x", NEW(NumExpr)(5),
							 NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))
					  ->to_pretty_string() == "2 * _let x = 5\n"
											  "    _in  x + 1");
			CHECK(
				(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5),
											NEW(LetExpr)("x", NEW(NumExpr)(5),
														 NEW(MultExpr)(NEW(VarExpr)("x"),
																	   NEW(NumExpr)(2)))),
							  NEW(NumExpr)(1)))
					->to_pretty_string() == "5 * (_let x = 5\n"
											"     _in  x * 2) + 1");
			CHECK((NEW(MultExpr)(
				(NEW(AddExpr)(
					NEW(MultExpr)(NEW(NumExpr)(5),
								  NEW(LetExpr)("x", NEW(NumExpr)(5),
											   NEW(MultExpr)(NEW(VarExpr)("x"),
															 NEW(NumExpr)(2)))),
					NEW(NumExpr)(1))),
				NEW(NumExpr)(7)))
					  ->to_pretty_string() == "(5 * (_let x = 5\n"
											  "      _in  x * 2) + 1) * 7");
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(10),
				NEW(MultExpr)(
					NEW(MultExpr)(NEW(VarExpr)("x"),
								  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
															  NEW(NumExpr)(10)),
												NEW(NumExpr)(10))),
					NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
					  ->to_pretty_string() == "_let x = 10\n"
											  "_in  (x * (10 * 10) * 10) * 10 * 10");
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(1),
				NEW(MultExpr)(
					NEW(MultExpr)(NEW(VarExpr)("x"),
								  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
															  NEW(NumExpr)(10)),
												NEW(VarExpr)("x"))),
					NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
					  ->to_pretty_string() == "_let x = 1\n"
											  "_in  (x * (10 * 10) * x) * 10 * 10");
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(1),
				NEW(MultExpr)(
					NEW(MultExpr)(NEW(VarExpr)("x"),
								  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
															  NEW(NumExpr)(10)),
												NEW(VarExpr)("x"))),
					NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(10)))))
					  ->to_pretty_string() == "_let x = 1\n"
											  "_in  (x * (10 * 10) * x) * y * 10");
		}
	}SECTION("Let_equals_mine") {
		SECTION("Values_same") {
			REQUIRE((NEW(LetExpr)("x", NEW(NumExpr)(4),
								  NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))
						->equals(NEW(LetExpr)(
							"x", NEW(NumExpr)(4),
							NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x")))));
		}SECTION("Values_same_different_rhs") {
			REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4),
								   NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))
				->equals(NEW(LetExpr)(
					"x", NEW(NumExpr)(5),
					NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x")))));
		}SECTION("Values_same_different_lhs") {
			REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4),
								   NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))
				->equals(NEW(LetExpr)(
					"y", NEW(NumExpr)(4),
					NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x")))));
		}SECTION("Values_same_different_body") {
			REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4),
								   NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))
				->equals(NEW(LetExpr)(
					"x", NEW(NumExpr)(4),
					NEW(MultExpr)(NEW(NumExpr)(3), NEW(VarExpr)("y")))));
		}SECTION("different_types") {
			REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4),
								   NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))
				->equals(NEW(MultExpr)(NEW(NumExpr)(3), NEW(VarExpr)("y"))));
		}
	}
//	SECTION("Let_has_variable_mine") {
//		SECTION("has") {
//			REQUIRE((NEW(LetExpr)("x", NEW(NumExpr)(4),
//								 NEW(AddExpr)(NEW(NumExpr)(2), NEW(VarExpr)("x"))))
//						->has_variable() == false);
//		}SECTION("does_not_has") {
//			REQUIRE(!(NEW(LetExpr)("x", NEW(NumExpr)(4),
//								  NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(4))))
//				->has_variable());
//		}
//	}
	SECTION("Let_print_mine") {
		CHECK((NEW(LetExpr)("x", NEW(NumExpr)(5),
							NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
													  NEW(AddExpr)(NEW(VarExpr)("y"),
																   NEW(NumExpr)(2))),
										 NEW(VarExpr)("x"))))
				  ->to_string() == "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
		CHECK(
			(NEW(LetExpr)(
				"x", NEW(NumExpr)(1),
				NEW(LetExpr)(
					"y", NEW(NumExpr)(1),
					NEW(LetExpr)("z", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
								 NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
															NEW(VarExpr)("y")),
											   NEW(VarExpr)("z"))))))
				->to_string() ==
				"(_let x=1 _in (_let y=1 _in (_let z=(x+1) _in ((x+y)*z))))");
	}SECTION("Let_interp_mine") {
		SECTION("hw_examples") {
			CHECK((NEW(AddExpr)(
				NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
															NEW(VarExpr)("x"))),
				NEW(NumExpr)(1)))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(26)));
			CHECK((NEW(MultExpr)(
				NEW(NumExpr)(5),
				NEW(LetExpr)("x", NEW(NumExpr)(5),
							 NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(30)));
		}SECTION("from_pretty_print_edge") {
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(1),
				NEW(LetExpr)(
					"y", NEW(NumExpr)(1),
					NEW(LetExpr)("z",
								 NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)),
								 NEW(MultExpr)(NEW(AddExpr)(NEW(VarExpr)("x"),
															NEW(VarExpr)("y")),
											   NEW(VarExpr)("z"))))))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(4)));
			CHECK((NEW(MultExpr)(
				(NEW(AddExpr)(
					NEW(MultExpr)(NEW(NumExpr)(5),
								  NEW(LetExpr)("x", NEW(NumExpr)(5),
											   NEW(MultExpr)(NEW(VarExpr)("x"),
															 NEW(NumExpr)(2)))),
					NEW(NumExpr)(1))),
				NEW(NumExpr)(7)))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(357))); // 51 * 7
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(10),
				NEW(MultExpr)(
					NEW(MultExpr)(NEW(VarExpr)("x"),
								  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
															  NEW(NumExpr)(10)),
												NEW(NumExpr)(10))),
					NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(1000000)));
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(1),
				NEW(MultExpr)(
					NEW(MultExpr)(NEW(VarExpr)("x"),
								  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
															  NEW(NumExpr)(10)),
												NEW(VarExpr)("x"))),
					NEW(MultExpr)(NEW(NumExpr)(10), NEW(NumExpr)(10)))))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(10000)));
			CHECK_THROWS_WITH(
				((NEW(LetExpr)(
					"x", NEW(NumExpr)(1),
					NEW(MultExpr)(
						NEW(MultExpr)(NEW(VarExpr)("x"),
									  NEW(MultExpr)(NEW(MultExpr)(NEW(NumExpr)(10),
																  NEW(NumExpr)(10)),
													NEW(VarExpr)("x"))),
						NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(10)))))
					->interp(Env::empty)
					->equals(NEW(NumVal)(10000))),
				"free variable: y");
		}SECTION("bypass_middle_let") {
			CHECK((NEW(LetExpr)(
				"x", NEW(NumExpr)(2),
				NEW(LetExpr)("z", NEW(NumExpr)(4),
							 NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(10)))))
					  ->interp(Env::empty)
					  ->equals(NEW(NumVal)(12)));
		}
	}

	SECTION("Pretty Print based on Matthew Flatt's examples") {
		std::stringstream out("");
		(NEW(LetExpr)("x", NEW(NumExpr)(5),
					  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  x + 1");
		out.str(std::string());
		(NEW(AddExpr)(NEW(LetExpr)("x", NEW(NumExpr)(5), NEW(VarExpr)("x")),
					  NEW(NumExpr)(1)))
			->pretty_print(out);
		CHECK(out.str() == "(_let x = 5\n"
						   " _in  x) + 1");
		out.str(std::string());
		(NEW(MultExpr)(NEW(NumExpr)(5),
					   NEW(LetExpr)("x", NEW(NumExpr)(5),
									NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1)))))
			->pretty_print(out);
		CHECK(out.str() == "5 * _let x = 5\n"
						   "    _in  x + 1");
		out.str(std::string());
		(NEW(AddExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(LetExpr)("x", NEW(NumExpr)(5),
																  NEW(VarExpr)("x"))),
					  NEW(NumExpr)(1)))
			->pretty_print(out);
		CHECK(out.str() == "5 * (_let x = 5\n"
						   "     _in  x) + 1");
		out.str(std::string());
		(NEW(LetExpr)(
			"x", NEW(NumExpr)(5),
			NEW(AddExpr)(NEW(LetExpr)("y", NEW(NumExpr)(3),
									  NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
						 NEW(VarExpr)("x"))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = 5\n"
						   "_in  (_let y = 3\n"
						   "      _in  y + 2) + x");
		out.str(std::string());
		(NEW(LetExpr)("x",
					  NEW(LetExpr)("y", NEW(NumExpr)(6),
								   NEW(MultExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))),
					  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))))
			->pretty_print(out);
		CHECK(out.str() == "_let x = _let y = 6\n"
						   "         _in  y * 2\n"
						   "_in  x + 1");
	}
}

TEST_CASE("Parse") {
	CHECK_THROWS_WITH(parse_str("()"), "invalid input - not included condition");

	CHECK(parse_str("(1)")->equals(NEW(NumExpr)(1)));
	CHECK(parse_str("(((1)))")->equals(NEW(NumExpr)(1)));

	CHECK_THROWS_WITH(parse_str("(1"), "invalid input - missing ')' - parse_inner");

	CHECK(parse_str("1")->equals(NEW(NumExpr)(1)));
	CHECK(parse_str("10")->equals(NEW(NumExpr)(10)));
	CHECK(parse_str("-3")->equals(NEW(NumExpr)(-3)));
	CHECK(parse_str("  \n 5  ")->equals(NEW(NumExpr)(5)));
	CHECK_THROWS_WITH(parse_str("-"), "invalid input - no number seen");
	CHECK_THROWS_WITH(parse_str("(((-1))"), "invalid input - missing ')' - parse_inner");

	CHECK_THROWS_WITH(parse_str(" -   5  "), "invalid input - no number seen");
	CHECK(parse_str("x")->equals(NEW(VarExpr)("x")));
	CHECK(parse_str("xyz")->equals(NEW(VarExpr)("xyz")));
	CHECK(parse_str("xYz")->equals(NEW(VarExpr)("xYz")));

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
		NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));
	CHECK(parse_str("x     + y")
			  ->equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));
	CHECK(parse_str("    x     + y ")
			  ->equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));
	CHECK(parse_str("x+y")->equals(
		NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));
	CHECK(parse_str("(x+y)")->equals(
		NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));

	CHECK(parse_str("x * y")->equals(
		NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y"))));

	CHECK(
		parse_str("z * x + y")
			->equals(NEW(AddExpr)(NEW(MultExpr)(NEW(VarExpr)("z"), NEW(VarExpr)("x")),
								  NEW(VarExpr)("y"))));

	CHECK(parse_str("z * (x + y)")
			  ->equals(
				  NEW(MultExpr)(NEW(VarExpr)("z"),
								NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y")))));

	CHECK(parse_str("3222")->equals(NEW(NumExpr)(3222)));
	CHECK(parse_str(" 1211")->equals(NEW(NumExpr)(1211)));
	CHECK(parse_str("-19 ")->equals(NEW(NumExpr)(-19)));
	CHECK(parse_str("( -3    )")->equals(NEW(NumExpr)(-3)));
	CHECK_THROWS_WITH(parse_str("(99"), "invalid input - missing ')' - parse_inner");

	CHECK(
		parse_str("2 + 1")->equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(1))));
	CHECK(parse_str("-7 + 6")->equals(
		NEW(AddExpr)(NEW(NumExpr)(-7), NEW(NumExpr)(6))));
	CHECK(parse_str("(3 + 2)")->equals(
		NEW(AddExpr)(NEW(NumExpr)(3), NEW(NumExpr)(2))));
	CHECK(
		parse_str("   5+1")->equals(NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(1))));
	CHECK_THROWS_WITH(parse_str("(9 +"), "invalid input - not included condition");
	CHECK_THROWS_WITH(parse_str("(9 +1"), "invalid input - missing ')' - parse_inner");
	CHECK_THROWS_WITH(parse_str("9 +)"), "invalid input - not included condition");

	CHECK(parse_str("6 * 12")->equals(
		NEW(MultExpr)(NEW(NumExpr)(6), NEW(NumExpr)(12))));
	CHECK(
		parse_str("-1*2")->equals(NEW(MultExpr)(NEW(NumExpr)(-1), NEW(NumExpr)(2))));
	CHECK(parse_str("(-8)*  4")
			  ->equals(NEW(MultExpr)(NEW(NumExpr)(-8), NEW(NumExpr)(4))));
	CHECK(parse_str("(2  * 1)")
			  ->equals(NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(1))));
	CHECK_THROWS_WITH(parse_str("(2  * 1"), "invalid input - missing ')' - parse_inner");
	CHECK_THROWS_WITH(parse_str("2  * 1)"), "invalid input - still have character after parsing the whole expression");

	CHECK(parse_str("cat")->equals(NEW(VarExpr)("cat")));
	CHECK(parse_str("  dog")->equals(NEW(VarExpr)("dog")));
	CHECK(parse_str("OWLS")->equals(NEW(VarExpr)("OWLS")));
	CHECK_THROWS_WITH(parse_str("mo.ngo"), "invalid input - still have character after parsing the whole expression");

	CHECK(
		parse_str("_let x = 5 _in x+2")
			->equals(NEW(LetExpr)("x", NEW(NumExpr)(5),
								  NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(2)))));
	CHECK(parse_str("_let x = (x+2) _in      (x+-3)")
			  ->equals(
				  NEW(LetExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(2)),
							   NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(-3)))));
	CHECK_THROWS_WITH(parse_str("_let x = 1    _i"), "'_in' is required in _let");

	CHECK(
		parse_str("6 + (2 * -7)")
			->equals(NEW(AddExpr)(NEW(NumExpr)(6),
								  NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(-7)))));
	CHECK(parse_str("(-3)  +  4 * (_let x = 2 _in x+1)")
			  ->equals(NEW(AddExpr)(
				  NEW(NumExpr)(-3),
				  NEW(MultExpr)(NEW(NumExpr)(4),
								NEW(LetExpr)("x", NEW(NumExpr)(2),
											 NEW(AddExpr)(NEW(VarExpr)("x"),
														  NEW(NumExpr)(1)))))));
	CHECK(parse_str("(1234*((_let x=1_in x+-2)+7))")
			  ->equals(NEW(MultExpr)(
				  NEW(NumExpr)(1234),
				  NEW(AddExpr)(
					  NEW(LetExpr)("x", NEW(NumExpr)(1),
								   NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(-2))),
					  NEW(NumExpr)(7)))));
}

static std::string run(std::string s) {
	return parse_str(s)->interp(Env::empty)->to_string();
}

TEST_CASE("Refactor") { // TODO: add more tests on refactored since bool, and need to check if pretty print works
	SECTION("NumVal") {
		CHECK((NEW(NumVal)(3))->equals(NEW(NumVal)(3)) == true);
		CHECK((NEW(NumVal)(3))->equals(NEW(NumVal)(-3)) == false);
		CHECK((NEW(NumVal)(3))->equals(nullptr) == false);
		CHECK((NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(3)));
		CHECK(parse_str("2 + 1")->interp(Env::empty)->equals(NEW(NumVal)(3)));
		CHECK(parse_str("2 + 1")->interp(Env::empty)->to_string() == "3");
		CHECK(run("1 + 2") == "3");
		CHECK((NEW(LetExpr)("x", NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)),
							NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("x"))))
				  ->interp(Env::empty)
				  ->equals(NEW(NumVal)(25)));
	}SECTION("BoolVal") {
		CHECK((NEW(BoolVal)(true))->equals(NEW(BoolVal)(true)) == true);
		CHECK((NEW(BoolVal)(true))->equals(NEW(BoolVal)(false)) == false);
		CHECK((NEW(BoolVal)(true))->equals(nullptr) == false);
		CHECK((NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)))->interp(Env::empty)
				  ->equals(NEW(BoolVal)(false)));
		CHECK(parse_str("1 == 2")->interp(Env::empty)->equals(NEW(BoolVal)(false)));
		CHECK(parse_str("1 == 2")->interp(Env::empty)->to_string() == "_false");
		CHECK(run("1 == 2") == "_false");
	} SECTION("from quiz") {
		CHECK((NEW(EqExpr)(NEW(NumExpr)(3), NEW(NumExpr)(3)))->interp(Env::empty)->equals(NEW(BoolVal)(true)) == true);
		CHECK((NEW(EqExpr)(NEW(NumExpr)(3), NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2))))->interp(Env::empty)
				  ->equals(NEW(BoolVal)(true)) == true);
		CHECK((parse_str("_if 1 == 2 _then 5 _else 6"))->
			equals(NEW(IfExpr)(NEW(EqExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(5), NEW(NumExpr)(6))));

		CHECK((((parse_str("_if 1 == 2 _then 5 _else 6"))->interp(Env::empty))->to_string()) == "6");
		CHECK((((parse_str("1 == 2"))->interp(Env::empty))->to_string()) == "_false");
		CHECK((((parse_str("(1 + 2) == (3 + 0)"))->interp(Env::empty))->to_string()) == "_true");
		CHECK((((parse_str("1 + 2 == 3 + 0"))->interp(Env::empty))->to_string()) == "_true");
		CHECK_THROWS_WITH(((((parse_str("(1 == 2) + 3 "))->interp(Env::empty))->to_string()) == "_true"),
						  "add of non-number");
		CHECK((((parse_str("1==2+3"))->interp(Env::empty))->to_string()) == "_false");
		CHECK((((parse_str("_if _false\n"
						   "_then 5\n"
						   "_else 6"))->interp(Env::empty))->to_string()) == "6");
		CHECK((((parse_str("_if _false\n"
						   "_then _false\n"
						   "_else _true"))->interp(Env::empty))->to_string()) == "_true");
		CHECK((((parse_str("_if _false\n"
						   "_then 5\n"
						   "_else _false"))->interp(Env::empty))->to_string()) == "_false");
		CHECK_THROWS_WITH(((((parse_str("_true + _false"))->interp(Env::empty))->to_string()) == "_false"),
						  "add of non-number");
		CHECK_THROWS_WITH(((((parse_str("_true + 1"))->interp(Env::empty))->to_string()) == "_false"),
						  "add of non-number");
		CHECK((((parse_str("_true == _true"))->interp(Env::empty))->to_string()) == "_true");
		CHECK((((parse_str("1 == _true"))->interp(Env::empty))->to_string()) == "_false");
		CHECK_THROWS_WITH(((((parse_str("_if 1 + 2\n"
										"_then _false\n"
										"_else _true"))->interp(Env::empty))->to_string()) == "_false"),
						  "IfExpr's condition isn't BoolVal");
		CHECK((((parse_str("_if _true\n"
						   "_then 5\n"
						   "_else _true + 1"))->interp(Env::empty))->to_string()) == "5");
		CHECK_THROWS_WITH(((((parse_str("_if _false\n"
										"_then 5\n"
										"_else _true + 1"))->interp(Env::empty))->to_string()) == "_false"),
						  "add of non-number");
		CHECK_THROWS_WITH(((((parse_str("_let x = _true + 1\n"
										"_in  _if _true\n"
										"     _then 5\n"
										"     _else x"))->interp(Env::empty))->to_string()) == "_false"),
						  "add of non-number");
		CHECK_THROWS_WITH(((((parse_str("_let x = _true + 1\n"
										"_in  _if _true\n"
										"     _then 5\n"
										"     _else x"))->interp(Env::empty))->to_string()) == "_false"),
						  "add of non-number");
		CHECK((((parse_str("(_if _true\n"
						   " _then 5\n"
						   " _else _true) + 1"))->interp(Env::empty))->to_string()) == "6");
		CHECK((((parse_str("_if (_if 1 == 2\n"
						   "     _then _false\n"
						   "     _else _true)\n"
						   "_then 5\n"
						   "_else 6"))->interp(Env::empty))->to_string()) == "5");
		CHECK((((parse_str("_if (_if 1 == 2\n"
						   "     _then _true\n"
						   "      _else _false)\n"
						   "_then 5\n"
						   "_else 6"))->interp(Env::empty))->to_string()) == "6");
	}
}

TEST_CASE("Function") {
	SECTION("Tests_from_quiz") {
		// 1
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in f(5) ")->interp(Env::empty)->equals(NEW(NumVal)(6)));

		// 2
		CHECK(parse_str("_let f = _fun (x)\n"
						"           7\n"
						"_in f(5)")->interp(Env::empty)->equals(NEW(NumVal)(7)));

		// 3
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _true\n"
						"_in f(5) ")->interp(Env::empty)->equals(NEW(BoolVal)(true)));

		// 4
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x)\n"
									"           x + _true\n"
									"_in f(5) ")->interp(Env::empty), "add of non-number");

		// 5
		CHECK(parse_str("_let f = _fun (x)\n"
						"           x + _true\n"
						"_in 5 + 1 ")->interp(Env::empty)->equals(NEW(NumVal)(6)));

		// 6
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x)\n"
									"           7\n"
									"_in  f(5 + _true)")->interp(Env::empty), "add of non-number");

		// 7
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x) x+ 1\n"
									"_in f + 5")->interp(Env::empty), "add of non-number");

		// 8
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _if _false\n"
						"    _then f(5)\n"
						"    _else f(6)")->interp(Env::empty)->equals(NEW(NumVal)(7)));

		// 9
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y) y+ 2 \n"
						"_in _if _true\n"
						"    _then f(5)\n"
						"    _else g(5)")->interp(Env::empty)->equals(NEW(NumVal)(6)));

		// 10
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y) y+ 2 \n"
						"_in f(g(5)) ")->interp(Env::empty)->equals(NEW(NumVal)(8)));

		// 11
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y)\n"
						"              f(y + 2)\n"
						"_in g(5) ")->interp(Env::empty)->equals(NEW(NumVal)(8)));
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (y)\n"
						"              f(y + 2)\n"
						"_in g(5) ")
				  ->equals(NEW(LetExpr)("f", NEW(FunExpr)("x", NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1))),
										NEW(LetExpr)("g",
													 NEW(FunExpr)("y",
																  NEW(CallExpr)(NEW(VarExpr)("f"),
																				NEW(AddExpr)(NEW(VarExpr)("y"),
																							 NEW(NumExpr)(2)))),
													 NEW(CallExpr)(NEW(VarExpr)("g"), NEW(NumExpr)(5))))) == true);

		// 12
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in _let g = _fun (x)\n"
						"              f(2) + x\n"
						"_in g(5) ")->interp(Env::empty)->equals(NEW(NumVal)(8)));

		// 13
		CHECK_THROWS_WITH(parse_str("_let f = _fun (x) x+ 1 \n"
									"_in f 5 ")->interp(Env::empty),
						  "invalid input - still have character after parsing the whole expression");

		// 14
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in (f)(5) ")->interp(Env::empty)->equals(NEW(NumVal)(6)));

		// 15
		PTR(AddExpr) add_x_1 = NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(1));
		PTR(FunVal) fun_val_x_add_x_1 = NEW(FunVal)("x", add_x_1, Env::empty);
		CHECK(parse_str("_fun (x) x+ 1 ")->interp(Env::empty)->equals(fun_val_x_add_x_1));

		//16
		CHECK(parse_str("_let f = _fun (x) x+ 1 \n"
						"_in f ")->interp(Env::empty)->equals(fun_val_x_add_x_1));

		// 17
		CHECK(parse_str("(_fun (x)\n"
						"   x + 1)(5)")->interp(Env::empty)->equals(NEW(NumVal)(6)));

		// 18
		CHECK(parse_str("_let f = _if _false\n"
						"            _then _fun (x)  \n"
						"                        x+ 1 \n"
						"           _else _fun (x)\n"
						"                       x+ 2\n"
						"_in f(5)")->interp(Env::empty)->equals(NEW(NumVal)(7)));

		// 19
		CHECK(parse_str("(_if _false \n"
						"  _then _fun (x)\n"
						"            x+ 1\n"
						"   _else _fun (x)\n"
						"                x + 2)(5)")->interp(Env::empty)->equals(NEW(NumVal)(7)));

		// 20
		CHECK(parse_str("_let f = _fun (g)\n"
						"           g(5)\n"
						"_in _let g = _fun (y)  \n"
						"             y + 2\n"
						"_in f(g) ")->interp(Env::empty)->equals(NEW(NumVal)(7)));

		// 21
		CHECK(parse_str("_let f = _fun (g)\n"
						"           g(5)\n"
						"_in f(_fun (y)\n"
						"        y + 2)")->interp(Env::empty)->equals(NEW(NumVal)(7)));

		// 22
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (y)\n"
						"x+ y _in (f(5))(1) ")->interp(Env::empty)->equals(NEW(NumVal)(6)));

		// 23
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (y)\n"
						"x+ y _in f(5)(1) ")->interp(Env::empty)->equals(NEW(NumVal)(6)));
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (y)\n"
						"x+ y _in f(5)(1) ")->equals(NEW(LetExpr)("f",
																  NEW(FunExpr)("x",
																			   NEW(FunExpr)("y",
																							NEW(AddExpr)(NEW(VarExpr)(
																											 "x"),
																										 NEW(VarExpr)(
																											 "y")))),
																  NEW(CallExpr)(NEW(CallExpr)(NEW(VarExpr)("f"),
																							  NEW(NumExpr)(5)),
																				NEW(NumExpr)(1)))));

		// 24
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (g)\n"
						"             g(x + 1)\n"
						"_in _let g = _fun (y)\n"
						"              y+ 2 \n"
						"_in (f(5))(g) ")->interp(Env::empty)->equals(NEW(NumVal)(8)));

		// 25
		CHECK(parse_str("_let f = _fun (x)\n"
						"           _fun (g)\n"
						"             g(x + 1)\n"
						"_in _let g = _fun (y)\n"
						"y+ 2 _in f(5)(g)")->interp(Env::empty)->equals(NEW(NumVal)(8)));

		// 26
		CHECK(parse_str("_let f = _fun (f)\n"
						"           _fun (x)\n"
						"             _if x == 0\n"
						"             _then 0\n"
						"             _else x + f(f)(x + -1)\n"
						"_in f(f)(3)")->interp(Env::empty)->equals(NEW(NumVal)(6)));
	} SECTION("factorial function recusion test") {
		PTR(Expr) factrl_expr = NEW(LetExpr)(
			"factrl",
			NEW(FunExpr)(
				"factrl",
				NEW(FunExpr)(
					"x",
					NEW(IfExpr)(
						NEW(EqExpr)(
							NEW(VarExpr)("x"),
							NEW(NumExpr)(1)
						),
						NEW(NumExpr)(1),
						NEW(MultExpr)(
							NEW(VarExpr)("x"),
							NEW(CallExpr)(
								NEW(CallExpr)(
									NEW(VarExpr)("factrl"),
									NEW(VarExpr)("factrl")
								),
								NEW(AddExpr)(
									NEW(VarExpr)("x"),
									NEW(NumExpr)(-1)
								)
							)
						)
					)
				)
			),
			NEW(CallExpr)(
				NEW(CallExpr)(
					NEW(VarExpr)("factrl"),
					NEW(VarExpr)("factrl")
				),
				NEW(NumExpr)(10)
			)
		);

		CHECK(factrl_expr->to_pretty_string() == "_let factrl = _fun (factrl)\n"
												 "                _fun (x)\n"
												 "                  _if x == 1\n"
												 "                  _then 1\n"
												 "                  _else x * factrl(factrl)(x + -1)\n"
												 "_in  factrl(factrl)(10)");

		CHECK(factrl_expr->interp(Env::empty)->equals(NEW(NumVal)(3628800)));
		std::string test_str = "_let factrl = _fun (factrl)\n"
							   "                _fun (x)\n"
							   "                  _if x == 1\n"
							   "                  _then 1\n"
							   "                  _else x * factrl(factrl)(x + -1)\n"
							   "_in  factrl(factrl)(10)";

		PTR(Expr) parsed_expr = parse_str(test_str);
		std::string parsed_expr_pretty_str = parsed_expr->to_pretty_string();
		std::string parsed_expr_str = parsed_expr->to_string();
		CHECK(parsed_expr_pretty_str == test_str);
		CHECK(parsed_expr->equals(parse_str(parsed_expr_pretty_str)));
		CHECK(parsed_expr->equals(parse_str(parsed_expr_str)));
		CHECK(parsed_expr->interp(Env::empty)->equals(NEW(NumVal)(3628800)));
	}
}