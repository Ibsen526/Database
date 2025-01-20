#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <variant>
#include <string>

#include "trees/tree.hpp"

class Table {
public:
    Table(const std::string pName, const std::vector<std::string>& pColumns); // Empty table
    Table(const std::string pName, const size_t pWidth, std::vector<std::pair<std::string, std::vector<Node*>>>& pData); // Table filled with data
    ~Table();
    void PrintFull();
    void PrintTree(const std::string& column);
    std::string Serialize();
    std::string Search(const std::string& column, const std::string& value);
    void Insert(const std::vector<Node*>& nodes);
    std::string GetName();

private: 
    void LinkNodesHorizontal(std::vector<std::vector<Node*>>& nodes);
    std::string name;
    std::vector<std::pair<std::string, Tree*>> data;
};