#include <QApplication>
#include "View/mainwindow.h"

#include "Model/DataType/date.h"
#include <iostream>
#include <QDate>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
