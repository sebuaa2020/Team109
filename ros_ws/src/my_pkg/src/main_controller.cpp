#include <ros/ros.h>
#include <iostream>


std::string INSTRUCTION = "1 手动模式" \
                          "2 语音模式" \
                          "3 结束";

std::string INSTRUCTION_MANUAL = "可选择的命令:"
                                 "1 "
                                 "";

// TODO: support complex voice service
// voice now support move only
std::string INSTRUCTION_VOICE = "支持语音为:"
                                "1 到达目标坐标x"
                                "2 识别附近物体"
                                "3 ";

std::string INSTRUCTION_UNKNOWN = "unknown instruction";


void voice_service() {

}


void manual_service() {

}


int main(int argc, char **argv) {
    ros::init(argc, argv, "main_controller");

    while (ros::ok()) {
        std::cout << INSTRUCTION << std::endl;
        int instruction;
        std::cin >> instruction;

        switch (instruction) {
            case 1:
                manual_service();
                break;
            case 2:
                voice_service();
                break;
            case 3:
                return 0;
            default:
                std::cout << INSTRUCTION_UNKNOWN << std::endl;
                break;
        }
    }

    return 0;
}
