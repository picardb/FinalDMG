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

    emul.runForCycles(1);

    printCpuInfo(emul);
    printMemInfo(emul);
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
    cout << "A: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_A)) << " F: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_F)) << endl;
    cout << "B: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_B)) << " C: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_C)) << endl;
    cout << "D: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_D)) << " E: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_E)) << endl;
    cout << "H: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_H)) << " L: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuReg8(Cpu::REG8_L)) << endl;
    cout << "PC: " << ConsoleHelper::UInt16ToHexStr(emul.getCpuRegPc()) << endl;
    cout << "SP: " << ConsoleHelper::UInt16ToHexStr(emul.getCpuRegSp()) << endl;
    cout << "Current opcode: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuOpcode()) << endl;
    cout << "Remaining cycles on current opcode: " << ConsoleHelper::UInt8ToHexStr(emul.getCpuRemainingCycles()) << endl;
    cout << endl;
}

static void printMemInfo(const Emulator& emul)
{
    uint8_t block[256];
    for (int i = 0; i < 256; i++) {
        block[i] = emul.busRead(i);
    }
    cout << "Bootstrap ROM" << endl;
    cout << "-------------" << endl;
    cout << ConsoleHelper::BlockToHexStr(block, 256) << endl;
    cout << endl;
}