#include "BootstrapRom.h"

using namespace std;
using namespace HelperLib;

namespace FinalDMG
{
    void BootstrapRom::loadFomFile(const std::string& fileName) {
        File::loadFromFile(m_rom.data(), fileName, 256);
    }
}