/// @file frame.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#include "src/frame/frame.h"

#include <utility>

namespace ad_framework
{
void FrameCollection::AddFrame(FramePtr frame)
{
    if (frames_.size() >= kMaxSize)
    {
        size_t diff = frames_.size() - kMaxSize + 1;
        frames_.erase(frames_.begin(), std::next(frames_.begin(), diff));
    }
    frames_.push_back(std::move(frame));
}

size_t FrameCollection::GetFrameCount() const { return frames_.size(); }
}  // namespace ad_framework
