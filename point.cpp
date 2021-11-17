#include "point.hpp"

std::ostream& operator<<(std::ostream &os, point const& p){
    os << "(" << p.x << ", " << p.y  << ")" << std::endl;
    return os;
}