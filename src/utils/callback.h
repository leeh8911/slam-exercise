/// @file callback.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_CALLBACK_H_
#define SRC_CALLBACK_H_

#include <any>
#include <memory>

namespace ad_framework::callback
{
struct Callback
{
    virtual ~Callback() = default;

    virtual std::any operator()(const std::any& src) = 0;
};

using CallbackPtr = std::shared_ptr<Callback>;

class NullCallback : public ::ad_framework::callback::Callback
{
 public:
    std::any operator()(const std::any& src) override { return src; }
};
}  // namespace ad_framework::callback

#endif  // SRC_CALLBACK_H_
