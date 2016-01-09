#include <map>
#include <vector>

#include <boost/thread/mutex.hpp>

#include <utility>
#include <string>

#include "utils.h"

class dataPushThread
{
    public:
        dataPushThread();

        void push(std::pair<std::string, float> readyData);

        void start();
        void stop();

    protected:
        bool isRunning;
        boost::mutex mtx;

        bool isDataReady;
        std::pair<std::string, float> readyData;

        virtual void run() = 0;
};
