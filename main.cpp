#include <QApplication>

#include "View/mainwindow.h"
#include "Model/DataType/date.h"
#include "Model/Container/unorderedmultimap.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
