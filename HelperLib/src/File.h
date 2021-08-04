#ifndef HELPER_LIB_FILE_H_
#define HELPER_LIB_FILE_H_

#include <string>

namespace HelperLib 
{
    namespace File 
    {
        void loadFromFile(uint8_t dest[], const std::string& fileName, int size);
    }
}


#endif /* HELPER_LIB_FILE_H_ */
