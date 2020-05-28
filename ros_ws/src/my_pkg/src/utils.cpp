#include "utils.h"


std::string path_join(std::string src_path, std::string add_path) {
    if (src_path.at(src_path.length() - 1) == '/') {
        return src_path + add_path;
    } else {
        // std::cout << "[INFO] src_path: " << src_path << std::endl;
        return src_path.append("/") + add_path;
    }
}