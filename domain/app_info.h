//
// Created by hua on 2024/9/6.
//

#ifndef APPSTORE_APP_INFO_H
#define APPSTORE_APP_INFO_H
#include <string>
#include <map>
#include <QObject>
using namespace std;

class AppInfo : public QObject {
Q_OBJECT
private:
    string name;
    string description;
    string logoUrl;
    string webUrl;
    string category;
    map<string, string> windowsUrl;
    map<string, string> linuxUrl;
    map<string, string> macOSUrl;
public:
    const string &getName() const;

    void setName(const string &name);

    const string &getDescription() const;

    void setDescription(const string &description);

    const string &getLogoUrl() const;

    void setLogoUrl(const string &logoUrl);

    const string &getWebUrl() const;

    void setWebUrl(const string &webUrl);

    const string &getCategory() const;

    void setCategory(const string &category);

    const map<string, string> &getWindowsUrl() const;

    void setWindowsUrl(const map<string, string> &windowsUrl);

    const map<string, string> &getLinuxUrl() const;

    void setLinuxUrl(const map<string, string> &linuxUrl);

    const map<string, string> &getMacOsUrl() const;

    void setMacOsUrl(const map<string, string> &macOsUrl);

};


#endif //APPSTORE_APP_INFO_H
