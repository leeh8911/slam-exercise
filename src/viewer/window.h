/// @file window.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-09
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VIEWER_WINDOW_H_
#define SRC_VIEWER_WINDOW_H_

#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>

#include "imgui.h"

namespace ad_framework
{
class Window;

struct Section
{
    Section(const ImVec2& top_left, const ImVec2& bottom_right, Window* parent);
    virtual ~Section() = default;
    virtual void Render(bool* open_ptr);

 private:
    ImVec2 top_left_{0.f, 0.f};
    ImVec2 bottom_right_{0.f, 0.f};
    Window* parent_{nullptr};
};

/// @brief Window window implemented by imgui library
class Window
{
 public:
    Window();
    explicit Window(std::string name);
    Window(std::string name, int width, int height);
    ~Window() = default;

    void Render(bool* open_ptr);
    ImVec2 GetWindowSize() const;

 private:
    std::vector<std::unique_ptr<Section>> sections_;
    std::string name_;
    int width_{1280};
    int height_{720};
    GLFWwindow* window_{nullptr};
};

}  // namespace ad_framework

#endif  // SRC_VIEWER_WINDOW_H_
