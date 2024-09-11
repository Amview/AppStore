//
// Created by hua on 2024/9/7.
//

#ifndef APPSTORE_LAYOUT_UTILS_H
#define APPSTORE_LAYOUT_UTILS_H


#include <QLayout>

class LayoutUtils {
public:

    static void clearLayout(QLayout* layout);
    static QWidget* createQWidget(QLayout* layout);

};


#endif //APPSTORE_LAYOUT_UTILS_H
