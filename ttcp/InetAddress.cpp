#include "InetAddress.h"
#include <stdio.h>
#include <assert.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

InetAddress::InetAddress(uint16_t port, bool loopbackOnly)
{
    ::bzero(&saddr_, sizeof(saddr_));
    saddr_.sin_family = AF_INET;
    saddr_.sin_addr.s_addr = htonl(loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY);
    saddr_.sin_port = htons(port);
}

std::string InetAddress::toIp() const
{
    char buf[32] = "";
    ::inet_ntop(AF_INET, &saddr_.sin_addr, buf, sizeof buf);
    return buf;
}

std::string InetAddress::toIpPort() const
{
    char buf[32] = "";
    ::inet_ntop(AF_INET, &saddr_.sin_addr, buf, sizeof buf);
    int end = ::strlen(buf);
    uint16_t port = portHostEndian();
    snprintf(buf + end, sizeof buf - end, ":%u", port);
    return buf;
}
