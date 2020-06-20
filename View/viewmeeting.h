#ifndef VIEWMEETING_H
#define VIEWMEETING_H

#include <QTimeEdit>

#include <QListWidget>
#include <QSpinBox>
#include "enterlineedit.h"

#include "modview.h"
#include "../Model/Hierarchy/meeting.h"

class ViewMeeting : public ModView {
    Q_OBJECT

private slots:
    void addEmail();

private:
    static bool isEmail(const std::string&);
    bool hasEmail(const QString&) const;
    std::vector<std::string> getEmails() const;

    //Elementi della view
    QTimeEdit* inizio;
    QTimeEdit* fine;
    QSpinBox* alert;

    EnterLineEdit* emailLineEdit;
    QListWidget* emailList;

    QCheckBox* checkRep;

    QLabel* alertL;
    QLabel* emailLabel;
    QLabel* start;
    QLabel* end;

public:
      explicit ViewMeeting(QWidget *parent = 0);
      ~ViewMeeting() = default;

      void setEnabled(bool) override;
      void pushSaves(const Model::It&) const override;
      void fillView(const Model::It&) override;
      bool checkPushable(QString&) const override;
      Meeting* createEvent(const QDate& date) const override;
};

#endif // VIEWMEETING_H
