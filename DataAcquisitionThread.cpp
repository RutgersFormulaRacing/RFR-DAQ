#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <iostream>
#include <fstream>

#include "DataAcquisitionThread.h"

DataAcquisitionThread::DataAcquisitionThread(int sampleRate)
{
    this->sampleRate = sampleRate;
    this->sampleTime = (int)((1.0/sampleRate)*1000);

    this->isRunning = false;
}

DataAcquisitionThread::~DataAcquisitionThread()
{
    isRunning = false;
}

void DataAcquisitionThread::start()
{
    this->isRunning = true;

    run();
}

void DataAcquisitionThread::stop()
{
    this->isRunning = false;
}

void DataAcquisitionThread::passDataFrameEntries(std::vector<dataFrameEntry*>* dataFrameEntries)
{
    this->dataFrameEntries = dataFrameEntries;
}

void DataAcquisitionThread::passAnalogInputsMap(std::map<std::string, AnalogInput*>* analogInputsMap)
{
    this->analogInputsMap = analogInputsMap;
}

void DataAcquisitionThread::passDigitalInputsMap(std::map<std::string, DigitalInput*>* digitalInputsMap)
{
    this->digitalInputsMap = digitalInputsMap;
}

std::vector<std::pair<std::string, float> > DataAcquisitionThread::getRecentDataFrame()
{
    mtx.lock();

    std::vector<std::pair<std::string, float> > ret = recentDataFrame;

    mtx.unlock();

    return ret;
}

void DataAcquisitionThread::run()
{
    while(isRunning)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(sampleRate));
    }
}
