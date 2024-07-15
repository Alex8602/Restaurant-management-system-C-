#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Serializable.h"

using namespace std;

class BinaryFileManager {
public:
    static void writeToFile(const string& filename, const Serializable& obj) {
        ofstream ofs(filename, ios::binary);
        obj.write(ofs);
        ofs.close();
    }

    static void readFromFile(const string& filename, Serializable& obj) {
        ifstream ifs(filename, ios::binary);
        obj.read(ifs);
        ifs.close();
    }
};