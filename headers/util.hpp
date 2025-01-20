#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <limits>

using TableValue = std::variant<char, short, int, float, double, long, std::string>;

class Util {
public:
    static std::vector<std::string> Split(const std::string& input, const char& splitChar);
    static TableValue DetermineDatatype(std::string input);
};