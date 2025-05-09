#include <iostream>
#include <fstream>
#include <csignal>
#include <unistd.h>
#include <unitree/robot/channel/channel_subscriber.hpp>
#include "msg/PubServoInfo_.hpp"

using namespace unitree::robot;

std::ofstream outfile;

// Gracefully close the file on Ctrl+C
void SignalHandler(int signum)
{
    std::cout << "\n[INFO] Interrupt received (Ctrl+C), closing file..." << std::endl;
    if (outfile.is_open())
    {
        outfile.close();
        std::cout << "[INFO] File closed successfully." << std::endl;
    }
    exit(signum);
}

void Handler(const void *msg)
{
    const unitree_arm::msg::dds_::PubServoInfo_ *pm = (const unitree_arm::msg::dds_::PubServoInfo_ *)msg;

    if (!outfile.is_open())
        return;

    outfile << pm->servo0_data_() << ","
            << pm->servo1_data_() << ","
            << pm->servo2_data_() << ","
            << pm->servo3_data_() << ","
            << pm->servo4_data_() << ","
            << pm->servo5_data_() << ","
            << pm->servo6_data_() << std::endl;

    outfile.flush(); // 👈 ensure it's written immediately
    std::cout << "Saved a frame!" << std::endl;
}

int main()
{
    // Setup signal handler to close file on Ctrl+C
    signal(SIGINT, SignalHandler);

    outfile.open("recorded_angles.csv");
    if (!outfile.is_open())
    {
        std::cerr << "❌ Error: Could not open recorded_angles.csv for writing!" << std::endl;
        return -1;
    }

    ChannelFactory::Instance()->Init(0);
    ChannelSubscriber<unitree_arm::msg::dds_::PubServoInfo_> subscriber("current_servo_angle");
    subscriber.InitChannel(Handler);

    std::cout << "Recording started. Move the D1 arm. Press Ctrl+C to stop..." << std::endl;

    // Keep alive until interrupted
    while (true)
    {
        sleep(1);
    }

    return 0;
}
