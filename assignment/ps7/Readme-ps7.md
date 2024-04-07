# PS7: Kronos Log Parsing

## Contact

> Name: Zhuojian Chen (James)
>
> Student ID: 02151380
>
> Section: COMP 2040 P 1 203
>
> Time to Complete: Apr 6, 2024

## Description
This project entails developing a program designed to scan through log files in their entirety. The objective is to generate a comprehensive report file that chronologically details every instance when the device and its associated services underwent restart procedures.

### Features

This project is easy to implement, so I added many features to the program to enhance its readability, extensibility, and maintainability.

* `LogPattern` namespace: A namespace containing all regular expressions (constants).
Here's an improved version:
* Structs in a hierarchy:
  * `LogEntry`: Contains metadata about a log file, such as its name.
  * `BootLogEntry`: Extends `LogEntry` to include information about boot processes, such as the start and completion line numbers.
  * `ServiceBootLogEntry`: Represents a log entry specific to the boot process of a service. Extends `LogEntry` to include details like service name and elapsed time.
  * `DeviceBootLogEntry`: Represents a log entry specific to the boot process of a server. Extends `BootLogEntry` to include start and completion date times, as well as a collection of `ServiceBootLogEntry` instances.
* Helper functions accepting lambda as parameters reduce code complexity. There are two essential functions in this program:
  * `traverseFile`: Traverses the lines of a file, invoking a callback function for each line. This function reads each line from the provided input file stream and invokes the specified callback function for each line. The callback function is called with two parameters: the current line as a string and its corresponding line number.
  * `match`: Finds matches in a given string using a regular expression pattern. This function searches for matches of the specified regular expression pattern within the provided string. If one or more matches are found, the callback function is invoked for each match, providing the matched substring and its index within the original string as parameters.


### Approach
I tackled this challenge by employing a line-by-line reading approach to the file, leveraging regular expressions to identify specific patterns within each line. When a line corresponds to a server initialization indication, I instantiate a `DeviceBootLogEntry`, capture the start time as well as the line number, and append it to a vector. Conversely, when encountering a line indicating the completion of server startup, I update the completion time for the most recent `DeviceBootLogEntry` in the vector.

Upon finishing the scanning, all instances of `DeviceBootLogEntry` are systematically outputted to a report file, adhering to a predefined format and maintaining chronological order.

### Regex
Four regular expressions are used in this project:

*  ```c++
   (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}): \(log\.c\.166\) server started.*)
   // `(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})` matches datetime string in the format of "YYYY-MM-DD HH:MM:SS"
   // `(log.c.166) server started` is the fixed string in the server start line
   // Match example: 2014-01-26 14:02:39: (log.c.166) server started 
   ```

* ```c++
  (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\.\d{3}:INFO:oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080.*
  // \d{3} matches three digits, which represent milliseconds
  // `oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080` is the fixed string in the completion line
  // match example: 2014-01-26 14:05:24.465:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080
  ```

* ```c++
  Starting Service\.\s*(\w*).*
  // `\s*` matches zero or more whitespace characters (space characters, etc.)
  // `\w*` matches the name of the service
  // match example: Starting Service.  Logging 1.0
  ```

* ```c++
  Service started successfully\.\s*(\w*)\s+\S*\s*\((\d+) ms\).*
  // \S* matches the version following the service name
  // `\d+` matches one or more digit characters, which is the boot time for the service
  // Service started successfully.  Logging 1.0 (269 ms)
  ```

### Extra Credit
1. I added a summary header and tracked the start and elapsed time of each service.

## Acknowledgments
[regex101](https://regex101.com)
