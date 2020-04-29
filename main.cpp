#include "View/mainwindow.h"
#include <QApplication>

#include "Model/DataType/date.h"
#include "Model/Container/intervaltree.h"
#include "Model/DataType/deepptr.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

   // DeepPtr<int> p(new int(5));
  //  std::cout << *p << std::endl;

   // return 0;
}
