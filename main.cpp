#include "View/mainwindow.h"
#include <QApplication>

#include "Model/DataType/date.h"
#include "Model/Container/intervaltree.h"

int main(int argc, char *argv[]) {
 /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    IntervalTree<std::string, Date> tree;
    tree.insert("1", Date(2020, 4, 10), Date(2021, 5, 10));
    tree.insert("2", Date(1998, 7, 10), Date(2000, 5, 10));
    tree.insert("3", Date(2008, 4, 10), Date(2010, 5, 10));
    tree.insert("4", Date(2009, 8, 10), Date(2009, 12, 10));
    tree.insert("5", Date(2050, 10, 10), Date(2070, 5, 10));
    tree.insert("6", Date(2070, 1, 10), Date(2070, 5, 10));
    tree.insert("7", Date(2020, 12, 10), Date(2021, 5, 10));

  std::cout << tree._root->_maxBoundChild << std::endl;
    auto it = tree.end();
       --it;
    std::cout << *it << std::endl;

    tree.erase(it);

   // tree.insert("100", Date(2100, 10, 10), Date(2200, 10, 10));

    std::cout << tree._root->_maxBoundChild << std::endl;

    return 0;
}
