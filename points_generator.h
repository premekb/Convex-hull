#pragma once
#include <vector>
#include "point.hpp"

/**
 * Generates random set of points.
 */
class points_generator {
public:
    points_generator(unsigned long long int amountOfPoints, unsigned long long int maximumAxisLength);
    std::vector<point> get_points();

private:
    unsigned long long amount_of_points;
    unsigned long long maximum_axis_length;
};
