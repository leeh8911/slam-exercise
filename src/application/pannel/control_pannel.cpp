/// @file control_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/pannel/control_pannel.h"

#include <iostream>

#include "bindings/imgui.h"


namespace ad_framework::application
{
ControlPannel::ControlPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Control", position, size)
{
}

void ControlPannel::RenderInterface(bool& open) const
{
    ImGui::Text("Control Pannel");
    ImGui::Spacing();

    ImGui::LabelText("Name", "Dataset");
    {
        const char* items[] = {"Kitti"};
        static int item_current = 0;
        ImGui::Combo("Select", &item_current, items, IM_ARRAYSIZE(items));
    }

    if (ImGui::Button("Load"))
    {
        std::cout << "Loading..." << std::endl;
    }
}
}  // namespace ad_framework::application