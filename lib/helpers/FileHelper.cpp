#include "FileHelper.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace FinalDMG {
    void FileHelper::readBios(uint8_t* pBios) {
        ifstream biosFile("bootstrap.bin", ios::in|ios::binary);
        if (biosFile.is_open()) {
            biosFile.read(reinterpret_cast<char*>(pBios), 256);
        }   
    }
}