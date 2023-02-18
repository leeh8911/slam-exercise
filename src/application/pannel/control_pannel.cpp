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

class ControlPannel::Impl
{
 public:
    Impl() = default;
    ~Impl() = default;

    inline void SelectType(size_t type)
    {
        dataloader_ptr_->SelectType(static_cast<DatasetType>(type));
    }

    inline void SelectSequence(size_t index)
    {
        dataloader_ptr_->SelectSequence(index);
    }

    inline const char* const* GetDatasetList() const
    {
        return DataLoader::kItems.data();
    }

    inline int GetDatasetListSize() const
    {
        return static_cast<int>(DataLoader::kItems.size());
    }

    inline bool IsSequenceListEmpty() const
    {
        return dataloader_ptr_->GetSequencePathList().empty();
    }

    inline int GetSequenceListSize() const
    {
        return static_cast<int>(dataloader_ptr_->GetSequencePathList().size());
    }

    inline void SetDataLoader(DataLoaderPtr dataloader_ptr)
    {
        dataloader_ptr_ = dataloader_ptr;
    }

 private:
    std::shared_ptr<DataLoader> dataloader_ptr_{nullptr};
};

ControlPannel::ControlPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Control", position, size), pimpl_(nullptr)
{
}

void ControlPannel::RenderInterface(bool& open)
{
    if (!open)
    {
        return;
    }
    if (pimpl_ == nullptr)
    {
        pimpl_ = std::make_unique<Impl>();
        pimpl_->SetDataLoader(dataloader_ptr_);
    }

    ImGui::Text("Control Pannel");
    ImGui::Spacing();

    ImGui::LabelText("Name", "Dataset");
    {
        static int item_current = 0;
        ImGui::Combo("Select", &item_current, pimpl_->GetDatasetList(),
                     pimpl_->GetDatasetListSize());
        pimpl_->SelectType(static_cast<size_t>(item_current));
    }

    std::string load_button_label = "Load";
    if (pimpl_->IsSequenceListEmpty())
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

        if (ImGui::BeginCombo("Sequence", current_item.c_str()))
        {
            for (size_t n = 0; n < pimpl_->GetSequenceListSize(); n++)
            {
                selected_item = std::to_string(n);
                bool is_selected = (current_item == selected_item);
                if (ImGui::Selectable(selected_item.c_str(), is_selected))
                {
                    current_item = selected_item;
                    pimpl_->SelectSequence(n);
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