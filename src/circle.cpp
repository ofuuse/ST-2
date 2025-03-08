#include <cstdint>
#include <cmath>
#include <stdexcept>
#include "circle.h"

Circle::Circle(double r) {
    setRadius(r);
}

void Circle::updateFerence() {
    ference = 2 * M_PI * radius;
}

void Circle::updateArea() {
    area = M_PI * radius * radius;
}

void Circle::setRadius(double r) {
    if (r < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    radius = r;
    updateFerence();
    updateArea();
}

void Circle::setFerence(double f) {
    if (f < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    ference = f;
    radius = f / (2 * M_PI);
    updateArea();
}

void Circle::setArea(double a) {
    if (a < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    area = a;
    radius = sqrt(a / M_PI);
    updateFerence();
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getFerence() const {
    return ference;
}

double Circle::getArea() const {
    return area;
}
