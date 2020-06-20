#ifndef VIEWCOMPLEANNO_H
#define VIEWCOMPLEANNO_H

#include "modview.h"
#include <QSpinBox>
#include "../Model/Hierarchy/birthday.h"

class ViewBirthday : public ModView {
    Q_OBJECT

    QSpinBox* annoNascita;
    QLabel* nascita;

    public:
      explicit ViewBirthday(QWidget *parent = 0);
      ~ViewBirthday() = default;

       BirthDay* createEvent(const QDate& date) const override;

       void setEnabled(bool) override;
       void pushSaves(const Model::It&) const override;
       void fillView(const Model::It&) override;
       bool checkPushable(QString&) const override;
};

#endif // VIEWCOMPLEANNO_H
