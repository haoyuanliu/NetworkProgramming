#include <iostream>
#include <boost/program_options.hpp>
#include <sys/time.h>

struct Options
{
    uint16_t port;
    int length;
    int number;
    bool transmit, receive, nodelay;
    std::string host;
    Options() : port(0), length(0), number(0),
        transmit(false), receive(false), nodelay(false) {}
};

struct SessionMessage
{
    int32_t number;
    int32_t length;
} __attribute__((__packed__));

struct PayloadMessage
{
    int32_t length;
    char data[0];
};

double now()
{
    struct timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

bool parseCommandLine(int argc, char *argv[], Options *opt)
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help, h", "Help")
        ("port, p", po::value<uint16_t>(&opt->port)->default_value(5001), "TCP port")
        ("length, l", po::value<int>(&opt->length)->default_value(65536), "Buffer Length")
        ("number, n", po::value<int>(&opt->number)->default_value(8192), "Number of buffers")
        ("trans, t", po::value<std::string>(&opt->host), "Transmit")
        ("recv, r", "Receive")
        ("nodelay, D", "set TCP_NODELAY")
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    opt->transmit = vm.count("trans");
    opt->receive = vm.count("recv");
    opt->nodelay = vm.count("nodelay");
    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        return false;
    }
    if(opt->transmit == opt->receive)
    {
        printf("either -t or -r must be specifies.\n");
        return false;
    }

    printf("port = %d\n", opt->port);
    if(opt->transmit)
    {
        printf("buffer length = %d\n", opt->length);
        printf("number of buffers = %d\n", opt->number);
    }
    else
    {
        printf("accepting..\n");
    }
    return true;
}

void transmit(const Options &opt)
{
    InetAddress addr(opt.port);
    if(!InetAddress::resolve(opt.host.c_str(), &addr))
    {
        printf("Unable to resolve %s\n", opt.host.c_str());
        return;
    }
    printf("Connecting to %s\n", addr.toIPPort().c_str());
}
