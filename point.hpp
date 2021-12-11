#pragma once
#include <iostream>

struct point {
    point(int x, int y) : x(x), y(y) {}

    int x;
    int y;

    bool operator==(const point& rhs) const{
        return x == rhs.x && y == rhs.y;
    }
};

std::ostream& operator<<(std::ostream &os, point const& p);


