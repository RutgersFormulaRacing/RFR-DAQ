//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <sstream>

namespace http {
namespace server3 {

connection::connection(boost::asio::io_service& io_service, DataLoggingThread *dataLoggingThread)
  : strand_(io_service),
    socket_(io_service)
{
    this->dataLoggingThread = dataLoggingThread;
}

boost::asio::ip::tcp::socket& connection::socket()
{
  return socket_;
}

void connection::start()
{
    std::vector<std::pair<std::string, float> > dataFrame = dataLoggingThread->getRecentDataFrame();

    if(dataFrame.size() > 0)
    {
        std::string s;
        s += "{";

        for(unsigned int i = 0; i < dataFrame.size(); i++)
        {
            s += "\"" + std::string(dataFrame.at(i).first) + "\":" + boost::lexical_cast<std::string>(dataFrame.at(i).second);

            if(i < dataFrame.size() - 1)
                s += ",";
        }
        s += "}";

        socket_.send(boost::asio::buffer(s, s.length()));
    }
    boost::system::error_code ignored_ec;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
}


} // namespace server3
} // namespace http
