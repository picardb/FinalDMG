#include "emulator/Emulator.h"

#include "ConsoleHelper.h"

#include <iostream>

using namespace std;
using namespace FinalDMG;

int main(void) {
    Emulator emul;

    cout << "* FinalDMG playground v1*" << endl << endl;

     uint8_t block[256];
     emul.readMemBlock(0, 256, block);
     cout << "Bootstrap ROM" << endl;
     cout << "-------------" << endl;
     cout << ConsoleHelper::BlockToHexStr(block, 256) << endl;

     system("pause");
}