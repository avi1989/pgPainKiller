cmake_minimum_required(VERSION 3.10)
project(pgPainKiller)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/include/pqxx)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
file(GLOB_RECURSE SOURCE_FILES "./*.cpp")

include_directories("include/")
include_directories("models/")

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(references/json
        ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json)

add_executable(pgPainKiller src/main.cpp src/models/databaseSettings.h src/utilities/databaseSettingsReader.cpp src/utilities/databaseSettingsReader.h src/database/databaseExtractor.cpp src/database/databaseExtractor.h src/database/queries.h src/models/databaseModel.h src/types/maybe.h)
TARGET_LINK_LIBRARIES(pgPainKiller
        PUBLIC ${PQXX_LIB} ${PQ_LIB}
        PRIVATE nlohmann_json)
