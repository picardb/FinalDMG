#include "ConsoleHelper.h"

#include <sstream>
#include <iomanip>

using namespace std;

namespace FinalDMG
{
    namespace ConsoleHelper
    {
        std::string ByteToHexStr(uint8_t byte)
        {
            std::stringstream ss;
            ss << std::hex;
            ss << setw(2) << setfill('0') << (int)byte;

            return ss.str();
        }

        std::string BlockToHexStr(uint8_t block[], int blockLength, int columnSize)
        {
            std::stringstream ss;
            ss << std::hex;

            int nextColumn = 0;
            for (int i = 0; i < blockLength; i++) {
                ss << setw(2) << setfill('0') << (int)block[i];
                nextColumn++;

                // New line after last column
                if (nextColumn == columnSize) {
                    nextColumn = 0;
                    ss << endl;
                }
                else {
                    ss << ' ';
                }
            }

            return ss.str();
        }
    }
}