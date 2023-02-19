/// @file top_view_pannel.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_USER_INTERFACE_PANNEL_TOP_VIEW_PANNEL_H_
#define SRC_APPLICATION_USER_INTERFACE_PANNEL_TOP_VIEW_PANNEL_H_

#include <memory>

#include "abstract_pannel.h"
#include "bindings/imgui.h"
#include "src/application/user_interface/drawer/top_view_drawer.h"

namespace ad_framework::application
{

/// @brief This class is for rendering the top view of measurements (from lidar,
/// camera, radar, and etc), and processed measurements for autonomous driving.
/// Drawing measurements are kind of 3D points, bounding boxes, freespace, grid
/// map, and etc.
class TopViewPannel : public Pannel
{
 public:
    TopViewPannel(const ImVec2& position, const ImVec2& size);
    ~TopViewPannel() = default;

 private:
    void RenderInterface(bool& open) override;

    std::unique_ptr<TopViewDrawer> drawer_{nullptr};
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_USER_INTERFACE_PANNEL_TOP_VIEW_PANNEL_H_
