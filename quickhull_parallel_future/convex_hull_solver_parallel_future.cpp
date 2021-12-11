#include "convex_hull_solver_parallel_future.hpp"
#include "thread"
#include <math.h>
#include <future>

std::vector<point> convex_hull_solver_parallel_future::quickhull_parallel() {
    result = find_leftmost_and_rightmost_points();
    point leftmost = result[0];
    point rightmost = result[1];
    std::vector<point> left_points;
    std::vector<point> right_points;

    for (point p : this->points){
        if (p == leftmost || p == rightmost) continue;
        if (is_point_left(leftmost, rightmost, p)){
            left_points.push_back(p);
        }

        else{
            right_points.push_back(p);
        }
    }

    std::mutex mut;
    this->mutex = &mut;
    this->threads_started = 2;
    std::future<std::vector<point>> ret1 = std::async(&convex_hull_solver_parallel_future::findhull, this, right_points, leftmost, rightmost);
    std::future<std::vector<point>> ret2 = std::async(&convex_hull_solver_parallel_future::findhull, this, left_points, rightmost, leftmost);
    std::vector<point> left_result = ret1.get();
    std::vector<point> right_result = ret2.get();

    result.insert(result.end(), right_result.begin(), right_result.end());
    result.insert(result.end(), left_result.begin(), left_result.end());

    return result;
}

std::vector<point> convex_hull_solver_parallel_future::findhull(std::vector<point> points, point point1, point point2) {
    std::vector<point> local_result;
    if (points.empty()) return local_result;
    double max_distance = -1;
    double curr_distance;
    point max_point = points[0];
    for (point p : points){
        curr_distance = distance_from_line(point1, point2, p);
        if (curr_distance > max_distance){
            max_distance = curr_distance;
            max_point = p;
        }
    }

    local_result.push_back(max_point);

    std::vector<point> left_points;
    std::vector<point> right_points;

    for (point p : points){
        if (p == max_point){
            continue;
        }
        if (!is_in_triangle(point1, point2, max_point, p)){
            if (!is_point_left(point1, max_point, p)){
                left_points.push_back(p);
            }

            else if (!is_point_left(max_point, point2, p)){
                right_points.push_back(p);
            }
        }
    }

    std::vector<point> left_result;
    std::vector<point> right_result;
    if (this->threads_started < this->threads_max){
        std::future<std::vector<point>> ret1 = std::async(&convex_hull_solver_parallel_future::findhull, this, left_points, point1, max_point);
        std::future<std::vector<point>> ret2 = std::async(&convex_hull_solver_parallel_future::findhull, this, right_points, max_point, point2);
        increment_threads_started(2);
        left_result = ret1.get();
        right_result = ret2.get();
    }

    else{
        left_result = findhull(left_points, point1, max_point);
        right_result = findhull(right_points, max_point, point2);
    }

    local_result.insert(local_result.end(), right_result.begin(), right_result.end());
    local_result.insert(local_result.end(), left_result.begin(), left_result.end());
    return local_result;
}

std::vector<point> convex_hull_solver_parallel_future::find_leftmost_and_rightmost_points() const{
    std::vector<point> result;
    point leftmost = point(-1, -1);
    point rightmost = point(-1, -1);
    for (point cur_point : this->points){
        if (leftmost.x == - 1) {
            leftmost = cur_point;
            rightmost = cur_point;
        }

        else {
            if (cur_point.x < leftmost.x) leftmost = cur_point;
            else if (cur_point.x > rightmost.x) rightmost = cur_point;
        }
    }

    result.push_back(leftmost);
    result.push_back(rightmost);

    return result;
}

bool convex_hull_solver_parallel_future::is_point_left(point& leftmost, point& rightmost, point& tested_point) const{
    return (rightmost.x - leftmost.x) * (tested_point.y - leftmost.y) - (tested_point.x - leftmost.x) * (rightmost.y - leftmost.y) > 0;
}


double convex_hull_solver_parallel_future::distance_from_line(point& line_point1, point& line_point2, point& tested_point) const{
    double numerator = abs((line_point2.x - line_point1.x) * (line_point1.y - tested_point.y) - (line_point1.x - tested_point.x) * (line_point2.y - line_point1.y));
    double denominator = sqrt((line_point2.x - line_point1.x) * (line_point2.x - line_point1.x) + (line_point2.y - line_point1.y) * (line_point2.y - line_point1.y));
    return numerator / denominator;
}

/**
 * Inspired by the formula on this website:
 * http://totologic.blogspot.com/2014/01/accurate-point-in-triangle-test.html
 * @param t_point1
 * @param t_point2
 * @param t_point3
 * @param tested_point
 * @return
 */
bool convex_hull_solver_parallel_future::is_in_triangle(point& t_point1, point& t_point2, point& t_point3, point& tested_point) const{
    double denominator = ((t_point2.y - t_point3.y) * (t_point1.x - t_point3.x) +
                          (t_point3.x - t_point2.x) * (t_point1.y - t_point3.y));
    double a = ((t_point2.y - t_point3.y) * (tested_point.x - t_point3.x) +
                (t_point3.x - t_point2.x) * (tested_point.y - t_point3.y)) / denominator;
    double b = ((t_point3.y - t_point1.y) * (tested_point.x - t_point3.x) +
                (t_point1.x - t_point3.x) * (tested_point.y - t_point3.y)) / denominator;
    double c = 1 - a - b;

    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}

void convex_hull_solver_parallel_future::increment_threads_started(int increment){
    std::unique_lock<std::mutex> lock(*this->mutex);
    this->threads_started += increment;
}