#include "circle.hpp"
#include <cmath>

void Circle::move(double dx, double dy) {
    center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
    // CASE1: r1 + r2 <= dist(c1,c2)     iA = 0
    double pi = 3.1415926535;
    double d = center.distanceFrom(otherCircle.center);
    double r1 = (radius > otherCircle.radius) ? radius : otherCircle.radius;
    double r2 = (radius > otherCircle.radius) ? otherCircle.radius : radius;
    if (d >= r1 + r2) {
        return 0;
    }
    // CASE2: inside
    else if (d <= r1 - r2) {
        return pi * r2 * r2;
    }
    // CASE3: interact
    else {
        double angle1=acos((r1*r1+d*d-r2*r2)/(2*r1*d));
        double angle2=acos((r2*r2+d*d-r1*r1)/(2*r2*d));
        return r1*r1*angle1+r2*r2*angle2-sin(angle1)*r1*d;
    }
}