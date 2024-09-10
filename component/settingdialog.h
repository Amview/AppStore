#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>

class SettingDialog : public QDialog
{
public:
    QLineEdit *name;
    QLineEdit *host;
    QLineEdit *port;
    QLineEdit *username;
    QLineEdit *passwd;

    SettingDialog(QWidget *parent = nullptr);

private slots:
    void checkBeforeClosing();
};

#endif // CONNECTDIALOG_H
