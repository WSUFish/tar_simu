//
// Created by 86189 on 2020/12/6.
//

#include "Block.h"
Block::Block() {
    //block = (char *)calloc(512, sizeof(char));
    block = new char[512]();
}
Block::~Block() {
    delete []block;
}
Block::Block(const Block &block1) {
    block = new char[512]();
    memcpy(block, block1.block, 512*sizeof(char));
}
int Block::read(FILE *fileName) {
    return fread(this->block, sizeof(char), 512, fileName);
}

int Block::write(FILE *fileName) {
    return fwrite(block, sizeof(char), 512, fileName);
}

int Block::read(const char *source, int size) {
    if(size<=512){
        memcpy(block, source, size*sizeof(char));
        return 1;
    }else{
        return 0;
    }
}