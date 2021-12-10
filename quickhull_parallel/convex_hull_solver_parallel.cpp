#include "convex_hull_solver_parallel.hpp"
#include "thread"
#include <math.h>

/**
 * TODO doplicate result
 * 100,100
 * 250,250
 * 500,500
 * 700,400
 */

std::vector<point> convex_hull_solver_parallel::quickhull_parallel() {
    result = find_leftmost_and_rightmost_points();
    point leftmost = result[0];
    point rightmost = result[1];
    std::vector<point> left_points;
    std::vector<point> right_points;

    for (point p : this->points){
        if (is_point_left(leftmost, rightmost, p)){
            left_points.push_back(p);
        }

        else{
            right_points.push_back(p);
        }
    }

    std::mutex mut;
    this->mutex = &mut;
    std::thread t1(&convex_hull_solver_parallel::findhull, this, right_points, leftmost, rightmost);
    std::thread t2(&convex_hull_solver_parallel::findhull, this, left_points, rightmost, leftmost);
    t1.join();
    t2.join();
    return result;
}

void convex_hull_solver_parallel::findhull(std::vector<point> points, point point1, point point2) {
    if (points.empty()) return;
    double max_distance = -1;
    double curr_distance;
    point max_point = points[0]; // TODO if only 2 or 1 points are present
    for (point p : points){
        curr_distance = distance_from_line(point1, point2, p);
        if (curr_distance > max_distance){
            max_distance = curr_distance;
            max_point = p;
        }
    }

    add_to_result(max_point);


    std::vector<point> left_points;
    std::vector<point> right_points;

    for (point p : points){
        if (p.x == max_point.x && p.y == max_point.y){
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

    findhull(left_points, point1, max_point);
    findhull(right_points, max_point, point2);
}

// TODO tady asi referenci, tohle nechcu modifikovat
convex_hull_solver_parallel::convex_hull_solver_parallel(std::vector<point> *points) {
    this->points = *points;
}

std::vector<point> convex_hull_solver_parallel::find_leftmost_and_rightmost_points() {
    auto *result = new std::vector<point>;
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

    result->push_back(leftmost);
    result->push_back(rightmost);

    return *result;
}

bool convex_hull_solver_parallel::is_point_left(point leftmost, point rightmost, point tested_point) {
    return (rightmost.x - leftmost.x) * (tested_point.y - leftmost.y) - (tested_point.x - leftmost.x) * (rightmost.y - leftmost.y) > 0;
}


double convex_hull_solver_parallel::distance_from_line(point line_point1, point line_point2, point tested_point) {
    double numerator = abs((line_point2.x - line_point1.x) * (line_point1.y - tested_point.y) - (line_point1.x - tested_point.x) * (line_point2.y - line_point1.y));
    double denominator = sqrt((line_point2.x - line_point1.x) * (line_point2.x - line_point1.x) + (line_point2.y - line_point1.y) * (line_point2.y - line_point1.y));
    return numerator / denominator;
}

void convex_hull_solver_parallel::remove_point(point point_to_remove) {
    // TODO if two generated poitns are the same, then continue in generator
    for (int i = 0; i < points.size(); i++){
        if (points[i].x == point_to_remove.x && points[i].y == point_to_remove.y){
            points.erase(points.begin(), points.begin() + i);
        }
    }
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
bool convex_hull_solver_parallel::is_in_triangle(point t_point1, point t_point2, point t_point3, point tested_point) {
    double denominator = ((t_point2.y - t_point3.y) * (t_point1.x - t_point3.x) +
                          (t_point3.x - t_point2.x) * (t_point1.y - t_point3.y));
    double a = ((t_point2.y - t_point3.y) * (tested_point.x - t_point3.x) +
                (t_point3.x - t_point2.x) * (tested_point.y - t_point3.y)) / denominator;
    double b = ((t_point3.y - t_point1.y) * (tested_point.x - t_point3.x) +
                (t_point1.x - t_point3.x) * (tested_point.y - t_point3.y)) / denominator;
    double c = 1 - a - b;

    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}

void convex_hull_solver_parallel::add_to_result(point p){
    std::unique_lock<std::mutex> lock(*this->mutex);
    result.push_back(p);
}