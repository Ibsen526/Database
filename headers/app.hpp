#pragma once
#include <iostream>
#include <vector>

#include "database.hpp"

class App {
public:
    App();
    ~App();
    void Save();
    void Load();
    void CreateDatabase(std::string name);
    std::string ListDatabases();
    Database* MatchDatabase(size_t index);
    Database* MatchDatabase(const std::string& name);

private: 
    std::vector<Database*> databases;
};