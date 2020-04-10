#include <iostream>
#include "utilities/databaseSettingsReader.h"
#include "./database/databaseExtractor.h"

int main(int argc, char *argv[]) {
    DatabaseSettings settings = readDatabaseSettings(argc, argv);

    try {
        pqxx::connection connection(settings.toConnectionString());
        DatabaseExtractor extractor(&connection);
        extractor.GetTables();
    }
    catch (pqxx::broken_connection &c) {
        std::cerr << "Unable to connect to database" <<"\n " << c.what();
        return 1;
    }

//    std::string host = result["host"].as<std::string>();
    /*pqxx::connection conn("user=postgres "
                          "password=password "
                          "host=localhost "
                          "port=5432 "
                          "dbname=pgpainkiller");
    std::cout << "Connected to " << conn.dbname() << std::endl;

    pqxx::work tran{conn};

    pqxx::result R{tran.exec("SELECT * FROM public.person")};
    std::cout << "Found " << R.size() << "rows\n";

    for (pqxx::result::tuple row: R) {
        int id = row["id"].as<int>();
        std::cout << id << row["first_name"].c_str() << std::endl;
        std::cout << row[0].table_column();
    }*/

    return 0;
}
