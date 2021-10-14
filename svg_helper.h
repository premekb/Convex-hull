//
// Created by Přemek Bělka on 15.10.2021.
//

#ifndef SEMESTRALKA_SVG_HELPER_H
#define SEMESTRALKA_SVG_HELPER_H
#include <fstream>
#include "point.hpp"


class svg_helper {
public:
    bool export_to_svg_file(std::fstream file_stream);

private:
    void insert_point(point point);
};


#endif //SEMESTRALKA_SVG_HELPER_H
