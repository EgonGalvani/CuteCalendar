#include "tagpicker.h"

#include <QVBoxLayout>
#include <QColor>
#include <QKeyEvent>
#include <iostream>
#include <QScrollBar>
#include <QMessageBox>
#include <QSizePolicy>

TagPicker::TagPicker(QWidget* parent) : QWidget(parent), enabled(true) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    txtEdit = new EnterLineEdit(this);
    list = new QListWidget(this);

    txtEdit->setPlaceholderText("Inserire tag e premere invio");
    list->setFlow(QListView::LeftToRight);
    list->setFixedHeight(60);
    layout->addWidget(txtEdit);
    layout->addWidget(list);

    QString style = QString("QListWidget {background-color: transparent; }  QListWidget::item { background-color: #fff; color: #000; border-radius: 5px; border: 1px solid #000;  margin: 2px 4px; padding: 8px; }");
    list->setStyleSheet(style);
    setLayout(layout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    // connessione dei segnali
    connect(txtEdit, SIGNAL(enterKeyPressed()), this, SLOT(addNewTag()));
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(deleteTag(QListWidgetItem*)));
}

// slot usato per la gestione dell'inserimento di nuovi tag
void TagPicker::addNewTag() {
    addTag(txtEdit->text().toStdString()); // il tag viene inserito
    txtEdit->clear(); // l'editText usata per la scrittura del tag viene pulita
}

std::vector<std::string> TagPicker::getTags() const {
    std::vector<std::string> tags;
    for(int i = 0; i < list->count(); i++)
        tags.push_back(list->item(i)->text().toStdString());

    return tags;
}

// aggiunta di un singolo tag
void TagPicker::addTag(const std::string& tag) {
    QString qtag = QString::fromStdString(tag).trimmed();
    if(!qtag.isEmpty()) {

        // controllo che il tag non sia già presente
        bool found = false;
        for(int i = 0; i < list->count() && !found; i++)
            if(list->item(i)->text() == qtag)
                found = true;

        // se il tag non è già presente lo inserisco
        if(!found) {
            auto item = new QListWidgetItem(qtag);
            list->addItem(item);
            list->scrollToItem(item);
        }else
            QMessageBox::critical(this, QString("Error"), QString("Tag già presente"));
    }
}

// aggiunta di una lista di tag
void TagPicker::addTags(const std::vector<std::string>& tags) {
    for(auto it = tags.begin(); it != tags.end(); it++)
        addTag(*it);
}

// rimozione di un tag selezionato
void TagPicker::deleteTag(QListWidgetItem* wi) {
    if(enabled) {
        list->removeItemWidget(wi);
        delete wi;
    }
}

// gestione dello stato di attivazione del widget
bool TagPicker::isEnabled() const {
    return enabled;
}

void TagPicker::setEnabled(bool e) {
    enabled = e;
    txtEdit->setEnabled(e);
}




