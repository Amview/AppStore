
#include <QScrollArea>
#include <QDesktopServices>
#include <filesystem>
#include "mainwindow.h"
#include "component/app.h"
#include "component/customlineedit.h"
#include "utils/config_utils.h"
#include <set>
#include "utils/layout_utils.h"
#include "utils/string_utils.h"
#include "blur_effect.h"
MainWindow::MainWindow(QWidget *parent)
    : CFramelessWindow(parent)
{
    initUI();
    ConfigUtils::createDir(ConfigUtils::cachePath);
}

MainWindow::~MainWindow() {}

void MainWindow::readAppConfig() {
    appList = ConfigUtils::readApps();
}

void MainWindow::loadApps(const string& category, const string& name) {
    LayoutUtils::clearLayout(appLayout);
    App *app;
    for (size_t i = 0; i < appList.size(); ++i) {
        auto item = appList[i];
        app = new App(item->getName());
        app->setLogoUrl(item->getLogoUrl());
        app->setDescription(item->getDescription());
        app->setWindowsUrl(item->getWindowsUrl());
        app->setWebUrl(item->getWebUrl());
        if (!category.empty()) {
            if (category != item->getCategory()) {
                continue;
            }
        }
        if (!name.empty()) {
            if (!StringUtils::contains(item->getName(), name)) {
                continue;
            }
        }
        appLayout->addWidget(app);
    }
    appLayout->addStretch(1);
    appLayout->update();
}

void MainWindow::loadCategories() {
    set<string> categories;
    for (const auto &item: appList) {
        if (!item->getCategory().empty()) {
            categories.insert(item->getCategory());
        }
    }
    for (const auto &item: categories) {
        tagList->addItem(QString::fromStdString(item));
    }
}