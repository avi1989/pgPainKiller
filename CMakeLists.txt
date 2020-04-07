cmake_minimum_required(VERSION 3.10)
project(pgPainKiller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/include/pqxx)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
file(GLOB_RECURSE SOURCE_FILES "./*.cpp")

include_directories("include/")
include_directories("models/")
add_executable(pgPainKiller main.cpp utilities/databaseSettingsReader.cpp utilities/databaseSettingsReader.h)
TARGET_LINK_LIBRARIES(pgPainKiller  ${PQXX_LIB} ${PQ_LIB})