//
// Created by akumar on 10-04-2020.
//

#ifndef PGPAINKILLER_QUERIES_H
#define PGPAINKILLER_QUERIES_H

#include <iostream>

namespace queries {
    const std::string getAllTables = "SELECT table_name, table_schema\n"
                                     "FROM information_schema.tables\n"
                                     "WHERE table_schema NOT IN ('pg_catalog', 'information_schema')\n"
                                     "AND table_schema NOT LIKE 'pg_toast%'\n"
                                     "AND table_type = 'BASE TABLE';";

    const std::string getAllColumns = "SELECT table_name, table_schema, column_name, ordinal_position, column_default, is_nullable, udt_name::regtype::text as data_type, character_maximum_length\n"
                                      "FROM information_schema.columns\n"
                                      "WHERE table_schema NOT IN ('pg_catalog', 'information_schema')";

}
#endif //PGPAINKILLER_QUERIES_H
