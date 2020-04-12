#include "databaseExtractor.h"
#include <vector>
#include "queries.h"

DatabaseExtractor::DatabaseExtractor(pqxx::connection *connection) {
    m_tran = new pqxx::work(*connection);
}

void DatabaseExtractor::getTables() {
    pqxx::result result(m_tran->exec(queries::getAllTables));
    std::cout << "Tables found " << result.size() << " rows\n";

    std::vector<Table> tables;
    auto allColumns = getAllColumns();

    for (pqxx::result::tuple row : result) {
        auto table = Table(
                row["table_name"].as<std::string>(),
                row["table_schema"].as<std::string>()
        );

        tables.push_back(table);
    }
}

void DatabaseExtractor::getDatabaseModel() {
    getTables();
}

pqxx::result DatabaseExtractor::getAllColumns() {
    pqxx::result result(m_tran->exec(queries::getAllColumns));
    return result;
}

DatabaseExtractor::~DatabaseExtractor() {
    delete m_tran;
}