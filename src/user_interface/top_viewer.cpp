/// @file top_viewer.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-27
///
/// @copyright Copyright (c) 2023
///
///

#include "src/user_interface/top_viewer.h"

#include <imgui.h>

#include "src/data_structure/frame.h"
#include "src/utils/log.h"

namespace ad_framework::ui
{

TopViewer::TopViewer(std::string title, ImVec2 size, ImVec2 pos)
    : UserInterface(title, size, pos)
{
}

void TopViewer::operator()()
{
    ImGui::Begin(Title().c_str());
    ImGui::End();
}

std::any TopViewer::FrameSender::operator()(const std::any& src)
{
    if (!src.has_value())
    {
        LOG(log::LogLevel::kDebug);
    }
    return frame_;
}

void TopViewer::FrameSender::SetFrame(const data_structure::Frame& frame)
{
    frame_ = frame;
}

}  // namespace ad_framework::ui