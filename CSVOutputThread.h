#include "DataPushThread.h"

class CSVOutputThread : public dataPushThread
{
    public:
        CSVOutputThread() : dataPushThread() {}

    protected:
        void run();

    private:

};
