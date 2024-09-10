//
// Created by hua on 2024/9/8.
//

#include "string_utils.h"

StringUtils::StringUtils() {

}

vector<string> StringUtils::splitStr(const string &s, const string &split) {
    std::vector<std::string> strs;
    size_t start = 0, end = 0;
    while ((end = s.find(split, start)) != std::string::npos) {
        strs.push_back(s.substr(start, end - start));
        start = end + 1;
    }
    strs.push_back(s.substr(start));
    return strs;
}

bool StringUtils::contains(const std::string &mainStr, const std::string &subStr) {
    // 使用 find 函数查找子字符串
    size_t found = mainStr.find(subStr);
    // 如果找到子字符串，返回 true；否则返回 false
    return found != std::string::npos;
}

string StringUtils::getFileNameFromUrl(const std::string &url) {
    vector<string> splits = splitStr(url, "/");
    return splits[splits.size() - 1];
}
