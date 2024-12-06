#pragma once

#include <sstream>
#include <string>
struct Position {
    int x;
    int y;
    std::string str() {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }
};
