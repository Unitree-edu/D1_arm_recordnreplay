#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <unitree/robot/channel/channel_publisher.hpp>
#include "msg/ArmString_.hpp"

using namespace unitree::robot;

std::vector<std::vector<float>> load_csv(const std::string& path)
{
    std::ifstream file(path);
    std::vector<std::vector<float>> data;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::vector<float> row;
        std::string value;
        while (std::getline(ss, value, ','))
        {
            row.push_back(std::stof(value));
        }
        data.push_back(row);
    }

    return data;
}

int main()
{
    ChannelFactory::Instance()->Init(0);
    ChannelPublisher<unitree_arm::msg::dds_::ArmString_> publisher("rt/arm_Command");
    publisher.InitChannel();

    auto angles = load_csv("recorded_angles.csv");
    std::cout << "Loaded " << angles.size() << " frames" << std::endl;

    for (const auto& frame : angles)
    {
        if (frame.size() != 7)
        {
            continue;
        }

        std::string json_msg = "{\"seq\":4,\"address\":1,\"funcode\":2,\"data\":{";
        json_msg += "\"mode\":1";
        for (int i = 0; i < 7; i++)
        {
            json_msg += ",\"angle" + std::to_string(i) + "\":" + std::to_string(frame[i]);
        }
        json_msg += "}}";

        unitree_arm::msg::dds_::ArmString_ msg;
        msg.data_() = json_msg;
        publisher.Write(msg);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
