//
// Created by 86189 on 2020/12/20.
//

#ifndef PATH_CHINESE_TEST_CONVERTGBK_H
#define PATH_CHINESE_TEST_CONVERTGBK_H

#include <iostream>
#include <windows.h>
#include <QString>

std::string GbkToUtf8(const char *src_str);
std::wstring GbkToWString(const char *src_str);
std::string WStringToGbk(const wchar_t *wstr);
std::string Utf8ToGbk(const char *src_str);
std::wstring Utf8ToWString(const char *src_str);
std::string WStringToUtf8(const wchar_t *wstr);

std::string GbkToUtf8(const std::string &src);
std::wstring GbkToWString(const std::string &src_str);
std::string WStringToGbk(const std::wstring &wstr);
std::string Utf8ToGbk(const std::string &src_str);
std::wstring Utf8ToWString(const std::string &src_str);
std::string WStringToUtf8(const std::wstring &wstr);

QString GbkToQ(const std::string &src);
QString GbkToQ(const char *src);
std::string QToGbk(const QString &q);

void testConvert(const std::string &s);
void testQ(const std::string &s);


#endif //PATH_CHINESE_TEST_CONVERTGBK_H
