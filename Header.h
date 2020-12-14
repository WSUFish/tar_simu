#ifndef TAR_SIMU_HEADER_H
#define TAR_SIMU_HEADER_H
#include "Block.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <exception>
#include <cstdlib>
#include <vector>
#include <map>
#include <iostream>
#define MODE_DIR 1
#define MODE_REG 4
class Header: public Block{
    public:
    char *name; //文件名（包括相对路径）   长度100
    char *name_extra;//文件名是否拓展？    长度1
    char *mode; //文件类型                 长度2 (unsigned short)
    char *uid;//                            2
    char *gid;//                            2
    char *size;//                           8 off64_t
    char *check;
    std::map<std::string, std::vector<Block>> extraField;
    Header() : Block(){
        name = block;
        name_extra = name + 100;
        mode = name_extra + 1;
        uid = mode + 2;
        gid = uid + 2;
        size = gid + 2;
        check = size + 8;
    };
    void setFileInfo(std::string archivePath, std::string fileName);
    void setName(std::string fileName);
    void setMode(unsigned short mode);
    void setSize(off64_t file_size);
    int getSize();
    std::string getName();
    int getMode(); //判断文件类型
    void writeExtraField(const std::string &key, const std::string &field);
    std::string getExtraField(const std::string &key);
};

#endif //TAR_SIMU_HEADER_H
