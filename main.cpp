#include <QApplication>

#include "View/mainwindow.h"
#include "Model/DataType/date.h"
#include "Model/Container/unorderedmultimap.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

  /*  UnorderedMultimap<Date, std::string> map;
    auto it = map.insert(Date(17, 11, 1999), "Egon");
    map.insert(Date(6, 5, 1997), "Asia");
    map.insert(Date(6, 5, 2000), "Anna");
    map.insert(Date(14, 2, 1966), "mamma");
    map.insert(Date(5, 5, 2100), "Asia");
    auto primo = map.insert(Date(7, 5, 19), "Asia");

    std::cout << "Chiavi: ";
    for(auto it = map.begin(); it != map.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    it = map.erase(it);
    map.erase(primo);
    std::cout << "Chiavi: ";
    for(auto it = map.begin(); it != map.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Nuova radice: " << *it << std::endl;

    for(auto it = map.begin(Date(14, 2, 1966)); it != map.end(Date(14, 2, 1966)); it++)
        std::cout << *it << std::endl;

    std::cout << "Chiavi: ";
    for(auto it = map.begin(); it != map.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl; */
}
