/// @file image_viewer.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-25
///
/// @copyright Copyright (c) 2023
///
///

#include "src/user_interface/image_viewer.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <utility>

#include "GLFW/glfw3.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl2.h"
#include "src/utils/log.h"

namespace ad_framework::ui
{

ImageViewer::ImageViewer(std::string title, ImVec2 size, ImVec2 pos)
    : UserInterface(std::move(title), size, pos)
{
}

ImageViewer::ImageViewer(std::string title)
    : ImageViewer(title, ImVec2{0, 0}, ImVec2{0, 0})
{
}

void ImageViewer::operator()()
{
    ImGui::SetNextWindowSize(Size());
    ImGui::SetNextWindowPos(Pos());

    auto callbacks = GetCallbacks();

    auto image_texture =
        (*callbacks["image-texture"])(std::any{});  // send empty data

    auto image_texture_data =
        std::any_cast<std::pair<size_t, ImVec2>>(image_texture);

    ImGui::Begin("Image Viewer");
    ImGui::Image((void*)image_texture_data.first, image_texture_data.second);
    ImGui::End();
}

ImageViewer::ImageSender::ImageSender(bool is_gray) : is_gray_{is_gray} {}

std::any ImageViewer::ImageSender::operator()(const std::any& src)
{
    if (src.has_value())
    {
        // do nothing
    }
    if (image_path_.empty())
    {
        LOG_MSG(LogLevel::kError, "image path is empty");
    }

    cv::Mat image;

    image = cv::imread(image_path_, cv::IMREAD_COLOR);
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

    if (image.empty())
    {
        LOG_MSG(LogLevel::kError, "image is empty");
    }

    // Generate texture object
    GLuint texture_id = 0;
    glGenTextures(1, &texture_id);

    // Bind texture object
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image data into texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, image.ptr());

    ImVec2 image_size =
        ImVec2{static_cast<float>(image.cols), static_cast<float>(image.rows)};

    return std::pair<size_t, ImVec2>(static_cast<size_t>(texture_id),
                                     image_size);
}

void ImageViewer::ImageSender::SetImagePath(const std::string& image_path)
{
    image_path_ = image_path;
}
}  // namespace ad_framework::ui