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

#include <array>
#include <filesystem>
#include <iostream>
#include <string>

#include "bindings/imgui.h"

namespace ad_framework::application
{
ControlPannel::ControlPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Control", position, size), dataset_{std::make_shared<Dataset>()}
{
}

void ControlPannel::RenderInterface(bool& open)
{
    ImGui::Text("Control Pannel");
    ImGui::Spacing();

    ImGui::LabelText("Name", "Dataset");
    {
        static std::array<const char*, 5> items = {"kitti"};
        static int item_current = 0;
        ImGui::Combo("Select", &item_current, items.data(),
                     static_cast<int>(items.size()));

        dataset_->FindSequences(static_cast<DatasetType>(item_current));
    }

    if (ImGui::Button("Load"))
    {
        std::cout << "Loading..." << std::endl;
    }

    ImGui::BeginChild("left pane", ImVec2(150, 0), true);
    static int selected_index = 0;
    int current_index = 0;
    for (const auto& sequence : dataset_->GetSequenceList())
    {
        std::string label = sequence.filename().string();
        if (ImGui::Selectable(label.c_str(), selected_index == current_index))
        {
            selected_index = current_index;
        }
        ++current_index;
    }
    ImGui::EndChild();
}
}  // namespace ad_framework::application