/// @file ui.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <memory>
#include <string>

#include "src/utils/callback.h"


namespace ad_framwork::ui
{
class UserInterface
{
    using CallbackPtr = ::ad_framework::callback::CallbackPtr;

 public:
    virtual ~UserInterface() = default;

    virtual void operator()() = 0;

 private:
    CallbackPtr callback_{nullptr};
};

}  // namespace ad_framwork::ui
#endif  // SRC_UI_H_
