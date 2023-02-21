/// @file window.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#include "src/window.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include "GLFW/glfw3.h"
#include "bindings/imgui.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl2.h"
#include "bindings/implot.h"

namespace ad_framework::window
{
Window::Window(std::string title) : title_{title}, window_{nullptr}
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    window_ =
        glfwCreateWindow(static_cast<int>(size_.x), static_cast<int>(size_.y),
                         title_.c_str(), nullptr, nullptr);
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
}

Window::~Window()
{
    // Clean up ImGui
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Clean up GLFW
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Window::AddCallback(Window::CallbackPtr callback)
{
    callbacks_.emplace_back(callback);
}
void Window::AddUI(Window::UserInterfacePtr ui) { uis_.emplace_back(ui); }

void Window::operator()()
{
    // Main loop
    while (!glfwWindowShouldClose(window_))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto& callback : callbacks_)
        {
            (*callback)(0);
        }
        ImGui::Begin("Main Frame");
        for (auto& ui : uis_)
        {
            (*ui)();
        }
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w = 0, display_h = 0;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(background_color_.x, background_color_.y,
                     background_color_.z, background_color_.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }
}
}  // namespace ad_framework::window
