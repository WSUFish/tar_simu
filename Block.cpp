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
int Block::read(FILE *fileName, int size) {
    return fread(this->block, sizeof(char), size, fileName);
}

int Block::write(FILE *fileName, int size) {
    return fwrite(block, sizeof(char), size, fileName);
}

void Block::read(std::istream &is, int size){
    is.read(block, sizeof(char)*size);
}
void Block::write(std::ostream &os, int size){
    os.write(block, sizeof(char)*size);
}

int Block::read(const char *source, int size) {
    if(size<=512){
        memcpy(block, source, size*sizeof(char));
        return 1;
    }else{
        return 0;
    }
}
