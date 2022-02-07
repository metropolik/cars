#pragma once
#include <vector>
#include <string>

typedef std::vector<int> Path;

std::vector<std::string> split_string_by_space(const std::string& string);
std::vector<std::string> split_string_by(const std::string& string, const std::string& seperator);