/**
 * \mainpage MSDScript
 * \author Juisheng Hung (Rason)
 * \date 01-16-2023
 * \brief passing arguments through command line, execute with --help, --test ...
 */

#include "cmdline.h"
#include "expr.h"

/*! \brief passing arguments through command line
 *  --help --test ...
*/
int main(int argc, const char * argv[]) {
    use_arguments(argc, argv);
    return 0;
}
