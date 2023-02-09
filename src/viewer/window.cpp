/// @file window.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-09
///
/// @copyright Copyright (c) 2023
///
///

#include "src/viewer/window.h"

#include <GLFW/glfw3.h>

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

namespace ad_framework
{

Section::Section(const ImVec2& top_left, const ImVec2& bottom_right,
                 Window* parent)
    : top_left_{}, bottom_right_{}
{
    auto parent_size = parent->GetWindowSize();
    top_left_ = ImVec2(top_left.x * parent_size.x, top_left.y * parent_size.y);
    bottom_right_ =
        ImVec2(bottom_right.x * parent_size.x, bottom_right.y * parent_size.y);
}
void Section::Render(bool* open_ptr)
{
    ImGui::SetNextWindowPos(top_left_);
    ImGui::SetNextWindowSize(
        ImVec2(bottom_right_.x - top_left_.x, bottom_right_.y - top_left_.y));
    ImGui::Begin("Section", open_ptr);
    ImGui::End();
}

Window::Window() : Window("AD Framework") {}
Window::Window(std::string name) : Window(name, 1280, 720) {}

Window::Window(std::string name, int width, int height)
    : sections_{}, window_{nullptr}, name_{name}, width_{width}, height_{height}
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window_ =
        glfwCreateWindow(width_, height_, name_.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard
    // Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable
    // Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL2_Init();

    sections_.push_back(
        std::make_unique<Section>(ImVec2(0.f, 0.f), ImVec2(1.f, 0.1f), this));
    sections_.push_back(
        std::make_unique<Section>(ImVec2(0.f, 0.9f), ImVec2(1.f, 1.f), this));
    sections_.push_back(
        std::make_unique<Section>(ImVec2(0.f, 0.1f), ImVec2(0.3f, 0.9f), this));
    sections_.push_back(
        std::make_unique<Section>(ImVec2(0.3f, 0.1f), ImVec2(1.f, 0.5f), this));
    sections_.push_back(
        std::make_unique<Section>(ImVec2(0.3f, 0.5f), ImVec2(1.f, 0.9f), this));
}

void Window::Render(bool* open_ptr)
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(window_))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto& section : sections_)
        {
            section->Render(open_ptr);
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

ImVec2 Window::GetWindowSize() const
{
    return ImVec2(static_cast<float>(width_), static_cast<float>(height_));
}
}  // namespace ad_framework