#ifndef MODVIEW_H
#define MODVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QMessageBox>

#include "Model/model.h"
#include "tagpicker.h"
#include "../Model/Hierarchy/event.h"

class ModView : public QWidget {
    Q_OBJECT

public:
    explicit ModView(QWidget *parent = nullptr);
    virtual ~ModView() = default;

    virtual void setEnabled(bool);
    virtual void pushSaves(const Model::It&) const;
    virtual void fillView(const Model::It&);
    virtual bool checkPushable(QString&) const;
    virtual Event* createEvent(const QDate& date) const = 0;

    bool isEnabled() const;

protected:
    bool enabled;

    //Elementi della view
    QVBoxLayout* mainLayout;
    QLabel* lNome;
    QLabel* lDesc;
    QLabel* lLuogo;
    QLabel* lTag;

    QLineEdit* txtNome;
    QLineEdit* txtLuogo;
    QTextEdit* txtDesc;
    TagPicker* checkTag;
};

#endif // MODVIEW_H
