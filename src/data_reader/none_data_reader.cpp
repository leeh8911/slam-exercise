/// @file none_data_reader.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#include "src/data_reader/none_data_reader.h"

#include <filesystem>

namespace ad_framework
{
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
}  // namespace ad_framework