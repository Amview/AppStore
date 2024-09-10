//
// Created by hua on 2024/9/7.
//

#ifndef APPSTORE_DOWNLOAD_CARD_H
#define APPSTORE_DOWNLOAD_CARD_H


#include <QWidget>
#include <QLabel>
#include <string>
#include <QHBoxLayout>

using namespace std;
class DownloadCard : public QWidget {
Q_OBJECT
private:
    QHBoxLayout *layout;
    QLabel *arch_label;
    QLabel *url_label;
public:
    explicit DownloadCard(QWidget *parent = nullptr);

    void setArch(const QString& arch);

    void setUrl(const QString& url);

};


#endif //APPSTORE_DOWNLOAD_CARD_H
