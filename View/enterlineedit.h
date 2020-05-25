#ifndef ENTERLINEEDIT_H
#define ENTERLINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class EnterLineEdit : public QLineEdit {
    Q_OBJECT

public:
    EnterLineEdit(QWidget* = nullptr);
    virtual void keyPressEvent(QKeyEvent*);

signals:
    void enterKeyPressed();
};

#endif // ENTERLINEEDIT_H
