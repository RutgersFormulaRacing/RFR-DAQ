#include "DataHubThread.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <iostream>
#include <fstream>

#include <wiringPi.h>
#include <wiringSerial.h>

DataHubThread::DataHubThread()
{
    pinMode(SERIAL_SYNC_PIN, OUTPUT);
}

DataHubThread::~DataHubThread()
{}

void DataHubThread::setFD(int fd)
{
    this->serialFD = fd;
}

int DataHubThread::getFD()
{
    return serialFD;
}

void DataHubThread::start()
{
    isRunning = true;
    run();
}

void DataHubThread::stop()
{
    isRunning = false;
}

void DataHubThread::run()
{
    int count = 0;

    while(isRunning)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));

        digitalWrite(SERIAL_SYNC_PIN, HIGH);

        digitalWrite(SERIAL_SYNC_PIN, LOW);
    }
}
