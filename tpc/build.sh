#!/bin/sh

SRCS="Acceptor.cpp InetAddress.cpp TcpStream.cpp Socket.cpp"

set -x
CC=${CC:-g++}

$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS ttcp.cpp -o ttcp -lboost_program_options
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS echoClient.cpp -o echoClient
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS echo.cpp -o echo -lpthread
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS roundTripUDP.cpp -o roundTripUDP -lpthread
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS nodelayClient.cpp -o nodelayClient
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS nodelayServer.cpp -o nodelayServer
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS sender.cpp -o sender -lpthread
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS netcat.cpp -o netcat -lpthread
$CC -std=c++11 -Wall -Wextra -g -O2 $SRCS chargen.cpp ../datetime/Timestamp.cpp -o chargen -lpthread
