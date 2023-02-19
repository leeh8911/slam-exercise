/// @file control_center.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_CONTROL_CONTROL_CENTER_H_
#define SRC_APPLICATION_CONTROL_CONTROL_CENTER_H_

#include <memory>

#include "src/application/model/dataset_handler.h"

namespace ad_framework
{

class ControlCenter
{
 public:
    ControlCenter();
    ~ControlCenter() = default;

    void SelectDataset(size_t index);
    void SelectSequence(size_t index);
    void SelectTimeIndex(size_t index);

    void ViewCameraType(size_t index);

 private:
    DatasetHandlerPtr dataset_handler_ptr_{nullptr};
};

using ControlCenterPtr = std::shared_ptr<ControlCenter>;

}  // namespace ad_framework

#endif  // SRC_APPLICATION_CONTROL_CONTROL_CENTER_H_
