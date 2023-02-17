/// @file pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "pannel.h"

#include "bindings/imgui.h"

namespace ad_framework::application
{

Pannel::Pannel(std::string name, const ImVec2& position, const ImVec2& size)
    : name_{name},
      position_{position},
      size_{size},
      window_flags_{0},
      dataset_{nullptr}
{
    window_flags_ |= ImGuiWindowFlags_NoTitleBar;
    window_flags_ |= ImGuiWindowFlags_NoResize;
    window_flags_ |= ImGuiWindowFlags_NoMove;
}

void Pannel::SetDataset(DatasetPtr dataset) { dataset_ = dataset; }
std::string Pannel::GetName() const { return name_; }
void Pannel::Render(bool& open, const ImVec2& window_size)
{
    SetSize(window_size);
    SetPosition(window_size);

    ImGui::Begin(name_.c_str(), &open, window_flags_);
    RenderInterface(open);
    ImGui::End();
}

void Pannel::SetSize(const ImVec2& window_size) const
{
    ImVec2 size = ImVec2(size_.x * window_size.x, size_.y * window_size.y);

    ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
}

void Pannel::SetPosition(const ImVec2& window_size) const
{
    ImVec2 position =
        ImVec2(position_.x * window_size.x, position_.y * window_size.y);
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);
}

}  // namespace ad_framework::application