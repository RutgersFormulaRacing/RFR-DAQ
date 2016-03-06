#ifndef _DATA_ACQUISITION_THREAD_H_
#define _DATA_ACQUISITION_THREAD_H_

#include <map>
#include <vector>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <utility>
#include <string>

#include "DigitalInput.h"
#include "AnalogInput.h"

#include "utils.h"

class DataAcquisitionThread
{
    public:
        DataAcquisitionThread(int sampleRate);
        ~DataAcquisitionThread();

        void start();
        void stop();

        void pause();
        void play();

        void passDataFrameEntries(std::vector<dataFrameEntry*>* dataFrameEntries);
        void passDigitalInputs(std::vector<DigitalInput*>* digitalInputs);
        void passAnalogInputs(std::vector<AnalogInput*>* analogInputs);

        std::vector<std::pair<std::string, float> > getRecentDataFrame();
        std::vector<std::pair<std::string, float> >* getRecentSerialDataFrame();
        std::vector<std::pair<std::string, float> >** getRecentWirelessDataFrame();
        std::vector<std::pair<std::string, float> >* getRecentCSVDataFrame();

    private:
        int sampleRate;
        int sampleTime;

        bool isRunning, isPaused;

        std::vector<std::pair<std::string, float> > recentDataFrame;

        std::vector<std::pair<std::string, float> > serialDataFrameSwap1;
        std::vector<std::pair<std::string, float> > wirelessDataFrameSwap1;
        std::vector<std::pair<std::string, float> > csvDataFrameSwap1;

        std::vector<std::pair<std::string, float> > serialDataFrameSwap2;
        std::vector<std::pair<std::string, float> > wirelessDataFrameSwap2;
        std::vector<std::pair<std::string, float> > csvDataFrameSwap2;

        std::vector<std::pair<std::string, float> >* serialDataFrameWritePtr;
        std::vector<std::pair<std::string, float> >* wirelessDataFrameWritePtr;
        std::vector<std::pair<std::string, float> >* csvDataFrameWritePtr;

        std::vector<std::pair<std::string, float> >* serialDataFrameReadPtr;
        std::vector<std::pair<std::string, float> >* wirelessDataFrameReadPtr;
        std::vector<std::pair<std::string, float> >* csvDataFrameReadPtr;

        std::vector<AnalogInput*>* analogInputs;
        std::vector<DigitalInput*>* digitalInputs;

        boost::mutex mtx;

        void run();
};

#endif
