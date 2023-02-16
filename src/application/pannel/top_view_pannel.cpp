/// @file top_view_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/pannel/top_view_pannel.h"

namespace ad_framework::application
{

TopViewPannel::TopViewPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Top View", position, size),
      drawer_{std::make_unique<TopViewDrawer>()}
{
}

/// @brief Draw 3D plot for top view. Top view data is stored in the Frame
/// object.
/// @param open
void TopViewPannel::RenderInterface(bool& open)
{
    ImGui::Text("Top View");

    drawer_->Draw();
}
}  // namespace ad_framework::application