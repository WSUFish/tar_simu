//#include <stdexcept>
#include "Header.h"

//std::wstring Header::StringToWString(const std::string& str) {
//    int num = MultiByteToWideChar(0, 0, str.c_str(), -1, NULL, 0);
//    wchar_t *wide = new wchar_t[num];
//    MultiByteToWideChar(0, 0, str.c_str(), -1, wide, num);
//    std::wstring w_str(wide);
//    delete[] wide;
//    return w_str;
//}

void Header::setName(std::string fileName) {
    //set name
    if(fileName.length()<=99){
        strcpy(name, fileName.c_str());
        *name_extra='n';
    }else{
        strcpy(name, std::to_string(fileName.length()).c_str());
        *name_extra='y';
        setExtraField("name", fileName);
        //printf("too long~~~~~~~~\n");
    }
}

void Header::setExtraField(const std::string &key, const std::string &field) {
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

char Header::getMode() {
    // unsigned short mode = *(unsigned short*)(this->mode);
    // if(mode & S_IFDIR){
    //     //printf("is dir!\n");
    //     return MODE_DIR;
    // }else if(mode & S_IFREG){
    //     //printf("is wenjian\n");
    //     return MODE_REG;
    // }else if(allZero()){
    //     return MODE_ZERO;
    // }else{
    //     throw std::runtime_error("not expected file type!");
    // }
    if(*mode == '\0'){
        if(allZero()){
            return MODE_ZERO;
        }
        throw std::runtime_error("not expected file type!");
    }else{
        return *mode;
    }
}

std::string Header::getName() {
    if(*name_extra=='n'){
        return std::string(name);
    }else if(*name_extra=='y'){
        return getExtraField("name", atoi(name));
    }else{
        std::string s = name;
        std::cout<<(int)*name_extra<<std::endl;
        throw std::runtime_error(s+" name_extra wrong ");
    }
}

void Header::setFileInfo(std::string archivePath, std::string fileName){
    std::string filePath = archivePath + fileName;



    //fs::path p = GbkToWString(filePath);
//    fs::path p = GbkToWString(filePath);
//    fs::file_status fss = fs::symlink_status(p);

//    if(!fs::exists(fss)){
//        testConvert(filePath);
//        std::cout << WStringToGbk(p.wstring()) << std::endl;
//        std::cout << filePath << std::endl;
//        throw std::invalid_argument("file name error: " + filePath);
//    }
//    setName(fileName);
//    setMode(fss);
//    if(getMode()!=MODE_REG){
//        setSize(0);
//    }else{
//        setSize(fs::file_size(p));
//    }

//    std::cout << getName() << " , " <<getMode()  << " , " << getSize() << std::endl;

    // struct stat64 buf; //获取文件信息
    // if (stat64((archivePath + fileName).c_str(), &buf) == -1)
    // {
    //    throw std::invalid_argument("file name error: " + archivePath + fileName);
    // }
    // setName(fileName);



    //struct tm *p = gmtime(&buf.st_atime);
    
    //printf("%d %d %d", p->tm_year, p->tm_mon, p->tm_mday);

}

void Header::setFileInfoQt(const QString &archivePath, const QString &fileName){

    QFileInfo fi(QDir(archivePath), fileName);

    if(!fi.exists()){

        std::cout<<Utf8ToGbk(fi.absoluteFilePath().toStdString())+ "not exit!"<<std::endl;
        throw std::runtime_error("找不到 "+std::string(fi.absoluteFilePath().toLocal8Bit().constData()));
    }
    setName(fileName.toLocal8Bit().constData());
    setMode(fi);
    if(getMode()!=MODE_REG){
        setSize(0);
    }else{
        setSize(fi.size());
    }

    printHead();

}

void Header::setMode(const QFileInfo &fi){
    if(fi.isDir()){
        *mode = MODE_DIR;
    }else if(fi.isFile()){
        *mode = MODE_REG;
    }else if(fi.isSymLink()){
        *mode = MODE_SYM;
    }else{
        std::cerr<<"error! unknown file type"<<std::endl;
    }
}

void Header::setSize(uintmax_t file_size){
    memcpy(size, &file_size, 8);
}

int Header::getSize(){
    return (int)*(off64_t *)size;
}

std::string Header::getExtraField(const std::string &key, int size){
    auto iter = extraField.find(key);
    if(iter==extraField.end()){
        throw std::runtime_error(key+ ": 未找到对应字段");
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

int Header::read(FILE *fileName){
    int result = Block::read(fileName);
    readExtraField(fileName, "name", name, name_extra);
    return result;
}
int Header::write(FILE *fileName){
    int result = Block::write(fileName);
    writeExtraField(fileName, "name", name_extra);
    return result;
}

void Header::readExtraField(FILE *fileName, const std::string &key, char *field, char *field_extra){
    int nameLength = 0;
    if(*field_extra == 'y'){
        std::vector<Block> v;
        nameLength = atoi(field);
        while(nameLength > 0){
            Block b;
            b.read(fileName);
            v.push_back(b);
            nameLength -= 512;
        }
        extraField.insert(std::pair<std::string, std::vector<Block>>(key, v));
    }
}

void Header::writeExtraField(FILE *fileName, const std::string &key, char *field_extra){
    if(*field_extra=='y'){
        auto v = extraField.find(key);
        if(v!=extraField.end()){
            for(auto &b: v->second){
                b.write(fileName);
            }
        }
    }
}

void Header::setMode(const fs::file_status &fss){
    if(fs::is_directory(fss)){
        *mode = MODE_DIR;
    }else if(fs::is_symlink(fss)){
        *mode = MODE_SYM;
        std::cout << "识别为symlink了！！！！！！！！！！！！" << std::endl;
    }else if(fs::is_regular_file(fss)){
        *mode = MODE_REG;
    }
}

void Header::printHead(){
    std::cout<<" name: " <<getName()<< '\n'
             <<" mode: " <<getMode()<< '\n'
             <<" size: " <<getSize()<< '\n'
            <<std::endl;
}

void Header::read(std::istream &is){
    Block::read(is);
    readExtraField(is, "name", name, name_extra);
}
void Header::write(std::ostream &os){
    Block::write(os);
    writeExtraField(os, "name", name_extra);
}
void Header::readExtraField(std::istream &is, const std::string &key,char *field, char *field_extra){
    int nameLength = 0;
    if(*field_extra == 'y'){
        std::vector<Block> v;
        nameLength = atoi(field);
        while(nameLength > 0){
            //printf("读了一块额外内容\n");
            Block b;
            b.read(is);
            v.push_back(b);
            nameLength -= 512;
        }
        extraField.insert(std::pair<std::string, std::vector<Block>>(key, v));
    }
}
void Header::writeExtraField(std::ostream &os, const std::string &key, char *field_extra){
    if(*field_extra=='y'){
        auto v = extraField.find(key);
        if(v!=extraField.end()){
            for(auto &b: v->second){
                b.write(os);
            }
        }
    }
}
