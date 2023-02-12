/// @file user_interface.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-12
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/user_interface.h"

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>
#include <stdexcept>
#include <string>

#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl2.h"

namespace ad_framework::application
{

Pannel::Pannel(std::string name, const ImVec2& position, const ImVec2& size)
    : name_{name}, position_{position}, size_{size}, window_flags_{0}
{
    // window_flags_ |= ImGuiWindowFlags_NoTitleBar;
    // window_flags_ |= ImGuiWindowFlags_NoResize;
    // window_flags_ |= ImGuiWindowFlags_NoMove;
}

void Pannel::Render(bool& open, const ImVec2& window_size) const
{
    SetSize(window_size);
    SetPosition(window_size);

    ImGui::Begin(name_.c_str(), &open, window_flags_);
    RenderInterface(open);
    ImGui::End();
}

void Pannel::SetSize(const ImVec2& window_size) const
{
    ImVec2 size = ImVec2(size_.x * window_size.x, size_.y * window_size.y);

    ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
}

void Pannel::SetPosition(const ImVec2& window_size) const
{
    ImVec2 position =
        ImVec2(position_.x * window_size.x, position_.y * window_size.y);
    ImGui::SetNextWindowPos(position, ImGuiCond_FirstUseEver);
}

ControlPannel::ControlPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Control", position, size)
{
}

void ControlPannel::RenderInterface(bool& open) const
{
    ImGui::Text("Control Pannel");
    ImGui::Spacing();

    ImGui::LabelText("Name", "Dataset");
    {
        const char* items[] = {"Kitti"};
        static int item_current = 0;
        ImGui::Combo("Select", &item_current, items, IM_ARRAYSIZE(items));
    }

    if (ImGui::Button("Load"))
    {
        std::cout << "Loading..." << std::endl;
    }
}

TopViewPannel::TopViewPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Top View", position, size)
{
}

/// @brief Draw 3D plot for top view. Top view data is stored in the Frame
/// object.
/// @param open
void TopViewPannel::RenderInterface(bool& open) const
{
    ImGui::Text("Top View");

    // Get the size of the child (i.e. the whole draw size of the windows).
    ImVec2 wsize = ImGui::GetWindowSize();
    // Because I use the texture from OpenGL, I need to invert the V from
    // the UV.
    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
}

void CamViewPannel::RenderInterface(bool& open) const
{
    ImGui::Text("Hello, world!");
}

CamViewPannel::CamViewPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Cam View", position, size)
{
}

DialogPannel::DialogPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Dialog", position, size)
{
}

void DialogPannel::RenderInterface(bool& open) const
{
    ImGui::Text("Hello, world!");
}

MediaPannel::MediaPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Media", position, size)
{
}

void MediaPannel::RenderInterface(bool& open) const
{
    ImGui::Text("Hello, world!");
}

Window::Window()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    window_ = glfwCreateWindow(kWidth, kHeight, "Autonomous Driving Framework",
                               nullptr, nullptr);
    if (window_ == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL2_Init();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void Window::Render(std::forward_list<PannelPtr>& pannels) const
{
    bool open = true;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(window_))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto& pannel : pannels)
        {
            pannel->Render(open, GetSize());
        }
        // Rendering
        ImGui::Render();
        int display_w = 0, display_h = 0;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }
}

ImVec2 Window::GetSize() const
{
    int width = 0;
    int height = 0;

    glfwGetWindowSize(window_, &width, &height);

    return ImVec2(static_cast<float>(width), static_cast<float>(height));
}

UserInterface::UserInterface() : window_{Window{}}, pannels_{}
{
    ImVec2 cam_view_position = ImVec2(0.00f, 0.00f);
    ImVec2 cam_view_size = ImVec2(0.20f, 0.40f);
    ImVec2 dialog_position = ImVec2(0.00f, 0.40f);
    ImVec2 dialog_size = ImVec2(0.20f, 0.55f);

    ImVec2 top_view_position = ImVec2(0.20f, 0.00f);
    ImVec2 top_view_size = ImVec2(0.60f, 0.95f);

    ImVec2 control_position = ImVec2(0.80f, 0.00f);
    ImVec2 control_size = ImVec2(0.20f, 0.95f);

    ImVec2 media_position = ImVec2(0.00f, 0.95f);
    ImVec2 media_size = ImVec2(1.00f, 0.05f);

    pannels_.emplace_front(
        std::make_unique<CamViewPannel>(cam_view_position, cam_view_size));
    pannels_.emplace_front(
        std::make_unique<DialogPannel>(dialog_position, dialog_size));
    pannels_.emplace_front(
        std::make_unique<TopViewPannel>(top_view_position, top_view_size));
    pannels_.emplace_front(
        std::make_unique<ControlPannel>(control_position, control_size));
    pannels_.emplace_front(
        std::make_unique<MediaPannel>(media_position, media_size));
}

void UserInterface::Execute() { window_.Render(pannels_); }

}  // namespace ad_framework::application