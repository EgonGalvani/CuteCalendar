#include "msgscheduler.h"
#include <iostream>
#include <algorithm>

MsgScheduler::MsgScheduler(QObject *parent)
    : QObject(parent) {}

void MsgScheduler::clear() {
    for(QTimer* timer : timers) {
        timer->stop();
        delete timer;
    }

    timers.clear();
    msgs.clear();
}

void MsgScheduler::addMsg(const std::string& msg, int msec) {
    QTimer *timer = new QTimer(this);
    timer->setInterval(msec);
    connect(timer, SIGNAL(timeout()), this, SLOT(ontimeout()));
    timer->start();

    timers.push_back(timer);
    msgs.emplace(timer->timerId(), msg);
}

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
    // rimuovo il messaggio telativo al timer
    msgs.erase(timer->timerId());

    // trovo il timer e lo rimuovo da quelli salvati
    auto timerIt = std::find(timers.begin(), timers.end(), timer);
    timers.erase(timerIt);

    // elimino il timer
    delete timer;
}

MsgScheduler::~MsgScheduler() {
    clear();
    // std::cout << "Cleaned from distructor" << std::endl;
}
