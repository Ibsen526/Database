#include "../headers/commands.hpp"

bool Commands::PatternMatching(App& app, const std::string& cmd) {
    try {
        if (cmd == "exit") {
            return false;
        }
        else if (cmd == "save") {
            app.Save();
            std::cout << "Saved successfully\n\n";
        }
        else {
            std::vector<std::string> splitResult = Util::Split(cmd, ' ');
            if (splitResult.size() == 0) 
                throw std::string("Command");

            if (splitResult[0] == "create" && splitResult.size() == 3) {
                if (splitResult[1] == "db" || splitResult[1] == "database") { // create db dbName
                    app.CreateDatabase(splitResult[2]);
                    std::cout << "Created database " + splitResult[2] + " successfully\n\n";
                }
                else { // create dbName.tableName {column1,column2,...}
                    auto components = Util::Split(splitResult[1], '.');
                    if (components.size() == 2) {
                        Database* db = app.MatchDatabase(components[0]);
                        if (db != nullptr) {
                            auto columnNames = splitResult[2];
                            columnNames.erase(columnNames.begin()); // Deletes the { 
                            columnNames.pop_back(); // Deletes the }
                            auto names = Util::Split(columnNames, ',');
                            db->CreateTable(components[1], names);
                            std::cout << "Created table " + components[1] + " successfully\n\n";
                        }
                        else throw std::string("Database");
                    } 
                    else throw std::string("Identifier");
                }
            }
            else if (splitResult[0] == "get" && splitResult.size() == 3) { //get dbName.tableName columnName=value
                auto components = Util::Split(splitResult[1], '.');
                auto columnValue = Util::Split(splitResult[2], '=');
                if (components.size() == 2) {
                    Database* db = app.MatchDatabase(components[0]);
                    if (db != nullptr) {
                        Table* table = db->MatchTable(components[1]);
                        if (table != nullptr) {
                            std::cout << table->Search(columnValue[0], columnValue[1]) << "\n\n";
                        }
                        else throw std::string("Table");
                    }
                    else throw std::string("Database");
                } 
                else throw std::string("Identifier");
            }
            else if (splitResult[0] == "insert" && splitResult.size() == 3) { //insert dbName.tableName {value1,value2,...}
                auto components = Util::Split(splitResult[1], '.');
                auto columnValues = splitResult[2];
                if (components.size() == 2) {
                    Database* db = app.MatchDatabase(components[0]);
                    if (db != nullptr) {
                        Table* table = db->MatchTable(components[1]);
                        if (table != nullptr) {
                            columnValues.erase(columnValues.begin()); // Deletes the { 
                            columnValues.pop_back(); // Deletes the }
                            auto values = Util::Split(columnValues, ',');
                            std::vector<Node*> nodes = std::vector<Node*>();
                            nodes.reserve(values.size());
                            for (std::string& v : values) {
                                nodes.push_back(new Node(Util::DetermineDatatype(v)));
                            }
                            table->Insert(nodes);
                            std::cout << "Inserted node successfully\n\n";
                        }
                        else throw std::string("Table");
                    }
                    else throw std::string("Database");
                } 
                else throw std::string("Identifier");
            }
            else if (splitResult[0] == "list" && splitResult.size() == 2) {
                if (splitResult[1] == "db" || splitResult[1] == "dbs" || splitResult[1] == "database" || splitResult[1] == "databases") {
                    std::cout << app.ListDatabases() << "\n";
                }
                else {
                    auto components = Util::Split(splitResult[1], '.');
                    if (components.size() == 2) {
                        Database* db = app.MatchDatabase(components[0]);
                        if (db != nullptr) {
                            std::cout << db->ListTables() << "\n";
                        }
                        else throw std::string("Database");
                    }
                    else throw std::string("Identifier");
                }
            }
            else if (splitResult[0] == "print") {
                if (splitResult.size() == 2) { // print dbName.table
                    auto components = Util::Split(splitResult[1], '.');
                    if (components.size() == 2) {
                        Database* db = app.MatchDatabase(components[0]);
                        if (db != nullptr) {
                            Table* table = db->MatchTable(components[1]);
                            if (table != nullptr) {
                                table->PrintFull();
                            }
                            else throw std::string("Table");
                        }
                        else throw std::string("Database");
                    }
                    else throw std::string("Identifier");
                    
                }
                else if (splitResult.size() == 3) { // print dbName.table columnName
                    auto components = Util::Split(splitResult[1], '.');
                    if (components.size() == 2) {
                        Database* db = app.MatchDatabase(components[0]);
                        if (db != nullptr) {
                            Table* table = db->MatchTable(components[1]);
                            if (table != nullptr) {
                                table->PrintTree(splitResult[2]);
                            }
                            else throw std::string("Table");
                        }
                        else throw std::string("Database");
                    }
                    else throw std::string("Identifier");
                }
            }
            else throw std::string("Command");
        }
    }
    catch(const std::string& source) {
        std::cout << source + " not found\n\n";
    }
    return true;
}