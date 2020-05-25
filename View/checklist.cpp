#include "checklist.h"

#include <QListWidgetItem>
#include <QCheckBox>
#include <stdexcept>

CheckList::CheckList(QWidget* parent)
    : QListWidget(parent) {

    setSpacing(4);
}

void CheckList::addItem(const QString& label, bool checked) {
    QString itemLabel = label.trimmed();
    if(!itemLabel.isEmpty()) {

        if(!hasItem(itemLabel)) {
            QListWidgetItem* item = new QListWidgetItem;
            QListWidget::addItem(item);
            QCheckBox *checkBox = new QCheckBox(itemLabel, this);
            checkBox->setChecked(checked);
            setItemWidget(item, checkBox);
            scrollToItem(item);
        } else
            throw std::logic_error("Elemento già presente nella lista");
    } else
        throw std::logic_error("La stringa da inserire non può essere vuota");
}

bool CheckList::hasItem(const QString &label) const {
    bool found = false;
    for(int i = 0; i < count() && !found; i++) {
        QCheckBox *checkBox = dynamic_cast<QCheckBox*>(itemWidget(item(i)));
        found = checkBox->text() == label;
    }
    return found;
}

std::vector<std::pair<std::string, bool>>
CheckList::getStatus() const {
    std::vector<std::pair<std::string, bool>> list;

    for(int i = 0; i < count(); i++) {
        QCheckBox *checkBox = dynamic_cast<QCheckBox*>(itemWidget(item(i)));
        list.emplace_back(
            checkBox->text().toStdString(),
            checkBox->checkState()
        );
    }

    return list;
}


