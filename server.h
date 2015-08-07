#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

class Server
{
    public:
        Server();
        ~Server();

    private:
        boost::asio::io_service m_ioService;

};

#endif
