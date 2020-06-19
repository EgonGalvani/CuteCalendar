#ifndef VIEWCOMPLEANNO_H
#define VIEWCOMPLEANNO_H

#include "modview.h"
#include <QSpinBox>
#include "../Model/Hierarchy/birthday.h"

class ViewCompleanno : public ModView {
    Q_OBJECT

    QSpinBox* annoNascita;
    QLabel* nascita;

    public:
      explicit ViewCompleanno(QWidget *parent = 0);
      ~ViewCompleanno() = default;

       BirthDay* createEvent(QDate date) override;

       void setEnabled(bool) override;
       void pushSaves(Model::It) override;
       void fillView(const Model::It&) override;
       bool checkPushable() override;
};

#endif // VIEWCOMPLEANNO_H
