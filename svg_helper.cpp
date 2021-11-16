#include <vector>
#include <math.h>
#include "svg_helper.h"

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

void svg_helper::draw_line_between_points(std::pair<point, point> points) {
    *this->file_stream << "<line x1=\"" <<
    points.first.x << "\" y1=\""<<
    points.first.y <<"\" x2=\""<<
    points.second.x <<"\" y2=\"" <<
    points.second.y << "\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />"
    << std::endl;
}

bool svg_helper::export_to_svg_file(const std::vector<point> &points, const std::vector<point> &hull_points) {
    this->insert_svg_header();

    for (point p : points){
        this->insert_point(p, green_color);
    }

    for (point p : hull_points){
        insert_point(p, red_color);
        //std::pair<point, point> closest_points = find_two_closest_points(hull_points, p);
        //draw_line_between_points(std::pair<point, point>{closest_points.first, p});
        //draw_line_between_points(std::pair<point, point>{closest_points.second, p});
    }

    this->insert_svg_ending_tag();
    this->file_stream->close();
    return true;

}

std::pair<point, point> svg_helper::find_two_closest_points(const std::vector<point> &points, point p) {
    double min_distance;
    point closest_point = point(-1, -1);
    point second_closest_point = point(-1, -1);

    double curr_distance;
    for (point p2 : points){
        if (p2.x == p.x && p2.y == p.y) continue;
        if (closest_point.x == -1) {
            closest_point = p2;
            second_closest_point = p2;
            min_distance = get_point_distance(p, p2);
            continue;
        }
        curr_distance = get_point_distance(p, p2);
        if (curr_distance < min_distance){
            second_closest_point = closest_point;
            min_distance = curr_distance;
            closest_point = p2;
        }
    }
    return std::pair<point, point>{closest_point, second_closest_point};
}

double svg_helper::get_point_distance(point point1, point point2) {
    return sqrt(((point2.x - point1.x) * (point2.x - point1.x) + ((point2.y - point1.y) * (point2.y - point1.y))));
}
