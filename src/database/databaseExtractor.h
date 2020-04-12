#ifndef PGPAINKILLER_DATABASEEXTRACTOR_H
#define PGPAINKILLER_DATABASEEXTRACTOR_H

#include <iostream>
#include <pqxx/pqxx>
#include "../models/databaseModel.h"

class DatabaseExtractor {
private:
    pqxx::work *m_tran;
    pqxx::result getAllColumns();
    std::vector<Column*> getColumns(pqxx::result &allColumns, const std::string& tableSchema, const std::string& tableName);
    void getTables();
public:
    explicit DatabaseExtractor(pqxx::connection* connection);
    ~DatabaseExtractor();
    void getDatabaseModel();
};


#endif //PGPAINKILLER_DATABASEEXTRACTOR_H
