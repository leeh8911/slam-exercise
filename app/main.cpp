/// @file main.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-09
///
/// @copyright Copyright (c) 2023
///
///

#include <any>
#include <iostream>

#include "src/user_interface/button.h"
#include "src/utils/callback.h"
#include "src/window.h"

class SampleCallback : public ::ad_framework::callback::Callback
{
 public:
    std::any operator()(const std::any& src) override
    {
        if (src.has_value())
        {
            std::cout << "src has value" << std::endl;
        }
        return src;
    }
};

int main()
{
    ::ad_framework::window::Window window("main window");

    window.AddCallback(std::make_shared<SampleCallback>());
    window.AddUI(std::make_shared<::ad_framework::ui::Button>("button"));

    window();

    return 0;
}
