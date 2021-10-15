#include <vector>
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

    // TODO Delete later ------------
    point leftmost = point(-1, -1);
    point rightmost = point(-1, -1);
    for (point cur_point : points){
        if (leftmost.x == - 1) {
            leftmost = cur_point;
            rightmost = cur_point;
        }

        else {
            if (cur_point.x < leftmost.x) leftmost = cur_point;
            else if (cur_point.x > rightmost.x) rightmost = cur_point;
        }
    }
    draw_line_between_points(std::pair<point, point>{leftmost, rightmost});
// TODO delete ----------
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
