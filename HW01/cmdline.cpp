//
//  cmdline.cpp
//  CommandLine
//
//  Created by Rason Hung on 1/16/23.
//

#pragma include once
#include "cmdline.h"
using namespace std;

void use_arguments(int argc, const char *argv[]){
//    string first_arg = argv[0];
//    if(first_arg.compare("./msdscript") != 0){
//        cerr << "Invalid program name" << endl;
//        exit(1);
//    }
    if(argc == 1){
        return;
    }else{ //argc >= 2
        string second_arg = argv[1];
        if(second_arg.compare("--help") == 0){
            cout << "Enter '--test' as argument to get the program tested" << endl;
            exit(0);
        }
        if(argc == 2 && second_arg.compare("--test") == 0){ //only if one "--test" existed
            cout << "Tests passed" << endl;
            return;
            /*
             //instead of using for loop to judge compare arguments (coming after the first "--test") with "--test", I combined it to the situation with other invalid input
             //example code if it is required to use a loop:
             
             for(int i = 2; i < argc; i++){
                string ith_arg = arg[i];
                if(arg[i].compare("--test") == 0){
                    cerr << "Duplicate arguments" << endl;
                    exit(1);
                }else{
                    cerr << "Invalid argument(s)" << endl;
                    exit(1);
                }
             }
             //actually, it will only examine to the third argument at most, and exit with 1 anyway. The only difference is different error message
            */
        }
        cerr << "Invalid argument(s)" << endl;
        exit(1);
    }
}
