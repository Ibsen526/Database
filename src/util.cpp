#include "../headers/util.hpp"

std::vector<std::string> Util::Split(const std::string& input, const char& splitChar) {
    std::vector<std::string> splitResult = std::vector<std::string> { "" };
    unsigned short currentWordIndex = 0;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == splitChar) {
            splitResult.push_back("");
            currentWordIndex++;
        }
        else {
            splitResult[currentWordIndex] += input[i];
        }
    }
    return splitResult;
}

TableValue Util::DetermineDatatype(std::string input) {
    if (input.size() == 1 && !std::isdigit(input[0])){
        return input[0];
    }

    bool isInt = true;
    bool isFloat = true;
    for (size_t i = 0; i < input.size(); i++) {
        if (!std::isdigit(input[i])) {
            if (input[i] == '.') {
                isInt = false;
            }
            else {
                isInt = false;
                isFloat = false;
                break;
            }
        }
    }

    if (isInt) {
        long l = std::stol(input);
        if (l < std::numeric_limits<short>::max() && l > std::numeric_limits<short>::min()) 
            return (short)l;
        else if (l < std::numeric_limits<int>::max() && l > std::numeric_limits<int>::min()) 
            return (int)l;
        else 
            return l;
    }
    else if (isFloat) {
        double d = std::stod(input);
        if (d < std::numeric_limits<float>::max() && d > std::numeric_limits<float>::lowest())
            return (float)d;
        else
            return d;
    }
    else // String
        return input;
}