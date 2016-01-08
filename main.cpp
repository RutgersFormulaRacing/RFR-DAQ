#define HARDWARE_VER    0
#define SOFTWARE_VER    0.1

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <exception>
#include <signal.h>
#include <unistd.h>

#include <map>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>

#include "DataAcquisitionThread.h"
#include "SerialHubThread.h"
#include "server.hpp"

#include "mpu6050.h"
#include "mlx90616.h"

int main()
{
    std::map<std::string, AnalogInput*> analogInputsMap;
    std::map<std::string, DigitalInput*> digitalInputsMap;
    std::vector<dataFrameEntry*> dataFrameFields;

    std::vector<I2CDevice*> i2cDevices;
    i2cDevices.push_back(new mpu6050("AccelGyro", 0));

    int i2cFDTable[128];
    for(int i = 0; i < 128; i++)
        i2cFDTable[i] = -1;

    int serialFD = -1;

    std::cout << "RFR DAQ" << std::endl;
    std::cout << "Hardware Ver.\t" << HARDWARE_VER << std::endl;
    std::cout << "Software Ver.\t" << SOFTWARE_VER << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Designed and Coded by Sam Stratter" << std::endl;
    std::cout << "He's just that good" << std::endl;

    std::cout << "\n\n\n";

    std::cout << "Reading in pin configurations" << std::endl;
    //Todo: Read in the pin configurations

    boost::property_tree::ptree config; //Read in device connections
    try
    {
        boost::property_tree::read_xml("DAQConfig.xml", config);

        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, config.get_child("AnalogInputs"))
        {
            if(v.first.compare("AnalogInput") == 0)
            {
                AnalogInput *temp = new AnalogInput();

                temp->setName(v.second.get<std::string>("Name"));
                temp->setBank(v.second.get<unsigned char>("Bank"));
                temp->setChannel(v.second.get<unsigned char>("Channel"));
                temp->setMapFrom(std::pair<float, float>(v.second.get<float>("MapFromMin"), v.second.get<float>("MapFromMax")));
                temp->setMapTo(std::pair<float, float>(v.second.get<float>("MapToMin"), v.second.get<float>("MapToMax")));

                analogInputsMap.insert(std::pair<std::string, AnalogInput*>(temp->getName(), temp));
            }
        }

        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, config.get_child("DigitalInputs"))
        {
            if(v.first.compare("DigitalInput") == 0)
            {
                DigitalInput *temp = new DigitalInput();

                temp->setName(v.second.get<std::string>("Name"));
                temp->setBank(v.second.get<unsigned char>("Bank"));
                temp->setChannel(v.second.get<unsigned char>("Channel"));
                temp->setPolarity(v.second.get<int>("Polarity"));

                digitalInputsMap.insert(std::pair<std::string, DigitalInput*>(temp->getName(), temp));
            }
        }

        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, config.get_child("I2C"))
        {
        }
    }
    catch(std::exception& e)
    {
        std::cout << "Error" << std::endl;
        std::cout << e.what() << std::endl;

        return -1;
    }
    std::cout << "Success" << std::endl;
    std::cout << std::endl;

    std::cout << "Loading SPI Kernel: 1KB Buffer" << std::endl;
    system("gpio load spi 1");

    std::cout << "Loading I2C Kernel: 100 Kbps" << std::endl;
    system("gpio load i2c 100");

    std::cout << "Searching for I2C devices..." << std::endl;
    system("gpio i2cdetect");

    wiringPiSetup();
    wiringPiSPISetup(0, 1000000);
    wiringPiSPISetup(1, 1000000);

    serialFD = serialOpen("/dev/ttyAMA0", 115200);

    lastChipSelect = -1;

    setupChipSelect();
    setupDigitalInputs();

    //Starting logging thread
    DataAcquisitionThread dataLoggingThread(10);
    dataLoggingThread.passDataFrameEntries(&dataFrameFields);
    dataLoggingThread.passAnalogInputsMap(&analogInputsMap);
    dataLoggingThread.passDigitalInputsMap(&digitalInputsMap);

    boost::thread t(boost::bind(&DataAcquisitionThread::start, &dataLoggingThread));

    http::server3::server server(4660, 5, &dataLoggingThread); //5 for now
    boost::thread s(boost::bind(&http::server3::server::run, &server));

    bool exit = false;
    while(!exit)
    {
        char c;
        std::cin >> c;

        switch(c)
        {
            case 'x':

            case 'X':
            exit = true;
            break;
        }
    }

    dataLoggingThread.stop();
    t.join();

    return 0;
}
