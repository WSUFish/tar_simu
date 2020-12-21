#include "Compress.h"


void Compress::setPower(){
    std::ifstream is(sourceFile);
    char tempC;
    is.get(tempC);
    while(!is.eof()){
        charPower[int(tempC)]++;
        is.get(tempC);
    }
    ht.construct(charPower, 256);
    //ht.printCodeV();
    is.close();
}

void Compress::genCompressed(const std::string &targetFile){
    std::ifstream is(sourceFile);
    std::ofstream os(targetFile, std::ios::out|std::ios::binary);

    char tempC;
    is.get(tempC);
    while(!is.eof()){
        writeCode(tempC, os);
        is.get(tempC);
    }
    
}

void Compress::writeCode(char c, std::ostream &os){
    std::string code = ht.codeM[c];

    for(auto bit: code){
        writeSingleBit(bit);
        nextBit(os);
    }

}


Compress::Compress(const std::string &filePath):ht(),sourceFile(filePath){
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
            buffP = buff;
        }
    }
}