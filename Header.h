#ifndef TAR_SIMU_HEADER_H
#define TAR_SIMU_HEADER_H
#include "Block.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <exception>
#include <cstdlib>
class Header: public Block{
    public:
    char *name; //文件名（包括相对路径）   长度100
    char *name_extra;//文件名是否拓展？    长度1
    Header() : Block(){
        name = block;
        name_extra = name + 100;
    };
    void setFileInfo(std::string archivePath, std::string fileName);
    void setName(std::string fileName);
    std::string getName();
};

#endif //TAR_SIMU_HEADER_H
