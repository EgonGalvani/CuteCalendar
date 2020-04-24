#include "View/mainwindow.h"
#include <QApplication>

#include "Model/DataType/date.h"

int main(int argc, char *argv[]) {
  /*  QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    Date d;
    std::cout << d << std::endl;
    std::cout << d.dayOfWeek() << std::endl;

    return 0;
}
