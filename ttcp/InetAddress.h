#pragma once
#include "Common.h"
#include <string>
#include <vector>
#include <netinet/in.h>

class InetAddress : copyable
{
    public:
        InetAddress(StringArg ip, uint16_t port);
        explicit InetAddress(StringArg ipPort);
        explicit InetAddress(unit16_t port, bool loopbackOnly = false);
        explicit InetAddress(const struct sockaddr_in& saddr) : saddr_(addr) { }

        std::string toIp() const;
        std::string toIpPort() const;
        const struct sockaddr_in& getSockAddrInet() const { return saddr_; }
        void setSockAddrInet(const struct sockaddr_in& saddr) { saddr_ = saddr; }
        void setPort(uint16_t port) { saddr_.sin_p = htons(port); }

    private:
        static bool resolveSlow(const char *hostname, InetAddress*);
        struct sockaddr_in addr_;
}
