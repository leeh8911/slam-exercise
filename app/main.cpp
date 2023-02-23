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

#include "src/user_interface.h"
#include "src/utils/callback.h"
#include "src/utils/log.h"
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

    auto button = std::make_shared<::ad_framework::ui::Button>("button");
    button->AddCallback(
        "title", std::make_shared<::ad_framework::ui::Button::ButtonChanger>());

    auto selector = std::make_shared<::ad_framework::ui::Selector>("selector");
    auto item_list_sender =
        std::make_shared<::ad_framework::ui::Selector::ItemListSender>();
    auto item_reciever =
        std::make_shared<::ad_framework::ui::Selector::ItemReciever>();
    item_list_sender->SetItems({"item1", "item2", "item3"});
    selector->AddCallback("items", item_list_sender);
    selector->AddCallback("item", item_reciever);

    auto frame = std::make_shared<::ad_framework::ui::Frame>("Main Frame");
    frame->AddUI(button);
    frame->AddUI(selector);

    window.AddUI(frame);

    window();

    return 0;
}
