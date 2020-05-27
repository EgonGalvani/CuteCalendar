#include "eventwidgetbuilder.h"

EventWidget* EventWidgetBuilder::buildBirthdayWidget(const Model::It& it, QListWidget* parent) {
    EventWidget* e = new EventWidget(it, QIcon(":/res/birthday.png"), parent);
    e->setBackgroundColor(QColor(Qt::red));
    return e;
}

EventWidget *EventWidgetBuilder::buildTodoListWidget(const Model::It& it, QListWidget* parent) {
    EventWidget* e = new EventWidget(it, QIcon(":/res/todolist.png"), parent);
    e->setBackgroundColor(QColor(Qt::green));
    return e;
}

EventWidget *EventWidgetBuilder::buildReminderWidget(const Model::It& it, QListWidget* parent) {
    EventWidget* e = new EventWidget(it, QIcon(":/res/reminder.png"), parent);
    e->setBackgroundColor(QColor(Qt::cyan));
    return e;
}

EventWidget *EventWidgetBuilder::buildMeetingWidget(const Model::It& it, QListWidget* parent) {
    EventWidget* e = new EventWidget(it, QIcon(":/res/meeting.jpg"), parent);
    e->setBackgroundColor(QColor(Qt::yellow));
    return e;
}

EventWidget *EventWidgetBuilder::buildWorkoutWidget(const Model::It& it, QListWidget* parent) {
    EventWidget* e =  new EventWidget(it, QIcon(":/res/workout.jpg"), parent);
    e->setBackgroundColor(QColor(Qt::lightGray));
    return e;
}
