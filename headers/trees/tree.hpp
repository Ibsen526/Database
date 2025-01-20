#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <variant>
#include <string>
#include <algorithm>

#include "node.hpp"

class Tree {
public:
    Tree();
    Tree(std::vector<Node*>& nodes);
    ~Tree();
    void Balance(std::vector<Node*>& nodes);
    inline void Sort(std::vector<Node*>& nodes);
    void Insert(Node* node);
    std::string Search(const std::string& value);
    void Display();
    std::string Serialize();
    void CountNodes(size_t& counter, Node* node);
    Node* GetRoot();

private:     
    Node* root = nullptr;
    Node* BalanceNodeRecursive(const std::vector<Node*>& nodes, int start, int end);
};