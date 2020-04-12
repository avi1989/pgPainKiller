#include <iostream>
#include "utilities/databaseSettingsReader.h"
#include "./database/databaseExtractor.h"

int main(int argc, char *argv[]) {
    DatabaseSettings settings = readDatabaseSettings(argc, argv);

    try {
        pqxx::connection connection(settings.toConnectionString());
        DatabaseExtractor extractor(&connection);
        extractor.getDatabaseModel();
    }
    catch (pqxx::broken_connection &c) {
        std::cerr << "Unable to connect to database" <<"\n " << c.what();
        return 1;
    }

    return 0;
}
