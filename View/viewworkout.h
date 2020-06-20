#ifndef VIEWALLENAMENTO_H
#define VIEWALLENAMENTO_H

#include "modview.h"
#include "../Model/Hierarchy/workout.h"

#include <QTimeEdit>
#include <QComboBox>

class ViewWorkout : public ModView {
    Q_OBJECT

    //Elementi della view
    QTimeEdit* inizio;
    QTimeEdit* fine;
    QLabel* start;
    QLabel* end;
    QComboBox* attivita;

public:
   explicit ViewWorkout(QWidget *parent = 0);
   ~ViewWorkout() = default;

   void setEnabled(bool) override;
   void pushSaves(const Model::It&) const override;
   void fillView(const Model::It&) override;
   bool checkPushable(QString&) const override;
   Workout *createEvent(const QDate& date) const override;
};

#endif // VIEWALLENAMENTO_H
