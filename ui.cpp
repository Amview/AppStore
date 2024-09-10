//
// Created by hua on 2024/9/10.
//
#include "mainwindow.h"
#include <QGridLayout>
#include <QDesktopServices>
#include <QScrollArea>
#include <QListWidget>
#include "component/settingdialog.h"
#include "component/app.h"
#include "component/customlineedit.h"

void MainWindow::initUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    mainWidget->setObjectName("main");

    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setContentsMargins(0,0,0,0);
    QWidget *contentWidget = new QWidget();
    contentWidget->setLayout(contentLayout);

    QVBoxLayout *menuLayout = new QVBoxLayout();
    menuLayout->setContentsMargins(10,10,10,10);
    QWidget *menuWidget = new QWidget();
    menuWidget->setObjectName("menuWidget");
    menuWidget->setFixedWidth(200);
    menuWidget->setLayout(menuLayout);

    CustomLineEdit *search = new CustomLineEdit();
    menuLayout->addWidget(search);
    connect(search, &CustomLineEdit::returnPressed, [this, search]() {
        loadApps(string(), search->text().toStdString());
    });

    QHBoxLayout *btns = new QHBoxLayout();
    btns->setContentsMargins(0,0,0,0);
    QWidget *btnsWidget = new QWidget();
    btnsWidget->setStyleSheet("border:none");
    btnsWidget->setLayout(btns);

    QPushButton *settingBtn = new QPushButton("");
    settingBtn->setToolTip("设置");
    settingBtn->setFixedSize(20, 20);
    settingBtn->setIconSize(QSize(20, 20));
    settingBtn->setCursor(Qt::PointingHandCursor);
    settingBtn->setIcon(QIcon(":/resource/settings.png"));
    connect(settingBtn, &QPushButton::clicked, []() {
        SettingDialog dialog;
        dialog.exec();
    });
//    settingBtn->setStyleSheet("border:none");

    QPushButton *githubBtn = new QPushButton("");
    githubBtn->setFixedSize(20, 20);
    githubBtn->setCursor(Qt::PointingHandCursor);
    githubBtn->setIconSize(QSize(20, 20));
    githubBtn->setIcon(QIcon(":/resource/github.png"));
    githubBtn->setToolTip("https://github.com/Amview");
//    githubBtn->setStyleSheet("border:none");
    connect(githubBtn, &QPushButton::clicked, [this]() {
        QUrl url(QString::fromStdString("https://github.com/Amview"));
        QDesktopServices::openUrl(url);
    });

    btns->addWidget(settingBtn, Qt::AlignCenter);
    btns->addWidget(githubBtn, Qt::AlignCenter);
    btns->addStretch(1);
    tagList = new QListWidget();
    tagList->setStyleSheet(R"(
        QListWidget {
            background-color: transparent;
            border-right: none;
            font-weight: bold;
        }
        QListWidget::item {
            font-weight: bold;
            border-radius: 6px;
            padding-left: 3px;
            min-width: 100px;
            height: 30px;
            text-align: center;
            color: #515151;
            font-size: 20px;
        }
        QListWidget::item:hover{
        }
        QListWidget::item:selected {
            background-color: #4ea4eb;
            color: white;
        }
    )");
    menuLayout->addWidget(tagList);
    menuLayout->addWidget(btnsWidget);

    connect(tagList, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        loadApps(item->text().toStdString(), string());
        qDebug() << item->text();
    });

    appLayout = new QVBoxLayout();
    QWidget *appWidget = new QWidget();
    appWidget->setLayout(appLayout);
    appWidget->setObjectName("appWidget");

    // 创建一个滚动区域
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true); // 允许根据内容调整大小
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 水平滚动条按需显示
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); // 垂直滚动条按需显示
    scrollArea->setWidget(appWidget);

    contentLayout->addWidget(menuWidget);
    contentLayout->addWidget(scrollArea);

    mainLayout->addWidget(contentWidget);
    readAppConfig();
    loadApps(string(), string());
    loadCategories();
}