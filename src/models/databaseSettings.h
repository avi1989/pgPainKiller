//
// Created by akumar on 07-04-2020.
//

#ifndef PGPAINKILLER_DATABASESETTINGS_H
#define PGPAINKILLER_DATABASESETTINGS_H
#include <iostream>
#include <sstream>

struct DatabaseSettings {
    std::string host, username, password;
    int port;

    std::string toString() {
        std::ostringstream strout;
        strout << "Host: " << host << "\nUsername: " << username << "\nPort: " << port << "\nPassword: " << password;
        return strout.str();
    }
};

#endif //PGPAINKILLER_DATABASESETTINGS_H
