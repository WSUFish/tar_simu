#include "mainwindow.h"
#include <QApplication>
#include "Compress.h"
#include "Decompress.h"
#include "Header.h"
#include "Archive.h"

void testCompress(){
    Compress c("D:/filetest/1/router.txt");
    c.genCompressed("D:/filetest/2/router.txt.hfz");

    Decompress d("D:/filetest/2/router.txt.hfz");
    d.decompress("D:/filetest/2/router.txt");
}
void testArchive(){
    Archive ar("D:/filetest/1/");
    std::vector<std::string> v;
    v.emplace_back("testQtMainWindow");
    v.emplace_back("router.txt");
    v.emplace_back("2021年全国硕士研究生招生考试数学一试题及答案.pdf");
    ar.create("D:/filetest/2/testTar.tar",v);
    ar.extract("D:/filetest/2/testTar","D:/filetest/2/testTar.tar");
}

int main(int argc, char *argv[])
{

    testArchive();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
