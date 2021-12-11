#pragma once
#include <vector>
#include "../point.hpp"

/**
 * Implements the quickhull algorithm as described in pseudocode on wikipedia.
 */
class convex_hull_solver {
public:
    std::vector<point> quickhull();
    void findhull(std::vector<point> points, point point1, point point2);

    convex_hull_solver(const std::vector<point>& points) : points(points) {};
private:
    const std::vector<point> points;
    std::vector<point> result;

    std::vector<point> find_leftmost_and_rightmost_points() const;
    bool is_point_left(point& leftmost, point& rightmost, point& tested_point) const;
    double distance_from_line(point& line_point1, point& line_point2, point& tested_point) const;
    bool is_in_triangle(point& t_point1, point& t_point2, point& t_point3, point& tested_point) const;
};
