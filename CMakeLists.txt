cmake_minimum_required(VERSION 3.17)
project(minishell C)
set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_SOURCE_DIR}/libft
        ${CMAKE_SOURCE_DIR}/includes
        )
link_directories(
        ${CMAKE_SOURCE_DIR}/libft
        )

add_executable(minishell
        srcs/main.c
        srcs/parser/parser.c
        srcs/executor/ft_echo.c
        srcs/executor/pre_executer.c
        srcs/executor/executor.c
        srcs/executor/example_pipe.c
        srcs/utils/get_next_line.c
        srcs/utils/copy_envp.c
        srcs/utils/new_command.c
        )

target_link_libraries(minishell LINK_PUBLIC
        m
        ${CMAKE_SOURCE_DIR}/libft/libft.a
        )