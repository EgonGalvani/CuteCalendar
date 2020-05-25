#include "enterlineedit.h"

#include <QKeyEvent>

EnterLineEdit::EnterLineEdit(QWidget* parent)
    : QLineEdit(parent) {}

void EnterLineEdit::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Return)
        emit enterKeyPressed();
    else QLineEdit::keyPressEvent(event);
}
