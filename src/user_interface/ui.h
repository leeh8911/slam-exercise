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
#include <unordered_map>
#include <vector>

#include "src/utils/callback.h"
#include "src/utils/imgui.h"

namespace ad_framework::ui
{

class UserInterface;
using UserInterfacePtr = std::shared_ptr<UserInterface>;

using CallbackMap = std::unordered_map<std::string, callback::CallbackPtr>;

class UserInterface : public std::enable_shared_from_this<UserInterface>
{
 public:
    UserInterface(std::string title, ImVec2 size, ImVec2 pos);
    virtual ~UserInterface() = default;

    virtual void operator()() = 0;

    std::string Title() const;
    void Rename(std::string title);
    ImVec2 Size() const;
    ImVec2 Pos() const;
    void Resize(ImVec2 size);
    void Move(ImVec2 pos);

    void SetParent(UserInterfacePtr parent);
    UserInterfacePtr GetParent() const;
    void AddCallback(std::string name, callback::CallbackPtr callback);
    CallbackMap GetCallbacks() const;

 private:
    std::string title_{""};
    ImVec2 size_{};
    ImVec2 pos_{};

    UserInterfacePtr parent_{nullptr};
    CallbackMap callbacks_{};
};

class Frame : public UserInterface
{
 public:
    Frame(std::string title, ImVec2 size, ImVec2 pos);
    Frame(std::string title);

    void operator()() override;

    void AddUI(UserInterfacePtr ui);

 private:
    std::vector<UserInterfacePtr> children_{};
};

}  // namespace ad_framework::ui
#endif  // SRC_UI_H_
