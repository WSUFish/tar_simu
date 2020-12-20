//
// Created by 86189 on 2020/12/11.
//

#include "Archive.h"

void Archive::create(const std::string &targetPath, std::vector<std::string> &fileNameVector) {
    FILE *targetFP = fopen(targetPath.c_str(),"w");
    if(targetFP == nullptr){
        throw std::runtime_error(targetPath+": can't create file!");
    }
    for(auto iter = fileNameVector.begin();iter!=fileNameVector.end();iter++){
        package((*iter), targetFP);
    }
    fclose(targetFP);
}

void Archive::extract(const std::string &targetPath, const std::string &packageName) {
    FILE *packageFP = fopen(packageName.c_str(), "r");
    if(packageFP == nullptr){
        throw std::runtime_error("can't find package!");
    }
    while(feof(packageFP)==0 && zeroBlockNum<2){
        unpack(packageFP, targetPath);
    }
    fclose(packageFP);
}
void Archive::package(const std::string &fileName, FILE *targetFP) {
    Header h;
    h.setFileInfo(archivePath, fileName);
    switch(h.getMode()){
        case MODE_REG:
            FILE *fp;
            fp = fopen((archivePath + fileName).c_str(), "r");
            if(fp == nullptr){
                throw std::runtime_error("file not exist!");
            }
            h.write(targetFP);
            readNwrite(fp, targetFP, h.getSize());
            fclose(fp);
            break;
        case MODE_DIR:
            h.write(targetFP);
            for(const auto &entry: fs::directory_iterator(archivePath+fileName)){
                //std::cout<<"relative path: "<<fs::relative(entry.path(), archivePath)<<std::endl;
                package(fs::relative(entry.path(), archivePath).string(), targetFP);
            }
            break;
        default:
            throw std::runtime_error("package:"+ fileName + " not expected file type!");
    }
}

void Archive::unpack(FILE *packetFP, const std::string &path){
    Header h;
    h.read(packetFP);
    switch(h.getMode()){
        case MODE_REG:
            FILE *fp;
            fp = fopen((path + h.getName()).c_str(), "w");
            if(fp==nullptr){
                throw std::runtime_error(path + h.getName()+": can't create file!");
            }
            readNwrite(packetFP, fp, h.getSize());
            fclose(fp);
            break;
        case MODE_DIR:
            fs::create_directory(path+h.getName());
            break;
        case MODE_ZERO:
            if(feof(packetFP)){ //C (!0) == true
                return;
            }
            zeroBlockNum++;
            break;
        default:

            throw std::runtime_error("unpack not expected file type!");
    }
}

void Archive::readNwrite(FILE *readFP, FILE *writeFP, int fileSize) {
    while(fileSize > 0){
        Block b;
        b.read(readFP);
        b.write(writeFP);
        fileSize -= 512;
    }
}

void Archive::iter_file(){
    std::string path = "F:/vsc_ccpp/tar_simu";
    for(const auto &entry: fs::directory_iterator(path)){
        std::cout << entry.path() << std::endl;
    }
}
