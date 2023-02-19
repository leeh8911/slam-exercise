/// @file view.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-20
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APP_VIEW_H_
#define SRC_APP_VIEW_H_

#include <memory>

#include "src/app/controller.h"

namespace ad_framework::app
{

struct IView
{
    virtual ~IView() = default;

    virtual void DrawPannels() = 0;
};
using ViewPtr = std::shared_ptr<IView>;

class View : public IView
{
 public:
    View(ControllerPtr view_ptr);

    void DrawPannels() override;

 private:
    ControllerPtr view_ptr_{nullptr};
};

}  // namespace ad_framework::app

#endif  // SRC_APP_VIEW_H_
