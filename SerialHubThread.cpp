#include "SerialHubThread.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <iostream>
#include <fstream>

#include <wiringPi.h>
#include <wiringSerial.h>

SerialHubThread::SerialHubThread()
{
    pinMode(SERIAL_SYNC_PIN, OUTPUT);
}

SerialHubThread::~SerialHubThread()
{}

void SerialHubThread::setFD(int fd)
{
    this->serialFD = fd;
}

int SerialHubThread::getFD()
{
    return serialFD;
}

void SerialHubThread::start()
{
    isRunning = true;
    run();
}

void SerialHubThread::stop()
{
    isRunning = false;
}

void SerialHubThread::run()
{
    int count = 0;

    while(isRunning)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));

        digitalWrite(SERIAL_SYNC_PIN, HIGH);

        digitalWrite(SERIAL_SYNC_PIN, LOW);
    }
}
