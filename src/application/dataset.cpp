/// @file dataset.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/dataset.h"

#include <filesystem>
#include <string>
#include <vector>

namespace ad_framework::application
{

namespace fs = std::filesystem;

Dataset::Dataset()
    : base_path_{"D:\\sangwon\\dataset"},
      type_{DatasetType::kKitti},
      selected_path_{""},
      sequence_list_{},
      candidate_path_list_{}
{
}

bool Dataset::IsExist(DatasetType type) const
{
    if (type == DatasetType::kKitti)
    {
        fs::path kitti_path(path_);
        if (fs::exists(kitti_path))
        {
            return true;
        }
    }
    return false;
}

std::vector<fs::path> Dataset::GetSequenceList() const
{
    std::vector<fs::path> sequence_list;
    if (IsExist(DatasetType::kKitti))
    {
        std::filesystem::path kitti_path(path_);
        for (const auto& entry :
             std::filesystem::directory_iterator(kitti_path))
        {
            sequence_list.push_back(entry.path().string());
        }
    }
    return sequence_list;
}

}  // namespace ad_framework::application