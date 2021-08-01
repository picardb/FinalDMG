#include "BootstrapRom.h"

using namespace std;

namespace FinalDMG
{
    void BootstrapRom::loadFomFile(const std::string& fileName) {
        FileHelper::loadFromFile(m_rom.data(), fileName, 256);
    }
}