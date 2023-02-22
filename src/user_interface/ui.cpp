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
#include "src/utils/log.h"

namespace ad_framework::ui
{

UserInterface::UserInterface(std::string title, ImVec2 size, ImVec2 pos,
                             UserInterfacePtr parent)
    : title_{std::move(title)}, size_{size}, pos_{pos}, parent_{parent}
{
}

std::string UserInterface::Title() const { return title_; }
void UserInterface::Rename(std::string title) { title_ = std::move(title); }

ImVec2 UserInterface::Size() const { return size_; }
ImVec2 UserInterface::Pos() const { return pos_; }

void UserInterface::Resize(ImVec2 size) { size_ = size; }
void UserInterface::Move(ImVec2 pos) { pos_ = pos; }

Frame::Frame(std::string title)
    : Frame(std::move(title), ImVec2(0.f, 0.f), ImVec2(0.f, 0.f))
{
}
Frame::Frame(std::string title, ImVec2 size, ImVec2 pos)
    : UserInterface(std::move(title), size, pos, nullptr)
{
}

void Frame::operator()()
{
    bool open = true;
    ImGui::Begin(Title().c_str(), &open);
    for (auto& ui : uis_)
    {
        if (ui != nullptr)
        {
            (*ui)();
        }
    }
    ImGui::End();
}

void Frame::AddUI(UserInterfacePtr ui)
{
    LOG_MSG(LogLevel::kDebug, ui->Title().c_str());
    uis_.push_back(ui);
}
}  // namespace ad_framework::ui