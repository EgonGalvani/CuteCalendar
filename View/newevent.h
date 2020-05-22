#ifndef NEWEVENT_H
#define NEWEVENT_H

#include "viewallenamento.h"
#include "viewcompleanno.h"
#include "viewmeeting.h"
#include "viewpromemoria.h"
#include "modview.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QCheckBox>

#include "../Model/Hierarchy/event.h"

class NewEvent : public QDialog {
    Q_OBJECT

public:
    explicit NewEvent(QDialog *parent = nullptr);
    ~NewEvent() = default;

signals:
    void newEventCreated(Event*);

private:
    QVBoxLayout* mainLayout;
    QComboBox* selEvento;
    QVBoxLayout* selLayout ;
    QVBoxLayout* eventLayout;

    ModView* view;



    void deleteLayout(QLayout*);
    void initComboBox();
    void initAllenamento();
    void initCompleanno();
    void initMeeting();
    void initPromemoria();

private slots:
    void changedSel(int);
    void addPushed();
};

#endif // NEWEVENT_H
