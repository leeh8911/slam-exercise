/// @file file_selector_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "file_selector_pannel.h"

#include "bindings/imgui.h"

namespace ad_framework::application
{
FileselectorPannel::FileselectorPannel(const ImVec2& position,
                                       const ImVec2& size)
    : Pannel("Fileselector", position, size)
{
}

void FileselectorPannel::RenderInterface(bool& open) const
{
    ImGui::Text("File Selector");
}
}  // namespace ad_framework::application