#include <iostream>
#include <cstdio>
#include "Archive.h"
#include "Compress.h"
#include "Decompress.h"
using namespace std;
void testBlockReadWrite();
void testHeader();
void testCreateNExtract(string rPath, string tPath);
void testCreateNExtract2();
void testFileIter();
void testExtraField();

void testExtraField2(const std::string &rPath, const std::string &tPath){
    Archive a(rPath);
    vector<string> vector1;
    vector1.emplace_back("directoryTest");
    vector1.emplace_back("中文目录");
    vector1.emplace_back("wTest.txt");
    a.create(tPath+"archive2.tar", vector1);
    a.extract(tPath, tPath+"archive2.tar");
}
void testArchive(){
    string rPath1 = "D:\\past\\F\\C++_file\\tar_simu2\\testFile\\1\\";
    string targetPath1 = "D:\\past\\F\\C++_file\\tar_simu2\\testFile\\2\\";
    string rPath2 = "F:\\vsc_ccpp\\tar_simu\\testFile\\1\\";
    string targetPath2 = "F:\\vsc_ccpp\\tar_simu\\testFile\\2\\";
    //testCreateNExtract(rPath1, targetPath1);
    //testCreateNExtract2();

    //testExtraField2();
    //testConvert("中文状况如何");
    //getchar();
    //std::cout << sizeof(std::uintmax_t) << std::endl;
    testExtraField2(rPath1, targetPath1);
}

int main() {
    Compress c("compressTest.txt");
    c.genCompressed("compressed.hfz");
    Decompress d("compressed.hfz");
    d.decompress("decompressedTest.txt");
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

void testCreateNExtract(string rPath, string tPath){
    Archive a(rPath);
    vector<string> vector1;
    vector1.emplace_back("test.txt");
    vector1.emplace_back("wTest.txt");
    vector1.emplace_back("directoryTest");
    a.create(tPath+"archive2.tar", vector1);
    a.extract(tPath, tPath+"archive2.tar");
}
void testCreateNExtract2(){
    Archive a("F:\\vsc_ccpp\\tar_simu\\");
    vector<string> vector1;
    vector1.emplace_back("test.txt");
    vector1.emplace_back("wTest.txt");
    vector1.emplace_back("directoryTest");
    a.create("F:\\test\\1\\archive2.tar", vector1);
    a.extract("F:\\test\\2\\", "F:\\test\\1\\archive2.tar");
}
void testFileIter(){
    Archive a("D:\\past\\F\\C++_file\\tar_simu2\\");
    a.iter_file();
}
void testExtraField1(){
    Header h;
    std::string s = "how long can the name be in windows?"
                    "kadhkehdkjehjjjjjjjjjjjjjjjjjjjjjjj]1"
                    "11111111111111111111111111111111111111"
                    "111111111111111111111111111111111111111"
                    "111111111111111111111111111111111111111"
                    "111111111111111111111111111111111111111"
                    "2222222222222222222222222222222222222222"
                    "222222222222222222222222222222222222222222"
                    "22222222222222222222222222222222222222"
                    "222222222222222222222222222222222222"
                    "3333333333333333333333333333333333333"
                    "4444444444444444444444444444444444444444"
                    "55555555555555555555555555555555555555555"
                    "6666666666666666666666666666666666666"
                    "77777777777777777777777777777777777777777"
                    "888888888888888888888888888888888888888"
                    "99999999999999999999999999999999999"
                    "111111111111111111111111111111111111";
    h.setExtraField("name", s);
    std::cout<<s.length()<<" : "<<h.getExtraField("name", s.length())<<std::endl;
}