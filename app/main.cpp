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

#include "src/callback.h"
#include "src/window.h"

class SampleCallback : public ::ad_framework::callback::Callback
{
 public:
    void operator()() override { std::cout << "Hello, world!" << std::endl; }
};

int main()
{
    ::ad_framework::window::Window window("main window");

    window.AddCallback(std::make_shared<SampleCallback>());

    window();
    return 0;
}
