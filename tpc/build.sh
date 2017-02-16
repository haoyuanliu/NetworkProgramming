#!/bin/sh

SRCS="Acceptor.cpp InetAddress.cpp TcpStream.cpp Socket.cpp"

set -x
CC=${CC:-g++}

$CC -std=c++11 -Wall -Wextra -g $SRCS ttcp.cpp -o ttcp -lboost_program_options
$CC -std=c++11 -Wall -Wextra -g $SRCS echoClient.cpp -o echoClient
$CC -std=c++11 -Wall -Wextra -g $SRCS echo.cpp -o echo -lpthread
$CC -std=c++11 -Wall -Wextra -g $SRCS roundTripUDP.cpp -o roundTripUDP -lpthread
$CC -std=c++11 -Wall -Wextra -g $SRCS nodelayClient.cpp -o nodelayClient
$CC -std=c++11 -Wall -Wextra -g $SRCS nodelayServer.cpp -o nodelayServer
$CC -std=c++11 -Wall -Wextra -g $SRCS sender.cpp -o sender -lpthread
$CC -std=c++11 -Wall -Wextra -g $SRCS netcat.cpp -o netcat -lpthread
