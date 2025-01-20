#include "../../headers/trees/tree.hpp"

Tree::Tree() { }

Tree::Tree(std::vector<Node*>& nodes) {
    Balance(nodes);
}

Tree::~Tree() {
   delete root; // This calls the destructor of root node, which recursively calls destructors of left and right child nodes
}

void Tree::Balance(std::vector<Node*>& nodes) {
    Sort(nodes);
    root = BalanceNodeRecursive(nodes, 0, nodes.size() - 1);
}

Node* Tree::BalanceNodeRecursive(const std::vector<Node*>& nodes, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int middle = (start + end) / 2; // Always rounds down
    Node* middleNode = nodes[middle];

    middleNode->left = BalanceNodeRecursive(nodes, start, middle - 1);
    middleNode->right = BalanceNodeRecursive(nodes, middle + 1, end);

    return middleNode;
}

inline void Tree::Sort(std::vector<Node*>& nodes) {
    for (size_t i = 0; i < nodes.size(); i++) {
        for (size_t j = 0; j < nodes.size(); j++) {
            if (nodes[i]->value > nodes[j]->value) {
                Node* temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }        
    }
}

void Tree::Insert(Node* node) {
    std::vector<Node*> nodes = std::vector<Node*>();
    if (root != nullptr)
        root->AppendRecursive(nodes);
    nodes.push_back(node);
    Balance(nodes);
}

std::string Tree::Search(const std::string& value) { // The Search only returns the first found value in the tree
    if (root != nullptr) {
        Node* result = root->CheckNode(Util::DetermineDatatype(value));
        if (result != nullptr) {
            std::string dataRow = "";
            result->GetColumnValues(dataRow, true, true, "; ");
            return dataRow;
        }
    }
    return "";
}

void Tree::Display() {
    if (root != nullptr) {
        std::vector<std::string> output = std::vector<std::string>();
        root->RecursiveTreeDisplay(output, 0);
        for (size_t i = 0; i < output.size(); i++) {
            for (size_t j = 0; j < (output.size() - i); j++) {
                std::cout << "\t";
            }
            std::cout << output[i] << "\n";
        }
        std::cout << "\n";
    }
}

std::string Tree::Serialize() {
    std::string output = "";
    root->SerializeRecursive(output);
    return output;
}
    
void Tree::CountNodes(size_t& counter, Node* node) {
    counter++;
    if (node->left != nullptr)
        CountNodes(counter, node->left);
    if (node->right != nullptr)
        CountNodes(counter, node->right);
}

Node* Tree::GetRoot() {
    return root;
}