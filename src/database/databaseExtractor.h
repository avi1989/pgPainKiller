#ifndef PGPAINKILLER_DATABASEEXTRACTOR_H
#define PGPAINKILLER_DATABASEEXTRACTOR_H

#include <iostream>
#include <pqxx/pqxx>

class DatabaseExtractor {
private:
    pqxx::connection* m_connection;
public:
    DatabaseExtractor(pqxx::connection* connection);

    void GetTables();
};


#endif //PGPAINKILLER_DATABASEEXTRACTOR_H
