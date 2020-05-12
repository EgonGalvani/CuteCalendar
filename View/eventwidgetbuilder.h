#ifndef EVENTWIDGETBUILDER_H
#define EVENTWIDGETBUILDER_H

#include <QListWidget>

#include "eventwidget.h"

class EventWidgetBuilder {

public:    
    static EventWidget* buildBirthdayWidget(const Model::It&, QListWidget* = nullptr );

    static EventWidget* buildTodoListWidget(const Model::It&, QListWidget* = nullptr);

    static EventWidget* buildReminderWidget(const Model::It&, QListWidget* = nullptr);

    static EventWidget* buildMeetingWidget(const Model::It&, QListWidget* = nullptr);

    static EventWidget* buildWorkoutWidget(const Model::It&, QListWidget* = nullptr);
};

#endif // EVENTWIDGETBUILDER_H
