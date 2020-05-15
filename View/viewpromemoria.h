#ifndef VIEWPROMEMORIA_H
#define VIEWPROMEMORIA_H

#include "modview.h"
#include <QTimeEdit>
#include <QCheckBox>

class ViewPromemoria : public ModView {
    Q_OBJECT

   protected slots:
       virtual void modifyPushed() override;
       virtual void confirmPushed() override;
       virtual void deletePushed() override;

   public:
      explicit ViewPromemoria(QDialog *parent = 0);
      ~ViewPromemoria();

      QTimeEdit* inizio;
      QTimeEdit* fine;

      QCheckBox* checkRep;

      QLabel* start;
      QLabel* end;
      QLabel* rep;

       //virtual

       void getInfo() override;
   };

#endif // VIEWPROMEMORIA_H
