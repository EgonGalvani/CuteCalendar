#ifndef NEWEVENT_H
#define NEWEVENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class NewEvent : public QWidget {
    Q_OBJECT

public:
    explicit NewEvent(QWidget *parent = nullptr);
    ~NewEvent();

private:

};

#endif // NEWEVENT_H
