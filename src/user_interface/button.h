/// @file button.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_USER_INTERFACE_BUTTON_H_
#define SRC_USER_INTERFACE_BUTTON_H_

#include <string>

#include "src/user_interface/ui.h"
#include "src/utils/callback.h"
#include "src/utils/imgui.h"

namespace ad_framework::ui
{
class Button : public UserInterface
{
    using CallbackPtr = ::ad_framework::callback::CallbackPtr;

 public:
    Button(std::string title, ImVec2 size, ImVec2 pos, CallbackPtr callback);
    Button(std::string title, ImVec2 size, ImVec2 pos);
    Button(std::string title, CallbackPtr callback);
    Button(std::string title);

    void operator()() override;

 private:
    CallbackPtr callback_{nullptr};
};
}  // namespace ad_framework::ui

#endif  // SRC_USER_INTERFACE_BUTTON_H_
