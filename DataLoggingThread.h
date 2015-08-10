#ifndef _DATA_LOGGING_THREAD_H_
#define _DATA_LOGGING_THREAD_H_

#include <fstream>
#include <vector>

#include <boost/thread/mutex.hpp>

#include "utils.h"

class DataLoggingThread
{
    public:
        DataLoggingThread(int sampleRate);
        ~DataLoggingThread();

        void start();
        void stop();

        void newLogFile();


    private:
        int sampleRate;
        int sampleTime;

        bool isRunning;

        boost::mutex mutex;

        std::ofstream logFile;

        void run();
};

#endif
