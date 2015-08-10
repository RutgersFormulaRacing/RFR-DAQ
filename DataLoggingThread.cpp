#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <string>

#include "DataLoggingThread.h"

DataLoggingThread::DataLoggingThread(int sampleRate)
{
    this->sampleRate = sampleRate;
    this->sampleTime = (int)((1.0/sampleRate)*1000);

    this->isRunning = false;
}

DataLoggingThread::~DataLoggingThread()
{}

void DataLoggingThread::start()
{
    this->isRunning = true;

    boost::thread t(boost::bind(&DataLoggingThread::run, this));
}

void DataLoggingThread::stop()
{
    this->isRunning = false;
}

void DataLoggingThread::newLogFile()
{
    mutex.lock();
    if(isRunning)
        logFile.close();

    char outputPath[1024];
    memset(outputPath, 0, 1024);

    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    sprintf(outputPath, "/Logs/%d-%d-%d_%d:%d.txt", now.date().month(), now.date().day(), now.date().year(), now.time_of_day().hours(), now.time_of_day().minutes());

    logFile.open(outputPath);
    mutex.unlock();
}

void DataLoggingThread::run()
{
    while(isRunning)
    {
        mutex.lock();
        mutex.unlock();

        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}
