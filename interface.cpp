#include "mainwindow.h"
#include <QApplication>
//#include <QTranslator>
#include "Compress.h"
#include "Decompress.h"
#include "Header.h"
#include "Archive.h"

void testCompress(){
    Compress c("D:/filetest/2/testTar.tar");
    c.genCompressed("D:/filetest/2/testTar.tar.hfz");

    //Decompress d("D:/filetest/2/2021年全国硕士研究生招生考试数学一试题及答案.pdf.hfz");
    //d.decompress("D:/filetest/2/2021年全国硕士研究生招生考试数学一试题及答案.pdf");
}
void testArchive(){
    Archive ar("D:/filetest/1/");
    std::vector<std::string> v;
    v.emplace_back("testQtMainWindow");
    v.emplace_back("router.txt");
    v.emplace_back("2021年全国硕士研究生招生考试数学一试题及答案.pdf");
    ar.create("D:/filetest/2/testTar.tar",v, "1234");
    ar.extract("D:/filetest/2","D:/filetest/2/testTar.tar", "12345");
}
void testDecompress(){
    Archive a;
    std::string s1 = "D:/filetest/2/testTar/";
    std::string s3 = "D:/filetest/2/testTar2/";
    std::string s2 = "D:/filetest/2/testTar.tar";
    a.extract(s1,s2);
    a.qExtract(QString::fromLocal8Bit(s3.c_str()),QString::fromLocal8Bit(s2.c_str()));
}

void testEncry(){
    std::string key = "12345678";
    Header h;
    QString sd = "D:/filetest/2";
    QString sn = "router.txt";
    h.setFileInfoQt(sd, sn, key);
    std::string inKey1 = "12345";
    if(h.checkPassword(inKey1)){
        std::cout<<"right!!!"<<std::endl;
    }else{
        std::cout<<"false!!!"<<std::endl;
    }
    std::string inKey2 = "12345678";
    if(h.checkPassword(inKey2)){
        std::cout<<"wrong!!!"<<std::endl;
    }else{
        std::cout<<"right!!!"<<std::endl;
    }
}
int main(int argc, char *argv[])
{

    //testArchive();
    //testCompress();
    //testDecompress();
    //testQ("D:/filetest/2/testTar.tar");
    //std::cout<<"stem="<<MainWindow::getStem("D:/filetest/2/testTar.tar.hfz").toStdString()<<std::endl;

    //testEncry();
    QApplication a(argc, argv);

//    QTranslator user;
//    user.load("qt_zh_CN.qm", "translation/");
//    a.installTranslator(&user);

    MainWindow w;
    w.show();
    return a.exec();
}
