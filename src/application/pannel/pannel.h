/// @file pannel.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-16
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_PANNEL_H_
#define SRC_APPLICATION_PANNEL_H_

#include <imgui.h>

#include <memory>
#include <string>

#include "src/application/dataloader.h"
#include "src/application/datareader.h"
namespace ad_framework::application

{
class Pannel
{
 public:
    Pannel(std::string name, const ImVec2& position_, const ImVec2& size_);
    virtual ~Pannel() = default;
    void Update(DataLoaderPtr dataloader_ptr, DataReaderPtr datareader_ptr);
    void Render(bool& open, const ImVec2& window_size);

    std::string GetName() const;

 protected:
    virtual void RenderInterface(bool& open) = 0;
    DataLoaderPtr dataloader_ptr_{nullptr};
    DataReaderPtr datareader_ptr_{nullptr};

 private:
    void SetSize(const ImVec2& window_size) const;
    void SetPosition(const ImVec2& window_size) const;
    std::string name_{};
    ImVec2 position_{};
    ImVec2 size_{};
    ImGuiWindowFlags window_flags_{};
};

using PannelPtr = std::shared_ptr<Pannel>;

}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_PANNEL_H_
