#ifndef _DATA_HUB_THREAD_
#define _DATA_HUB_THREAD_

#include "utils.h"

class DataHubThread
{

    public:
    DataHubThread();
    ~DataHubThread();

    void setFD(int fd);

    int getFD();

    void start();
    void stop();

    private:
    int serialFD;
    bool isRunning;

    void run();
};

#endif
