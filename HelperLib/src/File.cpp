#include "File.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace HelperLib {
    namespace File
    {
        void loadFromFile(uint8_t dest[], const string& fileName, int size)
        {
            ifstream file(fileName, ios::in|ios::binary);
            char byte;
            int count = 0;
            if (file.is_open()) {
                while (file.get(byte) && (count < size)) {
                    dest[count] = (uint8_t)byte;
                    count++;
                }
                file.close();
            }
            else {
                // TODO error
            }
        }
    }    
}