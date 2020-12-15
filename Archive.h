//
// Created by 86189 on 2020/12/11.
//

#ifndef TAR_SIMU2_ARCHIVE_H
#define TAR_SIMU2_ARCHIVE_H
#include "Header.h"
class Archive {
public:
    std::string archivePath; //archive原路径
    int zeroBlockNum;
    Archive(const std::string &relativePath){
        zeroBlockNum = 0;
        archivePath = relativePath;
    }
    void create(const std::string &targetPath, std::vector<std::string> &fileNameVector);
    void extract(const std::string &targetPath, const std::string &packageName);
    void package(const std::string &fileName, FILE *targetFP);
    void unpack(FILE *packetFP, const std::string &path);
    void writeHeader();
private:
    void readNwrite(FILE *readFP, FILE *writeFP, int fileSize);
};


#endif //TAR_SIMU2_ARCHIVE_H
