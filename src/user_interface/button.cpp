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

Button::Button(std::string title, ImVec2 size, ImVec2 pos)
    : UserInterface(std::move(title), size, pos)
{
}

Button::Button(std::string title) : Button(title, ImVec2{0, 0}, ImVec2{0, 0}) {}

void Button::operator()()
{
    ImGui::SetNextWindowSize(Size());
    ImGui::SetNextWindowPos(Pos());

    if (ImGui::Button(Title().c_str()))
    {
        auto callbacks = GetCallbacks();

        auto result = (*callbacks["title"])(Title());

        Rename(std::any_cast<std::string>(result));
    }
}

std::any Button::ButtonChanger::operator()(const std::any& src)
{
    std::any result = src;
    if ("button" == std::any_cast<std::string>(src))
    {
        result = std::string("click");
    }
    else
    {
        result = std::string("button");
    }
    return result;
}

}  // namespace ad_framework::ui