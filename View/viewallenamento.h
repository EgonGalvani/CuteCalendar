#ifndef VIEWALLENAMENTO_H
#define VIEWALLENAMENTO_H

#include "modview.h"
#include <QTimeEdit>

class ViewAllenamento : public ModView {
 Q_OBJECT




public:
   explicit ViewAllenamento(QWidget *parent = 0);
   ~ViewAllenamento();

   QTimeEdit* inizio;
   QTimeEdit* fine;
   QLabel* start;
   QLabel* end;


   void switchReadable() override;

};

#endif // VIEWALLENAMENTO_H
