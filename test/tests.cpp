// Copyright 2025 Durynichev Dmitriy

#include <gtest/gtest.h>
#include <cstdint>
#include <cassert>
#include <cmath>
#include "circle.h"
#include "tasks.h"

TEST(CircleTest, ConstructorPositiveRadius) {
Circle c(5.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 5.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 2 * M_PI * 5.0);
EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 25.0);
}

TEST(CircleTest, ConstructorZeroRadius) {
Circle c(0.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, ConstructorNegativeRadiusThrows) {
EXPECT_THROW(Circle c(-1.0), std::invalid_argument);
}

TEST(CircleTest, SetRadiusPositive) {
Circle c(1.0);
c.setRadius(3.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 3.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 2 * M_PI * 3.0);
EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 9.0);
}

TEST(CircleTest, SetRadiusZero) {
Circle c(1.0);
c.setRadius(0.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetRadiusNegativeThrows) {
Circle c(1.0);
EXPECT_THROW(c.setRadius(-2.0), std::invalid_argument);
}

TEST(CircleTest, SetFerencePositive) {
Circle c(1.0);
c.setFerence(2 * M_PI * 2.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 2.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 2 * M_PI * 2.0);
EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 4.0);
}

TEST(CircleTest, SetFerenceZero) {
Circle c(1.0);
c.setFerence(0.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetFerenceNegativeThrows) {
Circle c(1.0);
EXPECT_THROW(c.setFerence(-1.0), std::invalid_argument);
}

TEST(CircleTest, SetAreaPositive) {
Circle c(1.0);
c.setArea(M_PI * 4.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 2.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 2 * M_PI * 2.0);
EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 4.0);
}

TEST(CircleTest, SetAreaZero) {
Circle c(1.0);
c.setArea(0.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetAreaNegativeThrows) {
Circle c(1.0);
EXPECT_THROW(c.setArea(-1.0), std::invalid_argument);
}

TEST(CircleTest, GetRadius) {
Circle c(2.5);
EXPECT_DOUBLE_EQ(c.getRadius(), 2.5);
}

TEST(CircleTest, GetFerence) {
Circle c(2.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 2 * M_PI * 2.0);
}

TEST(CircleTest, GetArea) {
Circle c(3.0);
EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 9.0);
}

TEST(CircleTest, ConsistencyAfterMultipleSets) {
Circle c(1.0);
c.setRadius(2.0);
c.setFerence(2 * M_PI * 3.0);
c.setArea(M_PI * 4.0);
EXPECT_DOUBLE_EQ(c.getRadius(), 2.0);
EXPECT_DOUBLE_EQ(c.getFerence(), 2 * M_PI * 2.0);
EXPECT_DOUBLE_EQ(c.getArea(), M_PI * 4.0);
}

// Тесты для задач
TEST(TasksTest, CalculateGap) {
double gap = calculateGap();
double earthRadius = 6378.1;
double expectedNewRadius = (2 * M_PI * earthRadius + 0.001) / (2 * M_PI);
double expectedGap = expectedNewRadius - earthRadius;
EXPECT_NEAR(gap, expectedGap, 1e-10);
}

TEST(TasksTest, CalculatePoolCost) {
double cost = calculatePoolCost();
double poolRadius = 3.0;
double pathWidth = 1.0;
double concreteCost = 1000.0;
double fenceCost = 2000.0;

double poolArea = M_PI * poolRadius * poolRadius;
double totalArea = M_PI * (poolRadius + pathWidth) * (poolRadius + pathWidth);
double pathArea = totalArea - poolArea;
double fenceLength = 2 * M_PI * (poolRadius + pathWidth);

double expectedCost = pathArea * concreteCost + fenceLength * fenceCost;
EXPECT_NEAR(cost, expectedCost, 1e-10);
}

TEST(TasksTest, CalculatePoolCostZeroPathWidth) {
Circle pool(3.0);
Circle poolWithPath(3.0);  // pathWidth = 0
double concreteCost = 1000.0;
double fenceCost = 2000.0;

double pathArea = poolWithPath.getArea() - pool.getArea();
double fenceLength = poolWithPath.getFerence();
double expectedCost = pathArea * concreteCost + fenceLength * fenceCost;

EXPECT_NEAR(expectedCost, 2 * M_PI * 3.0 * 2000.0, 1e-10);
}

TEST(TasksTest, CalculateGapSmallIncrease) {
Circle earth(6378.1);
double originalFerence = earth.getFerence();
earth.setFerence(originalFerence + 0.001);
double gap = earth.getRadius() - 6378.1;
EXPECT_NEAR(calculateGap(), gap, 1e-10);
}

TEST(TasksTest, CircleConsistencyAfterTask) {
double poolRadius = 3.0;
Circle pool(poolRadius);
calculatePoolCost();
EXPECT_DOUBLE_EQ(pool.getRadius(), poolRadius);
}
