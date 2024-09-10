//
// Created by hua on 2024/9/8.
//

#ifndef APPSTORE_HTTP_UTILS_H
#define APPSTORE_HTTP_UTILS_H
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <QObject>
#include <string>
#include <httplib.h>
using namespace std;
class HttpUtils : public QObject {
Q_OBJECT
public:
    struct UrlPart
    {
        string host;
        string path;
        string lastPart;
    };
    HttpUtils();
    static void download(const string& url, httplib::Progress process);
    static UrlPart analyseUrl(const string& url);
};


#endif //APPSTORE_HTTP_UTILS_H
