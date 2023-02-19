/// @file datareader.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/datareader.h"

#include <string>

namespace ad_framework::application
{
namespace fs = std::filesystem;

class Image
{
 public:
    Image() = default;
    static ImagePtr ReadFromFile(const fs::path path) { return nullptr; }

 private:
};
class StereoImage
{
 public:
    StereoImage(ImagePtr left, ImagePtr right) : left_{left}, right_{right} {}

 private:
    ImagePtr left_{nullptr};
    ImagePtr right_{nullptr};
};
class PointCloud
{
 public:
    static PointCloudPtr ReadFromFile(const fs::path path) { return nullptr; }

 private:
};
class Calibration
{
 public:
    static CalibrationPtr ReadFromFile(const fs::path path) { return nullptr; }

 private:
};

std::string ToStringWithZeroPadding(size_t num, size_t padding = 6)
{
    std::string str = std::to_string(num);
    size_t rest_size = padding - str.length();

    if (rest_size > 0)
    {
        str = std::string(rest_size, '0') + str;
    }

    return str;
}

DataReader::DataReader(const fs::path path)
    : path_(path),
      current_index_{0},
      size_{0},
      color_image_ptr_{nullptr},
      gray_image_ptr_{nullptr},
      color_stereo_image_ptr_{nullptr},
      gray_stereo_image_ptr_{nullptr},
      point_cloud_{nullptr},
      calibration_{nullptr}
{
}

size_t DataReader::GetSize() const { return size_; }
void DataReader::SetSize(size_t size) { size_ = size; }
void DataReader::SetCalibration(CalibrationPtr calibration)
{
    calibration_ = calibration;
}

bool DataReader::LoadIndex(size_t index)
{
    if (index >= size_)
    {
        return false;
    }

    current_index_ = index;

    color_image_ptr_ = ReadColorImage(current_index_, path_);
    gray_image_ptr_ = ReadGrayImage(current_index_, path_);
    color_stereo_image_ptr_ = ReadColorStereoImage(current_index_, path_);
    gray_stereo_image_ptr_ = ReadGrayStereoImage(current_index_, path_);
    point_cloud_ = ReadPointCloud(current_index_, path_);

    return true;
}

const ImagePtr DataReader::GetGrayImage() const { return gray_image_ptr_; }
const ImagePtr DataReader::GetColorImage() const { return color_image_ptr_; }
const StereoImagePtr DataReader::GetGrayStereoImage() const
{
    return gray_stereo_image_ptr_;
}
const StereoImagePtr DataReader::GetColorStereoImage() const
{
    return color_stereo_image_ptr_;
}
const PointCloudPtr DataReader::GetPointCloud() const { return point_cloud_; }
const CalibrationPtr DataReader::GetCalibration() const { return calibration_; }

KittiDataReader::KittiDataReader(const fs::path path) : DataReader(path)
{
    SetSize(ReadSize());

    SetCalibration(ReadCalibration(path));
}

size_t KittiDataReader::ReadSize() { return 0; }

ImagePtr KittiDataReader::ReadGrayImage(size_t index, fs::path base_path)
{
    return Image::ReadFromFile(base_path / kGrayLeftImageFolder /
                               ToStringWithZeroPadding(index) / ".png");
}

ImagePtr KittiDataReader::ReadColorImage(size_t index, fs::path base_path)
{
    return Image::ReadFromFile(base_path / kColorLeftImageFolder /
                               ToStringWithZeroPadding(index) / ".png");
}

StereoImagePtr KittiDataReader::ReadGrayStereoImage(size_t index,
                                                    fs::path base_path)
{
    ImagePtr left_image =
        Image::ReadFromFile(base_path / kGrayLeftImageFolder /
                            ToStringWithZeroPadding(index) / ".png");
    ImagePtr right_image =
        Image::ReadFromFile(base_path / kGrayRightImageFolder /
                            ToStringWithZeroPadding(index) / ".png");

    return std::make_shared<StereoImage>(left_image, right_image);
}

StereoImagePtr KittiDataReader::ReadColorStereoImage(size_t index,
                                                     fs::path base_path)
{
    ImagePtr left_image =
        Image::ReadFromFile(base_path / kColorLeftImageFolder /
                            ToStringWithZeroPadding(index) / ".png");
    ImagePtr right_image =
        Image::ReadFromFile(base_path / kColorRightImageFolder /
                            ToStringWithZeroPadding(index) / ".png");

    return std::make_shared<StereoImage>(left_image, right_image);
}

PointCloudPtr KittiDataReader::ReadPointCloud(size_t index, fs::path base_path)
{
    return PointCloud::ReadFromFile(base_path / kPointCloudFolder /
                                    ToStringWithZeroPadding(index) / ".bin");
}

CalibrationPtr KittiDataReader::ReadCalibration(fs::path base_path)
{
    return Calibration::ReadFromFile(base_path / kCalibrationFile / ".txt");
}

NoneDataReader::NoneDataReader(const fs::path path) : DataReader(path) {}

size_t NoneDataReader::ReadSize() { return 0; }

ImagePtr NoneDataReader::ReadGrayImage(size_t index, fs::path base_path)
{
    if (index >= 0)
    {
        return nullptr;
    }
    return nullptr;
}

ImagePtr NoneDataReader::ReadColorImage(size_t index, fs::path base_path)
{
    if (index >= 0)
    {
        return nullptr;
    }
    return nullptr;
}

StereoImagePtr NoneDataReader::ReadGrayStereoImage(size_t index,
                                                   fs::path base_path)
{
    if (index >= 0)
    {
        return nullptr;
    }
    return nullptr;
}

StereoImagePtr NoneDataReader::ReadColorStereoImage(size_t index,
                                                    fs::path base_path)
{
    if (index >= 0)
    {
        return nullptr;
    }
    return nullptr;
}

PointCloudPtr NoneDataReader::ReadPointCloud(size_t index, fs::path base_path)
{
    if (index >= 0)
    {
        return nullptr;
    }
    return nullptr;
}

CalibrationPtr NoneDataReader::ReadCalibration(fs::path base_path)
{
    return nullptr;
}

}  // namespace ad_framework::application