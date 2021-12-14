#pragma once
#include <vector>
#include <mutex>
#include "../point.hpp"

/**
 * Implements the quickhull algorithm as described in pseudocode on wikipedia.
 *
 * I paralelised the part, where the algorithm recursively divides the points into two parts and checks,
 * whether they are inside or outside the triangle.
 *
 * This version uses mutexes, to synchronise acces to the variable result, where
 */
class convex_hull_solver_parallel {
public:
    std::vector<point> quickhull_parallel();
    void findhull(std::vector<point> points, point point1, point point2);

    convex_hull_solver_parallel(const std::vector<point>& points, int threads) :
    points(points),
    threads_max(threads),
    threads_started(0)
    {}
private:
    const std::vector<point> points;
    std::vector<point> result;
    std::mutex* mutex;
    int threads_started;
    const int threads_max;

    std::vector<point> find_leftmost_and_rightmost_points() const;
    bool is_point_left(point& leftmost, point& rightmost, point& tested_point) const;
    double distance_from_line(point& line_point1, point& line_point2, point& tested_point) const;
    bool is_in_triangle(point& t_point1, point& t_point2, point& t_point3, point& tested_point) const;
    void add_to_result(point& p);
    void increment_threads_started(int increment);
};
