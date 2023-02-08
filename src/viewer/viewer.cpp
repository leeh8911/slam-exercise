/// @file viewer.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-09
///
/// @copyright Copyright (c) 2023
///
///

#include "src/viewer/viewer.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

namespace ad_framework
{
Section::Section(const ImVec2& top_left, const ImVec2& bottom_right)
    : top_left_{top_left}, bottom_right_{bottom_right}
{
}

Window::Window() : window_{nullptr}, sections_(0)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window_ = glfwCreateWindow(1280, 720, "AD Framework", nullptr, nullptr);
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
        std::make_unique<MenuBar>(ImVec2(0, 0), ImVec2(1, 0.1)));
    sections_.push_back(std::make_unique<Slider>(ImVec2(0, 0.9), ImVec2(1, 1)));
    sections_.push_back(
        std::make_unique<Dashboard>(ImVec2(0, 0.1), ImVec2(0.3, 0.9)));
    sections_.push_back(
        std::make_unique<TopView>(ImVec2(0.3, 0.1), ImVec2(1, 0.5)));
    sections_.push_back(
        std::make_unique<Video>(ImVec2(0.3, 0.5), ImVec2(1, 0.9)));
}

void Window::Render()
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
            section->Render();
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

void MenuBar::Render() {}
void Dashboard::Render() {}
void TopView::Render() {}
void Video::Render() {}
void Slider::Render() {}

}  // namespace ad_framework