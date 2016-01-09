#include "DataPushThread.h"

dataPushThread::dataPushThread()
{
    this->isRunning = false;
    this->isDataReady = false;
}

void dataPushThread::start()
{
    this->isRunning = true;

    run();
}

void dataPushThread::stop()
{
    this->isRunning = false;
}

void dataPushThread::push(std::pair<std::string, float> readyData)
{
    this->mtx.lock();

    this->readyData = readyData;
    this->isDataReady = true;

    this->mtx.unlock();
}
