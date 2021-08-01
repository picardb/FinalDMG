#ifndef FINAL_DMG_FILE_HELPER_H_
#define FINAL_DMG_FILE_HELPER_H_

#include <string>

namespace FinalDMG {

    class FileHelper {
    public:
        static void loadFromFile(uint8_t dest[], const std::string& fileName, int size);
    };

}


#endif /* FINAL_DMG_FILE_HELPER_H_ */
