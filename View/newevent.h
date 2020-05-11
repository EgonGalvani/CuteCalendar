#ifndef NEWEVENT_H
#define NEWEVENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTimeEdit>
#include <QTextEdit>
#include <QPushButton>

class NewEvent : public QDialog {
    Q_OBJECT

private slots:
    void changedSel(int);


public:
    explicit NewEvent(QDialog *parent = nullptr);
    ~NewEvent();


private:
    QVBoxLayout* mainLayout;
    QComboBox* selEvento;
    QVBoxLayout* selLayout ;
    QVBoxLayout* eventLayout;





    void initComboBox();
    void initAllenamento();
    void initCompleanno();
    void initMeeting();
    void initPromemoria();


};

#endif // NEWEVENT_H
