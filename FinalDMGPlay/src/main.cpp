#include "emulator/Emulator.h"

#include "ConsoleHelper.h"

#include <iostream>

using namespace std;
using namespace FinalDMG;

static void printHelloMessage(void);
static void printCpuInfo(const Emulator& emul);
static void printMemInfo(const Emulator& emul);

int main(void) {
    printHelloMessage();

    Emulator emul;

    int cycleCount = 0;
    while (emul.cpu()->getReg16(Cpu::REG16_PC) != 0x28) {
        emul.runForCycles(1);
        cycleCount++;
    }

    printCpuInfo(emul);
    printMemInfo(emul);
    cout << "Cycle count: " << cycleCount << endl;

    system("pause");
}

static void printHelloMessage(void)
{
    cout << "**************************" << endl;
    cout << "* FinalDMG playground v1 *" << endl;
    cout << "**************************" << endl;
    cout << endl;
}

static void printCpuInfo(const Emulator& emul)
{
    cout << "CPU" << endl;
    cout << "---" << endl;
    cout << "A: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_A)) << " F: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_F)) << endl;
    cout << "B: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_B)) << " C: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_C)) << endl;
    cout << "D: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_D)) << " E: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_E)) << endl;
    cout << "H: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_H)) << " L: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getReg8(Cpu::REG8_L)) << endl;
    cout << "PC: " << ConsoleHelper::UInt16ToHexStr(emul.cpu()->getReg16(Cpu::REG16_PC)) << endl;
    cout << "SP: " << ConsoleHelper::UInt16ToHexStr(emul.cpu()->getReg16(Cpu::REG16_SP)) << endl;
    cout << "Current opcode: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getOpcode()) << endl;
    cout << "Remaining cycles on current opcode: " << ConsoleHelper::UInt8ToHexStr(emul.cpu()->getRemainingCycles()) << endl;
    cout << endl;
}

static void printMemInfo(const Emulator& emul)
{
    uint8_t block[256];
    for (int i = 0; i < 256; i++) {
        block[i] = emul.bus()->read(i);
    }
    cout << "Bootstrap ROM" << endl;
    cout << "-------------" << endl;
    cout << ConsoleHelper::BlockToHexStr(block, 256) << endl;
    cout << endl;
}