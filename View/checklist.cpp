#include "checklist.h"

#include <QListWidgetItem>
#include <QCheckBox>
#include <stdexcept>

CheckList::CheckList(QWidget* parent)
    : QListWidget(parent) {

    setSpacing(4);
}

// inserimento di un nuovo item nella checklist
void CheckList::addItem(const QString& label, bool checked) {
    QString itemLabel = label.trimmed();

    if(!itemLabel.isEmpty()) { // controlla che la label dell'item non sia vuota
        if(!hasItem(itemLabel)) { // controlla che non esista già l'item nella lista

            // aggiunta dell'item nella lista
            QListWidgetItem* item = new QListWidgetItem;
            QListWidget::addItem(item);
            QCheckBox *checkBox = new QCheckBox(itemLabel, this);
            checkBox->setChecked(checked);
            setItemWidget(item, checkBox);
            scrollToItem(item); // esegue lo scroll della lista per mostrare il nuovo item inserito
        } else
            throw std::logic_error("Elemento già presente nella lista");
    } else
        throw std::logic_error("La stringa da inserire non può essere vuota");
}

// controlla se un item con la stringa indicata è già presente nella lista
bool CheckList::hasItem(const QString &label) const {
    bool found = false;
    for(int i = 0; i < count() && !found; i++) {
        QCheckBox *checkBox = dynamic_cast<QCheckBox*>(itemWidget(item(i)));
        found = checkBox->text() == label;
    }
    return found;
}

// viene restituito un vector contenente dei pair che permettono
// di rappresentare correttamente un item della lista, formato da: testo e stato (checked o unchecked)
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


