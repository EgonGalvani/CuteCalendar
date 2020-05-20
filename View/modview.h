#ifndef MODVIEW_H
#define MODVIEW_H


#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ModView : public QWidget {
    Q_OBJECT
public:
    explicit ModView(QWidget *parent = nullptr);
    virtual ~ModView()=0;

    virtual void switchReadable();


protected:


    QVBoxLayout* mainLayout;


    QLabel* lNome;
    QLabel* lDesc;
    QLabel* lLuogo;
    QLabel* lTag;

    QTextEdit* txtNome;
    QTextEdit* txtLuogo;
    QTextEdit* txtDesc;
    QCheckBox* checkTag;



};

#endif // MODVIEW_H
