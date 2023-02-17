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

#include <stdio.h>

#include <algorithm>
#include <array>
#include <cstring>
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
    if (!open)
    {
        return;
    }
    ImGui::Text("Control Pannel");
    ImGui::Spacing();

    ImGui::LabelText("Name", "Dataset");
    {
        static int item_current = 0;
        ImGui::Combo("Select", &item_current, Dataset::kItems.data(),
                     static_cast<int>(Dataset::kItems.size()));
        dataset_->SelectType(static_cast<DatasetType>(item_current));
    }

    std::string load_button_label = "Load";
    if (dataset_->GetSequencePathList().empty())
    {
        load_button_label = "Download";
    }

    if (ImGui::Button(load_button_label.c_str()))
    {
        std::cout << "Downloading..." << std::endl;
    }

    ImGui::LabelText("Name", "Sequence");
    {
        static std::string current_item = "";
        static std::string selected_item = "";

        auto& path_list = dataset_->GetSequencePathList();
        if (ImGui::BeginCombo("Sequence", current_item.c_str()))
        {
            for (size_t n = 0; n < path_list.size(); n++)
            {
                selected_item = std::to_string(n);
                bool is_selected = (current_item == selected_item);
                if (ImGui::Selectable(selected_item.c_str(), is_selected))
                {
                    current_item = selected_item;
                    dataset_->SelectSequence(n);
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
    }
}
}  // namespace ad_framework::application