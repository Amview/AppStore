//
// Created by hua on 2024/9/6.
//

#ifndef APPSTORE_QJSON_UTILS_H
#define APPSTORE_QJSON_UTILS_H
#include <QObject>
#include <string>
#include <QJsonObject>
using namespace std;
class QJsonUtils : public QObject {
    Q_OBJECT
public:
    static string getString(const QJsonObject& obj, const string& key);

    static QJsonObject getObject(const QJsonObject& obj, const string& key);

    static map<string, string> object2map(const QJsonObject& obj);

    static QJsonDocument readJsonFile(const string& file_path);

};


#endif //APPSTORE_QJSON_UTILS_H
