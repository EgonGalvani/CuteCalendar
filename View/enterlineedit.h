#ifndef ENTERLINEEDIT_H
#define ENTERLINEEDIT_H

#include <QLineEdit>
#include <QWidget>

// QLineEdit con signal per il click del bottone invio
class EnterLineEdit : public QLineEdit {
    Q_OBJECT

public:
    EnterLineEdit(QWidget* = nullptr);

    // ridefinizione del metodo keyPressEvent della classe QLineEdit
    virtual void keyPressEvent(QKeyEvent*);

signals:
    void enterKeyPressed();
};

#endif // ENTERLINEEDIT_H
