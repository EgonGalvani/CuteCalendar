#ifndef VIEWCOMPLEANNO_H
#define VIEWCOMPLEANNO_H

#include "modview.h"
#include <QSpinBox>
#include "../Model/Hierarchy/birthday.h"

class ViewCompleanno : public ModView {
    Q_OBJECT

public:
    explicit ViewCompleanno(QWidget *parent = 0);
    ~ViewCompleanno() = default;

    BirthDay* createEvent(QDate date) override;
    void setEnabled(bool) override;
    void pushSaves(Model::It) override;
    void fillView(Model::It) override;


    //Elementi della view
    QSpinBox* annoNascita;
    QLabel* nascita;

};

#endif // VIEWCOMPLEANNO_H
