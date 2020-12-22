//
// Created by 86189 on 2020/12/22.
//

#include "Decompress.h"

#include <utility>

Decompress::Decompress(std::string filePath) :ht(),sourceFile(std::move(filePath)){
    bitSize = 0;
    buffP = buff;
    bitInP = 0;
    for(auto &i: charPower){
        i = 0;
    }
}

void Decompress::readHeader(std::ifstream &is) {
    struct cHeader h{};
    is.read((char*)&h, sizeof(h));
    
    bitSize = h.bitNum;
    for(int i = 0;i<h.powerPairNum;i++){
        struct powerPair p{};
        is.read((char*)&p, sizeof(p));
        charPower[(int)p.sourceCode] = p.power;
        
    }
    std::cout << "bitSize = " << h.bitNum << std::endl;
    ht.construct(charPower, 256);
    ht.printCodeV();
}

void Decompress::decompress(const std::string &targetFile) {

    std::ifstream is(sourceFile, std::ios::in|std::ios::binary);
    std::ofstream os(targetFile, std::ios::out|std::ios::binary);
    readHeader(is);

    is.read(buff, sizeof(char)*BUFFSIZE);
    while(bitSize>0){
        os.put(readCode(is));
    }
    is.close();
    os.close();
}

char Decompress::readCode(std::ifstream &is) {
    char result = '\0';
    while(!ht.decode(readSingleBit(), result)){
        nextBit(is);
    }
    nextBit(is);
    //std::cout<<result;
    return result;
}

bool Decompress::readSingleBit() {
    //第bitInP位是否为1
    return ( (*buffP) & ( (1 << ((bitInP)^7) ) ) );
}

void Decompress::nextBit(std::ifstream &is) {
    bitSize--;
    if(++bitInP==8){
        bitInP = 0;
        buffP++;
        if( buffP-buff == BUFFSIZE){
            is.read(buff, sizeof(char) * BUFFSIZE);
            //std::cout << "next block" << std::endl;
            buffP = buff;
        }
    }
}
