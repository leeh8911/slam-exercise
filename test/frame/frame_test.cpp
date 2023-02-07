/// @file frame_test.cpp
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-08
///
/// @copyright Copyright (c) 2023
///
///

#include "src/frame/frame.h"

#include <gtest/gtest.h>

namespace ad_framework::test
{
TEST(FrameTest, CreateNonDataFrameCase)
{
    FrameCollection frame_collection{};

    FramePtr frame_ptr = std::make_unique<CurrentFrame>();

    frame_collection.AddFrame(std::move(frame_ptr));

    EXPECT_EQ(frame_collection.GetFrameCount(), 1);
}
}  // namespace ad_framework::test
