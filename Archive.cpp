//
// Created by 86189 on 2020/12/11.
//

#include "Archive.h"

void Archive::create(const std::string &targetPath, std::vector<std::string> &fileNameVector) {

    std::ofstream os(targetPath, std::ios::binary|std::ios::out);
    if(!os){
        throw std::runtime_error("无法创建 "+targetPath);
    }
    for(auto iter = fileNameVector.begin();iter!=fileNameVector.end();iter++){
            package((*iter), os);
    }
    os.close();
}

void Archive::extract(const std::string &targetPath, const std::string &packageName) {

    std::ifstream is(packageName, std::ios::binary|std::ios::in);
    if(!is){
        throw std::runtime_error("无法打开 "+packageName);
    }
    while((!is.eof()) && zeroBlockNum<2){
        unpack(is, targetPath);
    }
    is.close();
}

void Archive::qExtract(const QString &targetPath, const QString &packageName)
{
    std::string targetPathS = targetPath.toLocal8Bit().constData();
    std::string packageNameS = packageName.toLocal8Bit().constData();
    extract(targetPathS, packageNameS);
}



void Archive::package(const std::string &fileName, std::ostream &os) {
    Header h;
    QDir currentPath(QString::fromLocal8Bit(archivePath.c_str()));
    QString qFileName = QString::fromLocal8Bit(fileName.c_str());
    h.setFileInfoQt(currentPath.path(), qFileName);

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
                throw std::runtime_error("无法打开 "+filePath);
            }
            h.write(os);
            packFrom(is, os, h.getSize());
            is.close();
            break;
        }
        case MODE_DIR:{
            h.write(os);
            QString hPath = QString::fromLocal8Bit(filePath.c_str());
            QDir qd(hPath);
            qd.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs );
            if(!qd.exists()){
                throw std::runtime_error("找不到 "+filePath);
            }
            for(auto &entry: qd.entryInfoList()){
                QString ePath = entry.absoluteFilePath();
                //std::cout<<"absolute entry path is "<<ePath.toLocal8Bit().constData()<<std::endl;
                QString rPath = currentPath.relativeFilePath(ePath);
                //std::cout<<"relative entry path is "<<rPath.toLocal8Bit().constData()<<std::endl;
                package(rPath, os);
            }
            break;
        }
        default:
            std::cerr<<"package: "<<archivePath<<fileName<<" no type! "<<h.getMode()<<std::endl;
            throw std::runtime_error(fileName + " 类型不对");
    }
}
void Archive::unpack(std::istream &is, const std::string &path){
    Header h;
    h.read(is);
    if(is.eof()){
        return;
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
                throw std::runtime_error("无法创建 "+path + h.getName());
            }
            unpackFrom(is, os, h.getSize());
            os.close();
            break;
        }
        case MODE_DIR:{
            QDir cd(QString::fromLocal8Bit(path.c_str()));
            if(!cd.mkpath(QString::fromLocal8Bit(h.getName().c_str()))){
                throw std::runtime_error("无法创建 "+path + h.getName());
            }
            break;
        }
        case MODE_ZERO:
            zeroBlockNum++;
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
    while(fileSize > 512){
        Block b;
        b.read(is);
        b.write(os);
        fileSize -= 512;
    }
    Block b;
    b.read(is);
    b.write(os, fileSize);
}
void Archive::package(const QString &fileName, std::ostream &os){
    package(std::string(fileName.toLocal8Bit().constData()), os);
}

