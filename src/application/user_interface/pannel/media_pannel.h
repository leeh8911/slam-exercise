/// @file media_pannel.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_USER_INTERFACE_PANNEL_MEDIA_PANNEL_H_
#define SRC_APPLICATION_USER_INTERFACE_PANNEL_MEDIA_PANNEL_H_

#include <imgui.h>

#include "abstract_pannel.h"
namespace ad_framework::application
{
class MediaPannel : public Pannel
{
 public:
    MediaPannel(const ImVec2& position, const ImVec2& size);
    ~MediaPannel() = default;

 private:
    void RenderInterface(bool& open) override;
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_USER_INTERFACE_PANNEL_MEDIA_PANNEL_H_
