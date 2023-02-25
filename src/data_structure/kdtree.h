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
#include <memory>

namespace ad_framwork::data_structure
{

class Node;
using NodePtr = std::shared_ptr<Node>;

class Node
{
 public:
    Node() = default;
    Node(const Eigen::Vector3d& point);

    double Distance(const Eigen::Vector3d& point) const;
    double Distance(const Node& point) const;

    Eigen::Vector3d point_{};
    NodePtr left_{nullptr};
    NodePtr right_{nullptr};
};

class Circle;
class Rectangle;
class Polygon;

class KdTree
{
 public:
    KdTree() = default;

    void Insert(const Eigen::Vector3d& point);
    NodePtr Nearest(const Eigen::Vector3d& point) const;

    NodePtr FindInBoundary(const Circle& circle) const;
    NodePtr FindInBoundary(const Rectangle& rectangle) const;
    NodePtr FindInBoundary(const Polygon& polygon) const;

 private:
    NodePtr Insert(NodePtr node, const Eigen::Vector3d& point, int depth);
    NodePtr Nearest(NodePtr node, const Eigen::Vector3d& point,
                    int depth) const;

    NodePtr root_{nullptr};
};
}  // namespace ad_framwork::data_structure

#endif  // SRC_DATA_STRUCTURE_KDTREE_H_
