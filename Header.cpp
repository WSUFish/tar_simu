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

void Header::writeExtraBlock(const std::string &key, const std::string &field) {
    std::vector<Block> v;
    int l =field.length();
    const char *source = field.c_str();
    while(l>0){
        Block b;
        if(l>=512){
            b.read(source, 512);
            l-=512;
            source+=512;
        }else{
            b.read(source, l);
            l = 0;
        }
        v.push_back(b);
    }
    extraField.insert(std::pair<std::string, std::vector<Block>>(key, v));
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
    }else if(allZero()){
        return MODE_ZERO;
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
//    fs::file_status s1 = fs::symlink_status(archivePath + fileName);
//    if(fs::is_directory(s1)){
//        std::cout << fileName << " is directory" << std::endl;
//    }else if(fs::is_symlink(s1)){
//        std::cout << fileName << " is a symlink!!!!!!!!" << std::endl;
//    }else if(fs::is_regular_file(s1)){
//        std::cout << fileName << " is a file?" << std::endl;
//    }
//    fs::file_status s2 = fs::status(archivePath + fileName);
//    if(fs::is_directory(s2)){
//        std::cout << fileName << " is directory" << std::endl;
//    }else if(fs::is_symlink(s2)){
//        std::cout << fileName << " is a symlink!!!!!!!!" << std::endl;
//    }else if(fs::is_regular_file(s2)){
//        std::cout << archivePath+fileName << " is a file?" << std::endl;
//    }
//    if(fs::is_symlink(archivePath + fileName)){
//        std::cout << archivePath+fileName << " is a symlink!!!!!!!!" << std::endl;
//    }
    struct stat64 buf; //获取文件信息
    if(stat64((archivePath+fileName).c_str(), &buf)==-1){
        throw std::invalid_argument("file name error: "+archivePath+fileName);
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

std::string Header::getExtraField(const std::string &key, int size){
    auto iter = extraField.find(key);
    if(iter==extraField.end()){
        throw std::runtime_error(key+ ": key not found!");
    }else{
        return connectBlock(iter->second, size);
    }
    return std::string();
}

bool Header::allZero() {
    for(int i = 0;i<512;i++){
        if(block[i]!='\0'){
            return false;
        }
    }
    return true;
}

std::string Header::connectBlock(const std::vector<Block> &bv, int size) {
    auto iter = bv.begin();
    char *buff = new char[size+1];
    buff[size] = '\0';
    char *temp = buff;
    while(size>512){
        size-=512;
        memcpy(temp, iter->block, 512*sizeof(char));
        temp+=512;
        iter++;
    }
    memcpy(temp, iter->block, size*sizeof(char));
    return std::string(buff);
}