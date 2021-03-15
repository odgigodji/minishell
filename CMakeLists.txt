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
        srcs/parser/pars.c
        srcs/parser/make_arguments.c
        srcs/executor/executor.c
        srcs/executor/example_pipe.c
        srcs/get_next_line/get_next_line.c
        srcs/get_next_line/get_next_line_utils.c
#        srcs/utils/get_next_line.c
        srcs/utils/copy_envp.c
        srcs/utils/split_path.c
        srcs/utils/free_line_list.c
        srcs/utils/common_init.c
        srcs/buildins/mini_pwd.c
        srcs/buildins/mini_cd.c
        srcs/buildins/mini_echo.c
        srcs/utils/get_envp_variable.c
        srcs/buildins/mini_export.c
        srcs/executor/execute_command.c
        srcs/buildins/mini_env.c
        )

add_executable(executor_tests
        srcs/executor/executor_tests/00_main_test.c
        srcs/parser/parser.c
        srcs/parser/pars.c
        srcs/executor/executor.c
        srcs/executor/example_pipe.c
#        srcs/utils/get_next_line.c
        srcs/get_next_line/get_next_line.c
        srcs/utils/copy_envp.c
        srcs/utils/split_path.c
        srcs/utils/free_line_list.c
        srcs/utils/common_init.c
        srcs/buildins/mini_pwd.c
        srcs/buildins/mini_cd.c
        srcs/buildins/mini_echo.c
        srcs/utils/get_envp_variable.c
        srcs/buildins/mini_export.c

        srcs/executor/executor_tests/01_test_get_envp_var_pointer.c
        srcs/executor/executor_tests/executor_tests.h
        srcs/executor/execute_command.c
        srcs/buildins/mini_env.c)

target_link_libraries(minishell LINK_PUBLIC
        m
        ${CMAKE_SOURCE_DIR}/libft/libft.a
        )

target_link_libraries(executor_tests LINK_PUBLIC
        m
        ${CMAKE_SOURCE_DIR}/libft/libft.a
        )