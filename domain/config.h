//
// Created by hua on 2024/9/9.
//

#ifndef APPSTORE_CONFIG_H
#define APPSTORE_CONFIG_H
#include <QObject>
#include <string>

using namespace std;
class Config : public QObject{

Q_OBJECT
private:
    string downloadPath;
    string appsUrl;

public:
    Config();
    // 拷贝构造函数
    Config(const Config& other);

    const string &getDownloadPath() const {
        return downloadPath;
    }

    void setDownloadPath(const string &downloadPath) {
        Config::downloadPath = downloadPath;
    }

    const string &getAppsUrl() const;

    void setAppsUrl(const string &appsUrl);
};


#endif //APPSTORE_CONFIG_H
