#ifndef PGPAINKILLER_DATABASEMODEL_H
#define PGPAINKILLER_DATABASEMODEL_H

#include <iostream>
#include <utility>
#include <vector>
#include "../types/maybe.h"

struct Table;

enum ConstraintType {
    PrimaryKey = 1,
    Unique = 2,
    Check = 3,
    ForeignKey = 4,
};

struct TableConstraint {
    virtual ConstraintType getType() = 0;

    virtual ~TableConstraint() = 0;
};

struct Column {
    Column(const std::string &name, const std::string &type, Maybe<int> *columnLength, Maybe<std::string> *defaultValue,
           bool isNullable) : name(name), type(type), columnLength(columnLength), defaultValue(defaultValue),
                              isNullable(isNullable) {}

    std::string name;
    std::string type;
    Maybe<int> *columnLength;
    Maybe<std::string> *defaultValue;
    bool isNullable;
};

struct PrimaryKeyConstraint : TableConstraint {
    explicit PrimaryKeyConstraint(std::vector<Column *> &columns) : columns(columns) {
    }

    ConstraintType getType() override {
        return ConstraintType::PrimaryKey;
    }

    ~PrimaryKeyConstraint() {
        for (auto column : columns) {
            delete column;
        }
    }

    std::vector<Column *> columns;
};

struct UniqueConstraint : TableConstraint {
    explicit UniqueConstraint(std::vector<Column *> &columns) : columns(columns) {
    }

    ConstraintType getType() override {
        return ConstraintType::Unique;
    }

    ~UniqueConstraint() {
        for (auto column : columns) {
            delete column;
        }
    }

    std::vector<Column *> columns;
};

struct CheckConstraint : TableConstraint {
    explicit CheckConstraint(std::string constraint) : constraint(std::move(constraint)) {
    }

    ConstraintType getType() override {
        return ConstraintType::Check;
    }

    ~CheckConstraint() {

    }

    std::string constraint;
};

struct ForeignKeyConstraint : TableConstraint {
    ForeignKeyConstraint(Table *destinationTable, std::vector<Column *> &destinationColumns,
                         std::vector<Column *> &sourceColumns) : destinationTable(destinationTable),
                                                                 destinationColumns(destinationColumns),
                                                                 sourceColumns(sourceColumns) {}

    ConstraintType getType() override {
        return ConstraintType::ForeignKey;
    }

    ~ForeignKeyConstraint() {
        for (auto column : sourceColumns) {
            delete column;
        }

        for (auto column : destinationColumns) {
            delete column;
        }
    }

    Table *destinationTable;
    std::vector<Column *> destinationColumns;
    std::vector<Column *> sourceColumns;
};

struct Table {
    Table(const std::string &name, const std::string &schema, std::vector<Column *> &columns) : name(name),
                                                                                               schema(schema),
                                                                                               columns(columns) {

    }

    std::string name;
    std::string schema;
    std::vector<Column *> columns;
    std::vector<TableConstraint *> constraints;

    ~Table() {
        for (auto column : columns) {
            delete column;
        }

        for (auto constraint : constraints) {
            delete constraint;
        }
    }
};

#endif //PGPAINKILLER_DATABASEMODEL_H
