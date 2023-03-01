//
// Created by Rason Hung on 2/28/23.
//

#include <string>
#include <iostream>
#include "exec.h"

const int Itr = 100;
const int Prob_Precision = 100;
const int Max_Num_Length = 5;
const int Max_Garbage_Length = 10; // the length limit of garbage string
const int Max_Var_Length = 10;
// Garbage_Prob + others = 100 (%)
const int Garbage_Prob = 10;
// The actual probability of the followings should be (100 - Garbage_Prob) * X_Prob (%)
// Num + Var + Add + Mult + Let = 100
const int Num_Prob = 35; // Num + Var probability should not be 0 - prevent infinite loop
const int Var_Prob = 15;
const int Par_Prob = 15;
const int Add_Prob = 10;
const int Mult_Prob = 15;
const int Let_Prob = 10; // though might not be used, still important

std::string random_string();
std::string random_expr_string();
std::string random_var_string();
//helper
int pow(int base, const int exponent);

int main(int argc, char *argv[]){

    if(argc <= 1 || argc >= 4){
        std::cerr << "Invalid argument numbers for test_msdscript, please input 2 to 3 arguments.\nUsage: test_msdscript <program0> <program1 (optional)>" << std::endl;
        exit(1);
    }

    /*
    test_msdscript program should work in two modes:
    When given a single argument, that argument is used as a path for an msdscript program,
        and test_msdscript should test that msdscript implementation on randomly generated programs.
    When given two arguments, each argument is used as the path to an msdscript program,
        and test_msdscript should try to find a program and mode (--interp, --print, or --pretty-print) where the two programs disagree.
     */

    srand(clock());

    // check the range for const arguments - not strict
    if((Let_Prob + Mult_Prob + Add_Prob + Par_Prob + Var_Prob + Num_Prob) / Prob_Precision != 1){
        std::cerr << "Please check the probability distribution of test generation, which should be equals to 100%." << std::endl;
        exit(1);
    }

    const char * const interp_argv[] = {argv[1], "--interp"};
    const char * const print_argv[] = {argv[1], "--print"};
    const char * const pretty_print_argv[] = {argv[1], "--pretty-print"};


    if(argc == 2 || argc == 3){
        for(int i = 0; i < Itr; i++){
            std::string in = random_string();
            std::string program_name = argv[1];
            std::cout << ">>>> Trying " << in << std::endl;

            ExecResult interp_result = exec_program(2, interp_argv, in);
            ExecResult print_result = exec_program(2, print_argv, in);
            ExecResult pretty_print_result = exec_program(2, pretty_print_argv, in);

            // test_msdscript <program0> -- only testing program0 without comparing with the other program
            if (argc == 2) {
                ExecResult re_interp_print_result = exec_program(2, interp_argv, print_result.out);
                ExecResult re_interp_pretty_print_result = exec_program(2, interp_argv,
                                                                        pretty_print_result.out);

                if (interp_result.exit_code != re_interp_print_result.exit_code) {
                    std::cout << "\t[" + program_name + "] Different exit code: interp(" +
                                 std::to_string(interp_result.exit_code) + ") - print(" +
                                 std::to_string(re_interp_print_result.exit_code) + ")." << std::endl;
                }

                if (interp_result.exit_code != re_interp_pretty_print_result.exit_code) {
                    std::cout << "\t[" + program_name + "] Different exit code: interp(" +
                                             std::to_string(interp_result.exit_code) + ") - pretty_print(" +
                                             std::to_string(re_interp_pretty_print_result.exit_code) + ")." << std::endl;
                }
                if (interp_result.out != re_interp_print_result.out) {
                    std::cout << "\t[" + program_name + "] Different output: interp(" + interp_result.out +") - print(" + re_interp_print_result.out + ")." << std::endl;
                }

                if (interp_result.out != re_interp_pretty_print_result.out) {
                    std::cout << "\t[" + program_name + "] Different output: interp(" + interp_result.out +") - pretty_print(" + re_interp_pretty_print_result.out + ")." << std::endl;
                }
            }

            // test_msdscript <program0> <program1> -- testing program0 comparing with program1
            if(argc == 3) {
                std::string program_name2 = argv[2];
                const char *const interp_argv2[] = {argv[2], "--interp"};
                const char *const print_argv2[] = {argv[2], "--print"};
                const char *const pretty_print_argv2[] = {argv[2], "--pretty-print"};

                ExecResult interp_result2 = exec_program(2, interp_argv2, in);
                ExecResult print_result2 = exec_program(2, print_argv2, in);
                ExecResult pretty_print_result2 = exec_program(2, pretty_print_argv2, in);

                if (interp_result.exit_code != interp_result2.exit_code || interp_result.out != interp_result2.out) {
                    std::cout << "\t[" + program_name + " & " + program_name2 + "] Different result for interp:\n"
                                                                                "\t[" + program_name + "] " +
                                 std::to_string(interp_result.exit_code) + ", " + interp_result.out +
                                 "\t[" + program_name2 + "] " + std::to_string(interp_result2.exit_code) + ", " +
                                 interp_result2.out << std::endl;
                }

                if (print_result.exit_code != print_result2.exit_code || print_result.out != print_result2.out) {
                    std::cout << "\t[" + program_name + " & " + program_name2 + "] Different result for print:\n"
                                                                                "\t[" + program_name + "] " +
                                 std::to_string(print_result.exit_code) + ", " + print_result.out +
                                 "\t[" + program_name2 + "] " + std::to_string(print_result2.exit_code) + ", " +
                                 print_result2.out << std::endl;
                }

                if (pretty_print_result.exit_code != pretty_print_result2.exit_code ||
                    pretty_print_result.out != pretty_print_result2.out) {
                    std::cout
                            << "\t[" + program_name + " & " + program_name2 + "] Different result for pretty_print:\n"
                                                                              "\t[" + program_name + "] " +
                               std::to_string(pretty_print_result.exit_code) + ", " + pretty_print_result.out +
                               "\t[" + program_name2 + "] " + std::to_string(pretty_print_result2.exit_code) + ", " +
                               pretty_print_result2.out << std::endl;
                }
            }
        }
    }
}

//generate all possible strings including garbage and valid expressions
std::string random_string(){
    if((rand() % 100 < Garbage_Prob)){
        std::string word = "";
        for(int i = rand() % Max_Garbage_Length; i >= 0; i--){
            word += rand() % 256;
        }
        return word;
    }else{
        return random_expr_string();
    }
}

//generate valid expression
std::string random_expr_string(){
    /*
     〈expr〉 = 〈number〉
             |〈variable〉
             | (〈expr〉)
             |〈expr〉 + 〈expr〉
             |〈expr〉 * 〈expr〉
             | _let〈variable〉=〈expr〉_in〈expr〉
     */
    int rand_num = rand();
    if(rand_num % 100 < Num_Prob){
        int neg = ((rand() % 2) == 0) ? -1 : 1;
        return std::to_string((rand() % pow(10, Max_Num_Length)) * neg);
    }else if(rand_num % 100 < Var_Prob + Num_Prob){
        return random_var_string();
    }else if(rand_num % 100 < Par_Prob + Var_Prob + Num_Prob){
        return "( " + random_expr_string() + " )";
    }else if(rand_num % 100 < Add_Prob + Par_Prob + Var_Prob + Num_Prob){
        return random_expr_string() + " + " + random_expr_string();
    }else if(rand_num % 100 < Mult_Prob + Add_Prob + Par_Prob + Var_Prob + Num_Prob){
        return random_expr_string() + " * " + random_expr_string();
    }else{
        return "_let " + random_var_string() + " = " + random_expr_string() + " _in " + random_expr_string();
    }

}

int pow(int base, const int exponent) {
    int result = 1;
    for(int i = 1; i <= exponent; i++){
        result *= base;
    }
    return result;
}

std::string random_var_string(){
    std::string word = "";
    for(int i = rand() % Max_Var_Length; i >= 0; i--){
        word += (rand() % 26 + (rand() % 2 == 0 ? 65 : 97));
    }
    return word;
}
