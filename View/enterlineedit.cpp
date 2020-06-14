#include "enterlineedit.h"

#include <QKeyEvent>

EnterLineEdit::EnterLineEdit(QWidget* parent)
    : QLineEdit(parent) {}

void EnterLineEdit::keyPressEvent(QKeyEvent* event) {

    // se l'evento è quello di interesse (click bottone enter), viene emesso un signal
    // altrimenti si comporta come QLineEdit
    if(event->key() == Qt::Key_Return)
        emit enterKeyPressed();
    else QLineEdit::keyPressEvent(event);
}
