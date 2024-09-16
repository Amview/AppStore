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
#include "../utils/layout_utils.h"
#include "customlineedit.h"
SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("设置");
    setMinimumSize(500, 300);

    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->setContentsMargins(10, 10, 10, 10);
    setLayout(mainLay);

    QFormLayout *formLay = new QFormLayout();
    QWidget *formWt = new QWidget();
    formLay->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formWt->setMinimumWidth(500);
    formWt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    formWt->setLayout(formLay);
    formLay->setLabelAlignment(Qt::AlignRight);
    pathSelectEdit = new PathSelectEdit();
    pathSelectEdit->setText(QString::fromStdString(ConfigUtils::readConfig().getDownloadPath()));
    formLay->addRow("下载路径：", pathSelectEdit);
    QPushButton *clearCacheBtn = new QPushButton("清除");
    clearCacheBtn->setFixedSize(50, 25);
    clearCacheBtn->setStyleSheet(R"(
        QPushButton {
            height: 25px;
            background-color: #fff;
            color: #606266;
            border-radius: 5px;
            border: 1px solid #dddfe5;
            margin-left: 0px;
        }
        QPushButton:hover {
            background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
    )");
    connect(clearCacheBtn, &QPushButton::clicked, []() {
        ConfigUtils::clearCache();
        QMessageBox::information(nullptr, "", "清除缓存成功");
    });
    formLay->addRow("清除缓存：", clearCacheBtn);
    appsUrlEdit = new CustomLineEdit();
    appsUrlEdit->setText(QString::fromStdString(ConfigUtils::readConfig().getAppsUrl()));
    formLay->addRow("应用更新地址：", appsUrlEdit);

    QPushButton *updateAppsBtn = new QPushButton("更新");
    updateAppsBtn->setFixedSize(50, 25);
    updateAppsBtn->setStyleSheet(R"(
        QPushButton {
            height: 25px;
            background-color: #fff;
            color: #606266;
            border-radius: 5px;
            border: 1px solid #dddfe5;
            margin-left: 0px;
        }
        QPushButton:hover {
            background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
    )");
    formLay->addRow("", updateAppsBtn);
    connect(updateAppsBtn, &QPushButton::clicked, []() {
       ConfigUtils::updateAppsConfig();
    });

    // 创建按钮框
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    // 连接按钮框的 accepted 和 rejected 信号到 QDialog 的 accept 和 reject 槽
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingDialog::checkBeforeClosing);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLay->addWidget(formWt);
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
    config.setAppsUrl(appsUrlEdit->text().toStdString());
    if (ConfigUtils::writeConfig(config)) {
        accept();
    }
}
