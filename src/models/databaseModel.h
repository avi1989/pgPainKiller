#ifndef PGPAINKILLER_DATABASEMODEL_H
#define PGPAINKILLER_DATABASEMODEL_H

#include <iostream>
#include <utility>
#include <vector>

typedef std::string string;

struct Table;

enum ConstraintType {
    PrimaryKey = 1,
    Unique = 2,
    Check = 3,
    ForeignKey = 4,
};

struct TableConstraint {
    virtual ConstraintType getType() {

    }
};

struct Column {
    string name;
    string type;
    string columnLength;
    string defaultValue;
    bool isNullable;
};

struct PrimaryKeyConstraint : TableConstraint {
    explicit PrimaryKeyConstraint(std::vector<Column> &columns) : columns(columns) {
    }

    ConstraintType getType() override {
        return ConstraintType::PrimaryKey;
    }

    std::vector<Column> columns;
};

struct UniqueConstraint : TableConstraint {
    explicit UniqueConstraint(std::vector<Column> &columns) : columns(columns) {
    }

    ConstraintType getType() override {
        return ConstraintType::Unique;
    }

    std::vector<Column> columns;
};

struct CheckConstraint : TableConstraint {
    explicit CheckConstraint(std::string constraint) : constraint(std::move(constraint)) {
    }

    ConstraintType getType() override {
        return ConstraintType::Check;
    }

    std::string constraint;
};

struct ForeignKeyConstraint : TableConstraint {
    ForeignKeyConstraint(Table *destinationTable, std::vector<Column> &destinationColumns,
                         std::vector<Column> &sourceColumns) : destinationTable(destinationTable),
                                                               destinationColumns(destinationColumns),
                                                               sourceColumns(sourceColumns) {}

    ConstraintType getType() override {
        return ConstraintType::ForeignKey;
    }

    Table *destinationTable;
    std::vector<Column> destinationColumns;
    std::vector<Column> sourceColumns;
};

struct Table {
    Table(const string &name, const string &schema) : name(name), schema(schema) {

    }

    string name;
    string schema;
    std::vector<Column> columns;
    std::vector<TableConstraint> constraints;
};

#endif //PGPAINKILLER_DATABASEMODEL_H
