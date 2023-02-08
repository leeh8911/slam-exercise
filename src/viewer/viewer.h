/// @file viewer.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-09
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_VIEWER_VIEWER_H_
#define SRC_VIEWER_VIEWER_H_

#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

namespace ad_framework
{
struct Section
{
    Section(const ImVec2& top_left, const ImVec2& bottom_right);
    virtual ~Section() = default;
    virtual void Render() = 0;

 private:
    ImVec2 top_left_;
    ImVec2 bottom_right_;
};

class MenuBar : public Section
{
 public:
    void Render() override;
};
class Dashboard : public Section
{
 public:
    void Render() override;
};

class TopView : public Section
{
 public:
    void Render() override;
};

class Video : public Section
{
 public:
    void Render() override;
};

class Slider : public Section
{
 public:
    void Render() override;
};

/// @brief Viewer window implemented by imgui library
class Window
{
 public:
    Window();
    ~Window();

    void Render();

 private:
    std::vector<std::unique_ptr<Section>> sections_;
    GLFWwindow* window_{nullptr};
};

}  // namespace ad_framework

#endif  // SRC_VIEWER_VIEWER_H_
