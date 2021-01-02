//
// Created by 86189 on 2020/12/11.
//

#include "Archive.h"

void Archive::create(const std::string &targetPath, std::vector<std::string> &fileNameVector, const std::string &key) {

    std::ofstream os(targetPath, std::ios::binary|std::ios::out);
    if(!os){
        throw std::runtime_error("无法创建 "+targetPath);
    }
    for(auto iter = fileNameVector.begin();iter!=fileNameVector.end();iter++){
            package((*iter), os, key);
    }
    os.close();
}

void Archive::extract(const std::string &targetPath, const std::string &packageName, const std::string &key) {

    std::ifstream is(packageName, std::ios::binary|std::ios::in);
    if(!is){
        throw std::runtime_error("无法打开备份文件 "+packageName);
    }
    while((!is.eof()) && zeroBlockNum<2){
        unpack(is, targetPath, key);
    }
    is.close();
}

void Archive::qExtract(const QString &targetPath, const QString &packageName, const std::string &key)
{
    std::string targetPathS = targetPath.toLocal8Bit().constData();
    std::string packageNameS = packageName.toLocal8Bit().constData();
    extract(targetPathS, packageNameS, key);
}

bool Archive::isEncrypt(const std::string &packageName)
{
    std::ifstream is(packageName);
    if(!is){
        throw std::runtime_error("无法打开备份文件 "+packageName);
    }
    Header h;
    h.read(is);
    is.close();
    if(h.isEncrypt()){
        return true;
    }else{
        return false;
    }
}

bool Archive::checkPassword(const std::string &packageName, const std::string &key)
{
    std::ifstream is(packageName);
    if(!is){
        throw std::runtime_error("无法打开备份文件 "+packageName);
    }
    Header h;
    h.read(is);
    is.close();
    return h.checkPassword(key);
}


void Archive::package(const std::string &fileName, std::ostream &os, const std::string &key) {
    Header h;
    QDir currentPath(QString::fromLocal8Bit(archivePath.c_str()));
    QString qFileName = QString::fromLocal8Bit(fileName.c_str());
    bool isEncry = false;
    if(key!=""){
        isEncry = true;
    }

    if(isEncry){
        h.setFileInfoQt(currentPath.path(), qFileName, key);
    }else{
        h.setFileInfoQt(currentPath.path(), qFileName);
    }


    std::string filePath;
    if(archivePath.at(archivePath.length()-1)!='/'){
        filePath = archivePath+"/" +fileName;
    }else{
        filePath = archivePath + fileName;
    }

    switch(h.getMode()){
        case MODE_REG:{
            std::ifstream is(filePath, std::ios::binary|std::ios::in);
            if(!is){
                throw std::runtime_error("无法打开原文件 "+filePath);
            }
            h.write(os);
            if(isEncry){
                packFromEncry(is, os, key, h.getSize());
            }else{
                packFrom(is, os, h.getSize());
            }
            is.close();
            break;
        }
        case MODE_DIR:{
            h.write(os);
            QString hPath = QString::fromLocal8Bit(filePath.c_str());
            QDir qd(hPath);
            qd.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs );
            if(!qd.exists()){
                throw std::runtime_error("找不到目录 "+filePath);
            }
            for(auto &entry: qd.entryInfoList()){
                QString ePath = entry.absoluteFilePath();
                //std::cout<<"absolute entry path is "<<ePath.toLocal8Bit().constData()<<std::endl;
                QString rPath = currentPath.relativeFilePath(ePath);
                //std::cout<<"relative entry path is "<<rPath.toLocal8Bit().constData()<<std::endl;
                package(rPath, os, key);
            }
            break;
        }
        default:
            std::cerr<<"package: "<<archivePath<<fileName<<" no type! "<<h.getMode()<<std::endl;
            throw std::runtime_error(fileName + " 类型不对");
    }
}


void Archive::unpack(std::istream &is, const std::string &path, const std::string &key){

    Header h;
    h.read(is);
    if(is.eof()){
        return;
    }
    bool isEncry = h.isEncrypt();
    if(isEncry){
        if(!h.checkPassword(key)){
            throw std::runtime_error("密码错误！");
        }
    }
    h.printHead();

    std::string filePath;
    if(path.at(path.length()-1)!='/'){
        filePath = path+"/" +h.getName();
    }else{
        filePath = path + h.getName();
    }
    switch(h.getMode()){
        case MODE_REG:{
            std::ofstream os(filePath, std::ios::binary | std::ios::out);
            if(!os){
                throw std::runtime_error("无法创建还原文件 "+filePath);
            }
            if(isEncry){
                unpackFromEncry(is, os, key, h.getSize());
            }else{
                unpackFrom(is, os, h.getSize());
            }
            os.close();
            break;
        }
        case MODE_DIR:{
            QDir cd(QString::fromLocal8Bit(path.c_str()));
            if(!cd.mkpath(QString::fromLocal8Bit(h.getName().c_str()))){
                throw std::runtime_error("无法创建还原目录 "+path + h.getName());
            }
            break;
        }
        case MODE_ZERO:
            zeroBlockNum++;
            std::cout<<"全零块"<<std::endl;
            break;
        default:

            throw std::runtime_error("无法识别 "+path + h.getName());
    }
}
void Archive::packFrom(std::istream &is, std::ostream &os, int fileSize) {
    while(fileSize > 0){
        Block b;
        b.read(is);
        b.write(os);
        fileSize -= 512;
    }
}
void Archive::unpackFrom(std::istream &is, std::ostream &os, int fileSize) {
    while(fileSize > 0){
        Block b;
        b.read(is);
        b.write(os, fileSize>512?512:fileSize);
        fileSize -= 512;
    }
}

void Archive::packFromEncry(std::istream &is, std::ostream &os, const std::string &key, int fileSize)
{
    while(fileSize > 0){
        Block b;
        b.readEncry(is, key.c_str(), fileSize>508? 508:fileSize);
        b.write(os);
        fileSize -= 508;
    }
}

void Archive::unpackFromEncry(std::istream &is, std::ostream &os, const std::string &key, int fileSize)
{
    while(fileSize > 0){
        Block b;
        b.read(is);
        b.writeEncry(os, key.c_str(),fileSize>508? 508:fileSize );
        fileSize -= 508;
    }
}
void Archive::package(const QString &fileName, std::ostream &os, const std::string &key){
    package(std::string(fileName.toLocal8Bit().constData()), os, key);
}

