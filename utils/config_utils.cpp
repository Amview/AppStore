//
// Created by hua on 2024/9/6.
//

#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonArray>
#include "config_utils.h"
#include <iostream>
#include <QJsonObject>
#include "qjson_utils.h"
#include <vector>
#include "../domain/app_info.h"
using namespace std;
namespace fs = std::filesystem;
const string ConfigUtils::cachePath = "cache";
const string ConfigUtils::configPath = "/Users/hua/file/project/guthub/AppStore/config.json";
const string ConfigUtils::appsPath = "/Users/hua/file/project/guthub/AppStore/apps.json";

vector<AppInfo*> ConfigUtils::readApps() {
    vector<AppInfo*> list;
    QJsonDocument doc = QJsonUtils::readJsonFile(appsPath);
    if (!doc.isEmpty() && doc.isArray()) {
        QJsonArray array = doc.array();
        for (const auto &item: array) {
            if (item.isObject()) {
                QJsonObject appObj = item.toObject();
                AppInfo *appInfo = new AppInfo();
                list.push_back(appInfo);
                appInfo->setName(QJsonUtils::getString(appObj, "name"));
                appInfo->setDescription(QJsonUtils::getString(appObj, "description"));
                appInfo->setLogoUrl(QJsonUtils::getString(appObj, "logoUrl"));
                appInfo->setWebUrl(QJsonUtils::getString(appObj, "webUrl"));
                appInfo->setCategory(QJsonUtils::getString(appObj, "category"));
                QJsonObject windowsObj = QJsonUtils::getObject(appObj, "windowsUrl");
                if (!windowsObj.isEmpty()) {
                    appInfo->setWindowsUrl(QJsonUtils::object2map(windowsObj));
                }
                QJsonObject linuxObj = QJsonUtils::getObject(appObj, "linuxUrl");
                if (!linuxObj.isEmpty()) {
                    appInfo->setLinuxUrl(QJsonUtils::object2map(linuxObj));
                }
                QJsonObject macOSObj = QJsonUtils::getObject(appObj, "macOSUrl");
                if (!macOSObj.isEmpty()) {
                    appInfo->setMacOsUrl(QJsonUtils::object2map(macOSObj));
                }
            }
        }
    }
    return list;
}

bool ConfigUtils::writeConfig(Config &config) {
    QJsonObject obj;
    obj.insert("downloadPath", QJsonValue(config.getDownloadPath().data()));
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Indented);
    QFile file(QString::fromStdString(configPath));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (!file.write(data)) {
            qDebug() << "Failed to write data to file.";
            return false;
        }
        file.close();
        return true;
    }
    return false;
}


Config ConfigUtils::readConfig() {
    QJsonDocument doc = QJsonUtils::readJsonFile(configPath);
    Config config;
    if (!doc.isEmpty() && doc.isObject()) {
        config.setDownloadPath(QJsonUtils::getString(doc.object(), "downloadPath"));
    }
    return config;
}

bool ConfigUtils::createDir(const std::string &dir) {
    fs::path path(dir);
    if (!fs::exists(path)) {
        if (fs::create_directories(path)) {
            qDebug() << "创建文件夹成功" << dir;
        } else {
            qDebug() << "创建文件夹失败" << dir;
            return false;
        }
    } else {
        qDebug() << "文件夹已存在" << dir;
    }
    return true;
}

bool ConfigUtils::clearCache() {
    QDir dir(QString::fromStdString(cachePath));
    if (!dir.exists()) {
        return true;
    }

}