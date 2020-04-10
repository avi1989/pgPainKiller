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

    DatabaseSettings(std::string host, std::string username, std::string password, std::string databaseName, int port)
            : host(host), username(username), password(password), databaseName(databaseName), port(port) {

    }

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
    }
};

#endif //PGPAINKILLER_DATABASESETTINGS_H
