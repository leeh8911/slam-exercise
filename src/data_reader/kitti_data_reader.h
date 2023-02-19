/// @file kitti_data_reader.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATAREADER_KITTI_DATA_READER_H_
#define SRC_DATAREADER_KITTI_DATA_READER_H_

#include <filesystem>

#include "src/data_reader/abstract_data_reader.h"

namespace ad_framework
{
class KittiDataReader : public DataReader
{
 public:
    KittiDataReader(const fs::path path);

 private:
    size_t ReadSize() override;

    ImagePtr ReadGrayImage(size_t index, fs::path base_path) override;
    ImagePtr ReadColorImage(size_t index, fs::path base_path) override;
    StereoImagePtr ReadGrayStereoImage(size_t index,
                                       fs::path base_path) override;
    StereoImagePtr ReadColorStereoImage(size_t index,
                                        fs::path base_path) override;
    PointCloudPtr ReadPointCloud(size_t index, fs::path base_path) override;
    CalibrationPtr ReadCalibration(fs::path base_path) override;

    constexpr static std::string kGrayLeftImageFolder = "image_0";
    constexpr static std::string kGrayRightImageFolder = "image_1";
    constexpr static std::string kColorLeftImageFolder = "image_2";
    constexpr static std::string kColorRightImageFolder = "image_3";
    constexpr static std::string kPointCloudFolder = "velodyne";
    constexpr static std::string kCalibrationFile = "calib.txt";
    constexpr static std::string kTimesFile = "times.txt";
};
}  // namespace ad_framework

#endif  // SRC_DATAREADER_KITTI_DATA_READER_H_
