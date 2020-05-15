#ifndef VIEWMEETING_H
#define VIEWMEETING_H

#include "modview.h"
#include <QTimeEdit>

class ViewMeeting : public ModView {
    Q_OBJECT

   protected slots:
       virtual void modifyPushed() override;
       virtual void confirmPushed() override;
       virtual void deletePushed() override;

   public:
      explicit ViewMeeting(QDialog *parent = 0);
      ~ViewMeeting();

      QTimeEdit* inizio;
      QTimeEdit* fine;
      QLabel* start;
      QLabel* end;

       //virtual

       void getInfo() override;
   };

#endif // VIEWMEETING_H
