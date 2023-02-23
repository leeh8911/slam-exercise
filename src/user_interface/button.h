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
 public:
    Button(std::string title, ImVec2 size, ImVec2 pos);
    Button(std::string title);

    void operator()() override;

    class ButtonChanger;
};

class Button::ButtonChanger : public callback::Callback
{
 public:
    ButtonChanger() = default;
    std::any operator()(const std::any& src) override;
};
}  // namespace ad_framework::ui

#endif  // SRC_USER_INTERFACE_BUTTON_H_
