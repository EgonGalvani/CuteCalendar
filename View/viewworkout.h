#ifndef VIEWALLENAMENTO_H
#define VIEWALLENAMENTO_H

#include "modview.h"
#include "../Model/Hierarchy/workout.h"

#include <QTimeEdit>
#include <QComboBox>

class ViewAllenamento : public ModView {
    Q_OBJECT

    //Elementi della view
    QTimeEdit* inizio;
    QTimeEdit* fine;
    QLabel* start;
    QLabel* end;
    QComboBox* attivita;

public:
   explicit ViewAllenamento(QWidget *parent = 0);
   ~ViewAllenamento() = default;

   void setEnabled(bool) override;
   void pushSaves(const Model::It&) const override;
   void fillView(const Model::It&) override;
   bool checkPushable(QString&) const override;
   Workout *createEvent(const QDate& date) override;
};

#endif // VIEWALLENAMENTO_H
