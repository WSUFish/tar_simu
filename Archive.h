//
// Created by 86189 on 2020/12/11.
//

#ifndef TAR_SIMU2_ARCHIVE_H
#define TAR_SIMU2_ARCHIVE_H
#include "Header.h"



class Archive {
public:
    std::string archivePath; //archive原路径
    int zeroBlockNum;
    Archive(){
        zeroBlockNum = 0;
        archivePath = "";
    }
    Archive(const std::string &relativePath){
        zeroBlockNum = 0;
        archivePath = relativePath;
    }
    void create(const std::string &targetPath, std::vector<std::string> &fileNameVector, const std::string &key = "");
    void extract(const std::string &targetPath, const std::string &packageName, const std::string &key = "");
    QStringList checkOut(const std::string &packageName, std::vector<std::string> &fileNameVector, const std::string &key = "");
    void qExtract(const QString &targetPath, const QString &packageName, const std::string &key = "");
    bool isEncrypt(const std::string &packageName);
    bool checkPassword(const std::string &packageName, const std::string &key);


    void package(const std::string &fileName, std::ostream &os, const std::string &key = "");
    void package(const QString &fileName, std::ostream &os, const std::string &key = "");
    void unpack(std::istream &is, const std::string &path, const std::string &key = "");

    QStringList compare(const std::string &fileName, std::istream &is, const std::string &key = "");

    void writeHeader();
    //void iter_file();

private:
    void packFrom(std::istream &is, std::ostream &os, int fileSize);
    void unpackFrom(std::istream &is, std::ostream &os, int fileSize);
    bool compareForm(std::istream &sis, std::istream &pis, int fileSize);
    void packFromEncry(std::istream &is, std::ostream &os, const std::string &key,int fileSize);
    void unpackFromEncry(std::istream &is, std::ostream &os, const std::string &key, int fileSize);
    bool compareFormEncry(std::istream &sis, std::istream &pis, const std::string &key, int fileSize);
    //bool compareDir(, std::istream &pis);
};


#endif //TAR_SIMU2_ARCHIVE_H
