#include "View/mainwindow.h"
#include <QApplication>

#include "Model/Container/vector.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
