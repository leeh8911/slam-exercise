/// @file frame.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_FRAME_FRAME_H_
#define SRC_FRAME_FRAME_H_

#include <memory>
#include <vector>

namespace ad_framework
{
struct Frame
{
    virtual ~Frame() = default;
};

using FramePtr = std::unique_ptr<Frame>;
using FrameSharedPtr = std::shared_ptr<Frame>;
using FrameSharedConstPtr = std::shared_ptr<const Frame>;

class CurrentFrame : public Frame
{
 public:
    CurrentFrame() = default;
};

class PrevFrame : public Frame
{
 public:
    PrevFrame() = default;
};

class FrameCollection : public Frame
{
 public:
    FrameCollection() = default;

    void AddFrame(FramePtr frame);

    size_t GetFrameCount() const;

 private:
    static constexpr size_t kMaxSize = 16;
    std::vector<FramePtr> frames_;
};

}  // namespace ad_framework

#endif  // SRC_FRAME_FRAME_H_
