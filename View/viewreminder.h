#ifndef VIEWPROMEMORIA_H
#define VIEWPROMEMORIA_H

#include <QTimeEdit>

#include "modview.h"
#include "../Model/Hierarchy/reminder.h"

class ViewPromemoria : public ModView {
    Q_OBJECT

public:
    explicit ViewPromemoria(QWidget *parent = 0);
    ~ViewPromemoria() = default;

    QTimeEdit* inizio;
    QTimeEdit* fine;
    QTimeEdit* alert;

    QCheckBox* checkRep;

    QLabel* alertL;
    QLabel* start;
    QLabel* end;
    QLabel* rep;

    void setEnabled(bool) override;
    void pushSaves(Model::It) override;
    void fillView(Model::It) override;
    virtual Reminder* createEvent() override;
};

#endif // VIEWPROMEMORIA_H
