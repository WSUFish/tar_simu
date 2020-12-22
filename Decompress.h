//
// Created by 86189 on 2020/12/22.
//

#ifndef TAR_SIMU2_DECOMPRESS_H
#define TAR_SIMU2_DECOMPRESS_H
#include <fstream>
#include <cstdio>
#include "HuffmanTree.h"
#define BUFFSIZE 512

class Decompress {
public:
    HuffmanTree ht;
    std::string sourceFile;
    int bitSize;
    int charPower[256]{};
    char buff[BUFFSIZE+1]{};
    char *buffP;
    int bitInP;
    Decompress(std::string filePath);
    void decompress(const std::string &targetFile);
    void readHeader(std::ifstream &is);
    char readCode(std::ifstream &is);
    bool readSingleBit();
    void nextBit(std::ifstream &is);
};


#endif //TAR_SIMU2_DECOMPRESS_H
