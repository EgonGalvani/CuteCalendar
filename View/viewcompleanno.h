#ifndef VIEWCOMPLEANNO_H
#define VIEWCOMPLEANNO_H

#include "modview.h"

class ViewCompleanno : public ModView {
    Q_OBJECT

   protected slots:
       virtual void modifyPushed() override;
       virtual void confirmPushed() override;
       virtual void deletePushed() override;

   public:
      explicit ViewCompleanno(QDialog *parent = 0);
      ~ViewCompleanno();

      void getInfo() override;
};

#endif // VIEWCOMPLEANNO_H
