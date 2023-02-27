/// @file application.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-28
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application.h"

#include <memory>

#include "src/data_structure/frame.h"
#include "src/data_structure/shape.h"
#include "src/user_interface.h"
#include "src/window.h"

Application::Application()
    : window_{std::make_shared<::ad_framework::window::Window>("main window")},
      uis_{}
{
    window_->AddUI(uis_);
}

Application::~Application() {}

void Application::Run() {}
