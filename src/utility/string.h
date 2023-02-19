/// @file string.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_UTILITY_STRING_H_
#define SRC_UTILITY_STRING_H_

#include <string>

namespace ad_framework
{

std::string ToStringWithZeroPadding(size_t num, size_t padding = 6);
}  // namespace ad_framework
#endif  // SRC_UTILITY_STRING_H_
