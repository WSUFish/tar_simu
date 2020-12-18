//
// Created by 86189 on 2020/12/6.
//

#ifndef TAR_SIMU_BLOCK_H
#define TAR_SIMU_BLOCK_H

#include <stdio.h>
#include <cstring>
#include <cstdlib>

class Block {
public:
    char *block;
    Block();
    Block(const Block &block1);
    ~Block();
    int read(FILE *fileName);
    int read(const char *source, int size);
    int write(FILE *fileName);
};


#endif //TAR_SIMU_BLOCK_H
