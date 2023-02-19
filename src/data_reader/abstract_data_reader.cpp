/// @file abstract_data_reader.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_reader/abstract_data_reader.h"

#include <iostream>
namespace ad_framework
{
namespace fs = std::filesystem;

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
    LoadIndex(0);
}

fs::path DataReader::GetPath() const { return path_; }
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
    std::cout << "LoadIndex: " << index << " / " << size_ << "\n";

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
}  // namespace ad_framework
