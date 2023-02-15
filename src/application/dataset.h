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

namespace ad_framework::application
{

enum class DatasetType
{
    kKitti,
    kNone
};

namespace fs = std::filesystem;
class Dataset
{
 public:
    Dataset();
    ~Dataset() = default;

    bool IsExist(DatasetType type) const;
    std::vector<fs::path> GetSequenceList() const;

 private:
    fs::path base_path_{};
    fs::path selected_path_{};
    std::vector<fs::path> sequence_list_{};
    std::vector<fs::path> candidate_path_list_{};
    DatasetType type_{};
};

using DatasetPtr = std::shared_ptr<Dataset>;

}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_DATASET_H_
