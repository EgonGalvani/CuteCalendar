#ifndef VIEWALLENAMENTO_H
#define VIEWALLENAMENTO_H

#include "modview.h"
#include <QTimeEdit>

class ViewAllenamento : public ModView {
 Q_OBJECT

protected slots:
    virtual void modifyPushed() override;
    virtual void confirmPushed() override;


public:
   explicit ViewAllenamento(const Model::It&,QDialog *parent = 0);
   ~ViewAllenamento();

   QTimeEdit* inizio;
   QTimeEdit* fine;
   QLabel* start;
   QLabel* end;

    //virtual

    void getInfo() override;
};

#endif // VIEWALLENAMENTO_H
