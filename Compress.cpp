#include "Compress.h"

#include <utility>


void Compress::setPower(){
    std::ifstream is(sourceFile);
    char tempC;
    is.get(tempC);
    while(!is.eof()){
        charPower[int(tempC)]++;
        is.get(tempC);
    }
    ht.construct(charPower, 256);
    ht.printCodeV();
    is.close();
}

void Compress::writeHeader(std::ostream &os) {
    int nonZero = 0;
    int bitNum = 0;
    for(int i=0;i<256;i++){
        if(charPower[i]!=0){
            nonZero++;
            bitNum += charPower[i]*(int)ht.codeM[(char)i].size();
        }
    }
    struct cHeader header = {nonZero,bitNum};
    os.write((char*)&header, sizeof(header));
    for(int i=0;i<256;i++){
        if(charPower[i]!=0){
            struct powerPair pair = {(char)i, charPower[i]};
            os.write((char*)&pair, sizeof(pair));
        }
    }
}
void Compress::genCompressed(const std::string &targetFile){
    setPower();

    std::ifstream is(sourceFile);
    std::ofstream os(targetFile, std::ios::out|std::ios::binary);
    writeHeader(os);

    char tempC;
    is.get(tempC);
    while(!is.eof()){
        writeCode(tempC, os);
        is.get(tempC);
    }
    std::cout<<std::endl;
    os.write(buff, sizeof(char)*(buffP-buff+ ((bitInP==0)?0:1) ));
    is.close();
    os.close();
}

void Compress::writeCode(char c, std::ostream &os){
    std::string code = ht.codeM[c];

    for(auto bit: code){
        writeSingleBit(bit);
        nextBit(os);

        std::cout<<bit;
    }

}


Compress::Compress(std::string filePath):ht(),sourceFile(std::move(filePath)){
    buffSize = 0;
    bitInP = 0;
    buffP = buff;

    for(auto &i: charPower){
        i = 0;
    }
}

void Compress::printPower(){
    for (int i = 0; i < 256;i++){
        std::cout << i << ":" << charPower[i] << std::endl;
    }
}

void Compress::writeSingleBit(char b){
    if(b=='0'){
        *buffP &= (~(1 << ((bitInP) ^ 7)));
        /*
            bitInP 在0~7之间, bitInP与7（0111）按位取反相当于 7-bitInP
            1 << (), 1左移（）位， 相当于从左往右数第bitInP位为1
            ~（） ，再取反， 相当于从左往右数第bitInP位为1，其余为0
            &= ，再做且运算， 相当于只有第bitInp位置0，其余不变
        */
    }else if(b=='1'){
        *buffP |= (1 << ((bitInP) ^ 7));
    }else{
        std::cerr << "error! neither 0 or 1!" << std::endl;
        return;
    }
    
}

void Compress::nextBit(std::ostream &os){
    if(++bitInP==8){
        bitInP = 0;
        buffP++;
        if( buffP-buff == BUFFSIZE){
            os.write(buff, sizeof(char) * BUFFSIZE);
            std::cout<<"块已满，写下一块"<<std::endl;
            buffP = buff;
        }
    }
}