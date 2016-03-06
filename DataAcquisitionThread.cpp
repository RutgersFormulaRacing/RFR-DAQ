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
    this->isPaused = true;
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

void DataAcquisitionThread::pause()
{
    mtx.lock();

    this->isPaused = true;

    mtx.unlock();
}

void DataAcquisitionThread::play()
{
    mtx.lock();

    this->isPaused = false;

    mtx.unlock();
}

void DataAcquisitionThread::passAnalogInputs(std::vector<AnalogInput*>* analogInputs)
{
    this->analogInputs = analogInputs;
}

void DataAcquisitionThread::passDigitalInputs(std::vector<DigitalInput*>* digitalInputs)
{
    this->digitalInputs = digitalInputs;
}

std::vector<std::pair<std::string, float> >** DataAcquisitionThread::getRecentWirelessDataFrame()
{
    mtx.lock();

    std::vector<std::pair<std::string, float> >** ret = &wirelessDataFrameReadPtr;

    mtx.unlock();

    return ret;
}

void DataAcquisitionThread::run()
{
    while(isRunning)
    {
        if(!isPaused)
        {
            serialDataFrameWritePtr->clear();
            wirelessDataFrameWritePtr->clear();
            csvDataFrameWritePtr->clear();

            for(int i = 0; i < analogInputs->size(); i++)
            {
                float val = analogInputs->at(i)->read();
            }

            for(int i = 0; i < digitalInputs->size(); i++)
            {
                bool val = digitalInputs->at(i)->read();
            }

            mtx.lock();

            std::swap(serialDataFrameWritePtr, serialDataFrameReadPtr);
            std::swap(wirelessDataFrameWritePtr, wirelessDataFrameReadPtr);
            std::swap(csvDataFrameWritePtr, csvDataFrameReadPtr);

            mtx.unlock();

            boost::this_thread::sleep(boost::posix_time::milliseconds(sampleRate));
        }
    }
}
