/// @file top_view_drawer.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-15
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_TOP_VIEW_DRAWER_H_
#define SRC_APPLICATION_TOP_VIEW_DRAWER_H_

#include "bindings/imgui.h"

namespace ad_framework::application
{
class TopViewDrawer
{
 public:
    TopViewDrawer() = default;
    ~TopViewDrawer() = default;

    void Draw() const;

 private:
    ImVec2 axes_range_x_ = ImVec2(-10, 10);
    ImVec2 axes_range_y_ = ImVec2(-10, 10);
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_TOP_VIEW_DRAWER_H_
