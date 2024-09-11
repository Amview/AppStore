#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "pathselectedit.h"

class SettingDialog : public QDialog
{
public:
    PathSelectEdit *pathSelectEdit;

    SettingDialog(QWidget *parent = nullptr);

private slots:
    void checkBeforeClosing();
};

#endif // CONNECTDIALOG_H
