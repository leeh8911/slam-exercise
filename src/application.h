/// @file application.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-28
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#include <memory>

#include "src/data_structure/frame.h"
#include "src/data_structure/shape.h"
#include "src/user_interface.h"
#include "src/window.h"

using WindowPtr = ::ad_framework::window::WindowPtr;
using UserInterfacePtr = ::ad_framework::user_interface::UserInterfacePtr;

class Application
{
 public:
    Application();
    ~Application();

    void Run();

 private:
    WindowPtr window_{nullptr};
    UserInterfacePtr uis_{};
};

#endif  // SRC_APPLICATION_H_
