// Copyright 2025 Durynichev Dmitriy

#include "circle.h"
#include "tasks.h"
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

const double PI = 3.141592653589793;
const double EPSILON = 1e-6;

TEST(CircleTest, Constructor) {
Circle c(5.0);
EXPECT_NEAR(c.getRadius(), 5.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 5.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 25.0, EPSILON);
}

TEST(CircleTest, DefaultConstructor) {
Circle c(0.0);
EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, SetRadius) {
Circle c(0.0);
c.setRadius(3.0);
EXPECT_NEAR(c.getRadius(), 3.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 3.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 9.0, EPSILON);
}

TEST(CircleTest, SetFerence) {
Circle c(0.0);
c.setFerence(2 * PI * 4.0);
EXPECT_NEAR(c.getRadius(), 4.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 4.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 16.0, EPSILON);
}

TEST(CircleTest, SetArea) {
Circle c(0.0);
c.setArea(PI * 25.0);
EXPECT_NEAR(c.getRadius(), 5.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 5.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 25.0, EPSILON);
}

TEST(CircleTest, ZeroRadius) {
Circle c(0.0);
EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, NegativeRadius) {
Circle c(-5.0);
EXPECT_NEAR(c.getRadius(), -5.0, EPSILON);
}

TEST(CircleTest, LargeRadius) {
Circle c(1e6);
EXPECT_NEAR(c.getRadius(), 1e6, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 1e6, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 1e12, EPSILON);
}

TEST(CircleTest, SetRadiusUpdatesAll) {
Circle c(1.0);
c.setRadius(2.0);
EXPECT_NEAR(c.getRadius(), 2.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 2.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 4.0, EPSILON);
}

TEST(CircleTest, SetFerenceUpdatesAll) {
Circle c(1.0);
c.setFerence(2 * PI * 3.0);
EXPECT_NEAR(c.getRadius(), 3.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 3.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 9.0, EPSILON);
}

TEST(CircleTest, SetAreaUpdatesAll) {
Circle c(1.0);
c.setArea(PI * 4.0);
EXPECT_NEAR(c.getRadius(), 2.0, EPSILON);
EXPECT_NEAR(c.getFerence(), 2 * PI * 2.0, EPSILON);
EXPECT_NEAR(c.getArea(), PI * 4.0, EPSILON);
}

TEST(CircleTest, ConsistencyCheck) {
Circle c(5.0);
double r = c.getRadius();
c.setFerence(c.getFerence());
EXPECT_NEAR(c.getRadius(), r, EPSILON);
}

TEST(CircleTest, PrecisionCheck) {
Circle c(1.23456789);
EXPECT_NEAR(c.getRadius(), 1.23456789, EPSILON);
}

TEST(TaskRopeTest, BasicCase) {
std::ostringstream oss;
std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
taskRope();
std::cout.rdbuf(oldCout);
double expectedGap = 1.0 / (2 * PI);
double gap;
sscanf(oss.str().c_str(), "Earth and Rope gap: %lf meters", &gap);
EXPECT_NEAR(gap, expectedGap, 1e-3);
}

TEST(TaskRopeTest, ZeroExtraLength) {
Circle earth(6378.1e3);
double initialFerence = earth.getFerence();
Circle stretchedEarth(0.0);
stretchedEarth.setFerence(initialFerence);
double gap = stretchedEarth.getRadius() - earth.getRadius();
EXPECT_NEAR(gap, 0.0, EPSILON);
}

TEST(TaskRopeTest, LargeExtraLength) {
Circle earth(6378.1e3);
double initialFerence = earth.getFerence();
Circle stretchedEarth(0.0);
stretchedEarth.setFerence(initialFerence + 1000.0);
double gap = stretchedEarth.getRadius() - earth.getRadius();
EXPECT_NEAR(gap, 1000.0 / (2 * PI), 1e-3);
}

TEST(TaskRopeTest, SmallRadius) {
Circle earth(1.0);
double initialFerence = earth.getFerence();
Circle stretchedEarth(0.0);
stretchedEarth.setFerence(initialFerence + 1.0);
double gap = stretchedEarth.getRadius() - earth.getRadius();
EXPECT_NEAR(gap, 1.0 / (2 * PI), 1e-3);
}

TEST(TaskPoolTest, BasicCase) {
std::ostringstream oss;
std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
taskPool();
std::cout.rdbuf(oldCout);
Circle pool(3.0);
Circle poolWithPath(4.0);
double pathArea = poolWithPath.getArea() - pool.getArea();
double fenceLength = poolWithPath.getFerence();
double expectedCost = pathArea * 1000.0 + fenceLength * 2000.0;
double cost;
sscanf(oss.str().c_str(), "Pool cost: %lf rubles", &cost);
EXPECT_NEAR(cost, expectedCost, EPSILON);
}

TEST(TaskPoolTest, ZeroPathWidth) {
Circle pool(3.0);
Circle poolWithPath(3.0);
double pathArea = poolWithPath.getArea() - pool.getArea();
double fenceLength = poolWithPath.getFerence();
double expectedCost = pathArea * 1000.0 + fenceLength * 2000.0;
EXPECT_NEAR(expectedCost, 2 * PI * 3.0 * 2000.0, EPSILON);
}

TEST(TaskPoolTest, LargePathWidth) {
Circle pool(3.0);
Circle poolWithPath(5.0);
double pathArea = poolWithPath.getArea() - pool.getArea();
double fenceLength = poolWithPath.getFerence();
double expectedCost = pathArea * 1000.0 + fenceLength * 2000.0;
double manualCost = (PI * 25.0 - PI * 9.0) * 1000.0 + 2 * PI * 5.0 * 2000.0;
EXPECT_NEAR(expectedCost, manualCost, EPSILON);
}

TEST(TaskPoolTest, ZeroRadius) {
Circle pool(0.0);
Circle poolWithPath(1.0);
double pathArea = poolWithPath.getArea() - pool.getArea();
double fenceLength = poolWithPath.getFerence();
double expectedCost = pathArea * 1000.0 + fenceLength * 2000.0;
double manualCost = PI * 1.0 * 1000.0 + 2 * PI * 1.0 * 2000.0;
EXPECT_NEAR(expectedCost, manualCost, EPSILON);
}