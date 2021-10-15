#pragma once
#include <vector>
#include "point.hpp"


class convex_hull_solver {
public:
    std::vector<point> quickhull();
    void findhull(std::vector<point> points, point point1, point point2);

    convex_hull_solver(const std::vector<point>* points);
private:
    const std::vector<point>* points;
    std::vector<point> result;
    std::vector<point> find_leftmost_and_rightmost_points();
    bool is_point_left(point leftmost, point rightmost, point tested_point);
    double distance_from_line(point line_point1, point line_point2, point tested_point);
    void remove_point(point point_to_remove); // TODO memory management
};
