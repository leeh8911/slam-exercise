/// @file point_cloud.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VALUE_POINT_CLOUD_H_
#define SRC_VALUE_POINT_CLOUD_H_

#include <Eigen/Dense>
#include <vector>


namespace ad_framework
{
using Vector3d = Eigen::Vector3d;

struct PointCloud
{
    std::vector<Vector3d> raw{};
};
}  // namespace ad_framework

#endif  // SRC_VALUE_POINT_CLOUD_H_
