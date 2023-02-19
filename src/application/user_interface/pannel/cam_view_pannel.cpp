/// @file cam_view_pannel.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/user_interface/pannel/cam_view_pannel.h"

#include <GLFW/glfw3.h>

#include <iostream>
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

    auto stereo_image = datareader_ptr_->GetColorStereoImage();
    if (stereo_image == nullptr)
    {
        return;
    }
    std::cout << "Read Image\n";
    auto left_image = stereo_image->Left();
    GLuint image_texture = 0;

    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int rows = static_cast<int>(left_image->GetRowSize());
    int cols = static_cast<int>(left_image->GetColSize());

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cols, rows, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, left_image->GetRawPointer());

    ImGui::Image((void*)(intptr_t)image_texture, ImGui::GetWindowSize());
}

}  // namespace ad_framework::application