cmake_minimum_required(VERSION 3.10)
project(cppStudy2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lambda src/lambda.cpp)
add_executable(game game/src/main.cpp
    game/src/map.cpp
    game/src/maps.cpp
    game/src/Player.cpp)
    
target_include_directories(lambda PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/game/include)

set_target_properties(lambda PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)