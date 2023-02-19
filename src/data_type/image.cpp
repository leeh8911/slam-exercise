/// @file image.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_type/image.h"

namespace ad_framework
{

ImagePtr Image::ReadFromFile(const fs::path path) { return nullptr; }

StereoImage::StereoImage(ImagePtr left, ImagePtr right)
    : left_{left}, right_{right}
{
}
}  // namespace ad_framework