#ifndef TAR_SIMU_HEADER_H
#define TAR_SIMU_HEADER_H
#include "Block.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <exception>
#include <cstdlib>
#define MODE_DIR 1
#define MODE_REG 4
class Header: public Block{
    public:
    char *name; //文件名（包括相对路径）   长度100
    char *name_extra;//文件名是否拓展？    长度1
    char *mode; //文件类型                 长度2 (unsigned short)
    char *uid;
    char *gid;
    char *size;
    char *check;

    Header() : Block(){
        name = block;
        name_extra = name + 100;
        mode = name_extra + 1;
    };
    void setFileInfo(std::string archivePath, std::string fileName);
    void setName(std::string fileName);
    void setMode(unsigned short mode);
    void setSize(off_t file_size);
    std::string getName();
    int getMode();
};

#endif //TAR_SIMU_HEADER_H
