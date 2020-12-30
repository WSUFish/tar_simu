//
// Created by 86189 on 2020/12/6.
//

#ifndef TAR_SIMU_BLOCK_H
#define TAR_SIMU_BLOCK_H

#include <stdio.h>
#include <fstream>
#include <cstring>
#include <cstdlib>

class Block {
public:
    char *block;
    Block();
    Block(const Block &block1);
    ~Block();
    int read(FILE *fileName, int size=512);
    int read(const char *source, int size);
    int write(FILE *fileName, int size=512);
    void read(std::istream &is, int size=512);
    void write(std::ostream &os, int size=512);
};


#endif //TAR_SIMU_BLOCK_H
