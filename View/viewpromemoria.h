#ifndef VIEWPROMEMORIA_H
#define VIEWPROMEMORIA_H

#include "modview.h"
#include <QTimeEdit>

class ViewPromemoria : public ModView {
    Q_OBJECT

public:
    explicit ViewPromemoria(QWidget *parent = 0);
    ~ViewPromemoria() = default;

    QTimeEdit* inizio;
    QTimeEdit* fine;

    QCheckBox* checkRep;

    QLabel* start;
    QLabel* end;
    QLabel* rep;

    void setEnabled(bool) override;
    void pushSaves(Model::It) override;
    void fillView(Model::It) override;
};

#endif // VIEWPROMEMORIA_H
