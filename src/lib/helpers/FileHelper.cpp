#include "FileHelper.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace FinalDMG {
    void FileHelper::loadBootstrap(uint8_t* pDest) {
        ifstream biosFile("bootstrap.bin", ios::in|ios::binary);
        if (biosFile.is_open()) {
            biosFile.read(reinterpret_cast<char*>(pDest), 256);
        }   
    }
}