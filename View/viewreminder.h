#ifndef VIEWPROMEMORIA_H
#define VIEWPROMEMORIA_H

#include <QTimeEdit>
#include <QSpinBox>


#include "modview.h"
#include "../Model/Hierarchy/reminder.h"

class ViewPromemoria : public ModView {
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
    explicit ViewPromemoria(QWidget *parent = 0);
    ~ViewPromemoria() = default;

    void setEnabled(bool) override;
    void pushSaves(const Model::It&) const override;
    void fillView(const Model::It&) override;
    bool checkPushable(QString&) const override;
    virtual Reminder* createEvent(const QDate& date) override;
};

#endif // VIEWPROMEMORIA_H
