/// @file frame.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-27
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_structure/frame.h"

namespace ad_framework::data_structure
{

Frame::Frame(const std::vector<ShapePtr>& shapes) : shapes_{shapes} {}

void Frame::AddShape(ShapePtr shape) { shapes_.emplace_back(shape); }
void Frame::AddShape(const std::vector<ShapePtr>& shapes)
{
    shapes_.insert(shapes_.end(), shapes.begin(), shapes.end());
}
void Frame::Clear() { shapes_.clear(); }

std::vector<ShapePtr> Frame::GetShapes() const { return shapes_; }
}  // namespace ad_framework::data_structure