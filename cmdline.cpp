//
//  cmdline.cpp
//  CommandLine
//
//  Created by Rason Hung on 1/16/23.
//

#define CATCH_CONFIG_RUNNER
#pragma include once

#include "cmdline.h"
#include "catch.h"
#include "expr.h"
#include "parse.h"
#include "val.h"
#include "env.h"

void use_arguments(int argc, const char *argv[]) {
	if (argc == 1) {
		return;
	} else { // argc >= 2
		bool testSeen = false;
		for (int i = 1; i < argc; i++) {
			std::string ith_arg = argv[i];
			if (ith_arg == "--help") {
				std::cout << "Help Info: (all commands below will exit with a non-zero "
							 "status if there are any failures)"
						  << std::endl;
				std::cout
					<< "\t--test:\t\trun tests and exit with a 0 status if all pass"
					<< std::endl;
				std::cout << "\t--interp:\taccept a single expression on standard "
							 "input, parse it, interp it, print the result to standard "
							 "output, and print a newline"
						  << std::endl;
				std::cout << "\t--print:\taccept a single expression on standard input "
							 "and print it back out to standard output using the print "
							 "method of Expr, print a newline"
						  << std::endl;
				std::cout << "\t--pretty-print:\taccept a single expression on "
							 "standard input and print it back out to standard output "
							 "using the pretty_print method of Expr, print a newline"
						  << std::endl;
				exit(0); // as long as "--help" was seen, do not examine the rest
				// arguments
			} else if (ith_arg == "--test") {
				if (!testSeen) {
					int result = Catch::Session().run(1, argv);
					if (result != 0) {
						exit(1);
					}
					testSeen = true;
				} else { // duplicate "--test" detection
					std::cerr << "Duplicate --test occurred" << std::endl;
					exit(1);
				} // will not be valid in this case when enter Catch2
			} else if (ith_arg == "--interp") {
				try {
					// parse the std::cin
					// interp the std::cin
					// print out result
					std::cout << parse_str(std::cin)->interp(Env::empty)->to_string() << std::endl;
				} catch (std::runtime_error &e) {
					std::cout << e.what();
					exit(1);
				}
				exit(0);
			} else if (ith_arg == "--print") {
				try {
					// parse the std::cin
					// print the std::cin
					std::cout << parse_str(std::cin)->to_string() << std::endl;
				} catch (std::runtime_error &e) {
					std::cout << e.what();
					exit(1);
				}
				exit(0);
			} else if (ith_arg == "--pretty-print") {
				try {
					// parse the std::cin
					// print the std::cin
					std::cout << parse_str(std::cin)->to_pretty_string() << std::endl;
				} catch (std::runtime_error &e) {
					std::cout << e.what();
					exit(1);
				}
				exit(0);
			} else { // other string as arguments
				std::cerr << "Unknown argument" << std::endl;
				exit(1);
			}
		}
		return;
	}
}
