/// @file ui.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <memory>
#include <string>

#include "src/utils/callback.h"
#include "src/utils/imgui.h"

namespace ad_framework::ui
{
class UserInterface
{
 public:
    UserInterface(std::string title, ImVec2 size, ImVec2 pos);
    virtual ~UserInterface() = default;

    virtual void operator()() = 0;

    void Resize(ImVec2 size);
    void Move(ImVec2 pos);

 protected:
    std::string Title() const;
    void Rename(std::string title);
    ImVec2 Size() const;
    ImVec2 Pos() const;

 private:
    std::string title_{""};
    ImVec2 size_{};
    ImVec2 pos_{};
};
using UserInterfacePtr = std::shared_ptr<UserInterface>;

}  // namespace ad_framework::ui
#endif  // SRC_UI_H_
