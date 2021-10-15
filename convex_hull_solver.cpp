#include <iostream>
#include <math.h>
#include "convex_hull_solver.h"

std::vector<point> convex_hull_solver::quickhull() {
    result = find_leftmost_and_rightmost_points();
    std::vector<point> left_points;
    std::vector<point> right_points;

    for (point p : *this->points){
        if (is_point_left(result[0], result[1], p)){
            left_points.push_back(p);
        }

        else {
            right_points.push_back(p);
        }
    }


    return result;
}

convex_hull_solver::convex_hull_solver(const std::vector<point> *points) {
    this->points = points;
}

std::vector<point> convex_hull_solver::find_leftmost_and_rightmost_points() {
    auto *result = new std::vector<point>;
    point leftmost = point(-1, -1);
    point rightmost = point(-1, -1);
    for (point cur_point : *this->points){
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

// TODO this might not work properly
bool convex_hull_solver::is_point_left(point leftmost, point rightmost, point tested_point) {
    return (tested_point.x - leftmost.x) * (rightmost.y - leftmost.y) - (tested_point.y - leftmost.y)*(rightmost.x - leftmost.x) > 0;
}

void convex_hull_solver::findhull(std::vector<point> points, point point1, point point2) {
    if (points.empty()) return;
    double max_distance = -1;
    double curr_distance;
    point max_point = point(0, 0); // TODO if only 2 or 1 points are present
    for (point p : points){
        curr_distance = distance_from_line(point1, point2, p);
        if (curr_distance > max_distance){
            max_distance = curr_distance;
            max_point = p;
        }
    }
    result.push_back(max_point);
}

double convex_hull_solver::distance_from_line(point line_point1, point line_point2, point tested_point) {
   double numerator = abs((line_point2.x - line_point1.x) * (line_point1.y - tested_point.y) - (line_point1.x - tested_point.x) * (line_point2.y - line_point1.y));
   double denominator = sqrt((line_point2.x - line_point1.x) * (line_point2.x - line_point1.x) + (line_point2.y - line_point1.y) * (line_point2.y - line_point1.y));
   return numerator / denominator;
}

void convex_hull_solver::remove_point(point point_to_remove) {
    point a = this->points;

    for (int i = 0; i < points->size(); i++){
        if (this->points[i].  == point_to_remove.x && p.y == point_to_remove.y){
            this->points.po
        } // TODO if two generated poitns are the same, then continue in generator
    }
}
