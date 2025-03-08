// Copyright 2025 Durynichev Dmitriy
#include "tasks.h"
#include "circle.h"

double calculateGap() {
    double earthRadius = 6378.1;
    Circle earth(earthRadius);

    double ropeLength = earth.getFerence() + 0.001;
    earth.setFerence(ropeLength);

    double newRadius = earth.getRadius();
    double gap = newRadius - earthRadius;

    return gap;
}

double calculatePoolCost() {
    double poolRadius = 3;
    double pathWidth = 1;
    double concreteCostPerSquareMeter = 1000;
    double fenceCostPerMeter = 2000;

    Circle pool(poolRadius);
    Circle poolWithPath(poolRadius + pathWidth);

    double pathArea = poolWithPath.getArea() - pool.getArea();
    double fenceLength = poolWithPath.getFerence();

    double totalConcreteCost = pathArea * concreteCostPerSquareMeter;
    double totalFenceCost = fenceLength * fenceCostPerMeter;

    return totalConcreteCost + totalFenceCost;
}
