/// @file log.h
/// @author sangwon lee (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-22
///
/// @copyright Copyright (c) 2023
///
///

#ifndef SRC_UTILS_LOG_H_
#define SRC_UTILS_LOG_H_

#include <iostream>

namespace ad_framework::log
{

enum class LogLevel
{
    kDebug,
    kInfo,
    kWarning,
    kError,
    kFatal,
};

class Log
{
 public:
    Log(LogLevel level, const char* file, int line, const char* msg = "")
    {
        switch (level)
        {
            case LogLevel::kDebug:
                stream_ << "[DEBUG] ";
                break;
            case LogLevel::kInfo:
                stream_ << "[INFO] ";
                break;
            case LogLevel::kWarning:
                stream_ << "[WARNING] ";
                break;
            case LogLevel::kError:
                stream_ << "[ERROR] ";
                break;
            case LogLevel::kFatal:
                stream_ << "[FATAL] ";
                break;
        }
        stream_ << file << ": (" << line << ") " << msg << "\n";
    }
    ~Log() {}

    inline std::ostream& stream() { return stream_; }

 private:
    std::ostream& stream_{std::cout};
};

}  // namespace ad_framework::log

using LogLevel = ::ad_framework::log::LogLevel;

#define LOG_MSG(level, msg) \
    ::ad_framework::log::Log(level, __FILE__, __LINE__, msg).stream()
#define LOG(level) \
    ::ad_framework::log::Log(level, __FILE__, __LINE__, "").stream()
#endif  // SRC_UTILS_LOG_H_
