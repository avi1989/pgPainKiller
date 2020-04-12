#include "databaseExtractor.h"
#include <vector>
#include "queries.h"

template<typename T>
Maybe<T> *getNullableValue(pqxx::result::tuple result, std::string columnName) {
    return result[columnName].is_null() ? Nothing<T>() : Just(result[columnName].as<T>());
}

DatabaseExtractor::DatabaseExtractor(pqxx::connection *connection) {
    m_tran = new pqxx::work(*connection);
}

void DatabaseExtractor::getTables() {
    pqxx::result result(m_tran->exec(queries::getAllTables));
    std::cout << "Tables found " << result.size() << " rows\n";

    std::vector<Table> tables;
    auto allColumns = getAllColumns();

    for (pqxx::result::tuple row : result) {
        auto tableName = row["table_name"].as<std::string>();
        auto tableSchema = row["table_schema"].as<std::string>();
        auto columns = getColumns(allColumns, tableSchema, tableName);
        auto table = Table(
                tableName,
                tableSchema,
                columns
        );

        tables.push_back(table);
    }
}

void DatabaseExtractor::getDatabaseModel() {
    //TODO: Get Sequences before tables;
    getTables();
}

pqxx::result DatabaseExtractor::getAllColumns() {
    pqxx::result result(m_tran->exec(queries::getAllColumns));
    return result;
}

std::vector<Column *> DatabaseExtractor::getColumns(pqxx::result &allColumns, const std::string &tableSchema,
                                                    const std::string &tableName) {
    std::vector<Column *> columnsForTable;
    for (auto row : allColumns) {
        auto currentTable = row["table_name"].as<std::string>();
        auto currentSchema = row["table_schema"].as<std::string>();
        auto columnName = row["column_name"].as<std::string>();

        if (currentSchema != tableSchema || currentTable != tableName) {
            continue;
        }

        auto *column = new Column(
                row["column_name"].as<std::string>(),
                row["data_type"].as<std::string>(),
                getNullableValue<int>(row, "character_maximum_length"),
                getNullableValue<std::string>(row, "column_default"),
                row["is_nullable"].as<std::string>() == "YES"
        );

        columnsForTable.push_back(column);
    }

    return columnsForTable;
}

DatabaseExtractor::~DatabaseExtractor() {
    delete m_tran;
}