/// @file top_viewer.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-27
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_USER_INTERFACE_TOP_VIEWER_H_
#define SRC_USER_INTERFACE_TOP_VIEWER_H_

#include "src/data_structure/frame.h"
#include "src/user_interface/ui.h"

namespace ad_framework::ui
{

class TopViewer : public UserInterface
{
 public:
    TopViewer(std::string title, ImVec2 size, ImVec2 pos);
    void operator()() override;

    class FrameSender;

 private:
};

class TopViewer::FrameSender : public callback::Callback
{
 public:
    FrameSender() = default;
    std::any operator()(const std::any& src) override;

    void SetFrame(const data_structure::Frame& frame);

 private:
    data_structure::Frame frame_{};
    std::string title_{};
};

}  // namespace ad_framework::ui

#endif  // SRC_USER_INTERFACE_TOP_VIEWER_H_
