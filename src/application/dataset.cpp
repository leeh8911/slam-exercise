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
#include <iostream>
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
      sequence_path_list_{},
      sequence_name_list_{},
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

void Dataset::SelectType(DatasetType type)
{
    type_ = type;
    FindSequences(type);
}

void Dataset::SelectSequence(size_t index)
{
    if (index < sequence_path_list_.size())
    {
        selected_path_ = fs::path(sequence_path_list_[index]);
    }
}

fs::path Dataset::GetSelectedPath() const { return selected_path_; }

void Dataset::FindSequences(DatasetType type)
{
    sequence_path_list_.clear();
    sequence_name_list_.clear();
    if (!candidate_map_.contains(type))
    {
        return;
    }
    fs::path dataset_path =
        candidate_map_.find(type)->second / "odometry\\dataset\\sequences";

    for (const auto& entry : fs::directory_iterator(dataset_path))
    {
        sequence_path_list_.emplace_back(entry.path());
    }
}

const SequencePathList& Dataset::GetSequencePathList() const
{
    return sequence_path_list_;
}

DatasetPathMap Dataset::GetCandidateMap() const { return candidate_map_; }
}  // namespace ad_framework::application