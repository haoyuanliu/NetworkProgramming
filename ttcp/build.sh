#!/bin/sh

SRCS="Acceptor.cpp InetAddress.cpp TcpStream.cpp Socket.cpp"

set -x
CC=${CC:-g++}

$CC -std=c++11 -Wall -Wextra -g Acceptor.cpp InetAddress.cpp TcpStream.cpp Socket.cpp ttcp.cpp -o ttcp -lboost_program_options
