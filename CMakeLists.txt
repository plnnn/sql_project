cmake_minimum_required(VERSION 3.23)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp sqlite/sqlite3.h sqlite/sqlite3.c)
