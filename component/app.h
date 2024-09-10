//
// Created by hua on 2024/9/7.
//

#ifndef APPSTORE_APP_H
#define APPSTORE_APP_H


#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <string>
#include <map>

using namespace std;
class App  : public QWidget {
Q_OBJECT
private:
    QLabel *name_label;
    QLabel *logo_label;
    QLabel *description_label;
    string web_url;
    QPushButton *web_btn;
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_reply;
    QWidget *downWidget;
    QVBoxLayout *downLayout;
public:
    explicit App(const string& name, QWidget *parent = nullptr);

    void init();

    void setAppName(const string& name);

    void setLogoUrl(const string& url);

    void setDescription(const string& description);

    void setWebUrl(const string& webUrl);

    void setWindowsUrl(const map<string, string> map);
};


#endif //APPSTORE_APP_H