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

void DatabaseExtractor::getDatabaseModel() {
    auto tables = getTables();
    auto sequences = getAllSequences();
    for (auto table : tables) {
        std::cout << "TABLE" << std::endl << "-----------------------------------------------------------" << std::endl;
        std::cout << table.schema << "." << table.name << std::endl;
        std::cout << std::endl << "COLUMNS" << std::endl;
        for (auto column : table.columns) {
            std::cout << column->name << "\t" << column->type;
            if (!column->columnLength->isNothing) {
                std::cout << "(" << column->columnLength->just << ")";
            }

            std::cout << "\t" << (column->isNullable ? "NOT NULL" : "");

            if (!column->defaultValue->isNothing) {
                std::cout << "\t" << column->defaultValue->just;
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    for (auto sequence:sequences) {
        std::cout << "SEQUENCE" << std::endl << "-----------------------------------------------------------"
                  << std::endl;

        std::cout << sequence->sequenceSchema << "." << sequence->sequenceName << std::endl;
    }
}

std::vector<Table> DatabaseExtractor::getTables() {
    pqxx::result result(m_tran->exec(queries::getAllTables));

    std::vector<Table> tables;
    auto allColumns = getAllColumns();
    auto allConstraints = getAllBasicConstraints();

    for (pqxx::result::tuple row : result) {
        auto tableName = row["table_name"].as<std::string>();
        auto tableSchema = row["table_schema"].as<std::string>();
        auto columns = getColumns(allColumns, tableSchema, tableName);
        auto constraints = getBasicConstraints(allConstraints, tableSchema, tableName);
        auto table = Table(
                tableName,
                tableSchema,
                columns
        );

        tables.push_back(table);
    }

    return tables;
}

std::vector<TableConstraint *> DatabaseExtractor::getBasicConstraints(pqxx::result &allConstraints,
                                                                      const std::string &tableSchema,
                                                                      const std::string &tableName) {
    std::vector<TableConstraint *> tableConstraints;

    for (auto row : allConstraints) {
        auto currentTableName = row["table_name"].as<std::string>();
        auto currentTableSchema = row["table_schema"].as<std::string>();

        if (tableName != currentTableName || tableSchema != currentTableSchema) {
            continue;
        }

        auto constraintName = row["constraint_name"].as<std::string>();
        auto constraintType = row["constraint_type"].as<std::string>();
        auto definition = row["definition"].as<std::string>();
        auto columns = row["columns"].as<string>();
    }

    return tableConstraints;
}

pqxx::result DatabaseExtractor::getAllBasicConstraints() {
    pqxx::result result(m_tran->exec(queries::getBasicConstraints));
    return result;
}

std::vector<Sequence *> DatabaseExtractor::getAllSequences() {
    pqxx::result result(m_tran->exec(queries::getAllSequences));
    std::vector<Sequence *> sequences;
    for (auto row: result) {
        auto *sequence = new Sequence(
                row["sequence_schema"].as<std::string>(),
                row["sequence_name"].as<std::string>(),
                row["data_type"].as<std::string>(),
                row["minimum_value"].as<int>(),
                row["maximum_value"].as<int>(),
                row["start_value"].as<int>(),
                row["cache"].as<int>()
        );

        sequences.push_back(sequence);
    }

    return sequences;
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