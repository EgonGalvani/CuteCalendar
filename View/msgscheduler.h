#ifndef MSGSCHEDULER_H
#define MSGSCHEDULER_H

#include <vector>
#include <QTimer>
#include <QWidget>
#include <QObject>
#include <unordered_map>

class MsgScheduler : public QObject {
    Q_OBJECT

    std::vector<QTimer*> timers;
    std::unordered_map<int, std::string> msgs;

    void removeTimer(QTimer*);

private slots:
    void ontimeout();

signals:
    void timeout(std::string);

public:
    MsgScheduler(QObject * = nullptr);
    void clear();
    void addMsg(const std::string&, int);

    ~MsgScheduler();
};

#endif // MSGSCHEDULER_H
