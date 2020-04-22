#include "View/mainwindow.h"
#include <QApplication>

#include "Model/Container/intervaltree.h"

#include <string>
#include <list>

#include "Model/DataType/time.h"

int main(int argc, char *argv[]) {
 /*   QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    IntervalTree<std::string, int, 0, 10000> tree;

    // insert(value, low, high)
   /* tree.insert("1", 1, 3000);
    tree.insert("2", 5, 7000);
    tree.insert("3", 1000, 3000);
    tree.insert("4", 600, 3500);
    tree.insert("5", 450, 1800);
    tree.insert("6", 8000, 10000);
    tree.insert("7", 1, 3000);
    tree.insert("8", 5000, 10000);
    tree.insert("9", 100, 200);
    tree.insert("10", 1, 10);
    tree.insert("11", 4000, 4000);


    std::list<IntervalTree<std::string, int, 0, 10000>::BaseIterator> results = tree.findAll(1500, 6000);
    for(IntervalTree<std::string, int, 0, 10000>::BaseIterator result : results) {
        std::cout << *result << " ";
    }

    std::cout << std::endl;*/

    tree.insert("1", 1, 10);
    tree.insert("3", 3, 10);
    tree.insert("2", 2, 10);
    tree.insert("6", 6, 10);
    tree.insert("4", 4, 10);
    tree.insert("5", 5, 10);
    tree.insert("7", 7, 10);


    std::cout << "Prova iteratori: ";
    for(auto it = tree.begin(); it != tree.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // test time.h

    Time t;
    std::cout << t.toString("hh:mm:ss") << std::endl;
    std::cout << t.toString("h:mm:s") << std::endl;
    std::cout << t.toString("h:m:s") << std::endl;


    return 0;
}
