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
        static int sequence_index = 0;

        auto item_getter = [](void* data, int idx, const char** out_text)
        {
            auto* dataset = static_cast<Dataset*>(data);
            std::string name = dataset->GetSequencePathList()[idx].string();
            *out_text = name.c_str();
            return true;
        };
        ImGui::Combo("Select", &sequence_index, item_getter, dataset_.get(),
                     static_cast<int>(dataset_->GetSequencePathList().size()));
        dataset_->SelectSequence(sequence_index);
    }
}
}  // namespace ad_framework::application