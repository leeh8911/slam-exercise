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
#include <imgui.h>

#include <iostream>
#include <stdexcept>
#include <string>

#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl2.h"

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
void Section::Render(bool* open_ptr) { ImGui::Separator(); }

Window::Window() : Window("AD Framework") {}
Window::Window(std::string name) : Window(name, 1280, 720) {}

Window::Window(std::string name, int width, int height)
    : sections_{}, window_{nullptr}, name_{name}, width_{width}, height_{height}
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    window_ =
        glfwCreateWindow(width_, height_, name_.c_str(), nullptr, nullptr);
    if (window_ == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // clang-format off
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // clang-format on

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL2_Init();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void Window::Render(bool* open_ptr)
{
    std::cout << "Start Rendering\n";
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(window_))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(open_ptr);

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