#include "CSVOutputThread.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <iostream>
#include <fstream>

void CSVOutputThread::run()
{
    std::ofstream file;
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

    std::string path = "Log " + boost::posix_time::to_simple_string(now) + ".csv";

    file.open(path.c_str());

    while(isRunning)
    {
        if(isDataReady)
        {
            mtx.lock();

            std::pair<std::string, float> data = readyData;
            isDataReady = false;

            mtx.unlock();
        }
        file << '\n';
    }
    file.close();
}
