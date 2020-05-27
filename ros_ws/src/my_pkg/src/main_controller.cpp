#include <ros/ros.h>
#include <iostream>
#include <cstdlib>


std::string INSTRUCTION = "1 手动模式\n" \
                          "2 语音模式\n" \
                          "3 结束";

std::string INSTRUCTION_MANUAL = "可选择的命令:\n" \
                                 "1 到达目标坐标\n" \
                                 "2 识别物体\n" \
                                 "3 键盘控制移动\n" \
                                 "4 巡航\n" \
                                 "5 巡逻拍照\n" \
                                 "6 退出";

// TODO: support complex voice service
// voice now support move only
std::string INSTRUCTION_VOICE = "支持语音为:\n" \
                                "1 到达目标坐标\n" \
                                "2 识别附近物体\n" \
                                "3 键盘控制移动\n" \
                                "4 巡航\n" \
                                "5 巡逻拍照\n" \
                                "6 退出";

std::string INSTRUCTION_UNKNOWN = "unknown instruction";


void move_to_target_service() {
    system("");
}


void detect_object_service() {

}


void move_by_keyboard_service() {

}


void cruise_service() {

}


void run_around_picture_service() {

}


void voice_service() {

}


void manual_service() {
    while (ros::ok()) {
        std::cout << INSTRUCTION_MANUAL << std::endl;
        int instruction_manual;
        std::cin >> instruction_manual;

        switch (instruction_manual) {
            case 1:
                move_to_target_service();
                break;
            case 2:
                detect_object_service();
                break;
            case 3:
                move_by_keyboard_service();
                break;
            case 4:
                cruise_service();
                break;
            case 5:
                run_around_picture_service();
                break;
            case 6:
                return;
            default:
                std::cout << INSTRUCTION_UNKNOWN << std::endl;
        }
    }
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
