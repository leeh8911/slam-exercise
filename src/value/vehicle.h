/// @file vehicle.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VALUE_VEHICLE_H_
#define SRC_VALUE_VEHICLE_H_

#include <Eigen/Dense>

namespace ad_framework
{
using Vector3d = Eigen::Vector3d;
using Angle = double;

struct Vehicle
{
    double steering_angle;

    Vector3d position{};
    Vector3d velocity{};
    Vector3d acceleration{};

    Vector3d orientation{};
    Vector3d angular_velocity{};
    Vector3d angular_acceleration{};
};
}  // namespace ad_framework

#endif  // SRC_VALUE_VEHICLE_H_
