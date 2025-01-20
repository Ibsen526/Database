#include "../headers/table.hpp"

Table::Table(const std::string pName, const std::vector<std::string>& pColumns) {
    name = pName;
    data = std::vector<std::pair<std::string, Tree*>>();
    data.reserve(pColumns.size());
    for (const std::string& col : pColumns) {
        data.push_back({col, new Tree()});
    }
}

Table::Table(const std::string pName, const size_t pWidth, std::vector<std::pair<std::string, std::vector<Node*>>>& pData) {
    name = pName;
    data = std::vector<std::pair<std::string, Tree*>>(pWidth);
    for (size_t i = 0; i < pData.size(); i++) {
        data[i] = {pData[i].first, new Tree(pData[i].second)};
    }
}

Table::~Table() {
    for (size_t i = 0; i < data.size(); i++) {
        delete data[i].second;
    }
}

void Table::LinkNodesHorizontal(std::vector<std::vector<Node*>>& nodes) {
    size_t treeNumber = nodes.size();
    if (treeNumber > 0) {
        size_t nodeVecSize = nodes[0].size();        
        for (size_t i = 0; i < nodeVecSize; i++) {
            for (size_t j = 0; j < treeNumber; j++) {
                if (j > 0) {
                    nodes[j][i]->previousColumnValue = nodes[j - 1][i];
                }
                if (j < treeNumber - 1) {
                    nodes[j][i]->nextColumnValue = nodes[j + 1][i];
                }
            }
        }
    }
}

void Table::PrintFull() {
    if (data.size() > 0) {
        for (auto& d : data) {
            std::cout << d.first << "\t";
        }
        std::cout << "\n------------------------------------------------------------------------\n";
            
        Node* root = data[0].second->GetRoot();
        if (root != nullptr) {
            std::vector<Node*> nodes = std::vector<Node*>();
            root->AppendRecursive(nodes);
            for (size_t i = 0; i < nodes.size(); i++) {
                std::string dataRow = "";
                nodes[i]->GetColumnValues(dataRow, true, true, "\t"); 
                std::cout << dataRow << "\n";
            }
        }
    }
    std::cout << "\n";
}

void Table::PrintTree(const std::string& column) {
    for (auto& [columnName, tree] : data) {
        if (columnName == column) {
            std::cout << columnName << ":\n";
            tree->Display();
            break;
        }
    }
}

std::string Table::Serialize() { //Serializes the table object into a string, that can then be stored by the database
    std::string output = "";
    size_t numColumns = data.size();
    if (numColumns > 0) { // Only serialize data, if table has any columns and tree isn't empty
        Node* root = data[0].second->GetRoot();
        size_t numRows = 0;
        if (root != nullptr)
            data[0].second->CountNodes(numRows, root);
        output += name + ";" + std::to_string(numColumns) + ";" + std::to_string(numRows) + "\n";

        for (size_t i = 0; i < numColumns; i++) {
            if (i == numColumns - 1)
                output += data[i].first;
            else
                output += data[i].first + ";";
        }
        output += "\n";
        if (root != nullptr)
            output += data[0].second->Serialize(); // This just needs to happen for one tree, since all row nodes are connected
    }
    return output;
}

std::string Table::Search(const std::string& column, const std::string& value) {
    for (auto& [columnName, tree] : data) {
        if (columnName == column) {
            return "{ " + tree->Search(value) + " }";
        }
    }
    return "{  }";
}

void Table::Insert(const std::vector<Node*>& nodes) { // Inserting a node, also causes a rebalancing of the tree: this could hit performance
    size_t numValues = nodes.size();

    //Link row values
    for (size_t i = 0; i < numValues; i++) {
        if (i > 0)
            nodes[i]->previousColumnValue = nodes[i - 1];
        if (i < numValues - 1)
            nodes[i]->nextColumnValue = nodes[i + 1];
    }    
    
    //Insert into tree
    try {
        for (size_t i = 0; i < data.size(); i++) {
            data[i].second->Insert(nodes[i]);
        }
    } 
    catch (...) {
        std::cout << "The inserted dataset doesn't match the size of the table\n";
    }
}

std::string Table::GetName() {
    return name;
}