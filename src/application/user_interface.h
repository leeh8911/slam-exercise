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

namespace ad_framework::application
{

class Pannel
{
 public:
    Pannel(std::string name, const ImVec2& position_, const ImVec2& size_);
    virtual ~Pannel() = default;
    void Render(bool& open, const ImVec2& window_size) const;
    virtual void RenderInterface(bool& open) const = 0;

 private:
    std::string name_{};
    ImVec2 position_{};
    ImVec2 size_{};
};

using PannelPtr = std::shared_ptr<Pannel>;

class ControlPannel : public Pannel
{
 public:
    ControlPannel(const ImVec2& position, const ImVec2& size);
    ~ControlPannel() = default;

    void RenderInterface(bool& open) const override;

 private:
};

class DialogPannel : public Pannel
{
 public:
    DialogPannel(const ImVec2& position, const ImVec2& size);
    ~DialogPannel() = default;

    void RenderInterface(bool& open) const override;

 private:
};

class TopViewPannel : public Pannel
{
 public:
    TopViewPannel(const ImVec2& position, const ImVec2& size);
    ~TopViewPannel() = default;

    void RenderInterface(bool& open) const override;

 private:
};

class CamViewPannel : public Pannel
{
 public:
    CamViewPannel(const ImVec2& position, const ImVec2& size);
    ~CamViewPannel() = default;

    void RenderInterface(bool& open) const override;

 private:
};

class MediaPannel : public Pannel
{
 public:
    MediaPannel(const ImVec2& position, const ImVec2& size);
    ~MediaPannel() = default;

    void RenderInterface(bool& open) const override;

 private:
};

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
};

}  // namespace ad_framework::application
#endif  // SRC_APPLICATION_USER_INTERFACE_H_
