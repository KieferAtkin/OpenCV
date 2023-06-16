#include "datetime_utils.h"
#include <ctime>
#include <cstring>

std::string getGMTDateTime() {
    std::time_t currentTime = std::time(nullptr);  // Get the current time as a time_t object
    std::tm gmtTime;

    // Use gmtime_s() on Microsoft Visual C++ and MinGW compilers
#if defined(_MSC_VER) || defined(__MINGW32__)
    gmtime_s(&gmtTime, &currentTime);
#else
    // Use gmtime_r() as a fallback for other platforms
    gmtime_r(&currentTime, &gmtTime);
#endif

    char dateTimeStamp[100];  // Create a character array to store the formatted date and time string
    std::strftime(dateTimeStamp, sizeof(dateTimeStamp), "%d-%m-%Y %H:%M:%S", &gmtTime);  // Format the GMT time struct into a string using strftime()
    return std::string(dateTimeStamp);  // Convert the character array to a string and return it
}
