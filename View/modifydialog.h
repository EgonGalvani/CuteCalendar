#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H


#include "Model/model.h"

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "modview.h"
#include "viewallenamento.h"
#include "viewcompleanno.h"
#include "viewmeeting.h"
#include "viewpromemoria.h"



class ModifyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyDialog(const Model::It&,QDialog *parent = nullptr);
    virtual ~ModifyDialog();

signals:
    void deleteEvent(Model::It);

protected slots:
    virtual void modifyPushed();
    virtual void confirmPushed();
    virtual void deletePushed();

private:

    Model::It it;

    ModView* view;

    QVBoxLayout* layout;
    QVBoxLayout* viewLayout;
    QHBoxLayout* buttomLayout;

    QPushButton* btnModify;
    QPushButton* btnDelete;
    QPushButton* btnConfirm;

    virtual void getInfo();

};

#endif // MODIFYDIALOG_H
