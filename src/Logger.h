
#pragma once

#include <functional>
#include <vector>
#include <string.h>
#include <format>

#define LOG_LEVEL LOG_LEVEL_TRACE


enum LogLevel {
    LOG_LEVEL_ALL = 0,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ALARM,
    LOG_LEVEL_ABORT,
    LOG_LEVEL_OFF
};

inline constexpr std::string_view  LOG_LEVEL_STRINGS[7] = { "ALL  ", "TRACE", "INFO ", "WARN ", "ALARM", "ABORT", "OFF" };



/////////////////////////  Background logger functionality not in namespace to avoid confusion  ///////////////////////////

using microlog_LogHandler = std::function<void(int Level, const std::string_view& Module, const std::string_view& Message)>;  // Define function signature

// Get logHandler vector
inline std::vector<microlog_LogHandler>& microlog_getLogHandlers() {
    static std::vector<microlog_LogHandler> handlers;
    return handlers;
}

// Call all log handlers
inline void microlog_CallLoggers(int level, const std::string_view& module, const std::string_view& msg) {
    for (microlog_LogHandler& handler : microlog_getLogHandlers()) {
        handler(level, module, msg);
    }
}

// Macro for defining logging functions
#define DEFINE_LOG_FN(NAME, LEVEL) \
    inline void NAME(const std::string_view& module, const std::string_view& msg) { \
        if constexpr (LOG_LEVEL <= LEVEL) microlog_CallLoggers(LEVEL, module, msg); \
    }




/////////////////////////  Logger namespace  ///////////////////////////

namespace Log {

    DEFINE_LOG_FN(Trace, LOG_LEVEL_TRACE)
    DEFINE_LOG_FN(Info,  LOG_LEVEL_INFO)
    DEFINE_LOG_FN(Warning, LOG_LEVEL_WARN)
    DEFINE_LOG_FN(Alarm, LOG_LEVEL_ALARM)
    DEFINE_LOG_FN(Abort, LOG_LEVEL_ABORT)

    inline void addLogger(const microlog_LogHandler& handler) {
        microlog_getLogHandlers().push_back(handler);
        Info("Logger", "New log handler added");
    }
}