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

void Header::setMode(unsigned short mode) {
    *(unsigned short*)this->mode = mode;
}

int Header::getMode() {
    unsigned short mode = *(unsigned short*)(this->mode);
    if(mode & S_IFDIR){
        printf("is dir!\n");
        return MODE_DIR;
    }else if(mode & S_IFREG){
        printf("is wenjian\n");
        return MODE_REG;
    }else{
        throw std::runtime_error("not expected file type!");
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
    struct stat64 buf; //获取文件信息
    if(stat64((archivePath+fileName).c_str(), &buf)==-1){
        throw std::invalid_argument("file name error");
    }
    setName(fileName);

    struct tm *p = gmtime(&buf.st_atime);
    printf("%d %d %d", p->tm_year, p->tm_mon, p->tm_mday);

    setMode(buf.st_mode);
    setSize(buf.st_size);

    
    std::cout << fileName <<","<< buf.st_mode << "," << buf.st_size << std::endl;
}

void Header::setSize(off64_t file_size){
    memcpy(size, &file_size, 8);
}

int Header::getSize(){
    return (int)*(off64_t *)size;
}

void writeExtraField(const std::string &key, const std::string &field){

}

std::string getExtraField(const std::string &key){

    return std::string();
}