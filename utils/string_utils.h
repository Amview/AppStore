//
// Created by hua on 2024/9/8.
//

#ifndef APPSTORE_STRING_UTILS_H
#define APPSTORE_STRING_UTILS_H


#include <QObject>
#include <string>

using namespace std;
class StringUtils : public QObject {
Q_OBJECT
public:
    StringUtils();
    static vector<string> splitStr(const string& s, const string& split);
    static bool contains(const std::string& mainStr, const std::string& subStr);
    static string getFileNameFromUrl(const string& url);
};


#endif //APPSTORE_STRING_UTILS_H
