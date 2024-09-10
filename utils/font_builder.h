//
// Created by hua on 2024/9/7.
//

#ifndef APPSTORE_FONT_BUILDER_H
#define APPSTORE_FONT_BUILDER_H


#include <QFont>

class FontBuilder : public QObject{
Q_OBJECT
public:
    QFont font;
    explicit FontBuilder(QWidget* parent = nullptr) : QObject(parent) {

    };

    FontBuilder* setBold(bool enable) {
        font.setBold(enable);
        return this;
    }

    FontBuilder* setPointSize(int size) {
        font.setPointSize(size);
        return this;
    }

    QFont build() {
        return font;
    }
};




#endif //APPSTORE_FONT_BUILDER_H
