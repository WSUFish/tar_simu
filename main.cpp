#include <iostream>
#include <cstdio>
#include "Block.h"
#include "Header.h"
void testBlockReadWrite();
void testHeader();
int main() {
    // std::cout << sizeof(int) << std::endl;
    // std::cout << sizeof(off64_t) << std::endl;
    // std::cout << sizeof(short) << std::endl;
    testHeader();
    return 0;
}
void testBlockReadWrite(){
    FILE *fp1, *fp2;
    fp1 = fopen("test.txt","r");
    fp2 = fopen("wTest", "w");
    Block block;
    std::cout<<block.read(fp1);
    std::cout<<block.write(fp2)<<std::endl;
    fclose(fp1);
    fclose(fp2);
}
void testHeader(){
    Header h1, h2;
    h1.setFileInfo("F:/vsc_ccpp/tar_simu/","test.txt");
    std::cout<<h1.getMode()<<std::endl;
    FILE  *fp2;

    fp2 = fopen("wTest", "w");
    h1.write(fp2);
    fclose(fp2);

    fp2 = fopen("wTest","r");
    h2.read(fp2);
    std::cout<<h2.getName()<<","<<h2.getMode()<<","<<h2.getSize()<<std::endl;
    fclose(fp2);

}