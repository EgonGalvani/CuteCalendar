#ifndef VIEWPROMEMORIA_H
#define VIEWPROMEMORIA_H

#include <QTimeEdit>
#include <QSpinBox>


#include "modview.h"
#include "../Model/Hierarchy/reminder.h"

class ViewReminder : public ModView {
    Q_OBJECT

    //Elementi della view
    QTimeEdit* inizio;
    QTimeEdit* fine;
    QSpinBox* alert;
    QSpinBox* urgency;

    QCheckBox* checkRep;

    QLabel* urg;
    QLabel* alertL;
    QLabel* start;
    QLabel* end;

public:
    explicit ViewReminder(QWidget *parent = 0);
    ~ViewReminder() = default;

    void setEnabled(bool) override;
    void pushSaves(const Model::It&) const override;
    void fillView(const Model::It&) override;
    bool checkPushable(QString&) const override;
    virtual Reminder* createEvent(const QDate& date) const override;
};

#endif // VIEWPROMEMORIA_H
