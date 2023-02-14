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
    Expr* test = new Mult(new Num(1234), new Let("x", new Let("z", new Num(2), new Add(new Variable("z"), new Num(5))), new Add(new Let("y", new Num(3), new Add(new Variable("y"), new Num(2))), new Variable("x"))));
    std::cout << test->to_string() << std::endl;
    std::cout << test->to_pretty_string() << std::endl;
    std::cout << test->to_string() << std::endl;
    return 0;
}
