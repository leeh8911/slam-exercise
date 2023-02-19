/// @file none_data_reader.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATAREADER_NONE_DATA_READER_H_
#define SRC_DATAREADER_NONE_DATA_READER_H_

#include "src/data_reader/abstract_data_reader.h"

namespace ad_framework
{

class NoneDataReader : public DataReader
{
 public:
    NoneDataReader(const fs::path path);

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
};
}  // namespace ad_framework

#endif  // SRC_DATAREADER_NONE_DATA_READER_H_
