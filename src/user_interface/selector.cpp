/// @file selector.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-24
///
/// @copyright Copyright (c) 2023
///
///

#include "src/user_interface/selector.h"

#include <algorithm>
#include <stdexcept>

#include "src/utils/imgui.h"
#include "src/utils/log.h"

namespace ad_framework::ui
{

Selector::Selector(std::string title, ImVec2 size, ImVec2 pos)
    : UserInterface(std::move(title), size, pos)
{
}

Selector::Selector(std::string title)
    : Selector(std::move(title), ImVec2{0, 0}, ImVec2{0, 0})
{
}

void Selector::operator()()
{
    ImGui::SetNextWindowSize(Size());
    ImGui::SetNextWindowPos(Pos());

    auto callbacks = GetCallbacks();

    LOG_MSG(
        LogLevel::kDebug,
        typeid(std::any_cast<decltype(items_)>((*callbacks["items"])("items")))
            .name());
    const auto items =
        std::any_cast<decltype(items_)>((*callbacks["items"])("items"));
    LOG_MSG(LogLevel::kDebug, typeid(items).name());
    LOG_MSG(LogLevel::kDebug, typeid(items_).name());
    items_ = std::any_cast<decltype(items_)>((*callbacks["items"])("items"));
    LOG(LogLevel::kDebug);

    LOG(LogLevel::kDebug);
    if (ImGui::BeginCombo(
            Title().c_str(),
            current_item_))  // The second parameter is the label
                             // previewed before opening the combo.
    {
        LOG(LogLevel::kDebug);
        for (int n = 0; n < items_.size(); n++)
        {
            LOG(LogLevel::kDebug);
            bool is_selected =
                (current_item_ ==
                 items_[n]);  // You can store your selection however you want,
                              // outside or inside your objects
            LOG(LogLevel::kDebug);
            if (ImGui::Selectable(items_[n], is_selected))
            {
                current_item_ = items_[n];
                std::any _ = (*callbacks["item"])(std::string(current_item_));
            }
            LOG(LogLevel::kDebug);
            if (is_selected)
            {
                // You may set the initial focus
                // when opening the combo
                // (scrolling + for keyboard
                // navigation support)
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

std::any Selector::ItemListSender::operator()(const std::any& src)
{
    if (std::any_cast<std::string>(src) != "items")
    {
        throw std::invalid_argument("src must be \"items\"");
    }

    return items_;
}

void Selector::ItemListSender::SetItems(const std::vector<std::string>& items)
{
    items_ = std::vector<const char*>(items.size());

    std::transform(std::begin(items), std::end(items), std::begin(items_),
                   [](auto& item) { return item.c_str(); });
}

std::any Selector::ItemReciever::operator()(const std::any& src)
{
    item_ = std::any_cast<std::string>(src);
    return item_;
}

std::string Selector::ItemReciever::GetItem() { return item_; };

}  // namespace ad_framework::ui
