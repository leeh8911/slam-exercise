/// @file kdtree.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-25
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_STRUCTURE_KDTREE_H_
#define SRC_DATA_STRUCTURE_KDTREE_H_

#include <Eigen/Dense>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace ad_framework::data_structure
{

class Node;
using NodePtr = std::shared_ptr<Node>;
using NodeList = std::list<Node>;
using NodePtrList = std::list<NodePtr>;

class Node
{
 public:
    Node() = default;
    Node(const Eigen::Vector3d& point);

    double Distance(const Eigen::Vector3d& point) const;
    double Distance(const Node& point) const;

    std::string ToString() const;

    Eigen::Vector3d point_{};
    NodePtr left_{nullptr};
    NodePtr right_{nullptr};
};

class Shape
{
 public:
    virtual ~Shape() = default;

    virtual bool IsIn(const Eigen::Vector3d& point) const = 0;
    virtual std::string ToString() const = 0;
};
using ShapePtr = std::shared_ptr<Shape>;

class Circle : public Shape
{
 public:
    Circle(const Eigen::Vector3d& center, double radius);
    bool IsIn(const Eigen::Vector3d& point) const override;
    std::string ToString() const override;

 private:
    Eigen::Vector3d center_{};
    double radius_{};
};
class Rectangle : public Shape
{
 public:
    Rectangle(const Eigen::Vector3d& center, const Eigen::Vector3d& size);
    bool IsIn(const Eigen::Vector3d& point) const override;
    std::string ToString() const override;

 private:
    Eigen::Vector3d center_{};
    Eigen::Vector3d size_{};
};
class Polygon : public Shape
{
 public:
    Polygon(const std::vector<Eigen::Vector3d>& points);
    bool IsIn(const Eigen::Vector3d& point) const override;
    std::string ToString() const override;

 private:
    std::vector<Eigen::Vector3d> points_{};
};

class KdTree
{
 public:
    KdTree() = default;

    void Insert(const Eigen::Vector3d& point);
    NodePtr Nearest(const Eigen::Vector3d& point) const;

    NodeList FindInBoundary(const ShapePtr& shape) const;

 private:
    NodePtr Insert(NodePtr node, const Eigen::Vector3d& point, int depth);
    NodePtr Nearest(NodePtr node, const Eigen::Vector3d& point,
                    int depth) const;

    NodeList FindInBoundary(NodePtr node, const ShapePtr& shape) const;
    NodePtr root_{nullptr};
};
}  // namespace ad_framework::data_structure

#endif  // SRC_DATA_STRUCTURE_KDTREE_H_
