#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <variant>
#include <string>

#include "../util.hpp"

class Node {
public:
    Node(TableValue v);
    ~Node();
    Node* CheckNode(const TableValue& input);
    void GetColumnValues(std::string& dataRow, bool previous, bool next, const std::string& delimiter);
    std::string TableValueToString(); //inline
    void RecursiveTreeDisplay(std::vector<std::string>& output, size_t depth);
    void AppendRecursive(std::vector<Node*>& nodes);
    void SerializeRecursive(std::string& output);

    Node* left = nullptr;
    Node* right = nullptr;
    TableValue value;
    Node* previousColumnValue = nullptr; //With this one can iterate all the values in one row
    Node* nextColumnValue = nullptr;
};