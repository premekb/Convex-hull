#pragma once

#include <fstream>
#include "point.hpp"


class svg_helper {
public:
    std::fstream* file_stream;

    svg_helper(std::fstream* file_stream);
    bool export_to_svg_file(const std::vector<point>& points);
    bool export_to_svg_file(const std::vector<point>& points, const std::vector<point>& hull_points);
    enum point_color{
        red_color,
        green_color,
        black_color
    };

private:
    void insert_point(point point, enum svg_helper::point_color);
    void draw_line_between_points(std::pair<point, point> points);
    void insert_svg_header();
    void insert_svg_ending_tag();
    std::pair<point, point> find_two_closest_points(const std::vector<point> &points, point p);
    double get_point_distance(point point1, point point2);
};


