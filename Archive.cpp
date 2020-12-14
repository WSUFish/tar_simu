//
// Created by 86189 on 2020/12/11.
//

#include "Archive.h"

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
            int fileSize = h.getSize();
            while(fileSize > 0){
                Block b;
                b.read(fp);
                b.write(targetFP);
                fileSize -= 512;
            }
            break;
        case MODE_DIR:
            break;
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
                throw std::runtime_error("can't create file!");
            }
            int fileSize
    }
}