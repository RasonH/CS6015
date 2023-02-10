//
//  cmdline.cpp
//  CommandLine
//
//  Created by Rason Hung on 1/16/23.
//

#define CATCH_CONFIG_RUNNER
#include "cmdline.h"
#include "catch.h"

using namespace std;

void use_arguments(int argc, const char *argv[]){
    if(argc == 1){
        return;
    }else{ //argc >= 2
        bool testSeen = false;
        for(int i = 1; i < argc; i++){
            string ith_arg = argv[i];
            if(ith_arg.compare("--help") == 0){
                cout << "Help: Enter '--test' as argument to get the program tested" << endl;
                exit(0); // as long as "--help" was seen, do not examine the rest arguments
            }else if(ith_arg.compare("--test") == 0){
                if(!testSeen){
                    int result = Catch::Session().run(1, argv);
                    if(result != 0){exit(1);}
                    testSeen = true;
                }else{ // duplicate "--test" detection
                    cerr << "Duplicate --test" << endl;
                    exit(1);
                } // will not be valid in this case when enter Catch2
            }else{ // other string as arguments
                cerr << "Unknown argument" << endl;
                exit(1);
            }
        }
        return;
    }
}
