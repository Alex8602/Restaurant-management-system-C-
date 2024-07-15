#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Serializable {
public:
    virtual void read(ifstream& ifs) = 0;
    virtual void write(ofstream& ofs) const = 0;
    virtual ~Serializable() {}
};