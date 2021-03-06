#ifndef PGPAINKILLER_DATABASEMODEL_H
#define PGPAINKILLER_DATABASEMODEL_H

#include <iostream>
#include <utility>
#include <vector>
#include "../types/maybe.h"

struct Table;
struct Column;
struct TableConstraint;
struct PrimaryKeyConstraint;
struct UniqueConstraint;
struct CheckConstraint;
struct ForeignKeyConstraint;
struct Sequence;

//<editor-fold desc="Table Types">

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
        columns.clear();
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
        columns.clear();
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
        destinationColumns.clear();
        sourceColumns.clear();
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
        columns.clear();
        constraints.clear();
    }
};
//</editor-fold>

struct Sequence {
    Sequence(const string &sequenceSchema, const string &sequenceName, const string &dataType, int minValue,
             int maxValue, int startValue, int cache) : sequenceSchema(sequenceSchema), sequenceName(sequenceName),
                                                        dataType(dataType), minValue(minValue), maxValue(maxValue),
                                                        startValue(startValue), cache(cache) {}

    std::string sequenceSchema;
    std::string sequenceName;
    std::string dataType;
    int minValue;
    int maxValue;
    int startValue;
    int cache;
};

struct Database {
    std::vector<Sequence *> sequences;
    std::vector<Table *> tables;

    ~Database() {
        sequences.clear();
        tables.clear();
    }
};

#endif //PGPAINKILLER_DATABASEMODEL_H
