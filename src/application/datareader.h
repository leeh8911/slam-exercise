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
namespace fs = std::filesystem;

class Image;
class StereoImage;
using ImagePtr = std::shared_ptr<Image>;
using StereoImagePtr = std::shared_ptr<StereoImage>;

class PointCloud;
using PointCloudPtr = std::shared_ptr<PointCloud>;

class Calibration;
using CalibrationPtr = std::shared_ptr<Calibration>;

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
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_DATAREADER_H_
