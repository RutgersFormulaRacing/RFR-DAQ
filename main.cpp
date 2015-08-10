#define HARDWARE_VER    0
#define SOFTWARE_VER    0.1

#define BOOST_SYSTEM_NO_DEPRECATED

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <exception>

#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <boost/thread/thread.hpp>

#include <boost/bind.hpp>

#include "utils.h"
#include "AnalogInput.h"
#include "ADC.h"

#include "DataLoggingThread.h"
#include "server.hpp"

int main()
{
    std::map<std::string, AnalogInput*> analogInputsMap;

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
    }
    catch(std::exception& e)
    {
        std::cout << "Error" << std::endl;
        std::cout << e.what() << std::endl;

        return -1;
    }
    std::cout << "Success" << std::endl;
    std::cout << std::endl;

    /*std::cout << "Loading SPI Kernel: 1KB Buffer" << std::endl;
    system("gpio load spi 1");

    std::cout << "Loading I2C Kernel: 100 Kbps" << std::endl;
    system("gpio load i2c 100");

    std::cout << "Searching for I2C devices..." << std::endl;
    system("gpio i2cdetect");

    DataLoggingThread dataLogger(10);
    boost::thread dataLoggingThread(boost::bind(&DataLoggingThread::start, &dataLogger));*/

    http::server3::server Server(4660, 5);
    Server.run();

    while(1)
    {

    }

    return 0;
}
