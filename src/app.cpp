#include "../headers/app.hpp"

App::App() {
    std::cout << "Application started!\n";
    databases = std::vector<Database*>();
    Load();
}

App::~App() {
    for (size_t i = 0; i < databases.size(); i++) {
        delete databases[i];
    }
}

void App::Save() {
    for (Database* db : databases) {
        db->Serialize();        
    }
}

void App::Load() {
    std::string storagePath = "./data";
    if (exists(storagePath)) {
        for (const auto& entry : directory_iterator(storagePath)) {
            std::string dbName = entry.path().stem().string();
            databases.push_back(new Database(dbName));
        }
    }
}

void App::CreateDatabase(std::string name) {
    databases.emplace_back(new Database(name)); // Directly inputs new database object into vector without a temporary allocation call
}

std::string App::ListDatabases() {
    std::string dbList = "";
    for (size_t i = 0; i < databases.size(); i++) {
        dbList += std::to_string(i) + "\t" + databases[i]->GetName() + "\n";
    }    
    return dbList;
}

Database* App::MatchDatabase(size_t index) {
    if (index >= 0 && index < databases.size()) {
        return databases[index];
    }
    return nullptr;
}

Database* App::MatchDatabase(const std::string& name) {
    for (Database* db : databases) {
        if (db->GetName() == name) {
            return db;
        }
    } 
    return nullptr;
}