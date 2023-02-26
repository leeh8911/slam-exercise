/// @file kdtree_test.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-25
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_structure/kdtree.h"

#include <gtest/gtest.h>

namespace ad_framwork::data_structure
{

TEST(KdTreeTest, NodeTest)
{
    Eigen::Vector3d point(1, 2, 3);
    Node node(point);

    EXPECT_EQ(node.point_, point);
    EXPECT_EQ(node.left_, nullptr);
    EXPECT_EQ(node.right_, nullptr);
}
TEST(KdTreeTest, DistanceTest)
{
    Eigen::Vector3d point_a(1, 2, 3);
    Eigen::Vector3d point_b(2, 2, 3);
    Node node_a(point_a);
    Node node_b(point_b);

    EXPECT_NEAR(node_a.Distance(point_b), 1, 1e-6);
}

TEST(KdTreeTest, FindNearestNodeCase)
{
    Eigen::Vector3d point_a(1, 2, 3);
    Eigen::Vector3d point_b(2, 2, 3);
    Eigen::Vector3d point_c(3, 2, 3);
    Eigen::Vector3d point_d(4, 2, 3);

    KdTree kdtree;
    kdtree.Insert(point_a);
    kdtree.Insert(point_b);
    kdtree.Insert(point_c);

    NodePtr node = kdtree.Nearest(point_d);

    EXPECT_EQ(node->point_, point_c);
}

TEST(KdTreeTest, FindNearestNodeCase2)
{
    Eigen::Vector3d point_a(1, 2, 3);
    Eigen::Vector3d point_b(2, 2, 3);
    Eigen::Vector3d point_c(3, 2, 3);
    Eigen::Vector3d point_d(4, 2, 3);
    Eigen::Vector3d point_e(5, 2, 3);

    KdTree kdtree;
    kdtree.Insert(point_a);
    kdtree.Insert(point_b);
    kdtree.Insert(point_c);
    kdtree.Insert(point_d);
    kdtree.Insert(point_e);

    Circle circle(point_c, 1);

    auto points = kdtree.FindInBoundary(circle);

    EXPECT_EQ(points.size(), 3);
}

}  // namespace ad_framwork::data_structure
