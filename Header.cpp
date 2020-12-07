#include "Header.h"

void Header::getFileInfo(std::string fileName){
    struct stat buf;
    stat(fileName.c_str(), &buf);
    struct tm *p = gmtime(&buf.st_atime);
    printf("%d %d %d", p->tm_year, p->tm_mon, p->tm_mday);
}