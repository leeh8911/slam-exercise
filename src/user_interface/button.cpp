/// @file button.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#include "src/user_interface/button.h"

#include "src/utils/imgui.h"
#include "src/utils/log.h"

namespace ad_framework::ui
{
class NullCallback : public ::ad_framework::callback::Callback
{
 public:
    std::any operator()(const std::any& src) override { return src; }
};

Button::Button(std::string title, ImVec2 size, ImVec2 pos,
               Button::CallbackPtr callback)
    : UserInterface(title, size, pos, nullptr), callback_(callback)
{
    if (callback == nullptr)
    {
        callback_ = std::make_shared<NullCallback>();
    }
}

Button::Button(std::string title, ImVec2 size, ImVec2 pos)
    : Button(title, size, pos, nullptr)
{
}
Button::Button(std::string title, Button::CallbackPtr callback)
    : Button(title, ImVec2{0, 0}, ImVec2{0, 0}, callback)
{
}
Button::Button(std::string title)
    : Button(title, ImVec2{0, 0}, ImVec2{0, 0}, nullptr)
{
}

void Button::operator()()
{
    ImGui::SetNextWindowSize(Size());
    ImGui::SetNextWindowPos(Pos());

    if (ImGui::Button(Title().c_str()))
    {
        auto result = (*callback_)(Title());
        Rename(std::any_cast<std::string>(result));
    }
}
}  // namespace ad_framework::ui