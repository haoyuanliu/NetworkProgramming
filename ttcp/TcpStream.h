#pragma once
#include "Common.h"
#include "Socket.h"
#include <memory>

class InetAddress;
class TcpStream;
typedef std::unique_ptr<TcpStream> TcpStreamPtr;

class TcpStream : noncopyable
{
    public:

    private:
        static TcpStreamPtr connectInternal(const InetAddress& serverAddr, const InetAddress* localAddr);
        Socket sock_;
};
