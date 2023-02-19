/// @file string.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-19
///
/// @copyright Copyright (c) 2023
///
///

#include "src/utility/string.h"

namespace ad_framework
{
std::string ToStringWithZeroPadding(size_t num, size_t padding)
{
    std::string str = std::to_string(num);
    size_t rest_size = padding - str.length();

    if (rest_size > 0)
    {
        str = std::string(rest_size, '0') + str;
    }

    return str;
}
}  // namespace ad_framework
