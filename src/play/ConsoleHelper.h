#ifndef FINAL_DMG_CONSOLE_HELPER_H_
#define FINAL_DMG_CONSOLE_HELPER_H_

#include <string>

namespace FinalDMG
{
    namespace ConsoleHelper
    {
        std::string ByteToHexStr(uint8_t byte);
        std::string BlockToHexStr(uint8_t block[], int blockLength, int columnSize = 16);
    }
}

#endif /* FINAL_DMG_CONSOLE_HELPER_H_ */