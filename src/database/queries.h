//
// Created by akumar on 10-04-2020.
//

#ifndef PGPAINKILLER_QUERIES_H
#define PGPAINKILLER_QUERIES_H

#include <iostream>

const std::string getAllTables = "SELECT table_name, table_schema\n"
                                 "FROM information_schema.tables\n"
                                 "WHERE table_schema NOT IN ('pg_catalog', 'information_schema')\n"
                                 "AND table_schema NOT LIKE 'pg_toast%'\n"
                                 "AND table_type = 'BASE TABLE';";

#endif //PGPAINKILLER_QUERIES_H
