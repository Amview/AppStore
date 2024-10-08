#include "pathselectedit.h"

PathSelectEdit::PathSelectEdit(QWidget *parent) : QLineEdit(parent){
    initUi();
}

PathSelectEdit::PathSelectEdit(const QString &s, QWidget *parent)
    : QLineEdit(s, parent) {
    initUi();
};

void PathSelectEdit::initUi() {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setFixedHeight(25);
    this->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #dddfe5;
            background-color: #f5f7fa;
            border-radius: 5px;
            padding-left: 5px;
            color: #555555;
        }
        QLineEdit:hover {
            //background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
//        QLineEdit:focus {
//            border: 1px solid #5b5bf1;
//        }
    )");
}
