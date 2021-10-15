#include <iostream>
#include <fstream>
#include <vector>
#include "svg_helper.h"
#include "points_generator.h"
#include "convex_hull_solver.h"

int main() {
    points_generator gen(50, 1000);

    std::fstream file("try.svg", std::fstream::out);

    const std::vector<point>* points = gen.get_points();
    convex_hull_solver solver = convex_hull_solver(points);
    std::vector<point> result = solver.quickhull();


    svg_helper x(&file);
    x.export_to_svg_file(result);
    return 0;
}
