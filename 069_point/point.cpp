#include "point.hpp"
#include <cmath>

void Point::move(double dx, double dy) {
    this->x += dx;
    this->y += dy;
}

double Point::distanceFrom(const Point & p) {
    return std::sqrt(std::pow(this->x-p.x, 2) + std::pow(this->y-p.y, 2));
}