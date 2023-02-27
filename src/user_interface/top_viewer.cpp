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
#include <implot.h>

#include "src/data_structure/frame.h"
#include "src/utils/log.h"

namespace ad_framework::ui
{

TopViewer::TopViewer(std::string title)
    : TopViewer(std::move(title), ImVec2{0, 0}, ImVec2{0, 0})
{
}

TopViewer::TopViewer(std::string title, ImVec2 size, ImVec2 pos)
    : UserInterface(title, size, pos)
{
}

// draw 3d vertex points in imgui window
void TopViewer::operator()()
{
    ImGui::SetNextWindowSize(Size());
    ImGui::SetNextWindowPos(Pos());

    auto callbacks = GetCallbacks();

    ImGui::Begin(Title().c_str());
    {
        auto frame = callbacks["frame_sender"]->operator()(std::any{});
        auto result = callbacks["frame_drawer"]->operator()(frame);
    }
    ImGui::End();
}

std::any TopViewer::FrameSender::operator()(const std::any& src)
{
    if (!src.has_value())
    {
        // do nothing
    }
    return frame_;
}

void TopViewer::FrameSender::SetFrame(const data_structure::Frame& frame)
{
    frame_ = frame;
}

std::any TopViewer::FrameDrawer::operator()(const std::any& src)
{
    frame_ = std::any_cast<data_structure::Frame>(src);

    float x[1000], y[1000];
    for (int i = 0; i < 1000; ++i)
    {
        x[i] = i * 0.01f;
        y[i] = std::sin(x[i]);
    }

    ImPlot::SetNextAxesLimits(-100, 100, -100, 100);
    if (ImPlot::BeginPlot("3D Viewer"))
    {
        LOG(log::LogLevel::kDebug);
        for (auto& shape : frame_.GetShapes())
        {
            shape;
        }

        ImPlot::PlotScatter("3D Viewer", x, y, 1000);
        ImPlot::EndPlot();
    }
    return std::any{};
}

}  // namespace ad_framework::ui
