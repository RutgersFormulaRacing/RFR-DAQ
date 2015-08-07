#include <boost/thread/xtime.hpp>

#include "DataLoggingThread.h"

DataLoggingThread::DataLoggingThread(int sampleRate)
{
    this->sampleRate = sampleRate;
    this->sampleTime = (int)((1.0/sampleRate)*1000);

    this->isRunning = false;
}

void DataLoggingThread::start()
{
    this->isRunning = true;
}

void DataLoggingThread::stop()
{
    this->isRunning = false;
}

void DataLoggingThread::run()
{
    while(isRunning)
    {
    }

}
