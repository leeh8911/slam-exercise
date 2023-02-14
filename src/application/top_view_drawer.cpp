/// @file top_view_drawer.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-15
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/top_view_drawer.h"

#include <array>
#include <utility>

#include "bindings/imgui.h"
#include "bindings/implot.h"

namespace ad_framework::application
{
void TopViewDrawer::Draw() const
{
    std::array<float, 11> bar_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::array<float, 1000> x_data = {0.f};
    std::array<float, 1000> y_data = {0.f};

    auto x_it = std::begin(x_data);
    auto y_it = std::begin(y_data);
    for (; x_it != std::end(x_data); ++x_it, ++y_it)
    {
        size_t index = std::distance(std::begin(x_data), x_it);
        *x_it = static_cast<float>(index) / 1000.f;
        *y_it = (*x_it) * (*x_it);
    }

    ImVec2 plot_size = ImGui::GetWindowSize();
    plot_size.x *= 0.9f;
    plot_size.y *= 0.9f;

    if (ImPlot::BeginPlot("My Plot", plot_size,
                          ImPlotFlags_NoTitle | ImPlotFlags_NoFrame |
                              ImPlotFlags_Equal | ImPlotFlags_NoLegend |
                              ImPlotFlags_NoBoxSelect))
    {
        ImPlot::SetupAxes("x", "y");
        ImPlot::PlotBars("My Bar Plot", bar_data.data(), 11);
        ImPlot::PlotLine("My Line Plot", x_data.data(), y_data.data(), 1000);
        ImPlot::EndPlot();
    }
}
}  // namespace ad_framework::application