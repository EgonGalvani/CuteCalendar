#ifndef VIEWALLENAMENTO_H
#define VIEWALLENAMENTO_H

#include "modview.h"
#include "../Model/Hierarchy/workout.h"

#include <QTimeEdit>

class ViewAllenamento : public ModView {
    Q_OBJECT

public:
   explicit ViewAllenamento(QWidget *parent = 0);
   ~ViewAllenamento() = default;

   QTimeEdit* inizio;
   QTimeEdit* fine;
   QLabel* start;
   QLabel* end;

   void setEnabled(bool) override;
   void pushSaves(Model::It) override;
   void fillView(Model::It) override;
   Workout *createEvent(QDate date) override;
};

#endif // VIEWALLENAMENTO_H
