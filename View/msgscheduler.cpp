#include "msgscheduler.h"
#include <iostream>
#include <algorithm>

MsgScheduler::MsgScheduler(QObject *parent)
    : QObject(parent) {}

// eliminazione dei timer attivi e dei relativi messaggi
void MsgScheduler::clear() {
    for(QTimer* timer : timers) {
        timer->stop();
        delete timer;
    }

    timers.clear();
    msgs.clear();
}

/* aggiunta di un nuovo messaggio e del relativo timer
 @param msg: messaggio
 @msec: numero di millisecondi che devono essere attesi prima di generare il signal relativo al messaggio
*/
void MsgScheduler::addMsg(const std::string& msg, int msec) {
    QTimer *timer = new QTimer(this);
    timer->setInterval(msec);
    connect(timer, SIGNAL(timeout()), this, SLOT(ontimeout()));
    timer->start();

    timers.push_back(timer);
    msgs.emplace(timer->timerId(), msg);
}

// slot che si occupa della gestione del signal generato dai singoli timer
void MsgScheduler::ontimeout() {
    QTimer* timer = qobject_cast<QTimer*>(sender());
    if(timer) {
        emit timeout(msgs.at(timer->timerId()));

        // fermo il timer e lo elimino
        timer->stop();
        removeTimer(timer);
    }
}

void MsgScheduler::removeTimer(QTimer* timer) {
    // il messaggio associato al timer viene rimosso
    msgs.erase(timer->timerId());

    // il timer viene trovato e rimosso da quelli salvati
    auto timerIt = std::find(timers.begin(), timers.end(), timer);
    timers.erase(timerIt);

    // distruzione del timer
    delete timer;
}

MsgScheduler::~MsgScheduler() {
    clear(); // rimozione di tutte le informazioni dalla classe (in particolare vegono distrutti i timer attivi)
}
