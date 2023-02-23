/// @file selector.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-24
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_USER_INTERFACE_SELECTOR_H_
#define SRC_USER_INTERFACE_SELECTOR_H_

#include <array>
#include <string>

#include "src/user_interface/ui.h"

namespace ad_framework::ui
{
class Selector : public UserInterface
{
 public:
    Selector(std::string title, ImVec2 size, ImVec2 pos);
    Selector(std::string title);

    void operator()() override;

    class ItemListSender;
    class ItemReciever;

 private:
    std::vector<const char*> items_{};
    const char* current_item_{nullptr};
};

class Selector::ItemListSender : public callback::Callback
{
 public:
    ItemListSender() = default;
    std::any operator()(const std::any& src) override;

    void SetItems(const std::vector<std::string>& items);

 private:
    std::vector<const char*> items_{};
};

class Selector::ItemReciever : public callback::Callback
{
 public:
    ItemReciever() = default;
    std::any operator()(const std::any& src) override;

    std::string GetItem();

 private:
    std::string item_{};
};

}  // namespace ad_framework::ui
#endif  // SRC_USER_INTERFACE_SELECTOR_H_
