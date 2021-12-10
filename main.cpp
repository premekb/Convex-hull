#include <iostream>
#include <fstream>
#include <vector>
#include "svg_helper.h"
#include "points_generator.h"
#include "quickhull_single_thead/convex_hull_solver.h"
#include "cmdline/app.cpp"
std::vector<std::string> get_commands(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    std::vector<std::string> string_commands = get_commands(argc, argv);
    start_app(string_commands);
    /**
    points_generator gen(100, 1000);

    std::fstream before_file("before_hull.svg", std::fstream::out);
    std::fstream after_file("after_hull.svg", std::fstream::out);

    std::vector<point>* points = gen.get_points();
    for (point p : *points){
        std::cout << p.x << ";" << p.y << std::endl;
    }

    svg_helper x(&before_file);
    x.export_to_svg_file(*points);

    convex_hull_solver solver = convex_hull_solver(points);
    std::vector<point> result = solver.quickhull();


    svg_helper y(&after_file);
    y.export_to_svg_file(*points, result);**/
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
