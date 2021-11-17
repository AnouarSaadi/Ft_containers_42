#!/bin/sh

if [ $1 = "compile" ]; then
    clang++ -Wall -Wextra -Werror -std=c++98 -I srcs main.cpp -o vector
    ./vector > ft
    ./vector std_vector > std
elif [ $1 = "diff" ]; then
    diff ft std
elif [ $1 = "leaks" ]; then
    valgrind -leak-check=full ./vector
elif [ $1 = "del" ]; then
    rm -rf vector vector.dSYM ft std 
fi