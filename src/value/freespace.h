/// @file freespace.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VALUE_FREESPACE_H_
#define SRC_VALUE_FREESPACE_H_

#include <Eigen/Dense>
#include <vector>

namespace ad_framework
{
using CellCollection = std::vector<Vector3d>;
struct Freespace
{
    CellCollection cell_collection{};
};
}  // namespace ad_framework
#endif