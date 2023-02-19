/// @file kitti_data_reader.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_reader/kitti_data_reader.h"

#include <filesystem>

#include "src/utility/string.h"

namespace ad_framework
{
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

}  // namespace ad_framework