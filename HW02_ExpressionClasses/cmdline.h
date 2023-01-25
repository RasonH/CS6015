//
//  cmdline.h
//  CommandLine
//
//  Created by Rason Hung on 1/16/23.
//

#pragma include once
#include <iostream>
#include <string>

/*
 Take arguments from command line as input, execute coressponding output as required
 "--help": if it is the next argument after program name, print out help message, and do not examine other arguments
 "--test": if it is the only argument after program name, then print out test result, otherwise, will be treated as invalid argument input
 any other strings as input: invalid argument, exit the program with 1
 */
void use_arguments(int argc, const char *argv[]);
