/// @file shape_drawer.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-28
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_USER_INTERFACE_SHAPE_DRAWER_H_
#define SRC_USER_INTERFACE_SHAPE_DRAWER_H_

#include <memory>
#include <vector>

#include "src/data_structure/frame.h"
#include "src/data_structure/shape.h"

namespace ad_framework::user_interface
{

class ShapeDrawer
{
 public:
    template <typename ShapeT, typename DrawT>
    ShapeDrawer(ShapeT shape)
        : pimpl_{std::make_unique<Model<ShapeT, DrawT>>(shape)}
    {
    }
    template <typename ShapeT>
    void Draw(ShapeT shape)
    {
        pimpl_ = std::make_unique<Model<ShapeT>>(shape);
        pimpl_->Draw();
    }

 private:
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void Draw() = 0;
    };

    template <typename ShapeT, typename DrawT>
    struct Model : public Concept
    {
        Model(ShapeT shape, DrawT draw) : shape_(shape), draw_(draw) {}
        void Draw() override { shape.Draw(); }

        ShapeT shape_;
        DrawT draw_;
    };

    std::unique_ptr<Concept> pimpl_{nullptr};
};

}  // namespace ad_framework::user_interface

#endif  // SRC_USER_INTERFACE_SHAPE_DRAWER_H_
