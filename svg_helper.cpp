#include <vector>
#include <math.h>
#include "svg_helper.h"
#include <math.h>

/**
 * Inserts a single points into the svg file.
 *
 * @param point
 * @param color
 */
void svg_helper::insert_point(point point, svg_helper::point_color color) {
    if (color == black_color){
        *this->file_stream << "<circle cx=\"" <<  point.x << "\" cy=\""<< point.y << "\" r=\"2\"/>" << std::endl;
    }

    else if (color == red_color){
        *this->file_stream << "<circle cx=\"" <<  point.x << "\" cy=\""<< point.y << "\" r=\"2\" fill=\"#ff0000\"/>" << std::endl;
    }

    else if (color == green_color){
        *this->file_stream << "<circle cx=\"" <<  point.x << "\" cy=\""<< point.y << "\" r=\"2\" fill=\"#008000\"/>" << std::endl;
    }
}

void svg_helper::insert_svg_header() {
    *this->file_stream << "<?xml version=\"1.0\"?>" << std::endl;
    *this->file_stream << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl;
    *this->file_stream << std::endl;
    *this->file_stream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">" << std::endl;
}

void svg_helper::insert_svg_ending_tag() {
    *this->file_stream << "</svg>" << std::endl;
}

svg_helper::svg_helper(std::fstream* file_stream) {
    this->file_stream = file_stream;
}

bool svg_helper::export_to_svg_file(const std::vector<point>& points) {
    this->insert_svg_header();

    for (point p : points){
        this->insert_point(p, green_color);
    }

    this->insert_svg_ending_tag();
    this->file_stream->close();
    return true;
}

/**
 * Connects two points with a line
 *
 * @param points
 */
void svg_helper::draw_line_between_points(std::pair<point, point> points) {
    *this->file_stream << "<line x1=\"" <<
    points.first.x << "\" y1=\""<<
    points.first.y <<"\" x2=\""<<
    points.second.x <<"\" y2=\"" <<
    points.second.y << "\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />"
    << std::endl;
}

/**
 * Exports points to a .svg file and connects the convex hull points with a line.
 *
 * @param points
 * @param hull_points
 * @return
 */
bool svg_helper::export_to_svg_file(const std::vector<point> &points, const std::vector<point> &hull_points) {
    this->insert_svg_header();

    double adjusted_ratio = get_ratio_change(1000, points);
    std::vector<point> points_adjusted_ratio = change_ratio(points, adjusted_ratio);
    std::vector<point> hull_points_adjusted_ratio = change_ratio(hull_points, adjusted_ratio);

    for (point p : points_adjusted_ratio){
        this->insert_point(p, green_color);
    }

    for (point p : hull_points_adjusted_ratio){
        insert_point(p, red_color);
    }

    std::vector<std::pair<double, point>> angles = get_points_sorted_by_angle(hull_points_adjusted_ratio, point(500, 500)); //TODO center

    for (int i = 0; i < angles.size() - 1; i++){
        draw_line_between_points(std::make_pair(angles[i].second, angles[i + 1].second));
    }

    draw_line_between_points(std::make_pair(angles[angles.size() - 1].second, angles[0].second));

    this->insert_svg_ending_tag();
    this->file_stream->close();
    return true;

}

/**
 * Calculates the angle of points in respect to a given center and sorts them.
 *
 * I am not completely sure with the math behind it, however it uses barycentric coordinates in respect to a center of
 * the 2 plane, and sorts the points by the angle they hold to the center.
 *
 * @return
 */
std::vector<std::pair<double, point>>
svg_helper::get_points_sorted_by_angle(const std::vector<point>& points, point center){
    std::vector<std::pair<double, point>> angles;

    for (point p : points){
        angles.push_back(std::make_pair(atan2(p.y - center.y, p.x - center.x), p));
    }

    std::sort(angles.begin(), angles.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    return angles;
}

/**
 * Changes the ratio of the points, so that they can be drawn on a 1000x1000 canvas.
 *
 * @param points
 * @return
 */
std::vector<point> svg_helper::change_ratio(const std::vector<point> &points, double ratio_change) {
    std::vector<point> changed_points;

    for (point p : points){
        changed_points.push_back(point(p.x / ratio_change, p.y / ratio_change));
    }

    return changed_points;
}

double svg_helper::get_ratio_change(const int &max_axis_length, const std::vector<point> &points) {
    double highest_axis_value = 0; // TODO if i decide to use negative values too
    for (point p : points){
        if (p.x > highest_axis_value) highest_axis_value = p.x;
        if (p.y > highest_axis_value) highest_axis_value = p.y;
    }
    double result = highest_axis_value / max_axis_length;
    return result > 1 ? result : 1;
}
