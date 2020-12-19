//
// Created by 86189 on 2020/12/20.
//

#ifndef PATH_CHINESE_TEST_CONVERTGBK_H
#define PATH_CHINESE_TEST_CONVERTGBK_H

#include <iostream>
#include <windows.h>

std::string GbkToUtf8(const char *src_str);
std::wstring GbkToWString(const char *src_str);
std::string WStringToGbk(const wchar_t *wstr);
std::string Utf8ToGbk(const char *src_str);

std::string GbkToUtf8(const std::string &src);
std::wstring GbkToWString(const std::string &src_str);
std::string WStringToGbk(const std::wstring &wstr);
std::string Utf8ToGbk(const std::string &src_str);

void testConvert(const std::string &s);


#endif //PATH_CHINESE_TEST_CONVERTGBK_H
