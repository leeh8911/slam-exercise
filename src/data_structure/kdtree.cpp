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
#include <sstream>
#include <utility>

#include "src/utils/log.h"

namespace ad_framework::data_structure
{

Circle::Circle(const Eigen::Vector3d& center, double radius)
    : center_(center), radius_(radius)
{
}
bool Circle::IsIn(const Eigen::Vector3d& point) const
{
    return (point - center_).norm() < radius_;
}

std::string Circle::ToString() const
{
    std::stringstream ss;
    ss << "Circle([" << center_[0] << ", " << center_[1] << ", " << center_[2]
       << "], " << radius_ << ")";
    return ss.str();
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
std::string Rectangle::ToString() const
{
    std::stringstream ss;
    ss << "Rectangle([" << center_[0] << ", " << center_[1] << ", "
       << center_[2] << "], [" << size_[0] << ", " << size_[1] << ", "
       << size_[2] << "])";
    return ss.str();
}

Polygon::Polygon(const std::vector<Eigen::Vector3d>& points) : points_(points)
{
}
bool Polygon::IsIn(const Eigen::Vector3d& point) const
{
    return Eigen::Vector3d{0, 0, 0} == point;
}
std::string Polygon::ToString() const
{
    std::stringstream ss;
    ss << "Polygon(";
    for (const auto& point : points_)
    {
        ss << "[" << point[0] << ", " << point[1] << ", " << point[2] << "], ";
    }
    ss << ")";
    return ss.str();
}

Node::Node(const Eigen::Vector3d& point) : point_(point) {}

double Node::Distance(const Eigen::Vector3d& point) const
{
    return (point_ - point).norm();
}

double Node::Distance(const Node& point) const
{
    return Distance(point.point_);
}

std::string Node::ToString() const
{
    std::stringstream ss;
    ss << "Node(" << point_[0] << ", " << point_[1] << ", " << point_[2] << ")"
       << " [" << (left_ == nullptr ? "null" : left_->ToString()) << ", "
       << (right_ == nullptr ? "null" : right_->ToString()) << "]";
    return ss.str();
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

NodeList KdTree::FindInBoundary(const ShapePtr& shape) const
{
    return FindInBoundary(root_, shape);
}

NodeList KdTree::FindInBoundary(NodePtr root, const ShapePtr& shape) const
{
    NodeList nodes{};

    if (root == nullptr)
    {
        return nodes;
    }

    LOG_MSG(log::LogLevel::kDebug, shape->ToString().c_str());
    LOG_MSG(log::LogLevel::kDebug, root->ToString().c_str());
    if (shape->IsIn(root->point_))
    {
        nodes.emplace_back(*root);
    }

    if (root->left_ && shape->IsIn(root->left_->point_))
    {
        LOG(log::LogLevel::kDebug);
        NodeList left_nodes = FindInBoundary(root->left_, shape);
        nodes.insert(nodes.end(), left_nodes.cbegin(), left_nodes.cend());
    }
    if (root->right_ && shape->IsIn(root->right_->point_))
    {
        LOG(log::LogLevel::kDebug);
        NodeList right_nodes = FindInBoundary(root->right_, shape);
        nodes.insert(nodes.end(), right_nodes.cbegin(), right_nodes.cend());
    }

    return nodes;
}
}  // namespace ad_framework::data_structure