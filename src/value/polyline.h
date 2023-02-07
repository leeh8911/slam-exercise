/// @file polyline.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VALUE_POLYLINE_H_
#define SRC_VALUE_POLYLINE_H_

#include <Eigen/Dense>
#include <vector>

namespace ad_framework
{
using Vector3d = Eigen::Vector3d;
using Polyline = std::vector<Vector3d>;
}  // namespace ad_framework

#endif  // SRC_VALUE_POLYLINE_H_
