/// @file dataset_handler.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_MODEL_DATASET_HANDLER_H_
#define SRC_APPLICATION_MODEL_DATASET_HANDLER_H_

#include <filesystem>
#include <string>
#include <vector>

#include "src/data_reader/abstract_data_reader.h"

namespace ad_framework
{

namespace fs = std::filesystem;

enum class XXDatasetType
{
    kKitti,
    kNuscenes,
    kWaymo,
    kArgoverse,
    kLyft,
    kNone
};

/// @brief 이 클래스는 데이터셋을 관리하는 클래스입니다.
class DatasetHandler
{
 public:
    DatasetHandler() = default;
    ~DatasetHandler() = default;

    void SetDataset(size_t index);
    void LoadSequence(size_t index);
    void SetTimeIndex(size_t index);
    void ViewCameraType(size_t index);

    std::vector<std::string> GetDatasetList() const;
    std::vector<std::string> GetSequenceList() const;

 private:
    DataReaderPtr data_reader_ptr_{nullptr};

    fs::path dataset_path_{"D:\\sangwon\\dataset"};

    XXDatasetType dataset_type_{XXDatasetType::kNone};
    std::vector<std::string> dataset_list_{};
    std::vector<std::string> sequence_list_{};
};
}  // namespace ad_framework

#endif  // SRC_APPLICATION_MODEL_DATASET_HANDLER_H_
