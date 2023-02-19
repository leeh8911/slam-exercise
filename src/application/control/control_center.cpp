/// @file control_center.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/control/control_center.h"

#include <filesystem>

#include "src/application/dataloader.h"

namespace ad_framework
{

ControlCenter::ControlCenter() : dataloader_ptr_{std::make_shared<DataLoader>()}
{
}

void ControlCenter::SelectDataset(size_t index)
{
    dataset_handler_ptr_->SetDataset(index);
}

void ControlCenter::SelectSequence(size_t index)
{
    dataset_handler_ptr_->LoadSequence(index);
}

void ControlCenter::SelectTimeIndex(size_t index)
{
    dataset_handler_ptr_->SetTimeIndex(index);
}

void ControlCenter::ViewCameraType(size_t index)
{
    dataset_handler_ptr_->ViewCameraType(index);
}
}  // namespace ad_framework
