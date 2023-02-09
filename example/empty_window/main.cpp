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
#include <thread>

#include "src/viewer/window.h"

int main()
{
    ::ad_framework::Window window("Empty window");
    bool open = true;
    window.Render(&open);
    return 0;
}
