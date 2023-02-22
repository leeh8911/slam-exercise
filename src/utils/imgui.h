/// @file imgui_helper.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_UTILS_IMGUI_H_
#define SRC_UTILS_IMGUI_H_

#include "bindings/imgui.h"

inline bool operator==(const ImVec2& lhs, const ImVec2& rhs)
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

inline bool operator!=(const ImVec2& lhs, const ImVec2& rhs)
{
    return !(lhs == rhs);
}

#endif  // SRC_UTILS_IMGUI_H_
