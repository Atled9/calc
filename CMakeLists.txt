cmake_minimum_required(VERSION 3.10)

project(calc)

add_executable(calc main.c calc.c collections/circular_list.c collections/collections.c token/token.c)

target_link_libraries(calc PRIVATE m)
