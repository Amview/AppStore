#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1000, 600);
    w.show();
    w.setStyleSheet(R"(
        QWidget#main {
            background: #ffffff;
        }
        QWidget#menuWidget {
            border-right: 1px solid #e6e6e6;
        }
        QListWidget {
            border: none;
        }
        QScrollArea {
            background: #ffffff;
            border-top: none;
        }
        QWidget#appWidget {
            background: #ffffff;

        }
    )");
    return a.exec();
}
