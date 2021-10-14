#pragma once

struct point {
    point(int x, int y);

    int x;
    int y;
};

point::point(int x, int y) : x(x), y(y) {}
