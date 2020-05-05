#ifndef NEWEVENT_H
#define NEWEVENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

class NewEvent : public QDialog {
    Q_OBJECT

public:
    explicit NewEvent(QDialog *parent = nullptr);
    ~NewEvent();

private:

};

#endif // NEWEVENT_H
