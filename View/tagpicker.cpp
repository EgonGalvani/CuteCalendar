#include "tagpicker.h"

#include <QVBoxLayout>
#include <QColor>
#include <QKeyEvent>
#include <iostream>
#include <QScrollBar>
#include <QMessageBox>

void EnterLineEdit::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Return)
        emit enterKeyPressed();
    else QLineEdit::keyPressEvent(event);
}

TagPicker::TagPicker(QWidget* parent) : QWidget(parent), enabled(true) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    txtEdit = new EnterLineEdit();
    list = new QListWidget();

    txtEdit->setPlaceholderText("Inserire tag e premere invio");

    list->setFlow(QListView::LeftToRight);
    list->setFixedHeight(60);
    layout->addWidget(txtEdit);
    layout->addWidget(list);

    // QScrollBar:vertical{display: none;}
    QString style = QString("QListWidget {background-color: transparent; }  QListWidget::item { background-color: #fff; color: #000; border-radius: 5px; border: 1px solid #000;  margin: 2px 4px; padding: 8px; }");
    list->setStyleSheet(style);

    setLayout(layout);

    connect(txtEdit, SIGNAL(enterKeyPressed()), this, SLOT(addNewTag()));
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(deleteTag(QListWidgetItem*)));
}

void TagPicker::addNewTag() {
    addTag(txtEdit->text().toStdString());
    txtEdit->clear();
}

std::vector<std::string> TagPicker::getTags() const {
    std::vector<std::string> tags;
    for(int i = 0; i < list->count(); i++)
        tags.push_back(list->item(i)->text().toStdString());

    return tags;
}

void TagPicker::addTag(const std::string& tag) {
    QString qtag = QString::fromStdString(tag).trimmed();
    if(!qtag.isEmpty()) {

        bool found = false;
        for(int i = 0; i < list->count() && !found; i++)
            if(list->item(i)->text() == qtag)
                found = true;

        if(!found) {
            auto item = new QListWidgetItem(qtag);
            list->addItem(item);
            list->scrollToItem(item);
        }
        else
            QMessageBox::critical(this, QString("Error"), QString("Tag già presente"));
    }
}

void TagPicker::addTags(const std::vector<std::string>& tags) {
    for(auto it = tags.begin(); it != tags.end(); it++)
        addTag(*it);
}

bool TagPicker::isEnabled() const {
    return enabled;
}

void TagPicker::setEnabled(bool e) {
    enabled = e;
    txtEdit->setEnabled(e);
}

void TagPicker::deleteTag(QListWidgetItem* wi) {
    if(enabled) {
        list->removeItemWidget(wi);
        delete wi;
    }
}


