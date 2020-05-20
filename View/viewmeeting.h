#ifndef VIEWMEETING_H
#define VIEWMEETING_H

#include "modview.h"
#include <QTimeEdit>

class ViewMeeting : public ModView {
    Q_OBJECT





   public:
      explicit ViewMeeting(QWidget *parent = 0);
      ~ViewMeeting();

      QTimeEdit* inizio;
      QTimeEdit* fine;
      QLabel* start;
      QLabel* end;

       //virtual

   };

#endif // VIEWMEETING_H
