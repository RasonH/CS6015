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
    if(argc == 1){
        return;
    }else{ //argc >= 2
        string second_arg = argv[1];
        if(second_arg.compare("--help") == 0){
            cout << "Enter '--test' as argument to get the program tested" << endl;
            exit(0);
        }
        if(second_arg.compare("--test") == 0){
            for(int i = 2; i < argc; i++){
                string ith_arg = arg[i];
                if(ith_arg.compare("--test") == 0){
                    cerr << "Duplicate arguments" << endl;
                    exit(1);
                }
            }
            cout << "Tests passed" << endl;
            return;
        }
        // the second argument is not --help or --test then it will be invalid
        cerr << "Invalid argument(s)" << endl;
        exit(1);
    }
}
