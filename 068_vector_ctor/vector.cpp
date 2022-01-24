#include "vector.hpp"

#include <cmath>
#include <cstdio>


double Vector2D::getMagnitude() const {
    return std::sqrt(std::pow(x,2) + std::pow(y,2));
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
    Vector2D ans;
    ans.x = this->x + rhs.x;
    ans.y = this->y + rhs.y;
    return ans;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
    this->x = this->x + rhs.x;
    this->y = this-> y + rhs.y;
    return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
    return this->x*rhs.x + this->y*rhs.y;
}
void Vector2D::print() const {
    std::printf("<%.2f, %.2f>", x, y);
}