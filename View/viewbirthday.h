#ifndef VIEWCOMPLEANNO_H
#define VIEWCOMPLEANNO_H

#include "modview.h"
#include <QSpinBox>
#include "../Model/Hierarchy/birthday.h"

class ViewCompleanno : public ModView {
    Q_OBJECT

    public:
      explicit ViewCompleanno(QDate date,QWidget *parent = 0);
      ~ViewCompleanno() = default;

       BirthDay* createEvent() override;
       QSpinBox* annoNascita;
       QLabel* nascita;
       void setEnabled(bool) override;
       void pushSaves(Model::It) override;
       void fillView(Model::It) override;

};

#endif // VIEWCOMPLEANNO_H
