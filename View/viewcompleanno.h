#ifndef VIEWCOMPLEANNO_H
#define VIEWCOMPLEANNO_H

#include "modview.h"
#include "../Model/Hierarchy/birthday.h"

class ViewCompleanno : public ModView {
    Q_OBJECT

   public:
      explicit ViewCompleanno(QWidget *parent = 0);
      ~ViewCompleanno() = default;

      // BirthDay* createEvent() override;
};

#endif // VIEWCOMPLEANNO_H
