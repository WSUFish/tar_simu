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
int Block::read(FILE *fileName) {
    return fread(this->block, sizeof(char), 512, fileName);
}

int Block::write(FILE *fileName) {
    return fwrite(block, sizeof(char), 512, fileName);
}