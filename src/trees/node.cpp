#include "../../headers/trees/node.hpp"

Node::Node(TableValue v) {
    value = v;
}

Node::~Node() {
    delete left;
    delete right;
}

Node* Node::CheckNode(const TableValue& input) {
    if (value == input) {
        return this;
    }
    else if (value < input) { // This should also work with strings, as they are lexicographically compared
        if (left != nullptr) {
            return left->CheckNode(input);
        }
    }
    else if (value > input) {
        if (right != nullptr) {
            return right->CheckNode(input);
        }
    }
    return nullptr;
}

void Node::GetColumnValues(std::string& dataRow, bool previous, bool next, const std::string& delimiter)
{
    if (previousColumnValue != nullptr && previous)
        previousColumnValue->GetColumnValues(dataRow, true, false, delimiter);

    if (nextColumnValue == nullptr && next)
        dataRow += TableValueToString();
    else 
        dataRow += TableValueToString() + delimiter;
    
    if (nextColumnValue != nullptr && next)
        nextColumnValue->GetColumnValues(dataRow, false, true, delimiter);
}

std::string Node::TableValueToString()
{
    std::string output = "";
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            output = arg;
        } else if constexpr (std::is_same_v<T, char>) {
            output = std::string(1, arg);
        } else if constexpr (std::is_arithmetic_v<T>) {
            output = std::to_string(arg);
        }
    }, value);
    return output;
}

void Node::RecursiveTreeDisplay(std::vector<std::string>& output, size_t depth) {
    std::string temp = TableValueToString();

    if (output.size() <= depth) {
        output.push_back(temp + "\t");
    } 
    else {
        output[depth] += (temp + "\t");        
    }

    if (left != nullptr)
        left->RecursiveTreeDisplay(output, depth + 1);
    if (right != nullptr)
        right->RecursiveTreeDisplay(output, depth + 1);
}

void Node::AppendRecursive(std::vector<Node*>& nodes) {
    nodes.push_back(this);
    if (left != nullptr)
        left->AppendRecursive(nodes);
    if (right != nullptr)
        right->AppendRecursive(nodes);
}

void Node::SerializeRecursive(std::string& output) {
    GetColumnValues(output, true, true, ";");
    output += "\n";

    if (left != nullptr)
        left->SerializeRecursive(output);
    if (right != nullptr)
        right->SerializeRecursive(output);
}