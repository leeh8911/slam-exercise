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

DatasetTypeToName Dataset::kDatasetTypeToName{{DatasetType::kKitti, "kitti"}};
DatasetNameToType Dataset::kDatasetNameToType{{"kitti", DatasetType::kKitti}};

Dataset::Dataset()
    : base_path_{"D:\\sangwon\\dataset"},
      type_{DatasetType::kKitti},
      selected_path_{""},
      sequence_list_{},
      candidate_map_{}
{
    FindCandidates();
}

void Dataset::FindCandidates()
{
    for (const auto& candidate : kDatasetTypeToName)
    {
        fs::path candidate_path = base_path_ / candidate.second;
        if (fs::exists(candidate_path))
        {
            candidate_map_.emplace(candidate.first, candidate_path);
        }
    }
}
void Dataset::FindSequences(DatasetType type)
{
    sequence_list_.clear();
    fs::path dataset_path =
        candidate_map_.find(type)->second / "odometry\\dataset\\sequences";
    for (const auto& entry : std::filesystem::directory_iterator(dataset_path))
    {
        sequence_list_.emplace_back(entry.path());
    }
}

SequenceList Dataset::GetSequenceList() const { return sequence_list_; }

DatasetPathMap Dataset::GetCandidateMap() const { return candidate_map_; }
}  // namespace ad_framework::application