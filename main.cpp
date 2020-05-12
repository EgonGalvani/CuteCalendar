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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}


