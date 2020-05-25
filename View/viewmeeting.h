#ifndef VIEWMEETING_H
#define VIEWMEETING_H

#include <QTimeEdit>

#include "modview.h"
#include "../Model/Hierarchy/meeting.h"

class ViewMeeting : public ModView {
    Q_OBJECT

   public:
      explicit ViewMeeting(QWidget *parent = 0);
      ~ViewMeeting() = default;

      QTimeEdit* inizio;
      QTimeEdit* fine;
      QTimeEdit* alert;
      QTextEdit* emails;

      QCheckBox* checkRep;

      QLabel* alertL;
      QLabel* emailLabel;
      QLabel* start;
      QLabel* end;
      QLabel* rep;

      void setEnabled(bool) override;
      void pushSaves(Model::It) override;
      void fillView(Model::It) override;
      Meeting* createEvent() override;
};

#endif // VIEWMEETING_H
