//
//  cmdline.h
//  CommandLine
//
//  Created by Rason Hung on 1/16/23.
//

/**
 * \file cmdline.h
 * \brief actual function that executes command line script
 */

#pragma include once

#include <iostream>
#include <string>

/**
* \brief Take arguments from command line as input, execute corresponding output as required
* \param argc first argument, the integer number of arguments passed into
* \param argv second argument, the pointer to the array of characters that is passed into as parameter
* \return returns void\n
* "--help": if it is the next argument after program name, print out help message, and do not examine other arguments\n
* "--test": if it is the only argument after program name, then print out test result\n
* otherwise, will be treated as invalid argument input any other strings as input: invalid argument, exit the program with 1
*/
void use_arguments(int argc, const char *argv[]);
