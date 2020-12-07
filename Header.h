#ifndef TAR_SIMU_HEADER_H
#define TAR_SIMU_HEADER_H
#include "Block.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
class Header: public Block{
    public:
        Header() : Block(){};
        void getFileInfo(std::string fileName);
};

#endif //TAR_SIMU_HEADER_H
