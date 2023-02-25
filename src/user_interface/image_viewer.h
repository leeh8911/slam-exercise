/// @file image_viewer.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-25
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_USER_INTERFACE_IMAGE_VIEWER_H_
#define SRC_USER_INTERFACE_IMAGE_VIEWER_H_

#include "src/user_interface/ui.h"

namespace ad_framework::ui
{
class ImageViewer : public UserInterface
{
 public:
    ImageViewer(std::string title, ImVec2 size, ImVec2 pos);
    ImageViewer(std::string title);

    void operator()() override;

    class ImageSender;
};

class ImageViewer::ImageSender : public callback::Callback
{
 public:
    ImageSender(bool is_gray = true);
    std::any operator()(const std::any& src) override;

    void SetImagePath(const std::string& image_path);

 private:
    std::string image_path_{};
    bool is_gray_{true};
};
}  // namespace ad_framework::ui

#endif  // SRC_USER_INTERFACE_IMAGE_VIEWER_H_
