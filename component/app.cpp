//
// Created by hua on 2024/9/7.
//

#include <QVBoxLayout>
#include <QPushButton>
#include <QDesktopServices>
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <future>
#include "app.h"
#include "../utils/string_utils.h"
#include "../utils/http_utils.h"
#include "../utils/font_builder.h"
#include "../utils/config_utils.h"

App::App(const string& name, QWidget *parent) : QWidget(parent){
    QGridLayout *mainLayout = new QGridLayout();
//    mainLayout->setVerticalSpacing(0);
//    mainLayout->setSpacing(5);
    setLayout(mainLayout);
    setObjectName("App");
    setStyleSheet(R"(
        QWidget#App{
            border: 1px solid lightgray;
        }
    )");
    QPushButton *down_btn = new QPushButton("下载");
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    down_btn->setFont(font);
    down_btn->setFixedSize(60, 22);
    down_btn->setCursor(Qt::PointingHandCursor);
    down_btn->setStyleSheet(R"(
        border-radius: 11px;
        color: #3478f6;
        background:#f2f2f7;
    )");

    web_btn = new QPushButton("官网");
    web_btn->setCursor(Qt::PointingHandCursor);
    web_btn->setFixedSize(50, 50);
    web_btn->setFont(font);
    web_btn->setStyleSheet(R"(
        border: none;
        color: #3478f6;
    )");
    web_btn->hide();

    name_label = new QLabel();
    name_label->setText(QString::fromStdString(name));
    name_label->setStyleSheet("font-weight:bold;font-size: 15px;");
    description_label = new QLabel();
    description_label->setStyleSheet("color:gray;font-size: 12px;");
    logo_label = new QLabel();
    logo_label->setFixedSize(50, 50);
    QPixmap logoPix(":/resource/AppStore.png");
    logo_label->setPixmap(logoPix);

    downLayout = new QVBoxLayout();
    downWidget = new QWidget();
    downWidget->setLayout(downLayout);
    downWidget->setFixedHeight(100);
    downWidget->setObjectName("downWidget");
    downWidget->setStyleSheet(R"(
        QWidget#downWidget{
            border: 1px solid #e6e6e6;
            border-radius: 5px;
        }
    )");
    downWidget->hide();
    connect(down_btn, &QPushButton::clicked, [this]() {
        if (downWidget->isHidden()) {
            downWidget->show();
        } else {
            downWidget->hide();
        }
    });
    connect(web_btn, &QPushButton::clicked, [this]() {
        QUrl url(QString::fromStdString(web_url));
        QDesktopServices::openUrl(url);
    });
    mainLayout->addWidget(logo_label, 0, 0, 2, 1);
    mainLayout->addWidget(name_label, 0, 1, 1, 1, Qt::AlignBottom);
    mainLayout->addWidget(description_label, 1, 1, 1, 1, Qt::AlignTop);
    mainLayout->addWidget(web_btn, 0, 2, 2, 1);
    mainLayout->addWidget(down_btn, 0, 3, 2, 1);
    mainLayout->addWidget(downWidget, 2, 0, 1, 4);
}

void App::setAppName(const string& name) {
    name_label->setText(QString::fromStdString(name));
}

void App::setDescription(const std::string &description) {
    description_label->setText(QString::fromStdString(description));
}

void App::setLogoUrl(const string& url) {
    if (url.empty()) {
        return;
    }
    string logoCachePath = ConfigUtils::cachePath + "/" + name_label->text().toStdString();
    if (!ConfigUtils::createDir(logoCachePath)) {
        return;
    }
    QFile logoFile(QString::fromStdString(logoCachePath + "/" + StringUtils::getFileNameFromUrl(url)));
    if (logoFile.exists() && logoFile.open(QIODevice::ReadOnly)) {
        QPixmap pixmap;
        pixmap.loadFromData(logoFile.readAll());
        logo_label->setPixmap(pixmap.scaled(logo_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        logoFile.close();
        return;
    }
    // 创建QNetworkAccessManager实例
    m_networkManager = new QNetworkAccessManager(this);
    // 设置图片URL
    QUrl imageUrl(QString::fromStdString(url));
    // 发送GET请求
    QNetworkRequest request(imageUrl);
    m_reply = m_networkManager->get(request);
    connect(m_reply, &QNetworkReply::finished, [this, logoCachePath, url]() {
        // 检查回复的状态码
        if (m_reply->error() == QNetworkReply::NoError) {
            // 读取图片数据
            QByteArray imageData = m_reply->readAll();
            // 将字节数组转换为QPixmap
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            // 显示图片
            logo_label->setPixmap(pixmap.scaled(logo_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // 写入文件
            string filename = StringUtils::getFileNameFromUrl(url);
            qDebug() << "文件路径" << logoCachePath + "/" + filename;
            QFile file(QString::fromStdString(logoCachePath + "/" + filename));
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件用于写入
                qDebug() << "Could not open file:" << filename;
                return;
            }
            file.write(imageData);
            file.close();
            qDebug() << "文件下载完成" << filename;
        } else {
            // 如果发生错误，显示错误信息
            qDebug() << "Error downloading image:" << m_reply->errorString();
        }
        // 清理资源
        m_reply->deleteLater();
    });
}

void App::setWebUrl(const std::string &webUrl) {
    web_url = webUrl;
    if (!webUrl.empty()) {
        web_btn->show();
    }
}

void App::setWindowsUrl(const map<string, string> map) {
    if (map.empty()) {
        return;
    }
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    QPixmap pixmap(":/resource/windows.svg");
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    layout->addWidget(imageLabel);

    for (const auto &item: map) {
        QPushButton *btn = new QPushButton(QString::fromStdString(item.first));
        QFont font;
        font.setBold(true);
        font.setPointSize(12);
        btn->setFont(font);
        btn->setFixedSize(60, 22);
//        btn->setFixedHeight(22);
//        btn->setMinimumWidth(60);
//        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            border-radius: 11px;
            color: #3478f6;
            background:#f2f2f7;
        )");
        btn->setToolTip(QString::fromStdString(item.second));
        connect(btn, &QPushButton::clicked, [item, btn]()  {
            if (btn->text() == "打开") {
                QString homePath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
                QUrl url(homePath);
                url.setScheme("file");
                // 使用 QDesktopServices 打开文件管理器
                if (!QDesktopServices::openUrl(url)) {
                    QMessageBox::warning(btn, tr("Open Directory"),
                                         tr("Could not open directory"));
                }
                return;
            }
            std::thread th([&](){
                HttpUtils::download(item.second, [&](uint64_t len, uint64_t total) {
                    printf("%lld / %lld bytes => %d%% complete\n",
                           len, total,
                           static_cast<int>(len * 100 / total));
                    if (len == total) {
                        btn->setText("打开");
                    } else {
                        btn->setText(QString::number(len * 100 / total) + "%");
                    }
                    return true; // 返回'false'以取消请求。
                });
            });
            th.detach();
        });
        layout->addWidget(btn);
    }
    layout->addStretch(1);
    downLayout->addWidget(widget);
    downLayout->addStretch(1);
}


