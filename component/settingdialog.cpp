#include "settingdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QBoxLayout>
#include <QMessageBox>
#include "pathselectedit.h"
#include "../utils/config_utils.h"
SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("设置");
    setFixedSize(500, 300);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->setContentsMargins(10, 10, 10, 10);

    QHBoxLayout *layout1 = new QHBoxLayout();
    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout1);
    pathSelectEdit = new PathSelectEdit();
    pathSelectEdit->setText(QString::fromStdString(ConfigUtils::readConfig().getDownloadPath()));
    layout1->addWidget(new QLabel("下载路径："));
    layout1->addWidget(pathSelectEdit);
    mainLay->addWidget(widget1);

    QHBoxLayout *layout2 = new QHBoxLayout();
    QWidget *widget2 = new QWidget();
    widget2->setLayout(layout2);
    QPushButton *clearCacheBtn = new QPushButton("清除");
    layout2->addWidget(new QLabel("清除缓存："));
    layout2->addWidget(clearCacheBtn, Qt::AlignLeft);
    layout2->addStretch(1);
    mainLay->addWidget(widget2);
    connect(clearCacheBtn, &QPushButton::clicked, []() {
        ConfigUtils::clearCache();
    });


    // 创建按钮框
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    // 连接按钮框的 accepted 和 rejected 信号到 QDialog 的 accept 和 reject 槽
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingDialog::checkBeforeClosing);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    // 将按钮框添加到布局
    mainLay->addStretch(1);
    mainLay->addWidget(buttonBox);
}

void SettingDialog::checkBeforeClosing()
{
//    if (name->text().isEmpty() || host->text().isEmpty() || port->text().isEmpty()
//        || username->text().isEmpty() || passwd->text().isEmpty()) {
//        QMessageBox::warning(this, tr("警告"), tr("不能输入为空"));
//    } else {
//        // 如果文本不为空，则正常关闭对话框
//        accept();
//    }
    Config config;
    config.setDownloadPath(pathSelectEdit->text().toStdString());
    if (ConfigUtils::writeConfig(config)) {
        accept();
    }
}
