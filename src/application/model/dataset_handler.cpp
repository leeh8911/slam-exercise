/// @file dataset_handler.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/model/dataset_handler.h"

#include "src/data_reader.h"
namespace ad_framework
{

constexpr std::vector<std::string> kDatasetList = {"kitti", "argoverse",
                                                   "waymo", "nuScenes", "lyft"};

DatasetHandler::DatasetHandler()
    : data_reader_ptr_{std::make_shared<DataReader>()},
      dataset_list_{kDatasetList},
      sequence_list_{}
{
}

void DatasetHandler::SetDataset(size_t index)
{
    dataset_type_ = static_cast<XXDatasetType>(index);

    switch (dataset_type_)
    {
        case XXDatasetType::kKitti:
            dataset_path_ = dataset_path_ / "kitti/odometry/dataset/sequences";
            break;
        default:
            break;
    }
}

void DatasetHandler::LoadSequence(size_t index) {}

void DatasetHandler::SetTimeIndex(size_t index)
{
    data_reader_ptr_->SetTimeIndex(index);
}

void DatasetHandler::ViewCameraType(size_t index)
{
    data_reader_ptr_->ViewCameraType(index);
}

void DatasetHandler::GetDatasetList() { data_reader_ptr_->GetDatasetList(); }

void DatasetHandler::GetSequenceList() { data_reader_ptr_->GetSequenceList(); }
}  // namespace ad_framework
