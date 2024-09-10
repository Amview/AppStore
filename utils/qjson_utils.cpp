//
// Created by hua on 2024/9/6.
//

#include "qjson_utils.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
string QJsonUtils::getString(const QJsonObject& obj, const string& key) {
    auto it = obj.find(QString::fromStdString(key));
    if (it != obj.end()) {
        return it.value().toString().toStdString();
    }
    return {};
}

QJsonObject QJsonUtils::getObject(const QJsonObject &obj, const std::string &key) {
    auto it = obj.find(QString::fromStdString(key));
    if (it != obj.end()) {
        return it.value().toObject();
    }
    return {};
}

map<string, string> QJsonUtils::object2map(const QJsonObject& obj) {
    map<string, string> map;
    for (QJsonObject::const_iterator it = obj.begin(); it != obj.end(); ++it) {
        map.insert(std::make_pair(it.key().toStdString(), it.value().toString().toStdString()));
    }
    return map;
}

QJsonDocument QJsonUtils::readJsonFile(const std::string &file_path) {
    QFile file(QString::fromStdString(file_path));
    QJsonDocument doc;
    if (!file.exists()) {
        return doc;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return doc;
    }
    QByteArray data = file.readAll();
    QJsonParseError jsonError;
    doc = QJsonDocument::fromJson(data, &jsonError);
    return doc;
}
