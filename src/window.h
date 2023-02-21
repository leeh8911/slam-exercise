/// @file window.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>

#include "bindings/imgui.h"
#include "src/callback.h"

namespace ad_framework::window
{
class Window
{
    using CallbackPtr = ::ad_framework::callback::CallbackPtr;

 public:
    Window(std::string title);
    ~Window();

    void AddCallback(CallbackPtr callback);
    void operator()();

 private:
    std::vector<CallbackPtr> callbacks_{};
    ImVec2 size_{1280, 720};
    ImVec4 background_color_{0.45f, 0.55f, 0.60f, 1.00f};
    std::string title_{""};
    GLFWwindow* window_{nullptr};
};
}  // namespace ad_framework::window

#endif  // SRC_WINDOW_H_
