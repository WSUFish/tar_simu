#include <stdexcept>
#include "Header.h"

void Header::setName(std::string fileName) {
    //set name
    if(fileName.length()<=99){
        strcpy(name, fileName.c_str());
        *name_extra='n';
    }else{
        strcpy(name, std::to_string(fileName.length()).c_str());
        *name_extra='y';
    }
}

std::string Header::getName() {
    if(*name_extra=='n'){
        return std::string(name);
    }else if(*name_extra=='y'){
        return std::string(name);
    }else{
        throw std::runtime_error("name_extra wrong");
    }
}

void Header::setFileInfo(std::string archivePath, std::string fileName){
    struct stat buf;
    if(stat((archivePath+fileName).c_str(), &buf)==-1){
        throw std::invalid_argument("file name error");
    }
    setName(fileName);
    struct tm *p = gmtime(&buf.st_atime);
    printf("%d %d %d", p->tm_year, p->tm_mon, p->tm_mday);
}