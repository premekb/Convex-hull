#include <iostream>
#include <fstream>
#include <vector>
#include "svg_helper.h"
#include "points_generator.h"
#include "quickhull_single_thead/convex_hull_solver.h"
#include "quickhull_parallel/convex_hull_solver_parallel.hpp"
#include "cmdline/app.cpp"
std::vector<std::string> get_commands(int argc, char *argv[]);


int main(int argc, char *argv[]) {
    std::vector<std::string> string_commands = get_commands(argc, argv);
    start_app(string_commands);
    return 0;
}

std::vector<std::string> get_commands(int argc, char *argv[]){
    std::vector<std::string> result;
    std::string tmp;
    for (int i = 1; i < argc; i++){
        tmp = argv[i];
        result.push_back(tmp);
    }
    return result;
}
