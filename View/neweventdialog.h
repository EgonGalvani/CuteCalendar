#ifndef NEWEVENT_H
#define NEWEVENT_H

#include "viewworkout.h"
#include "viewbirthday.h"
#include "viewmeeting.h"
#include "viewreminder.h"
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

class NewEventDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewEventDialog(QDialog *parent = nullptr);
    ~NewEventDialog() = default;

signals:
    void newEventCreated(Event*);

private:
    QVBoxLayout* mainLayout;
    QComboBox* selEvento;
    QVBoxLayout* selLayout ;
    QVBoxLayout* eventLayout;

    ModView* view;

    void initComboBox();
    void deleteLayout(QLayout*);

private slots:
    void changedSel(int);
    void addPushed();
};

#endif // NEWEVENT_H
