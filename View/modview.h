#ifndef MODVIEW_H
#define MODVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class ModView : public QWidget
{
    Q_OBJECT
public:
    explicit ModView(QWidget *parent = nullptr);
    virtual ~ModView() = 0;


protected slots:
    virtual void modifyPushed();
    virtual void confirmPushed();
    virtual void deletePushed();

protected:
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
