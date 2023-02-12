/// @file application.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-12
///
/// @copyright Copyright (c) 2023
///
///

#include "src/application/application.h"

#include "src/application/user_interface.h"

namespace ad_framework::application
{
void Application::Initialize() { ui_ = UserInterface{}; }

void Application::Shutdown() {}
void Application::Execute() { ui_.Execute(); }
}  // namespace ad_framework::application