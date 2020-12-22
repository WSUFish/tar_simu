#ifndef TAR_SIMU2_COMPRESS_H
#define TAR_SIMU2_COMPRESS_H
#define BUFFSIZE 512
#include <fstream>
#include <cstdio>
#include "HuffmanTree.h"

class Compress {
public:
    HuffmanTree ht;
    std::string sourceFile;
    int charPower[256]{};

    char buff[BUFFSIZE+1]{};
    char *buffP;
    int bitInP;

    int buffSize;
    

    Compress(std::string filePath);
    void setPower();
    void printPower();
    void genCompressed(const std::string &targetFile);
    void writeCode(char c, std::ostream &os);
    void writeHeader(std::ostream &os);
    void writeSingleBit(char b);
    void nextBit(std::ostream &os);
};

#endif