/// @file main.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-09
///
/// @copyright Copyright (c) 2023
///
///

#include <iostream>

#include "src/application/application.h"

int main()
{
    ::ad_framework::application::Application app{};

    app.Execute();
    return 0;
}
