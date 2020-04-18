#include "View/mainwindow.h"
#include <QApplication>

#include "Model/Container/intervaltree.h"

#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    IntervalTree<std::string, int, 0, 10000> tree;

    // insert(value, low, high)
    IntervalTree<std::string, int, 0, 10000>::BaseIterator it1 = tree.insert("ciao", 5, 20);
    std::cout << "Inserito correttamente: " << *it1 << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    IntervalTree<std::string, int, 0, 10000>::BaseIterator it2 =  tree.insert("prove", 4, 1000);
    std::cout << "Inserito correttamente: " << *it2 << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    IntervalTree<std::string, int, 0, 10000>::BaseIterator it3 =  tree.insert("a", 7, 500);
    std::cout << "Inserito correttamente: " << *it3 << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    IntervalTree<std::string, int, 0, 10000>::BaseIterator it4 = tree.insert("caso", 5, 10000);
    std::cout << "Inserito correttamente: " << *it4 << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Sono stati inseriti, in ordine: " << *it1 << "\t" << *it2 << "\t" << *it3 << "\t" << *it4 << std::endl;


    return 0;
}
