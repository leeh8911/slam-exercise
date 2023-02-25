/// @file kdtree.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-25
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_structure/kdtree.h"

#include <Eigen/Dense>
#include <memory>
#include <utility>

namespace ad_framwork::data_structure
{

Circle::Circle(const Eigen::Vector3d& center, double radius)
    : center_(center), radius_(radius)
{
}
bool Circle::IsIn(const Eigen::Vector3d& point) const
{
    return (point - center_).norm() < radius_;
}

Rectangle::Rectangle(const Eigen::Vector3d& center, const Eigen::Vector3d& size)
    : center_(center), size_(size)
{
}
bool Rectangle::IsIn(const Eigen::Vector3d& point) const
{
    return std::abs(point[0] - center_[0]) < size_[0] &&
           std::abs(point[1] - center_[1]) < size_[1] &&
           std::abs(point[2] - center_[2]) < size_[2];
}

Polygon::Polygon(const std::vector<Eigen::Vector3d>& points) : points_(points)
{
}
bool Polygon::IsIn(const Eigen::Vector3d& point) const { return false; }

Node::Node(const Eigen::Vector3d& point) : point_(point) {}

double Node::Distance(const Eigen::Vector3d& point) const
{
    return (point_ - point).norm();
}

double Node::Distance(const Node& point) const
{
    return Distance(point.point_);
}

void KdTree::Insert(const Eigen::Vector3d& point)
{
    root_ = Insert(root_, point, 0);
}

NodePtr KdTree::Nearest(const Eigen::Vector3d& point) const
{
    return Nearest(root_, point, 0);
}

NodePtr KdTree::Insert(NodePtr node, const Eigen::Vector3d& point, int depth)
{
    if (node == nullptr)
    {
        return std::make_shared<Node>(point);
    }

    int axis = depth % 3;
    if (point[axis] < node->point_[axis])
    {
        node->left_ = Insert(node->left_, point, depth + 1);
    }
    else
    {
        node->right_ = Insert(node->right_, point, depth + 1);
    }

    return node;
}

NodePtr KdTree::Nearest(NodePtr node, const Eigen::Vector3d& point,
                        int depth) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    int axis = depth % 3;
    NodePtr next_node;
    NodePtr opposite_node;

    if (point[axis] < node->point_[axis])
    {
        next_node = node->left_;
        opposite_node = node->right_;
    }
    else
    {
        next_node = node->right_;
        opposite_node = node->left_;
    }

    NodePtr best_node = Nearest(next_node, point, depth + 1);
    if (best_node == nullptr ||
        node->Distance(point) < best_node->Distance(point))
    {
        best_node = node;
    }

    if (std::abs(point[axis] - node->point_[axis]) < best_node->Distance(point))
    {
        NodePtr best_opposite_node = Nearest(opposite_node, point, depth + 1);
        if (best_opposite_node != nullptr &&
            best_opposite_node->Distance(point) < best_node->Distance(point))
        {
            best_node = best_opposite_node;
        }
    }

    return best_node;
}

NodeList KdTree::FindInBoundary(const Shape& shape) const
{
    return FindInBoundary(root_, shape);
}
NodeList KdTree::FindInBoundary(NodePtr root, const Shape& shape) const
{
    NodeList nodes{};

    if (root == nullptr)
    {
        return nodes;
    }

    if (shape.IsIn(root->point_))
    {
        nodes.push_back(root);
    }

    if (root->left_ && shape.IsIn(root->left_->point_))
    {
        NodeList left_nodes = FindInBoundary(root->left_, shape);
        nodes.insert_after(left_nodes.cbegin(), left_nodes.cend());
    }
    if (root->right_ && shape.IsIn(root->right_->point_))
    {
        NodeList right_nodes = FindInBoundary(root->right_, shape);
        nodes.insert_after(right_nodes.cbegin(), right_nodes.cend());
    }

    return nodes;
}
}  // namespace ad_framwork::data_structure