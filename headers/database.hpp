#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "../headers/table.hpp"

using namespace std::filesystem;

class Database {
public:
    Database(std::string pName);
    ~Database();
    void Serialize();
    void Deserialize();
    std::string GetName();
    std::string Search(const std::string& table, const std::string& column, const std::string& value);
    void CreateTable(const std::string& name, const std::vector<std::string>& columns);
    Table* MatchTable(const std::string& name);
    std::string ListTables();

private: 
    std::string name;
    std::vector<Table*> tables;
    std::string storagePath;
};