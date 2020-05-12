#include <QApplication>

#include "View/mainwindow.h"
#include "Model/DataType/date.h"
#include "Model/DataType/time.h"
#include "Model/Container/unorderedmultimap.h"
#include "Model/Hierarchy/event.h"
#include "Model/Hierarchy/workout.h"
#include "Model/Hierarchy/reminder.h"
#include "Model/Hierarchy/meeting.h"
//#include <unistd.h>
#include <QFile>
#include <QJsonDocument>
 void writeToDisk(const QString path,const QJsonDocument & obj) {
     try {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(obj.toJson());
     }catch (...) {}
}
int main(int argc, char *argv[]) {

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
    std::cout<<e1->getName()<<std::endl;
    std::cout<<e1->hasTag("Fit")<<std::endl;
    e1->deleteTag("Fit");
    std::cout<<e1->hasTag("Fit")<<std::endl;
    std::cout<<"Finito?" << e1->isCompleted()<<std::endl;
    std::cout<<"Dur"<<e1->getDuration()<<std::endl;

    std::cout<<"b";
    Time tt1 = Time(10,30,30);
    Time tt2 = Time(12,30,30);
    Time alert = Time(9,30,30);
    Date dd1 = Date(22,02,20);
    std::vector<std::string>* tags = new std::vector<std::string>();
    tags->push_back("Bambino");
    tags->push_back("Scuola");
    tags->push_back("Genitore");
    Event* e2 = new Reminder(0,tt1,tt2,alert,true,"Figlio","prendere bambino a scuola","Scuola",
                             dd1,tags);
    std::cout<<e2->getDate()<<std::endl;
    std::cout<<e2->getName()<<std::endl;
    /*
    Meeting(std::vector<std::string> part, Time start,
            Time end, Time alert,bool repeat, std::string nome,std::string descr,
            std::string luogo,Date data,std::vector<std::string>* vettoreTag);
    */
    std::vector<std::string> par = std::vector<std::string>();
    par.push_back("danielegiachetto1999@gmail.com");
    par.push_back("valtontahiraj@gmail.com");
    Event* e3 = new Meeting(par,tt1,tt2,alert,true,"meet","incontro zoom",
                            "casa",dd1,tags);


    QJsonObject json;
    e2->serialize(json);
    writeToDisk("test2.persona",QJsonDocument(json));
    e1->serialize(json);
    writeToDisk("test1.persona",QJsonDocument(json));
    e3->serialize(json);
    writeToDisk("test3.persona",QJsonDocument(json));
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

    // test time.h
    Time t;
    std::cout << t.toString("hh:mm:ss") << std::endl;
    std::cout << t.toString("h:mm:s") << std::endl;
    std::cout << t.toString("h:m:s") << std::endl;

    return 0;
    */
}


