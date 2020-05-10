#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include <QListWidgetItem>
#include <QListWidget>
#include <QString>

#include "../Model/model.h"

class EventWidget : public QListWidgetItem {
private:
    // Model::It it;
    QString info;
public:
    // EW(it, ...)

    EventWidget(const QString info, const QIcon& icon, const QString& text,
            QListWidget* view = nullptr)
        : QListWidgetItem(icon, text, view), info(info) {}

    QString getInfo() const { return info; }
};

#endif // EVENTWIDGET_H
