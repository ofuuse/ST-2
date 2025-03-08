// Copyright 2025 Durynichev Dmitriy
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_
#include <cstdint>

class Circle {
private:
    double radius;
    double ference;
    double area;
    void updateFerence();
    void updateArea();
public:
    explicit Circle(double r);
    void setRadius(double r);
    void setFerence(double f);
    void setArea(double a);
    double getRadius() const;
    double getFerence() const;
    double getArea() const;
};

#endif  // INCLUDE_CIRCLE_H_
