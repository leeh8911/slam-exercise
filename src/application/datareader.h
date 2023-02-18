/// @file datareader.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-18
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_DATAREADER_H_
#define SRC_APPLICATION_DATAREADER_H_

#include <filesystem>
#include <unordered_map>

namespace ad_framework::application
{
using fs = std::filesystem;

class Image;
class StereoImage;
using ImagePtr = std::shared_ptr<Image>;
using StereoImagePtr = std::shared_ptr<StereoImage>;

class PointCloud;
using PointCloudPtr = std::shared_ptr<PointCloud>;

class Calibration;
using CalibrationPtr = std::shared_ptr<Calibration>;

class Dataset
{
 public:
    Dataset(const fs::path path) : path_(path) {}
    virtual ~Dataset() = default;

    size_t GetSize() const;

    bool LoadIndex(size_t index);

    const ImagePtr& GetGrayImage() const;
    const ImagePtr& GetColorImage() const;
    const StereoImagePtr& GetGrayStereoImage() const;
    const StereoImagePtr& GetColorStereoImage() const;
    const PointCloudPtr& GetPointCloud() const;
    const CalibrationPtr& GetCalibration() const;

 private:
    fs::path path_{""};
    size_t current_index_{0};
    size_t size_{0};

    virtual void ReadData() = 0;

    ImagePtr color_image_ptr_{nullptr};
    ImagePtr gray_image_ptr_{nullptr};
    StereoImagePtr color_stereo_image_ptr_{nullptr};
    StereoImagePtr gray_stereo_image_ptr_{nullptr};
    PointCloudPtr point_cloud_{nullptr};
    CalibrationPtr calibration_{nullptr};
};

class KittiDataset : public Dataset
{
 public:
    KittiDataset(const fs::path path) : path_(path) {}

    size_t GetSize() const;

    bool LoadIndex(size_t index);

    const ImagePtr& GetGrayImage() const;
    const ImagePtr& GetColorImage() const;
    const StereoImagePtr& GetGrayStereoImage() const;
    const StereoImagePtr& GetColorStereoImage() const;
    const PointCloudPtr& GetPointCloud() const;
    const CalibrationPtr& GetCalibration() const;

 private:
    fs::path path_{""};
    size_t current_index_{0};
    size_t size_{0};

    void ReadData() override;

    ImagePtr color_image_ptr_{nullptr};
    ImagePtr gray_image_ptr_{nullptr};
    StereoImagePtr color_stereo_image_ptr_{nullptr};
    StereoImagePtr gray_stereo_image_ptr_{nullptr};
    PointCloudPtr point_cloud_{nullptr};
    CalibrationPtr calibration_{nullptr};

    constexpr static std::string kGrayLeftImageFolder = "image_0";
    constexpr static std::string kGrayRightImageFolder = "image_1";
    constexpr static std::string kColorLeftImageFolder = "image_2";
    constexpr static std::string kColorRightImageFolder = "image_3";
    constexpr static std::string kImageFolder = "velodyne";
    constexpr static std::string kCalibrationFile = "calib.txt";
    constexpr static std::string kTimesFile = "times.txt";
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_DATAREADER_H_
