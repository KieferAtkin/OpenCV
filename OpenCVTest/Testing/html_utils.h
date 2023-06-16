#ifndef HTML_UTILS_H
#define HTML_UTILS_H

#include <string>

void saveImageToHTML(const std::string& imagePath,
					 const std::string& outputFilename,
					 const std::string& variables,
					 const std::string& functions);

#endif // HTML_UTILS_H
