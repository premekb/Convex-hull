#include "points_generator.h"
#include <random>

points_generator::points_generator(unsigned long long int amountOfPoints, unsigned long long int maximumAxisLength)
        : amount_of_points(amountOfPoints), maximum_axis_length(maximumAxisLength) {
    this->amount_of_points = amountOfPoints;
    this->maximum_axis_length = maximumAxisLength;
}

std::vector<point>* points_generator::get_points() {
    std::vector<point> *points = new std::vector<point>;
    std::mt19937 mt{ std::random_device{}() };
    static std::uniform_int_distribution<> dist(0, this->maximum_axis_length); // todo je vrchni hranice inclusive oder nicht?
    for (int i = 0; i < this->amount_of_points; ++i) {
        points->push_back(point(dist(mt), dist(mt)));
    }
    return points;
}
