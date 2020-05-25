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
    explicit ViewToDoList(QDate date,QWidget *parent = 0);
    ~ViewToDoList() = default;

    void setEnabled(bool) override;
    void pushSaves(Model::It) override;
    void fillView(Model::It) override;

    virtual ToDoList* createEvent();
private slots:
    void addItem();
};

#endif // VIEWTODOLIST_H
