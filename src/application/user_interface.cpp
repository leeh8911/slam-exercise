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
#include "src/application/dataloader.h"
#include "src/application/datareader.h"
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
}

bool Window::IsOpen() const { return !glfwWindowShouldClose(window_); }

void Window::NewFrame() const
{
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::Render() const
{
    // Rendering
    ImGui::Render();
    int display_w = 0, display_h = 0;
    glfwGetFramebufferSize(window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(kClearColor.x, kClearColor.y, kClearColor.z, kClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window_);
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
      dataloader_ptr_{std::make_shared<DataLoader>()},
      datareader_ptr_{nullptr}
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

void UserInterface::UpdateDataReader()
{
    if (dataset_type_ == dataloader_ptr_->GetDatasetType())
    {
    }

    dataset_type_ = dataloader_ptr_->GetDatasetType();
    auto base_path = dataloader_ptr_->GetSelectedPath();

    switch (dataset_type_)
    {
        case (DatasetType::kKitti):
            datareader_ptr_ = std::make_shared<KittiDataReader>(base_path);
            break;
        case (DatasetType::kNuscenes):
            [[fallthrough]];
        case (DatasetType::kNone):
            [[fallthrough]];
        default:
            datareader_ptr_ = std::make_shared<NoneDataReader>(base_path);
            break;
    }
}

void UserInterface::Execute()
{
    bool open = true;

    while (window_.IsOpen())
    {
        window_.NewFrame();

        UpdateDataReader();

        for (auto& pannel : pannels_)
        {
            pannel->Update(dataloader_ptr_, datareader_ptr_);
        }
        for (auto& pannel : pannels_)
        {
            pannel->Render(open, window_.GetSize());
        }

        window_.Render();
    }
}

}  // namespace ad_framework::application