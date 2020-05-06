#include <QApplication>

#include "View/mainwindow.h"
#include "Model/DataType/date.h"
#include "Model/DataType/time.h"
#include "Model/Container/unorderedmultimap.h"
#include "Model/Hierarchy/event.h"
#include "Model/Hierarchy/workout.h"

int main(int argc, char *argv[]) {


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    /*
    std::cout<<"a";
    Time t1 = Time();
    Time t2 = Time();
    Date d1 = Date();
    std::vector<std::string>* vettoreTag = new std::vector<std::string>();
    vettoreTag->push_back("Fit");
    vettoreTag->push_back("Insta");
    vettoreTag->push_back("ValtonGay");
    Event* e1 = new Workout(0,t1,t2,"palestra","sollevamento pesi","casa",d1,vettoreTag);
    std::cout<<"a";
    std::cout<<e1->getName();
    */




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

    // test time.h
    Time t;
    std::cout << t.toString("hh:mm:ss") << std::endl;
    std::cout << t.toString("h:mm:s") << std::endl;
    std::cout << t.toString("h:m:s") << std::endl;

    return 0;
    */
}
