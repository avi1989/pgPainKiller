#include "databaseExtractor.h"
#include "queries.h"

DatabaseExtractor::DatabaseExtractor(pqxx::connection* connection) {
    m_connection = connection;
}

void DatabaseExtractor::GetTables() {
    pqxx::work tran (*m_connection);
    pqxx::result result(tran.exec(getAllTables));
    std::cout << "Tables found " << result.size() << " rows\n";

    for(pqxx::result::tuple row : result) {

    }
}
