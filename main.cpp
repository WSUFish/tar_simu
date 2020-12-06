#include <iostream>
#include <cstdio>
#include "Block.h"
int main() {
    FILE *fp1, *fp2;
    fp1 = fopen("D:/past/F/C++_file/tar_simu2/test.txt","r");
    fp2 = fopen("D:/past/F/C++_file/tar_simu2/wTest.txt", "w");
    Block block;
    std::cout<<block.read(fp1);
    std::cout<<block.write(fp2)<<std::endl;
    fclose(fp1);
    fclose(fp2);
    return 0;
}