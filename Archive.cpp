//
// Created by 86189 on 2020/12/11.
//

#include "Archive.h"

void Archive::create(const std::string &targetPath, std::vector<std::string> &fileNameVector) {
//    FILE *targetFP = fopen(targetPath.c_str(),"w");
//    if(targetFP == nullptr){
//        throw std::runtime_error(targetPath+": can't create file!");
//    }
//    for(auto iter = fileNameVector.begin();iter!=fileNameVector.end();iter++){
//        package((*iter), targetFP);
//    }
//    fclose(targetFP);
    std::ofstream os(targetPath, std::ios::binary|std::ios::out);
    if(!os){
        throw std::runtime_error(targetPath+": can't create file!");
    }
    for(auto iter = fileNameVector.begin();iter!=fileNameVector.end();iter++){
            package((*iter), os);
    }
    os.close();
}

void Archive::extract(const std::string &targetPath, const std::string &packageName) {
//    FILE *packageFP = fopen(packageName.c_str(), "r");
//    if(packageFP == nullptr){
//        throw std::runtime_error("can't find package!");
//    }
//    while(feof(packageFP)==0 && zeroBlockNum<2){
//        unpack(packageFP, targetPath);
//    }
//    fclose(packageFP);
    std::ifstream is(packageName, std::ios::binary|std::ios::in);
    if(!is){
        throw std::runtime_error(targetPath+": can't find file!");
    }
    while((!is.eof()) && zeroBlockNum<2){
        unpack(is, targetPath);
    }
    is.close();
}
void Archive::package(const std::string &fileName, FILE *targetFP) {
    Header h;
    QDir currentPath(QString::fromLocal8Bit(archivePath.c_str()));
    QString qFileName = QString::fromLocal8Bit(fileName.c_str());
    h.setFileInfoQt(currentPath.path(), qFileName);
    switch(h.getMode()){
        case MODE_REG:
            FILE *fp;
            fp = fopen((archivePath + fileName).c_str(), "r");
            if(fp == nullptr){
                throw std::runtime_error("file not exist!");
            }
            h.write(targetFP);
            packFrom(fp, targetFP, h.getSize());
            fclose(fp);
            break;
        case MODE_DIR:{
            h.write(targetFP);
            QString hPath = QString::fromLocal8Bit((archivePath+fileName).c_str());
            //QString hPath = currentPath.cd(qFileName);
            QDir qd(hPath);
            qd.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs );
            for(auto &entry: qd.entryInfoList()){
                QString ePath = entry.absoluteFilePath();
                //std::cout<<"absolute entry path is "<<ePath.toLocal8Bit().constData()<<std::endl;
                QString rPath = currentPath.relativeFilePath(ePath);
                //std::cout<<"relative entry path is "<<rPath.toLocal8Bit().constData()<<std::endl;
                package(rPath, targetFP);
            }
//            for(const auto &entry: fs::directory_iterator(GbkToWString(archivePath+fileName))){
//                //std::cout<<"relative path: "<<fs::relative(entry.path(), archivePath)<<std::endl;
//                package(WStringToGbk(fs::relative(entry.path(), GbkToWString(archivePath)).wstring()), targetFP);
//            }
            break;
        }
        default:
            std::cerr<<"package: "<<archivePath<<fileName<<" no type! "<<h.getMode()<<std::endl;
            //throw std::runtime_error("package:"+ fileName + " not expected file type!");
    }
}

void Archive::package(const QString &fileName, FILE *targetFP){
    package(std::string(fileName.toLocal8Bit().constData()), targetFP);
}

void Archive::unpack(FILE *packetFP, const std::string &path){
    Header h;
    h.read(packetFP);
    if(feof(packetFP)){ //C (!0) == true
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
            FILE *fp;
            fp = fopen(filePath.c_str(), "w");
            if(fp==nullptr){
                throw std::runtime_error(path + h.getName()+": can't create file!");
            }
            unpackFrom(packetFP, fp, h.getSize());
            fclose(fp);
            break;
        }
        case MODE_DIR:{
            QDir cd(QString::fromLocal8Bit(path.c_str()));
            cd.mkdir(QString::fromLocal8Bit(h.getName().c_str()));
            //fs::create_directory(GbkToWString(path+h.getName()));
            break;
        }
        case MODE_ZERO:
            zeroBlockNum++;
            break;
        default:

            throw std::runtime_error("unpack not expected file type!");
    }
}


void Archive::packFrom(FILE *readFP, FILE *writeFP, int fileSize) {
    while(fileSize > 0){
        Block b;
        b.read(readFP);
        b.write(writeFP);
        fileSize -= 512;
    }
}
void Archive::unpackFrom(FILE *readFP, FILE *writeFP, int fileSize) {
    while(fileSize > 512){
        Block b;
        b.read(readFP);
        b.write(writeFP);
        fileSize -= 512;
    }
    Block b;
    b.read(readFP);
    b.write(writeFP, fileSize);
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
                throw std::runtime_error("file not exist!");
            }
            h.write(os);
            packFrom(is, os, h.getSize());
            is.close();
            break;
        }
        case MODE_DIR:{
            h.write(os);
            QString hPath = QString::fromLocal8Bit((archivePath+fileName).c_str());
            //QString hPath = currentPath.cd(qFileName);
            QDir qd(hPath);
            qd.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs );
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
            //throw std::runtime_error("package:"+ fileName + " not expected file type!");
    }
}
void Archive::unpack(std::istream &is, const std::string &path){
    Header h;
    h.read(is);
    if(is.eof()){ //C (!0) == true
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
                throw std::runtime_error(path + h.getName()+": can't create file!");
            }
            unpackFrom(is, os, h.getSize());
            os.close();
            break;
        }
        case MODE_DIR:{
            QDir cd(QString::fromLocal8Bit(path.c_str()));
            cd.mkdir(QString::fromLocal8Bit(h.getName().c_str()));
            //fs::create_directory(GbkToWString(path+h.getName()));
            break;
        }
        case MODE_ZERO:
            zeroBlockNum++;
            break;
        default:

            throw std::runtime_error("unpack not expected file type!");
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

