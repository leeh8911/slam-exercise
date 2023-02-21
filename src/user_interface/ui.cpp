/// @file ui.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#include "ui.h"

#include <utility>

#include "src/utils/imgui.h"

namespace ad_framework::ui
{

UserInterface::UserInterface(std::string title, ImVec2 size, ImVec2 pos)
    : title_{std::move(title)}, size_{size}, pos_{pos}
{
}

std::string UserInterface::Title() const { return title_; }
void UserInterface::Rename(std::string title) { title_ = std::move(title); }

ImVec2 UserInterface::Size() const { return size_; }
ImVec2 UserInterface::Pos() const { return pos_; }

void UserInterface::Resize(ImVec2 size) { size_ = size; }
void UserInterface::Move(ImVec2 pos) { pos_ = pos; }

}  // namespace ad_framework::ui