/// @file shape.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-27
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_STRUCTURE_SHAPE_H_
#define SRC_DATA_STRUCTURE_SHAPE_H_

#include <Eigen/Dense>
#include <memory>
#include <vector>

namespace ad_framework::data_structure
{
struct Shape
{
    virtual ~Shape() = default;
};
using ShapePtr = std::shared_ptr<Shape>;

struct Point : public Shape
{
    Eigen::Vector3d point;
};

struct PointCloud : public Shape
{
    std::vector<Point> points;
};

struct Line : public Shape
{
    Point start_point;
    Point end_point;
};

struct Polygon : public Shape
{
    std::vector<Point> points;
};

struct Circle : public Shape
{
    Point center;
    double radius;
};

struct Rectangle : public Shape
{
    Point center;
    Point size;
};

}  // namespace ad_framework::data_structure

#endif  // SRC_DATA_STRUCTURE_SHAPE_H_
