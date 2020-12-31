//
// Created by 86189 on 2020/12/20.
//
#include "ConvertGBK.h"
void testConvert(const std::string &s){
    std::cout<<"s = "<<s<<"\n"
            <<"s->utf8 = "<<GbkToUtf8(s)<<"\n"
            <<"s->gbk = "<<Utf8ToGbk(s)<<"\n"
            <<"s->utf8->gbk = "<<Utf8ToGbk(GbkToUtf8(s))<<"\n"
            <<"s->gbk->utf8 = "<<GbkToUtf8(Utf8ToGbk(s))<<"\n"
            <<"s->wstring->gbk = "<<WStringToGbk(GbkToWString(s))<<"\n"
            //<<"s->wstring->utf8 = "<<WStringToGbk(GbkToWString(s))<<"\n"
            <<std::endl;
}
void testQ(const std::string &s)
{
    std::cout<<"s = "<<s<<"\n"
            <<"s->Q->gbk = "<<QToGbk(GbkToQ(s))<<"\n"
            <<std::endl;
}



std::string GbkToUtf8(const char *src_str)
{
    int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, nullptr, 0);
    auto* wstr = new wchar_t[len + 1]();
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char* str = new char[len + 1]();
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, nullptr, nullptr);
    std::string strTemp = str;
    delete[] wstr;
    delete[] str;
    return strTemp;
}

std::wstring GbkToWString(const char *src_str){
    int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, nullptr, 0);
    auto* wstr = new wchar_t[len + 1]();
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    std::wstring wTemp = wstr;
    delete[] wstr;
    return wTemp;
}
std::string WStringToGbk(const wchar_t *wstr){
    int len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto* str = new char[len+1]();
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, nullptr, nullptr);
    std::string sTemp = str;
    delete[] str;
    return sTemp;
}

std::wstring Utf8ToWString(const char *src_str){
    int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, nullptr, 0);
    auto* wstr = new wchar_t[len + 1]();
    MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wstr, len);
    std::wstring wTemp = wstr;
    delete[] wstr;
    return wTemp;
}
std::string WStringToUtf8(const wchar_t *wstr){
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto* str = new char[len+1]();
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, nullptr, nullptr);
    std::string sTemp = str;
    delete[] str;
    return sTemp;
}

std::string Utf8ToGbk(const char *src_str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, nullptr, 0);
    auto* wszGBK = new wchar_t[len + 1]();
    MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, nullptr, 0, nullptr, nullptr);
    char* szGBK = new char[len + 1]();
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, nullptr, nullptr);
    std::string strTemp(szGBK);
    delete[] wszGBK;
    delete[] szGBK;
    return strTemp;
}

std::string GbkToUtf8(const std::string &src){
    return GbkToUtf8(src.c_str());
}
std::wstring GbkToWString(const std::string &src_str){
    return GbkToWString(src_str.c_str());
}
std::string WStringToGbk(const std::wstring &wstr){
    return WStringToGbk(wstr.c_str());
}
std::wstring Utf8ToWString(const std::string &src_str){
    return Utf8ToWString(src_str.c_str());
}
std::string WStringToUtf8(const std::wstring &wstr){
    return WStringToUtf8(wstr.c_str());
}
std::string Utf8ToGbk(const std::string &src_str){
    return Utf8ToGbk(src_str.c_str());
}


QString GbkToQ(const std::string &src)
{
    return QString::fromLocal8Bit(src.c_str());
}

QString GbkToQ(const char *src)
{
    return QString::fromLocal8Bit(src);
}


std::string QToGbk(const QString &q)
{
    return q.toLocal8Bit().constData();
}


