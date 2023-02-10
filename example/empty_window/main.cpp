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

#include "src/viewer/window.h"

int main()
{
    std::cout << "Start main function\n";

    std::cout << "Create window\n";
    ::ad_framework::Window window{};
    std::cout << "Finish creating window\n";

    bool open = true;

    std::cout << "Start rendering\n";
    window.Render(&open);
    std::cout << "Finish rendering\n";
    return 0;
}
