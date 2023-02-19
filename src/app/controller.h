/// @file controller.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APP_CONTROLLER_H_
#define SRC_APP_CONTROLLER_H_

#include <memory>

#include "src/app/model.h"
#include "src/app/view.h"

namespace ad_framework::app
{
struct IController
{
    virtual ~IController() = default;
};
using ControllerPtr = std::shared_ptr<IController>;

class Controller : public IController
{
 public:
    Controller(ModelPtr model_ptr, ViewPtr view_ptr);

 private:
    ModelPtr model_ptr_{nullptr};
    ViewPtr view_ptr{nullptr};
};

}  // namespace ad_framework::app

#endif  // SRC_APP_CONTROLLER_H_
