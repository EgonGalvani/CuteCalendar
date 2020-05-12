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
    EventWidget(const Model::It& info, const QIcon& icon, const QString& text,
            QListWidget* view = nullptr)
        : QListWidgetItem(icon, text, view), _data(info) {}

    Model::It getData() const { return _data; }
};

#endif // EVENTWIDGET_H
