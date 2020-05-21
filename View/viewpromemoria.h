#ifndef VIEWPROMEMORIA_H
#define VIEWPROMEMORIA_H

#include "modview.h"
#include <QTimeEdit>


class ViewPromemoria : public ModView {
    Q_OBJECT




   public:
      explicit ViewPromemoria(QWidget *parent = 0);
      ~ViewPromemoria();

      QTimeEdit* inizio;
      QTimeEdit* fine;

      QCheckBox* checkRep;

      QLabel* start;
      QLabel* end;
      QLabel* rep;

      void switchReadable() override;
      void pushSaves(Model::It) override;
      void fillView(Model::It) override;


   };

#endif // VIEWPROMEMORIA_H
