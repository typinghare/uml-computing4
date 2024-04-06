// Copyright 2024 James Chen

#ifndef LOGPATTERN_HPP
#define LOGPATTERN_HPP

#include <regex>
#include <string>

/**
 * @brief Log file regex patterns.
 */
namespace LogPattern {

// Match datetime string in the format of "YYYY-MM-DD HH:MM:SS"
constexpr auto* datetimePatternString = R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}))";

// Match server start line
const std::regex
    SERVER_START(std::string(datetimePatternString) + R"(: \(log\.c\.166\) server started.*)");

// Match server boot complete line
const std::regex SERVER_COMPLETE(
    std::string(datetimePatternString) +
    R"(\.\d{3}:INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080.*)");

// Match service start line
const std::regex SERVICE_START(R"(Starting Service\.\s*(\w*).*)");

// Match service complete line
const std::regex SERVICE_COMPLETE(R"(Service started successfully\.\s*\w* \S*\s*\((\d+) ms\).*)");

}  // namespace LogPattern

#endif
