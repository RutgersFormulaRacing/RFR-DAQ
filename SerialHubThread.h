#ifndef _DATA_HUB_THREAD_
#define _DATA_HUB_THREAD_

#include "utils.h"

#include <vector>

class SerialHubThread
{

    public:
        SerialHubThread();
        ~SerialHubThread();

        void setFD(int fd);

        int getFD();

        void start();
        void stop();

        std::vector<float>* getDataFrame();

    private:
        int serialFD;
        bool isRunning;

        std::vector<float> dataFrame;
        int fullSize;

        void run();
};

#endif
