#ifndef MSGSCHEDULER_H
#define MSGSCHEDULER_H

#include <vector>
#include <QTimer>
#include <QWidget>
#include <QObject>
#include <unordered_map>

// classe usata per lo scheduling di messaggi
class MsgScheduler : public QObject {
    Q_OBJECT

    // lista di timer attivi
    std::vector<QTimer*> timers;

    // associazione tra timer e messaggio che deve essere mostrato
    std::unordered_map<int, std::string> msgs;

    // metodo per la rimozione di un timer
    void removeTimer(QTimer*);

private slots:
    // slot che si occupa della gestione del signal generato allo scadere di ogni timer
    void ontimeout();

signals:
    // segnale generato dalla classe allo scadere dei timer, indica il messaggio che deve essere mostrato
    void timeout(std::string);

public:
    MsgScheduler(QObject * = nullptr);

    // reset delle informazioni contenute, con relativa distruzione dei timer
    // precedentemente creati
    void clear();

    // aggiunta di un nuovo messaggio da mostrare
    void addMsg(const std::string&, int);

    ~MsgScheduler();
};

#endif // MSGSCHEDULER_H
