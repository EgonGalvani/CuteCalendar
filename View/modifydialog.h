#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "Model/model.h"
#include "modview.h"
#include "viewallenamento.h"
#include "viewcompleanno.h"
#include "viewmeeting.h"
#include "viewpromemoria.h"

class ModifyDialog : public QDialog {
    Q_OBJECT

public:
    explicit ModifyDialog(const Model::It&, QDialog *parent = nullptr);
    virtual ~ModifyDialog() = default;

signals:
    void deleteEvent(Model::It);

protected slots:
    virtual void modifyPushed();
    virtual void deletePushed();

private:
    Model::It it;
    ModView* view;
    bool modifyEnabled;

    QVBoxLayout* layout;
    QVBoxLayout* viewLayout;
    QHBoxLayout* buttomLayout;

    QPushButton* btnModify;
    QPushButton* btnDelete;
};

#endif // MODIFYDIALOG_H
