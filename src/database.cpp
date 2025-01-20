#include "../headers/database.hpp"

Database::Database(std::string pName) {
    name = pName;
    tables = std::vector<Table*>();
    storagePath = "./data";
    Deserialize();
}

Database::~Database() {
    for (size_t i = 0; i < tables.size(); i++) {
        delete tables[i];
    }    
}

void Database::Serialize() {
    if (!exists(storagePath)) { 
        create_directory(storagePath); 
        std::cout << "Directory created: " << storagePath << std::endl; 
    } 
  
    path filepath = storagePath + "/" + name + ".txt"; 
  
    std::ofstream file(filepath); 
    if (file.is_open()) { 
        for (size_t i = 0; i < tables.size(); i++) {
            file << tables[i]->Serialize() << "-\n"; 
        }
        file.close(); 
    } 
    else { 
        std::cerr << "Failed to create file: " << filepath << std::endl; 
    } 
}

void Database::Deserialize() {
    path filepath = storagePath + "/" + name + ".txt"; 
    if (!exists(filepath))
        return;

    std::ifstream file(filepath); 
    if (file.is_open()) { 
        std::string line;
        int counter = 0;

        std::string tblName = "";
        size_t tblWidth = 0;
        size_t tblHeight = 0;
        std::vector<std::pair<std::string, std::vector<Node*>>> tblData;

        while (std::getline(file, line)) {
            if (counter == 0) {
                auto elements = Util::Split(line, ';');
                tblName = elements[0];
                tblWidth = (size_t)std::stoi(elements[1]);
                tblHeight = (size_t)std::stoi(elements[2]);
                tblData = std::vector<std::pair<std::string, std::vector<Node*>>>(tblWidth);
                for (size_t i = 0; i < tblWidth; i++) {
                    tblData[i].second.reserve(tblHeight);
                }
            }
            else if (counter == 1) {
                auto columns = Util::Split(line, ';');
                for (size_t i = 0; i < columns.size(); i++) {
                    tblData[i].first = columns[i];
                }
            }
            else if (line == "-") {
                counter = -1;                    
                tables.push_back(new Table(tblName, tblWidth, tblData));
            }
            else {
                auto values = Util::Split(line, ';');
                for (size_t i = 0; i < values.size(); i++) { //Creating new nodes
                    tblData[i].second.push_back(new Node(Util::DetermineDatatype(values[i])));
                }
                for (size_t i = 0; i < values.size(); i++) { // Linking the rows
                    Node* nodeRef = tblData[i].second[tblData[i].second.size() - 1];
                    if (i > 0)
                        nodeRef->previousColumnValue = tblData[i - 1].second[tblData[i - 1].second.size() - 1];
                    if (i < tblData.size() - 1)
                        nodeRef->nextColumnValue = tblData[i + 1].second[tblData[i + 1].second.size() - 1];
                }
            }
            counter++;
        }

        file.close(); 
    } 
    else { 
        std::cerr << "Failed to create file: " << filepath << std::endl; 
    } 
}

std::string Database::GetName() {
    return name;
}

void Database::CreateTable(const std::string& name, const std::vector<std::string>& columns) {
    tables.emplace_back(new Table(name, columns));
}

Table* Database::MatchTable(const std::string& name) {
    for (Table* tbl : tables) {
        if (tbl->GetName() == name) {
            return tbl;
        }
    }
    return nullptr;
}

std::string Database::ListTables() {
    std::string tblList = "";
    for (size_t i = 0; i < tables.size(); i++) {
        tblList += std::to_string(i) + "\t" + tables[i]->GetName() + "\n";
    }    
    return tblList;
}