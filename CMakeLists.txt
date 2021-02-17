cmake_minimum_required(VERSION 3.17)
project(minishell)

set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_SOURCE_DIR}/libft
        ${CMAKE_SOURCE_DIR}/includes)

add_executable(minishell
        srcs/main.c
        srcs/parser.c
        srcs/get_next_line.c)