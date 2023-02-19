/// @file user_interface.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-12
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_USER_INTERFACE_H_
#define SRC_APPLICATION_USER_INTERFACE_H_

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <forward_list>
#include <memory>
#include <string>

#include "src/application/dataloader.h"
#include "src/application/user_interface/pannel/pannel.h"
#include "src/data_reader/abstract_data_reader.h"

namespace ad_framework::application
{

class Window
{
 public:
    Window();
    ~Window() = default;

    bool IsOpen() const;
    void Render() const;
    void NewFrame() const;

    ImVec2 GetSize() const;

 private:
    static constexpr int kWidth = 1280;
    static constexpr int kHeight = 720;
    static constexpr ImVec4 kClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    GLFWwindow* window_{nullptr};
};

class UserInterface
{
 public:
    UserInterface();
    ~UserInterface() = default;

    void Execute();

    void UpdateDataReader();

 private:
    Window window_;
    std::forward_list<PannelPtr> pannels_{};
    DataLoaderPtr dataloader_ptr_{nullptr};
    DataReaderPtr datareader_ptr_{nullptr};
    DatasetType dataset_type_{DatasetType::kNone};
};

}  // namespace ad_framework::application
#endif  // SRC_APPLICATION_USER_INTERFACE_H_
