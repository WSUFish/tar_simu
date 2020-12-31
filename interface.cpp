#include "mainwindow.h"
#include <QApplication>
#include "Compress.h"
#include "Decompress.h"
#include "Header.h"
#include "Archive.h"

void testCompress(){
    Compress c("D:/filetest/1/2021年全国硕士研究生招生考试数学一试题及答案.pdf");
    c.genCompressed("D:/filetest/2/2021年全国硕士研究生招生考试数学一试题及答案.pdf.hfz");

    Decompress d("D:/filetest/2/2021年全国硕士研究生招生考试数学一试题及答案.pdf.hfz");
    d.decompress("D:/filetest/2/2021年全国硕士研究生招生考试数学一试题及答案.pdf");
}
void testArchive(){
    Archive ar("D:/filetest/1/");
    std::vector<std::string> v;
    v.emplace_back("testQtMainWindow");
    v.emplace_back("router.txt");
    v.emplace_back("2021年全国硕士研究生招生考试数学一试题及答案.pdf");
    ar.create("D:/filetest/2/testTar.tar",v);
    ar.extract("D:/filetest/2/testTar/","D:/filetest/2/testTar.tar");
}
void testDecompress(){
    Archive a;
    std::string s1 = "D:/filetest/2/testTar/";
    std::string s3 = "D:/filetest/2/testTar2/";
    std::string s2 = "D:/filetest/2/testTar.tar";
    a.extract(s1,s2);
    a.qExtract(QString::fromLocal8Bit(s3.c_str()),QString::fromLocal8Bit(s2.c_str()));
}

int main(int argc, char *argv[])
{

    //testArchive();
    //testDecompress();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
