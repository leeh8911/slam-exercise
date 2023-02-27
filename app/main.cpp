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

    auto image_viewer =
        std::make_shared<::ad_framework::ui::ImageViewer>("image viewer");
    auto image_sender =
        std::make_shared<::ad_framework::ui::ImageViewer::ImageSender>();
    image_sender->SetImagePath(
        "D:\\sangwon\\dataset\\kitti\\odometry\\dataset\\sequences\\00\\image_"
        "0\\000000.png");
    image_viewer->AddCallback("image-texture", image_sender);

    auto image_viewer_1 =
        std::make_shared<::ad_framework::ui::ImageViewer>("image viewer 1");
    auto image_sender_1 =
        std::make_shared<::ad_framework::ui::ImageViewer::ImageSender>(false);
    image_sender_1->SetImagePath(
        "D:\\sangwon\\dataset\\kitti\\odometry\\dataset\\sequences\\00\\image_"
        "2\\000000.png");
    image_viewer_1->AddCallback("image-texture", image_sender_1);

    auto top_viewer =
        std::make_shared<::ad_framework::ui::TopViewer>("top viewer");
    auto frame_sender =
        std::make_shared<::ad_framework::ui::TopViewer::FrameSender>();
    auto frame_drawer =
        std::make_shared<::ad_framework::ui::TopViewer::FrameDrawer>();

    top_viewer->AddCallback("frame_sender", frame_sender);
    top_viewer->AddCallback("frame_drawer", frame_drawer);

    auto frame = std::make_shared<::ad_framework::ui::Frame>("Main Frame");
    frame->AddUI(button);
    frame->AddUI(selector);
    frame->AddUI(image_viewer);
    frame->AddUI(image_viewer_1);
    frame->AddUI(top_viewer);

    window.AddUI(frame);

    window();

    return 0;
}
