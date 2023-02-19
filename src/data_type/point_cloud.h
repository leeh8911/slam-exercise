/// @file point_cloud.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_TYPE_POINT_CLOUD_H_
#define SRC_DATA_TYPE_POINT_CLOUD_H_

#include <filesystem>

namespace ad_framework
{
namespace fs = std::filesystem;

class PointCloud;
using PointCloudPtr = std::shared_ptr<PointCloud>;

class PointCloud
{
 public:
    static PointCloudPtr ReadFromFile(const fs::path path);

 private:
};
}  // namespace ad_framework
#endif  // SRC_DATA_TYPE_POINT_CLOUD_H_
