#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QVBoxLayout>
#include "domain/app_info.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    vector<AppInfo*> appList;
    QListWidget *tagList;
    QVBoxLayout *appLayout;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();

    void readAppConfig();
    void loadApps(const string& category, const string& name);
    void loadCategories();
};
#endif // MAINWINDOW_H
