#ifndef TAR_SIMU_HEADER_H
#define TAR_SIMU_HEADER_H
#include "ConvertGBK.h"
#include "Block.h"
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <sys/stat.h>
#include <io.h>
#include <process.h>
#include <time.h>
#include <string>

#include <cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include <QDebug>
#include <filesystem> //C++17


namespace fs = std::filesystem;

#define MODE_DIR '1'
#define MODE_REG '4'
#define MODE_SYM '7'
#define MODE_ZERO '8'
class Header: public Block{
    public:
    char *name; //文件名（包括相对路径）   长度100
    char *name_extra;//文件名是否拓展？    长度1
    char *mode; //文件类型                 长度2 (unsigned short)
    char *uid;//                            2
    char *gid;//                            2
    char *size;//                           8 uintmax_t
    char *check;//                          8
    char *encrypt;//是否加密                 1
    char *checkEncry;//检测密码是否正确        16
    std::map<std::string, std::vector<Block>> extraField;
    Header() : Block(){
        name = block;
        name_extra = name + 100;
        mode = name_extra + 1;
        uid = mode + 2;
        gid = uid + 2;
        size = gid + 2;
        check = size + 8;
        encrypt = check + 8;
        checkEncry = encrypt +1;
    };
    void setFileInfo(std::string archivePath, std::string fileName);
    void setFileInfoQt(const QString &archivePath, const QString &fileName);
    void setFileInfoQt(const QString &archivePath, const QString &fileName, const std::string &key);
    //void setFileInfoQt(const QString &archivePath, const QString &fileName);
    void setName(std::string fileName);
    void setMode(unsigned short mode);
    void setMode(const fs::file_status &fss);
    void setMode(const QFileInfo &fi);
//    int getPerm(); //获取权限信息
    void setEncry(const char* key);
    void setSize(uintmax_t file_size);
    int getSize();
    std::string getName();
    char getMode(); //判断文件类型
    std::string getExtraField(const std::string &key, int size);
    bool allZero();
    bool isEncrypt();
    bool checkPassword(const std::string &key);
    void setExtraField(const std::string &key, const std::string &field);
    static std::string connectBlock(const std::vector<Block> &bv, int size);
    int read(FILE *fileName);
    int write(FILE *fileName);
    void readExtraField(FILE *fileName, const std::string &key,char *field, char *field_extra);
    void writeExtraField(FILE *fileName, const std::string &key, char *field_extra);

    void read(std::istream &is);
    void write(std::ostream &os);

    void readExtraField(std::istream &is, const std::string &key,char *field, char *field_extra);
    void writeExtraField(std::ostream &os, const std::string &key, char *field_extra);
    void printHead();
};

#endif //TAR_SIMU_HEADER_H
