#include "modview.h"


ModView::ModView(QWidget *parent)
        : QWidget(parent), enabled(true){

    mainLayout = new QVBoxLayout(this);

    lTag = new QLabel("Tag");
    lNome= new QLabel("Nome");
    lDesc= new QLabel("Descrizione");
    lLuogo = new QLabel("Luogo");
    completato = new QLabel("Completato");

    completato->setAlignment(Qt::AlignCenter);

    txtDesc = new QTextEdit();
    txtNome = new QLineEdit();
    txtLuogo = new QLineEdit();

    checkTag= new TagPicker();

    mainLayout->addWidget(completato);
    mainLayout->addWidget(lNome);
    mainLayout->addWidget(txtNome);
    mainLayout->addWidget(lLuogo);
    mainLayout->addWidget(txtLuogo);
    mainLayout->addWidget(lDesc);
    mainLayout->addWidget(txtDesc);
    mainLayout->addWidget(lTag);
    mainLayout->addWidget(checkTag);
}

void ModView::setEnabled(bool e) {
    enabled = e;

    txtDesc->setReadOnly(!e);
    txtNome->setReadOnly(!e);
    txtLuogo->setReadOnly(!e);
    checkTag->setEnabled(e);
}

bool ModView::isEnabled() const {
    return enabled;
}

void ModView::pushSaves(Model::It it) {
    (*it)->setDesc((txtDesc->toPlainText()).toStdString());
    (*it)->setName((txtNome->text()).toStdString());
    (*it)->setPlace((txtLuogo->text()).toStdString());
    (*it)->clearTags();
    for (auto tag: checkTag->getTags()){
       (*it)->addTag(tag);
    }
}

void ModView::fillView(Model::It it) {
    txtDesc->setText(QString::fromStdString((*it)->getDesc()));
    txtNome->setText(QString::fromStdString((*it)->getName()));
    txtLuogo->setText(QString::fromStdString((*it)->getPlace()));
    for (auto tag: (*it)->getTags()){
        checkTag->addTag(tag);
    }

    if((*it)->isCompleted()) {
        completato->setText("Completato");
        completato->setStyleSheet("QLabel { color: #fff; padding: 4px; background-color : green;}");
    } else {
        completato->setText("Non completato");
        completato->setStyleSheet("QLabel { color: #fff; padding: 4px; color: #fff; background-color : red;}");
    }
}

bool ModView::checkPushable()
{
    return !txtDesc->toPlainText().isEmpty() && !txtNome->text().isEmpty() && !txtLuogo->text().isEmpty();
}
