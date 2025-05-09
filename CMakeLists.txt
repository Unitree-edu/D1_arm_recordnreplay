cmake_minimum_required(VERSION 3.5)
project(marm_code)

set(CMAKE_CXX_STANDARD 17)

# Include headers for DDS + Iceoryx + Unitree SDK
include_directories(
    /usr/local/include/ddscxx
    /usr/local/include/iceoryx/v2.0.2
    /usr/local/include/unitree
    src
    src/msg
)

# Link necessary libraries
link_libraries(
    unitree_sdk2
    ddsc
    ddscxx
    pthread
    rt
)

# Sample SDK demos
add_executable(joint_angle_control
    src/joint_angle_control.cpp
    src/msg/ArmString_.cpp
)

add_executable(multiple_joint_angle_control
    src/multiple_joint_angle_control.cpp
    src/msg/ArmString_.cpp
)

add_executable(joint_enable_control
    src/joint_enable_control.cpp
    src/msg/ArmString_.cpp
)

add_executable(joint_disable_control
    src/joint_disable_control.cpp
    src/msg/ArmString_.cpp
)
target_link_libraries(joint_disable_control unitree_sdk2)


add_executable(arm_zero_control
    src/arm_zero_control.cpp
    src/msg/ArmString_.cpp
)

add_executable(get_arm_joint_angle
    src/get_arm_joint_angle.cpp
    src/msg/ArmString_.cpp
    src/msg/PubServoInfo_.cpp
)

# 🔴 NEW: record & replay tools
add_executable(record_joint_angles
    src/record_joint_angles.cpp
    src/msg/PubServoInfo_.cpp
)

add_executable(replay_joint_angles
    src/replay_joint_angles.cpp
    src/msg/ArmString_.cpp
)

