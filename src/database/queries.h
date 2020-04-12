//
// Created by akumar on 10-04-2020.
//

#ifndef PGPAINKILLER_QUERIES_H
#define PGPAINKILLER_QUERIES_H

#include <iostream>
#include <ostream>
#include <string>

namespace queries {
    const std::string getAllTables = R"###(
SELECT table_name, table_schema
FROM information_schema.tables
WHERE table_schema NOT IN ('pg_catalog', 'information_schema')
AND table_schema NOT LIKE 'pg_toast%'
AND table_type = 'BASE TABLE';

)###";

    const std::string getAllColumns = R"###(
SELECT table_name, table_schema, column_name, ordinal_position, column_default, is_nullable, udt_name::regtype::text as data_type, character_maximum_length
FROM information_schema.columns
WHERE table_schema NOT IN ('pg_catalog', 'information_schema')
)###";

    const std::string getAllSequences = R"###(
SELECT current_database()::information_schema.sql_identifier                     AS sequence_catalog,
       nc.nspname::information_schema.sql_identifier                             AS sequence_schema,
       c.relname::information_schema.sql_identifier                              AS sequence_name,
       format_type(s.seqtypid, NULL::integer)::information_schema.character_data AS data_type,
       s.seqstart::information_schema.character_data                             AS start_value,
       s.seqmin::information_schema.character_data                               AS minimum_value,
       s.seqmax::information_schema.character_data                               AS maximum_value,
       s.seqincrement::information_schema.character_data                         AS increment,
       s.seqcache::information_schema.character_data                             AS cache,
       CASE
           WHEN s.seqcycle THEN 'YES'::text
           ELSE 'NO'::text
           END::information_schema.yes_or_no                                     AS cycle_option
FROM pg_namespace nc,
     pg_class c,
     pg_sequence s
WHERE c.relnamespace = nc.oid
  AND c.relkind = 'S'::char
  AND NOT (EXISTS(SELECT 1
                  FROM pg_depend
                  WHERE pg_depend.classid = 'pg_class'::regclass::oid
                    AND pg_depend.objid = c.oid
                    AND pg_depend.deptype = 'i' ::char))
  AND NOT pg_is_other_temp_schema(nc.oid)
  AND c.oid = s.seqrelid
  AND (pg_has_role(c.relowner, 'USAGE'::text) OR has_sequence_privilege(c.oid, 'SELECT, UPDATE, USAGE'::text));
)###";

    const std::string getBasicConstraints = R"###(
SELECT c.conname                              AS constraint_name,
    c.contype                                     AS constraint_type,
    sch.nspname                                   AS table_schema,
    tbl.relname                                   AS table_name,
    ARRAY_AGG(col.attname ORDER BY u.attposition) AS columns,
            pg_get_constraintdef(c.oid)                   AS definition
    FROM pg_constraint c
            JOIN LATERAL UNNEST(c.conkey) WITH ORDINALITY AS u(attnum, attposition) ON TRUE
    JOIN pg_class tbl ON tbl.oid = c.conrelid
    JOIN pg_namespace sch ON sch.oid = tbl.relnamespace
    JOIN pg_attribute col ON (col.attrelid = tbl.oid AND col.attnum = u.attnum)
    WHERE contype <> 'f'
    GROUP BY constraint_name, constraint_type, table_schema, table_name, definition
            ORDER BY table_schema, table_name;
)###";
}
#endif //PGPAINKILLER_QUERIES_H
