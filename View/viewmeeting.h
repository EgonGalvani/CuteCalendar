#ifndef VIEWMEETING_H
#define VIEWMEETING_H

#include "modview.h"
#include <QTimeEdit>

class ViewMeeting : public ModView {
    Q_OBJECT

   public:
      explicit ViewMeeting(QWidget *parent = 0);
      ~ViewMeeting() = default;

      QTimeEdit* inizio;
      QTimeEdit* fine;
      QLabel* start;
      QLabel* end;

      void setEnabled(bool) override;
      void pushSaves(Model::It) override;
      void fillView(Model::It) override;
};

#endif // VIEWMEETING_H
