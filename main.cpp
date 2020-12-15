#include <iostream>
#include <cstdio>
#include "Archive.h"
using namespace std;
void testBlockReadWrite();
void testHeader();
void testCreateNExtract();
int main() {

    testCreateNExtract();
    //testHeader();
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

void testCreateNExtract(){
    Archive a("D:\\past\\F\\C++_file\\tar_simu2\\");
    vector<string> vector1;
    vector1.emplace_back("test.txt");
    vector1.emplace_back("wTest.txt");
    a.create("D:\\filetest\\1\\archive2.tar", vector1);
    a.extract("D:\\filetest\\2\\", "D:\\filetest\\1\\archive2.tar");
}