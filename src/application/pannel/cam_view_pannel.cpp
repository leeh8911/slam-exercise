/// @file cam_view_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/pannel/cam_view_pannel.h"

#include <GLFW/glfw3.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

#include "bindings/imgui.h"

namespace ad_framework::application
{

CamViewPannel::CamViewPannel(const ImVec2& position, const ImVec2& size)
    : Pannel("Cam View", position, size)
{
}

void CamViewPannel::RenderInterface(bool& open)
{
    if (!open)
    {
        return;
    }
    ImGui::Text("Hello, world!");

    // clang-format off
    std::string image_file = "D:\\sangwon\\dataset\\kitti\\odometry\\dataset\\sequences\\00\\image_3\\000000.png";
    // clang-format on

    cv::Mat img = cv::imread(image_file, cv::IMREAD_COLOR);

    GLuint image_texture = 0;

    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, img.ptr());

    ImGui::Image((void*)(intptr_t)image_texture, ImGui::GetWindowSize());
}

}  // namespace ad_framework::application