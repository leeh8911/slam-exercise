﻿/// @file user_interface.cpp
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

#include <array>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "bindings/imgui.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl2.h"
#include "bindings/implot.h"
#include "src/application/pannel/cam_view_pannel.h"
#include "src/application/pannel/control_pannel.h"
#include "src/application/pannel/dialog_pannel.h"
#include "src/application/pannel/media_pannel.h"
#include "src/application/pannel/pannel.h"
#include "src/application/pannel/top_view_pannel.h"

namespace ad_framework::application
{

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
    ImPlot::CreateContext();
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

UserInterface::UserInterface()
    : window_{Window{}},
      pannels_{},
      dataloader_ptr_{std::make_shared<DataLoader>()}
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

    for (auto& pannel : pannels_)
    {
        pannel->SetDataLoader(dataloader_ptr_);
    }
}

void UserInterface::Execute() { window_.Render(pannels_); }

}  // namespace ad_framework::application