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

namespace ad_framework::application
{
class TopViewDrawer
{
 public:
    TopViewDrawer() = default;
    ~TopViewDrawer() = default;

    void Draw() const;
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_TOP_VIEW_DRAWER_H_
