#include "View/mainwindow.h"
#include <QApplication>

#include "Model/Container/intervaltree.h"

#include <string>
#include <list>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    IntervalTree<std::string, int, 0, 10000> tree;

    // insert(value, low, high)
    tree.insert("1", 1, 3000);
    tree.insert("2", 5, 7000);
    tree.insert("3", 1000, 3000);
    tree.insert("4", 600, 3500);
    tree.insert("5", 450, 1800);
    tree.insert("6", 8000, 10000);
    tree.insert("7", 1, 3000);
    tree.insert("8", 5000, 10000);
    tree.insert("9", 100, 200);
    tree.insert("10", 1, 10);


    std::list<std::string*> results = tree.searchAll(1500, 6000);

    std::cout << "Intersezioni: ";
    for(std::string* result : results)
        std::cout << *result << " ";
    std::cout << std::endl;

    return 0;
}
