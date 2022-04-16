cmake_minimum_required (VERSION 2.8.11)

project (hiberlite)

add_definitions (-std=c++11)

include_directories (include)

#
#
#
list (APPEND SOURCES src/BeanLoader.cpp)
list (APPEND SOURCES src/BeanUpdater.cpp)
list (APPEND SOURCES src/ChildKiller.cpp)
list (APPEND SOURCES src/CppModel.cpp)
list (APPEND SOURCES src/Database.cpp)
list (APPEND SOURCES src/ModelExtractor.cpp)
list (APPEND SOURCES src/Registry.cpp)
list (APPEND SOURCES src/SQLiteStmt.cpp)
list (APPEND SOURCES src/Visitor.cpp)
list (APPEND SOURCES src/shared_res.cpp)

add_library (hiberlite ${SOURCES})

target_link_libraries (hiberlite sqlite3)
target_link_libraries (hiberlite pthread)
target_link_libraries (hiberlite dl)
