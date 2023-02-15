/// @file dialog_pannel.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_PANNEL_DIALOG_PANNEL_H_
#define SRC_APPLICATION_PANNEL_DIALOG_PANNEL_H_

#include <imgui.h>

#include "src/application/pannel/pannel.h"
namespace ad_framework::application
{

class DialogPannel : public Pannel
{
 public:
    DialogPannel(const ImVec2& position, const ImVec2& size);
    ~DialogPannel() = default;

 private:
    void RenderInterface(bool& open) const override;
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_PANNEL_DIALOG_PANNEL_H_
