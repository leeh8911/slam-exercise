/// @file calibration.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_TYPE_CALIBRATION_H_
#define SRC_DATA_TYPE_CALIBRATION_H_

#include <filesystem>

namespace ad_framework
{

namespace fs = std::filesystem;

class Calibration;
using CalibrationPtr = std::shared_ptr<Calibration>;

class Calibration
{
 public:
    static CalibrationPtr ReadFromFile(const fs::path path);

 private:
};
}  // namespace ad_framework

#endif  // SRC_DATA_TYPE_CALIBRATION_H_
