#ifndef VIEWTODOLIST_H
#define VIEWTODOLIST_H

#include "modview.h"
#include "checklist.h"
#include "enterlineedit.h"
#include "../Model/Hierarchy/todolist.h"

class ViewToDoList : public ModView {
    Q_OBJECT

    CheckList* checkList;
    EnterLineEdit* inputLine;
public:
    explicit ViewToDoList(QWidget *parent = 0);
    ~ViewToDoList() = default;

    void setEnabled(bool) override;
    void pushSaves(const Model::It&) const override;
    void fillView(const Model::It&) override;
    bool checkPushable(QString&) const override;
    ToDoList* createEvent(const QDate& date) const override;

private slots:
    void addItem();
};

#endif // VIEWTODOLIST_H
