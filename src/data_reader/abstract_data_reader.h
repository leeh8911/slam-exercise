/// @file abstract_data_reader.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_READER_ABSTRACT_DATA_READER_H_
#define SRC_DATA_READER_ABSTRACT_DATA_READER_H_

#include <filesystem>

#include "src/data_type/types.h"
namespace ad_framework
{
namespace fs = std::filesystem;

class DataReader
{
 public:
    DataReader(const fs::path path);
    virtual ~DataReader() = default;

    size_t GetSize() const;

    bool LoadIndex(size_t index);
    size_t GetIndex() const;
    fs::path GetPath() const;
    const ImagePtr GetGrayImage() const;
    const ImagePtr GetColorImage() const;
    const StereoImagePtr GetGrayStereoImage() const;
    const StereoImagePtr GetColorStereoImage() const;
    const PointCloudPtr GetPointCloud() const;
    const CalibrationPtr GetCalibration() const;

 protected:
    void SetSize(size_t size);
    void SetCalibration(CalibrationPtr calibration);

 private:
    fs::path path_{""};
    size_t current_index_{0};
    size_t size_{0};

    virtual size_t ReadSize() = 0;
    virtual ImagePtr ReadGrayImage(size_t index, fs::path base_path) = 0;
    virtual ImagePtr ReadColorImage(size_t index, fs::path base_path) = 0;
    virtual StereoImagePtr ReadGrayStereoImage(size_t index,
                                               fs::path base_path) = 0;
    virtual StereoImagePtr ReadColorStereoImage(size_t index,
                                                fs::path base_path) = 0;
    virtual PointCloudPtr ReadPointCloud(size_t index, fs::path base_path) = 0;
    virtual CalibrationPtr ReadCalibration(fs::path base_path) = 0;

    ImagePtr color_image_ptr_{nullptr};
    ImagePtr gray_image_ptr_{nullptr};
    StereoImagePtr color_stereo_image_ptr_{nullptr};
    StereoImagePtr gray_stereo_image_ptr_{nullptr};
    PointCloudPtr point_cloud_{nullptr};
    CalibrationPtr calibration_{nullptr};
};
using DataReaderPtr = std::shared_ptr<DataReader>;
}  // namespace ad_framework

#endif  // SRC_DATA_READER_ABSTRACT_DATA_READER_H_
