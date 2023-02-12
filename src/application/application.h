/// @file application.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-12
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_APPLICATION_APPLICATION_H_
#define SRC_APPLICATION_APPLICATION_H_

#include <memory>
#include <queue>
#include <thread>

#include "src/application/user_interface.h"

namespace ad_framework::application
{
class Application
{
 public:
    Application() = default;
    ~Application() = default;

    void Initialize();
    void Shutdown();
    void Execute();

 private:
    UserInterface ui_{};

    std::queue<std::thread> threads_{};

    static constexpr size_t kMaxThreadCount = 4;
};
}  // namespace ad_framework::application

#endif  // SRC_APPLICATION_APPLICATION_H_
