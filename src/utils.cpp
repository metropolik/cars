#include "utils.h"


std::vector<std::string> split_string_by(const std::string& string, const std::string& seperator) {
    std::vector<std::string> parts;

    size_t current_start = 0;
    size_t current_end = string.find(seperator);
    while (current_end != std::string::npos) {
        parts.push_back(string.substr(current_start, current_end - current_start));
        current_start = current_end + seperator.length(); // +1 to skip the whitespace
        current_end = string.find(seperator, current_start);
    }
    std::string last = string.substr(current_start);
    // in case of trailing seperator don't add an empty string
    if (last.length() > 0) {
        parts.push_back(last);
    }

    return parts;
}

std::vector<std::string> split_string_by_space(const std::string& string) {
    return split_string_by(string, std::string(" "));
}