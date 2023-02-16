/// @file media_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/pannel/media_pannel.h"

#include "bindings/imgui.h"

namespace ad_framework::application
{
MediaPannel::MediaPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Media", position, size)
{
}

void MediaPannel::RenderInterface(bool& open) { ImGui::Text("Hello, world!"); }

}  // namespace ad_framework::application
