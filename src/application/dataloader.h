/// @file dataset.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_DATASET_H_
#define SRC_APPLICATION_DATASET_H_

#include <array>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace ad_framework::application
{

enum class DatasetType
{
    kKitti,
    kNuscenes,
    kWaymo,
    kArgoverse,
    kLyft,
    kNone
};

namespace fs = std::filesystem;

using DataLoaderTypeToName = std::unordered_map<DatasetType, const char*>;
using DatasetNameToType = std::unordered_map<const char*, DatasetType>;
using DatasetPathMap = std::unordered_map<DatasetType, fs::path>;
using SequencePathList = std::vector<fs::path>;
using SequenceNameList = std::vector<std::string>;

class DataLoader
{
 public:
    DataLoader();
    ~DataLoader() = default;

    const SequencePathList& GetSequencePathList() const;
    DatasetPathMap GetCandidateMap() const;
    DatasetType GetDatasetType() const;
    void SelectType(DatasetType type);
    void FindSequences(DatasetType type);
    void SelectSequence(size_t index);
    fs::path GetSelectedPath() const;

    constexpr static std::array<const char*, 5> kItems = {
        "kitti", "nuscenes", "waymo", "argoverse", "lyft"};

 private:
    void FindCandidates();

    fs::path base_path_{"D:\\sangwon\\dataset"};
    fs::path selected_path_{};
    SequencePathList sequence_path_list_{};
    SequenceNameList sequence_name_list_{};
    DatasetPathMap candidate_map_{};
    static DataLoaderTypeToName kDatasetTypeToName;
    static DatasetNameToType kDatasetNameToType;
    DatasetType type_{};
};

using DataLoaderPtr = std::shared_ptr<DataLoader>;

}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_DATASET_H_
