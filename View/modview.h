#ifndef MODVIEW_H
#define MODVIEW_H

#include "Model/model.h"


#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class ModView : public QDialog
{
    Q_OBJECT
public:
    explicit ModView(const Model::It&, QDialog *parent = nullptr);
    virtual ~ModView()=0;

signals:
    void deleteEvent(Model::It);

protected slots:
    virtual void modifyPushed();
    virtual void confirmPushed();
    virtual void deletePushed();

protected:
    Model::It it;

    QVBoxLayout* mainLayout;
    QVBoxLayout* editLayout;
    QHBoxLayout* buttomLayout;

    QLabel* lNome;
    QLabel* lDesc;
    QLabel* lLuogo;
    QLabel* lTag;

    QTextEdit* txtNome;
    QTextEdit* txtLuogo;
    QTextEdit* txtDesc;
    QCheckBox* checkTag;

    QPushButton* btnModify;
    QPushButton* btnDelete;
    QPushButton* btnConfirm;

    virtual void getInfo();


};

#endif // MODVIEW_H
