cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell srcs/main.c srcs/function_unset.c srcs/utils.c srcs/function_env.c
        srcs/function_pwd.c srcs/function_echo.c srcs/function_cd.c srcs/function_export.c srcs/parser_env.c)