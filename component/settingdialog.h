#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "pathselectedit.h"
#include "customlineedit.h"
class SettingDialog : public QDialog
{
public:
    PathSelectEdit *pathSelectEdit;
    CustomLineEdit *appsUrlEdit;

    SettingDialog(QWidget *parent = nullptr);

private slots:
    void checkBeforeClosing();
};

#endif // CONNECTDIALOG_H
