//
// Created by hua on 2024/9/6.
//

#ifndef APPSTORE_CONFIG_UTILS_H
#define APPSTORE_CONFIG_UTILS_H


#include "../domain/app_info.h"
#include "../domain/config.h"
#include <QNetworkReply>
class ConfigUtils : public QObject{
Q_OBJECT
public:
    static const string cachePath;
    static const string configPath;
    static const string appsPath;

    static vector<AppInfo*> readApps();
    static Config readConfig();
    static bool updateAppsConfig();
    static bool writeConfig(Config& config);
    static bool createDir(const string& dir);
    static bool clearCache();

private:
//    static QNetworkReply *reply;
};


#endif //APPSTORE_CONFIG_UTILS_H
