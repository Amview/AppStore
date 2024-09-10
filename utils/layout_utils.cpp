//
// Created by hua on 2024/9/7.
//

#include "layout_utils.h"
#include <QLayout>
#include <QWidget>
#include <QLayoutItem>

void LayoutUtils::clearLayout(QLayout *layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        widget->deleteLater();
        delete item; // 删除布局项
    }
}
