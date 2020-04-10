//
// Created by akumar on 07-04-2020.
//

#ifndef PGPAINKILLER_DATABASESETTINGS_H
#define PGPAINKILLER_DATABASESETTINGS_H

#include <iostream>
#include <sstream>

struct DatabaseSettings {
    std::string host, username, password, databaseName;
    int port;

    std::string toString() {
        std::ostringstream strout;
        strout << "Host: " << host << "\nUsername: " << username << "\nPort: " << port << "\nPassword: " << password
               << "\n Database: " << databaseName << "\n";
        return strout.str();
    }

    std::string toConnectionString() {
        std::ostringstream connectionString;
        connectionString << "user=" << username << " password=" << password << " host=" << host << " port=" << port
                         << " dbname=" << databaseName;

        return connectionString.str();
        /*pqxx::connection conn("user=postgres "
                         "password=password "
                         "host=localhost "
                         "port=5432 "
                         "dbname=pgpainkiller"); */


    }
};

#endif //PGPAINKILLER_DATABASESETTINGS_H
