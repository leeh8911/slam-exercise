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

#include <opencv2/imgcodecs.hpp>
#include <utility>

namespace ad_framework
{
Image::Image(const cv::Mat& image) : image_{std::make_unique<cv::Mat>(image)} {}

Image::Image(const Image& other)
    : image_{std::make_unique<cv::Mat>(*other.image_)}
{
}
Image::Image(Image&& other) noexcept : image_{std::move(other.image_)} {}

Image& Image::operator=(const Image& other)
{
    if (this != &other)
    {
        image_ = std::make_unique<cv::Mat>(*other.image_);
    }
    return *this;
}

Image& Image::operator=(Image&& other) noexcept
{
    if (this != &other)
    {
        image_ = std::move(other.image_);
    }
    return *this;
}

size_t Image::GetRowSize() const { return image_->rows; }
size_t Image::GetColSize() const { return image_->cols; }
uint8_t* Image::GetRawPointer() const { return image_->ptr(); }

cv::Mat Image::GetRawImage() const { return *image_; }

ImagePtr Image::ReadFromFile(const fs::path path)
{
    return std::make_shared<Image>(cv::imread(path.string()));
}

StereoImage::StereoImage(ImagePtr left, ImagePtr right)
    : left_{left}, right_{right}
{
}

ImagePtr StereoImage::Left() const { return left_; }

ImagePtr StereoImage::Right() const { return right_; }
}  // namespace ad_framework