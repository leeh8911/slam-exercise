/// @file image.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_TYPE_IMAGE_H_
#define SRC_DATA_TYPE_IMAGE_H_

#include <filesystem>
#include <opencv2/core.hpp>

namespace ad_framework
{
namespace fs = std::filesystem;

class Image;
class StereoImage;
using ImagePtr = std::shared_ptr<Image>;
using StereoImagePtr = std::shared_ptr<StereoImage>;

class Image
{
 public:
    Image() = default;
    Image(const cv::Mat& image);

    Image(const Image& other);
    Image(Image&& other) noexcept;

    Image& operator=(const Image& other);
    Image& operator=(Image&& other) noexcept;

    size_t GetRowSize() const;
    size_t GetColSize() const;
    uint8_t* GetRawPointer() const;
    cv::Mat GetRawImage() const;

    static ImagePtr ReadFromFile(const fs::path path);

 private:
    std::unique_ptr<cv::Mat> image_{nullptr};
};

class StereoImage
{
 public:
    StereoImage(ImagePtr left, ImagePtr right);

    ImagePtr Left() const;
    ImagePtr Right() const;

 private:
    ImagePtr left_{nullptr};
    ImagePtr right_{nullptr};
};
}  // namespace ad_framework
#endif  // SRC_DATA_TYPE_IMAGE_H_
