#include "datetime_utils.h"
#include <chrono>
#include <ctime>
#include <sstream>

std::string getGMTDateTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm gmtTime;

#ifdef _MSC_VER
    // For Microsoft Visual C++, use gmtime_s
    gmtime_s(&gmtTime, &currentTime);
#else
    // For other platforms, use gmtime_r
    if (gmtime_r(&currentTime, &gmtTime) == nullptr) {
        // Handle the case where gmtime_r returns nullptr (e.g., due to an error)
        return "Error getting GMT time";
    }
#endif

    std::stringstream dateTimeStream;
    dateTimeStream << std::put_time(&gmtTime, "%d-%m-%Y %H:%M:%S");

    return dateTimeStream.str();
}
