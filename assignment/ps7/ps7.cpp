// Copyright 2024 James Chen

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::posix_time::ptime;

struct LogItem {
    // Name of the log file
    std::string filename;
};

struct DeviceBootLogItem : LogItem {
    // Boot start log line number
    int start_line_number = 0;

    // Boot completed log line number
    int completed_line_number = 0;

    // Boot start datetime
    ptime start_datetime;

    // Boot completed datetime
    ptime completed_datetime;
};

/**
 * @brief Traverses the lines of a file, invoking a callback function for each line. This function
 * reads each line from the provided input file stream and invokes the specified callback function
 * for each line. The callback function is called with two parameters: the current line as a string
 * and its corresponding line number.
 * @param ifstream The input file stream to traverse.
 * @param callback The callback function to invoke for each line, taking a string representing the
 * line content and an integer representing the line number as parameters.
 */
void traverseFile(
    std::ifstream& ifstream, const std::function<void(const std::string&, int)>& callback);

/**
 * @brief Finds matches in a given string using a regular expression pattern. This function searches
 * for matches of the specified regular expression pattern within the provided string. If one or
 * more matches are found, the callback function is invoked for each match, providing the matched
 * substring and its index within the original string as parameters.
 * @param string The string to search for matches.
 * @param pattern The regular expression pattern to match against the string.
 * @param callback The callback function to invoke for each match, taking two parameters: the
 * matched substring and its index within the original string.
 */
void match(
    const std::string& string,
    const std::regex& pattern,
    const std::function<void(const std::string&, int)>& callback);

/**
 * @brief Parses a datetime string into a Boost ptime object. This function takes a datetime string
 * in the format "YYYY-MM-DD HH:MM:SS" and converts it into a Boost ptime object. If the parsing
 * fails, an invalid ptime object is returned.
 * @param datetimeString The datetime string to parse.
 * @return A Boost ptime object representing the parsed datetime. If the parsing fails, an invalid
 * ptime object is returned.
 */
ptime parseDatetime(const std::string& datetimeString);

/**
 * @brief Converts a Boost ptime object into a string representation. This function converts the
 * specified Boost ptime object into a string representation using the format "YYYY-MM-DD HH:MM:SS".
 * The conversion is performed by utilizing a custom time_facet imbued with the desired format.
 * @param datetime The Boost ptime object to convert into a string.
 * @return A string representation of the specified datetime in the format "YYYY-MM-DD HH:MM:SS".
 */
std::string toString(const ptime& datetime);

/**
 * @brief Outputs device boot log items in a particular format.
 * @param ostream The output stream.
 * @param deviceBootLogItems The device boot log items to output.
 */
void outputDeviceBootLogItems(
    std::ostream& ostream, const std::vector<DeviceBootLogItem>& deviceBootLogItems);

/**
 * @brief Starts the universe simulation.
 * @param argc The number of arguments.
 * @param argv The arguments array. This program requires one argument:
 * 1. The path of the log file.
 */
int main(const int argc, const char* argv[]) {
    constexpr auto STATUS_ERROR = 1;

    if (argc != 2) {
        std::cerr << "Too many or too few arguments!" << std::endl;
        return STATUS_ERROR;
    }

    // Try to open the file
    std::filesystem::path filepath{ argv[1] };
    std::string filename = filepath.filename().string();
    std::ifstream fileStream{ filepath };
    if (!fileStream.is_open()) {
        std::cerr << "Fail to open file: " << filepath << std::endl;
        return STATUS_ERROR;
    }

    // Patterns
    const std::string datetimePatternString = R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}))";
    const std::regex serverStartLinePattern(
        datetimePatternString + R"(: \(log\.c\.166\) server started.*)");
    const std::regex completeLinePattern(
        datetimePatternString +
        R"(\.\d{3}:INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080.*)");

    std::vector<DeviceBootLogItem> device_boot_log_items;
    traverseFile(fileStream, [&](auto& line, auto line_number) {
        // Match "server start" lines
        match(line, serverStartLinePattern, [&](auto item, auto index) {
            if (index == 1) {
                DeviceBootLogItem log_item;
                log_item.filename = filename;
                log_item.start_line_number = line_number;
                log_item.start_datetime = parseDatetime(item);
                device_boot_log_items.push_back(log_item);
            }
        });

        // Match "server complete" lines
        match(line, completeLinePattern, [&](auto item, auto index) {
            if (index == 1 && !device_boot_log_items.empty()) {
                auto& log_item = device_boot_log_items.back();
                log_item.completed_line_number = line_number;
                log_item.completed_datetime = parseDatetime(item);
            }
        });
    });

    // Output all device boot log items to .rpt file
    std::filesystem::path reportFilepath{ filepath.string() + ".rpt" };
    std::ofstream outputStream{ reportFilepath };
    outputDeviceBootLogItems(outputStream, device_boot_log_items);
    outputStream.close();

    return 0;
}

void traverseFile(
    std::ifstream& ifstream, const std::function<void(const std::string&, int)>& callback) {
    int line_number = 1;
    std::string line;
    while (getline(ifstream, line)) {
        callback(line, line_number);
        ++line_number;
    }

    ifstream.close();
}

void match(
    const std::string& string,
    const std::regex& pattern,
    const std::function<void(const std::string&, int)>& callback) {
    std::smatch matches;
    if (std::regex_search(string, matches, pattern)) {
        int index = 0;
        for (const auto& matchItem : matches) {
            callback(matchItem, index++);
        }
    }
}

ptime parseDatetime(const std::string& datetimeString) {
    // Define the format of the datetime string
    static const std::locale loc(
        std::locale::classic(), new boost::posix_time::time_input_facet("%Y-%m-%d %H:%M:%S"));

    std::stringstream ss{ datetimeString };
    ss.imbue(loc);
    ptime datetime;

    return ss >> datetime ? datetime : ptime{};
}

std::string toString(const ptime& datetime) {
    static const std::locale loc(
        std::locale::classic(), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S"));

    std::stringstream ss;
    ss.imbue(loc);
    ss << datetime;

    return ss.str();
}

void outputDeviceBootLogItems(
    std::ostream& ostream, const std::vector<DeviceBootLogItem>& deviceBootLogItems) {
    bool isFirstElement = true;
    std::for_each(
        deviceBootLogItems.cbegin(), deviceBootLogItems.cend(), [&](const DeviceBootLogItem& item) {
            if (isFirstElement) {
                isFirstElement = false;
            } else {
                ostream << std::endl;
            }

            ostream << "=== Device boot ===" << std::endl;
            ostream << item.start_line_number << "(" << item.filename
                    << "): " << toString(item.start_datetime) << " Boot Start" << std::endl;
            if (item.completed_line_number > 0) {
                ostream << item.completed_line_number << "(" << item.filename
                        << "): " << toString(item.completed_datetime) << " Boot Completed"
                        << std::endl;
                const auto duration = item.completed_datetime - item.start_datetime;
                ostream << "\tBoot Time: " << duration.total_milliseconds() << "ms" << std::endl;
            } else {
                ostream << "**** Incomplete boot **** " << std::endl;
            }
        });
}
