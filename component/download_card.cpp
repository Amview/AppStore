//
// Created by hua on 2024/9/7.
//

#include <QHBoxLayout>
#include <QLabel>
#include "download_card.h"

DownloadCard::DownloadCard(QWidget *parent) : QWidget(parent) {
    layout = new QHBoxLayout();
    setFixedWidth(100);
    setLayout(layout);
    arch_label = new QLabel("Q");
    url_label = new QLabel("1");
    layout->addWidget(arch_label);
    layout->addWidget(url_label);
}

void DownloadCard::setUrl(const QString &url) {
    url_label->setText(url);
}

void DownloadCard::setArch(const QString &arch) {
    arch_label->setText(arch);
}

