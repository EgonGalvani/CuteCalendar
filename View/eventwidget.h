#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include <QListWidgetItem>
#include <QListWidget>
#include <QString>

#include "../Model/model.h"

class EventWidget : public QListWidgetItem {
private:
    Model::It _data;

public:
    EventWidget(const Model::It& info, const QIcon& icon, QListWidget* view = nullptr);

    Model::It getData() const;
};

#endif // EVENTWIDGET_H
