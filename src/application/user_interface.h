/// @file user_interface.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-12
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_USER_INTERFACE_H_
#define SRC_APPLICATION_USER_INTERFACE_H_

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <forward_list>
#include <memory>
#include <string>

#include "dataloader.h"
#include "src/application/pannel/pannel.h"

namespace ad_framework::application
{

class Window
{
 public:
    Window();
    ~Window() = default;

    void Render(std::forward_list<PannelPtr>& pannels) const;

    ImVec2 GetSize() const;

 private:
    static constexpr int kWidth = 1280;
    static constexpr int kHeight = 720;
    GLFWwindow* window_{nullptr};
};

class UserInterface
{
 public:
    UserInterface();
    ~UserInterface() = default;

    void Execute();

 private:
    Window window_;
    std::forward_list<PannelPtr> pannels_{};
    DataLoaderPtr dataloader_ptr_{};
};

}  // namespace ad_framework::application
#endif  // SRC_APPLICATION_USER_INTERFACE_H_
