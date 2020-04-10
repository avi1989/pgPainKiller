#include "databaseSettingsReader.h"
#include "cxxopts.h"
#include <iostream>

template<typename T>
T getRequiredArgument(cxxopts::ParseResult *parseResult, cxxopts::Options *options, const std::string &argumentName) {
    if (parseResult->count(argumentName) == 0) {
        std::cout << argumentName << " is required" << std::endl << options->help();
        exit(0);
    }

    return (*parseResult)[argumentName].as<T>();
}

DatabaseSettings readDatabaseSettings(int argc, char *argv[]) {
    cxxopts::Options options("pgPainKiller", "A clean way to version databases in PostgreSQL");

    options.add_options()
            ("host", "Host of the database", cxxopts::value<std::string>())
            ("port", "Port to connect to database", cxxopts::value<int>()->default_value("5432"))
            ("u,username", "Username to connect to the database", cxxopts::value<std::string>())
            ("p,password", "password to connect to the database", cxxopts::value<std::string>())
            ("d, dbname", "Database to connect to", cxxopts::value<std::string>())
            ("h,help", "Print usage");

    cxxopts::ParseResult result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    DatabaseSettings ret_val{
            getRequiredArgument<std::string>(&result, &options, "host"),
            getRequiredArgument<std::string>(&result, &options, "username"),
            getRequiredArgument<std::string>(&result, &options, "password"),
            getRequiredArgument<std::string>(&result, &options, "dbname"),
            result["port"].as<int>(),
    };

    return ret_val;
}