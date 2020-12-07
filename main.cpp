#include <iostream>
#include <cstdio>
#include "Block.h"
#include "Header.h"
int main() {
    FILE *fp1, *fp2;
    fp1 = fopen("test.txt","r");
    fp2 = fopen("wTest", "w");
    Block block;
    std::cout<<block.read(fp1);
    std::cout<<block.write(fp2)<<std::endl;
    fclose(fp1);
    fclose(fp2);
    Header h;
    h.getFileInfo("test.txt");
    return 0;
}