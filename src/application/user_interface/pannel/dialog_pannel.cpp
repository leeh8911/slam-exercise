﻿/// @file dialog_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/user_interface/pannel/dialog_pannel.h"

#include "bindings/imgui.h"

namespace ad_framework::application
{
DialogPannel::DialogPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Dialog", position, size)
{
}

void DialogPannel::RenderInterface(bool& open)
{
    if (!open)
    {
        return;
    }
    ImGui::Text("Hello, world!");
}

}  // namespace ad_framework::application