/// @file model.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APP_MODEL_H_
#define SRC_APP_MODEL_H_

#include <memory>

#include "src/app/controller.h"

namespace ad_framework::app
{

struct IModel
{
    ~IModel() = default;
};
using ModelPtr = std::shared_ptr<IModel>;

class Model : public IModel
{
 public:
    Model(ControllerPtr view_ptr);

 private:
    ControllerPtr view_ptr_{nullptr};
};

}  // namespace ad_framework::app

#endif  // SRC_APP_MODEL_H_
