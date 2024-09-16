//
// Created by hua on 2024/7/29.
//

#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit(parent) {
    this->initUi();
}

void CustomLineEdit::initUi() {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setMinimumHeight(25);
    this->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #dddfe5;
            background-color: #fff;
            padding-left: 3px;
            border-radius: 6px;
            color: #606266;
        }

        QLineEdit:focus {
            border: 3px solid #7a98db;
        }
    )");
//    QLineEdit:hover {
//        background-color: #fbfdff;
//        border: 1px solid #c1c4cb;
//    }
}
