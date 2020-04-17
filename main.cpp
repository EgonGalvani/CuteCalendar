#include "View/mainwindow.h"
#include <QApplication>

#include "Model/Container/intervaltree.h"

int main(int argc, char *argv[])
{
  /*  QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    IntervalTree<int, int, 10, 100> tree;

    return 0;
}
