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

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace ad_framework::application
{

enum class DatasetType
{
    kKitti,
    kNone
};

namespace fs = std::filesystem;

using DatasetTypeToName = std::unordered_map<DatasetType, const char*>;
using DatasetNameToType = std::unordered_map<const char*, DatasetType>;
using DatasetPathMap = std::unordered_map<DatasetType, fs::path>;
using SequenceList = std::vector<fs::path>;

class Dataset
{
 public:
    Dataset();
    ~Dataset() = default;

    std::vector<fs::path> GetSequenceList() const;
    DatasetPathMap GetCandidateMap() const;
    void FindSequences(DatasetType type);

 private:
    void FindCandidates();

    fs::path base_path_{"D:\\sangwon\\dataset"};
    fs::path selected_path_{};
    SequenceList sequence_list_{};
    DatasetPathMap candidate_map_{};
    static DatasetTypeToName kDatasetTypeToName;
    static DatasetNameToType kDatasetNameToType;
    DatasetType type_{};
};

using DatasetPtr = std::shared_ptr<Dataset>;

}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_DATASET_H_
