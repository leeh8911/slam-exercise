/// @file object.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VALUE_OBJECT_H_
#define SRC_VALUE_OBJECT_H_

#include <Eigen/Dense>

namespace ad_framework
{
using ID = size_t;
using Vector3d = Eigen::Vector3d;
using ObjectClass = size_t;
using Status = size_t;
using AliveCount = size_t;

struct Object
{
    ID id{};

    Vector3d position{};
    Vector3d velocity{};
    Vector3d acceleration{};

    Vector3d orientation{};
    Vector3d angular_velocity{};
    Vector3d angular_acceleration{};
    Vector3d shape{};

    ObjectClass object_class{};
    Status status{};
    AliveCount alive_count{};
};
}  // namespace ad_framework

#endif  // SRC_VALUE_OBJECT_H_
