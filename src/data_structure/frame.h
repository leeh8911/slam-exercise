/// @file frame.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-27
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_DATA_STRUCTURE_FRAME_H_
#define SRC_DATA_STRUCTURE_FRAME_H_

#include <vector>

#include "src/data_structure/shape.h"

namespace ad_framework::data_structure
{

class Frame
{
 public:
    Frame() = default;
    Frame(const std::vector<ShapePtr>& shapes);

    void AddShape(ShapePtr shape);
    void AddShape(const std::vector<ShapePtr>& shapes);
    void Clear();

    std::vector<ShapePtr> GetShapes() const;

 private:
    std::vector<ShapePtr> shapes_{};
};

}  // namespace ad_framework::data_structure
#endif  // SRC_DATA_STRUCTURE_FRAME_H_
