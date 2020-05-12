#include "eventwidget.h"

EventWidget::EventWidget(const Model::It& info, const QIcon& icon,
        QListWidget* view)
    : QListWidgetItem(icon, QString::fromStdString((*info)->getName()), view), _data(info) {}

Model::It EventWidget::getData() const {
    return _data;
}
