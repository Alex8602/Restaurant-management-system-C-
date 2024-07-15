#pragma once
#include <string>

using namespace std;

class Exceptie : exception {
private: string msg;
public:
    Exceptie(string msg) : msg(msg) {}

    string what() {
        return msg;
    }
};
