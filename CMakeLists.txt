cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c function_unset.c utils.c function_env.c
        function_pwd.c function_echo.c function_cd.c function_export.c)