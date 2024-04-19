// Copyright 2024 James Chen

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::posix_time::ptime;

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
const std::regex
    SERVICE_COMPLETE(R"(Service started successfully\.\s*(\w*)\s+\S*\s*\((\d+) ms\).*)");

}  // namespace LogPattern

struct LogEntry {
    // Name of the log file
    std::string filename;
};

struct BootLogEntry : LogEntry {
    // Boot start log line number
    int start_line_number = 0;

    // Boot completed log line number
    int completed_line_number = 0;
};

struct ServiceBootLogEntry : BootLogEntry {
    // The name of the service
    std::string service_name;

    // Elapsed time
    int elapsed_time = -1;
};

struct DeviceBootLogEntry : BootLogEntry {
    // Boot start datetime
    ptime start_datetime;

    // Boot completed datetime
    ptime completed_datetime;

    // Services log entries
    std::vector<ServiceBootLogEntry> service_log_entries;
};

/**
 * @brief Traverses the lines of a file, invoking a callback function for each line. This function
 * reads each line from the provided input file stream and invokes the specified callback function
 * for each line. The callback function is called with two parameters: the current line as a string
 * and its corresponding line number.
 * @param ifstream The input file stream to traverse.
 * @param callback The callback function to invoke for each line, taking a string representing the
 * line content and an integer representing the line number as parameters.
 * @return The total line number of the file.
 */
int traverseFile(
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
 * @param filename The name of the scanned file.
 * @param numScannedLine The number of scanned lines.
 */
void outputDeviceBootLogItems(
    std::ostream& ostream,
    const std::vector<DeviceBootLogEntry>& deviceBootLogItems,
    const std::string& filename,
    int numScannedLine);

/**
 * @brief Starts the universe simulation.
 * @param argc The number of arguments.
 * @param argv The arguments array. This program requires one argument:
 * 1. The path of the log file.
 */
int main(const int argc, const char* argv[]) {
    constexpr auto STATUS_ERROR = 1;
    // Names of all services that are started in every boot
    const std::vector<std::string> serviceNameVector = { "Logging",
                                                         "DatabaseInitialize",
                                                         "MessagingService",
                                                         "HealthMonitorService",
                                                         "Persistence",
                                                         "ConfigurationService",
                                                         "CacheService",
                                                         "ThemingService",
                                                         "PortConfigurationService",
                                                         "LandingPadService",
                                                         "DeviceIOService",
                                                         "StagingService",
                                                         "GateService",
                                                         "AVFeedbackService",
                                                         "ReaderDataService",
                                                         "BellService",
                                                         "StateManager",
                                                         "OfflineSmartviewService",
                                                         "DatabaseThreads",
                                                         "ProtocolService",
                                                         "SoftLoadService",
                                                         "WATCHDOG",
                                                         "DiagnosticsService",
                                                         "BiometricService" };

    // Check the arguments
    if (argc != 2) {
        std::cerr << "Too many or too few arguments!" << std::endl;
        return STATUS_ERROR;
    }

    // Try to open the file; exit the program if failing
    std::filesystem::path filepath{ argv[1] };
    std::string filename = filepath.filename().string();
    std::ifstream fileStream{ filepath };
    if (!fileStream.is_open()) {
        std::cerr << "Fail to open file: " << filepath << std::endl;
        return STATUS_ERROR;
    }

    std::vector<DeviceBootLogEntry> device_boot_log_entries;
    const int numScannedLine = traverseFile(fileStream, [&](auto& line, auto line_number) {
        // Match "server start" lines
        match(line, LogPattern::SERVER_START, [&](auto datetimeString, auto index) {
            if (index != 1) {
                return;
            }

            // Add absent services to previous device boot log entry
            if (!device_boot_log_entries.empty()) {
                auto& previous_entry = device_boot_log_entries.back();
                auto& service_log_entries = previous_entry.service_log_entries;
                for (const auto& serviceName : serviceNameVector) {
                    bool found = false;
                    for (const auto& entry : service_log_entries) {
                        if (entry.service_name == serviceName) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        ServiceBootLogEntry new_entry;
                        new_entry.filename = filename;
                        new_entry.service_name = serviceName;
                        service_log_entries.push_back(new_entry);
                    }
                }
            }

            // Add new boot log entry
            DeviceBootLogEntry log_entry;
            log_entry.filename = filename;
            log_entry.start_line_number = line_number;
            log_entry.start_datetime = parseDatetime(datetimeString);
            device_boot_log_entries.push_back(log_entry);
        });

        // Match "server complete" lines
        match(line, LogPattern::SERVER_COMPLETE, [&](auto datetime_string, auto index) {
            if (index == 1 && !device_boot_log_entries.empty()) {
                auto& log_entry = device_boot_log_entries.back();
                log_entry.completed_line_number = line_number;
                log_entry.completed_datetime = parseDatetime(datetime_string);
            }
        });

        if (device_boot_log_entries.empty()) {
            return;
        }

        auto& service_boot_log_entries = device_boot_log_entries.back().service_log_entries;

        // Match "service start" lines
        match(line, LogPattern::SERVICE_START, [&](auto service_name, auto index) {
            if (index == 1) {
                ServiceBootLogEntry log_entry;
                log_entry.filename = filename;
                log_entry.start_line_number = line_number;
                log_entry.service_name = service_name;
                service_boot_log_entries.push_back(log_entry);
            }
        });

        // Match "service complete" lines
        std::string service_name;
        match(line, LogPattern::SERVICE_COMPLETE, [&](auto matched_string, auto index) {
            if (index == 1) {
                service_name = matched_string;
            } else if (index == 2) {
                for (auto& entry : service_boot_log_entries) {
                    if (!service_name.empty() && entry.service_name == service_name) {
                        entry.completed_line_number = line_number;
                        entry.elapsed_time = std::stoi(matched_string);
                    }
                }
            }
        });
    });

    // Output all device boot log items to .rpt file
    std::filesystem::path reportFilepath{ filepath.string() + ".rpt" };
    std::ofstream outputStream{ reportFilepath };
    outputDeviceBootLogItems(outputStream, device_boot_log_entries, filename, numScannedLine);
    outputStream.close();

    return 0;
}

int traverseFile(
    std::ifstream& ifstream, const std::function<void(const std::string&, int)>& callback) {
    int line_number = 1;
    std::string line;
    while (getline(ifstream, line)) {
        callback(line, line_number);
        ++line_number;
    }

    ifstream.close();

    return line_number - 1;
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
    static const std::locale locale(
        std::locale::classic(), new boost::posix_time::time_input_facet("%Y-%m-%d %H:%M:%S"));

    std::stringstream ss{ datetimeString };
    ss.imbue(locale);
    ptime datetime;

    return ss >> datetime ? datetime : ptime{};
}

std::string toString(const ptime& datetime) {
    static const std::locale locale(
        std::locale::classic(), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S"));

    std::stringstream ss;
    ss.imbue(locale);
    ss << datetime;

    return ss.str();
}

void outputDeviceBootLogItems(
    std::ostream& ostream,
    const std::vector<DeviceBootLogEntry>& deviceBootLogItems,
    const std::string& filename,
    const int numScannedLine) {
    // Initiated boot count and completed boot count
    const auto initiatedBootCount = static_cast<int64_t>(deviceBootLogItems.size());
    const auto completedBootCount = std::count_if(
        deviceBootLogItems.cbegin(), deviceBootLogItems.cend(),
        [](const DeviceBootLogEntry& entry) { return entry.completed_line_number > 0; });

    // Print header
    ostream << "Device Boot Report" << std::endl << std::endl;
    ostream << "InTouch log file: " << filename << std::endl;
    ostream << "Lines Scanned: " << numScannedLine << std::endl << std::endl;
    ostream << "Device boot count: initiated = " << initiatedBootCount
            << ", completed: " << completedBootCount << std::endl
            << std::endl
            << std::endl;

    const auto serviceBootLogEntryHandler = [&](const ServiceBootLogEntry& entry) {
        ostream << "\t" << entry.service_name << std::endl;
        if (entry.start_line_number > 0) {
            ostream << "\t\t Start: " << entry.start_line_number << "(" << entry.filename << ")"
                    << std::endl;
        } else {
            ostream << "\t\t Start: Not started(" << entry.filename << ")" << std::endl;
        }

        if (entry.completed_line_number > 0) {
            ostream << "\t\t Completed: " << entry.completed_line_number << "(" << entry.filename
                    << ")" << std::endl;
            ostream << "\t\t Elapsed Time: " << entry.elapsed_time << " ms" << std::endl;
        } else {
            ostream << "\t\t Completed: Not Completed(" << entry.filename << ")" << std::endl;
            ostream << "\t\t Elapsed Time: " << std::endl;
        }
    };

    bool isFirstEntry = true;
    const auto deviceBootLogEntryHandler = [&](const DeviceBootLogEntry& entry) {
        if (isFirstEntry) {
            isFirstEntry = false;
        } else {
            ostream << std::endl;
        }

        // Print the boot log entry
        ostream << "=== Device boot ===" << std::endl;
        ostream << entry.start_line_number << "(" << entry.filename
                << "): " << toString(entry.start_datetime) << " Boot Start" << std::endl;
        if (entry.completed_line_number > 0) {
            ostream << entry.completed_line_number << "(" << entry.filename
                    << "): " << toString(entry.completed_datetime) << " Boot Completed"
                    << std::endl;
            const auto duration = entry.completed_datetime - entry.start_datetime;
            ostream << "\tBoot Time: " << duration.total_milliseconds() << "ms" << std::endl;
        } else {
            ostream << "**** Incomplete boot **** " << std::endl;
        }

        // Print service entries
        ostream << std::endl << "Services" << std::endl;
        const auto& service_log_entries = entry.service_log_entries;
        std::for_each(
            service_log_entries.cbegin(), service_log_entries.cend(), serviceBootLogEntryHandler);
    };
    std::for_each(
        deviceBootLogItems.cbegin(), deviceBootLogItems.cend(), deviceBootLogEntryHandler);
}
