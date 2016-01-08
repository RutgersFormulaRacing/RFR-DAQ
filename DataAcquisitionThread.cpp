#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <iostream>
#include <fstream>

#include "DataAcquisitionThread.h"

DataAcquisitionThread::DataLoggingThread(int sampleRate)
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
    std::ofstream file;
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

    std::string path = "Log " + boost::posix_time::to_simple_string(now) + ".csv";

    file.open(path.c_str());

    for(unsigned int i = 0; i < dataFrameEntries->size(); i++)
    {
        file << dataFrameEntries->at(i)->name << ',';
    }

    while(isRunning)
    {
        mtx.lock();
        recentDataFrame.clear();
        //std::cout << "UPDATE" << std::endl;

        for(unsigned int i = 0; i < dataFrameEntries->size(); i++)
        {
            std::map<std::string, AnalogInput*>::iterator AnalogInputIt = analogInputsMap->find(dataFrameEntries->at(i)->name);
            if(AnalogInputIt != analogInputsMap->end())
            {
                float reading = AnalogInputIt->second->read();
                file << reading << ",";
                recentDataFrame.push_back(std::pair<std::string, float>(dataFrameEntries->at(i)->name, reading));

                continue;
            }

            std::map<std::string, DigitalInput*>::iterator DigitalInputIt = digitalInputsMap->find(dataFrameEntries->at(i)->name);
            if(DigitalInputIt != digitalInputsMap->end())
            {
                int reading = (int)DigitalInputIt->second->read();
                file << reading << ",";
                recentDataFrame.push_back(std::pair<std::string, float>(dataFrameEntries->at(i)->name, reading));

                continue;
            }
        }
        file << '\n';

        mtx.unlock();

        boost::this_thread::sleep(boost::posix_time::milliseconds(sampleRate));
    }
    file.close();
}
