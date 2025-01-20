#include <iostream>
//#include <conio.h>

#include "../headers/commands.hpp"

int main() {
    std::cout << "Commands:\n\
        'exit'\t\t\t\t\t\t\t to stop application\n\
        'list db'\t\t\t\t\t\t to list all databases\n\
        'list dbName.table'\t\t\t\t\t to list all tables of a database\n\
        'print dbName.table'\t\t\t\t\t to print all values of a table\n\
        'print dbName.table columnName'\t\t\t\t to print the tree structure of a column\n\
        'create db name'\t\t\t\t\t to create new database\n\
        'create dbName.tableName {column1,column2,...}'\t\t to create new table\n\
        'get dbName.tableName columnName=value'\t\t\t to search for a value from selected table\n\
        'insert dbName.tableName {value1,value2,...}'\t\t to insert a row of values into table\n\
        'save'\t\t\t\t\t\t\t to save all data to the disk\n\n";
    
    App app = App();
    Commands commands = Commands();

    while (true)
    {
        std::string inputCommand = "";
        std::getline(std::cin, inputCommand);
        if (!commands.PatternMatching(app, inputCommand)) 
            break;
    }
    
    app.Save();
    return 0;
}