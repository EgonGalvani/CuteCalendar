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
   void pushSaves(Model::It,QString&) override;
   void fillView(const Model::It&) override;
   bool checkPushable(QString&) override;
   Workout *createEvent(QDate date,QString& err) override;
};

#endif // VIEWALLENAMENTO_H
