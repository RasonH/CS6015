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
    Expr* test = new Mult(new Num(1234),
                         new Let("x",
                                 new Let("z",
                                         new Num(2),
                                         new Add(new Var("z"),
                                                 new Num(5))),
                                 new Add(new Let("y",
                                                 new Num(3),
                                                 new Add(new Var("y"),
                                                         new Num(2))),
                                         new Var("x"))));
    Expr* test2 = new Add(new Mult(new Num(1234),
                          new Let("x",
                                  new Let("z",
                                          new Num(2),
                                          new Add(new Var("z"),
                                                  new Num(5))),
                                  new Let("y",
                                                  new Num(3),
                                                  new Add(new Var("y"),
                                                          new Num(2)))
                                          )),new Var("x"));
    std::cout << test->to_pretty_string() << std::endl;
    std::cout << test2->to_pretty_string() << std::endl; // should have parentheses for this, in front of first '_let' and in front of last 'x'

    return 0;
}
