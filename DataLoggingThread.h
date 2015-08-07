#ifndef _DATA_LOGGING_THREAD_H_
#define _DATA_LOGGING_THREAD_H_

#include "utils.h"

class DataLoggingThread
{
    public:
        DataLoggingThread(int sampleRate);
        ~DataLoggingThread();

        void start();
        void stop();



    private:
        int sampleRate;
        int sampleTime;

        bool isRunning;

        logDataFrame recentDataFrame;

        void run();
};

#endif
