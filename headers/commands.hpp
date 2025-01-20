#pragma once
#include <iostream>
#include <regex>

#include "app.hpp"
//#include "util.hpp"

class Commands {
public:
    bool PatternMatching(App& app, const std::string& cmd);
};