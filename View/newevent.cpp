#include "newevent.h"

NewEvent::NewEvent(QDialog *parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout();
    selLayout = new QVBoxLayout();
    eventLayout = new QVBoxLayout();

    mainLayout->setAlignment(Qt::AlignTop);
    initComboBox();
    setMinimumSize(QSize(500,600));
    setLayout(mainLayout);
}

void NewEvent::deleteLayout(QLayout* layout) {
    QLayoutItem* child;

    while(layout->count() > 0) {
        child = eventLayout->takeAt(0);

        if (child->layout() != 0)
            deleteLayout(child->layout());
        else if (child->widget() != 0)
            delete child->widget();

        delete child;
    }
}

void NewEvent::initComboBox() {
    selEvento = new QComboBox();
    selEvento->addItem("Allenamento");
    selEvento->addItem("Compleanno");
    selEvento->addItem("Meeting");
    selEvento->addItem("Promemoria");

    connect(selEvento, SIGNAL(currentIndexChanged(int)), this , SLOT(changedSel(int)) );

    selLayout->setAlignment(Qt::AlignTop);
    selLayout->addWidget(selEvento);
    mainLayout->addLayout(selLayout);
    mainLayout->addLayout(eventLayout);

    initAllenamento(); // scelta di default
}

void NewEvent::initAllenamento() {
    QLabel* inizio= new QLabel(tr("Inizio"));
    QLabel* fine= new QLabel(tr("Fine"));
    QLabel* nome= new QLabel(tr("Nome"));
    QLabel* desc= new QLabel(tr("Descrizione"));
    QLabel* luogo= new QLabel(tr("Luogo"));
    QLabel* tags= new QLabel(tr("Tags"));
    QTimeEdit* start= new QTimeEdit();
    QTimeEdit* end= new QTimeEdit();
    QTextEdit* txtNome = new QTextEdit();
    QTextEdit* txtDesc = new QTextEdit();
    QTextEdit* txtLuogo = new QTextEdit();
    QCheckBox* checkTag = new QCheckBox();
    QPushButton* addEvent = new QPushButton(tr("Aggiungi Evento"));

    eventLayout->addWidget(inizio);
    eventLayout->addWidget(start);
    eventLayout->addWidget(fine);
    eventLayout->addWidget(end);
    eventLayout->addWidget(nome);
    eventLayout->addWidget(txtNome);
    eventLayout->addWidget(desc);
    eventLayout->addWidget(txtDesc);
    eventLayout->addWidget(luogo);
    eventLayout->addWidget(txtLuogo);
    eventLayout->addWidget(tags);
    eventLayout->addWidget(checkTag);
    eventLayout->addWidget(addEvent);
}

void NewEvent::initCompleanno() {
    QLabel* nome= new QLabel(tr("Nome"));
    QLabel* desc= new QLabel(tr("Descrizione"));
    QLabel* luogo= new QLabel(tr("Luogo"));
    QLabel* tags= new QLabel(tr("Tags"));
    QTextEdit* txtNome = new QTextEdit();
    QTextEdit* txtDesc = new QTextEdit();
    QTextEdit* txtLuogo = new QTextEdit();
    QCheckBox* checkTag = new QCheckBox();
    QPushButton* addEvent = new QPushButton(tr("Aggiungi Evento"));

    eventLayout->addWidget(nome);
    eventLayout->addWidget(txtNome);
    eventLayout->addWidget(desc);
    eventLayout->addWidget(txtDesc);
    eventLayout->addWidget(luogo);
    eventLayout->addWidget(txtLuogo);
    eventLayout->addWidget(tags);
    eventLayout->addWidget(checkTag);
    eventLayout->addWidget(addEvent);
}

void NewEvent::initMeeting() {
    QLabel* inizio= new QLabel(tr("Inizio"));
    QLabel* fine= new QLabel(tr("Fine"));
    QLabel* nome= new QLabel(tr("Nome"));
    QLabel* desc= new QLabel(tr("Descrizione"));
    QLabel* luogo= new QLabel(tr("Luogo"));
    QLabel* tags= new QLabel(tr("Tags"));
    QTimeEdit* start= new QTimeEdit();
    QTimeEdit* end= new QTimeEdit();
    QTextEdit* txtNome = new QTextEdit();
    QTextEdit* txtDesc = new QTextEdit();
    QTextEdit* txtLuogo = new QTextEdit();
    QCheckBox* checkTag = new QCheckBox();
    QPushButton* addEvent = new QPushButton(tr("Aggiungi Evento"));

    eventLayout->addWidget(inizio);
    eventLayout->addWidget(start);
    eventLayout->addWidget(fine);
    eventLayout->addWidget(end);
    eventLayout->addWidget(nome);
    eventLayout->addWidget(txtNome);
    eventLayout->addWidget(desc);
    eventLayout->addWidget(txtDesc);
    eventLayout->addWidget(luogo);
    eventLayout->addWidget(txtLuogo);
    eventLayout->addWidget(tags);
    eventLayout->addWidget(checkTag);
    eventLayout->addWidget(addEvent);
}

void NewEvent::initPromemoria() {
    QLabel* inizio= new QLabel(tr("Inizio"));
    QLabel* fine= new QLabel(tr("Fine"));
    QLabel* nome= new QLabel(tr("Nome"));
    QLabel* desc= new QLabel(tr("Descrizione"));
    QLabel* luogo= new QLabel(tr("Luogo"));
    QLabel* tags= new QLabel(tr("Tags"));
    QLabel* rep= new QLabel(tr("Ripetizione"));
    QTimeEdit* start= new QTimeEdit();
    QTimeEdit* end= new QTimeEdit();
    QTextEdit* txtNome = new QTextEdit();
    QTextEdit* txtDesc = new QTextEdit();
    QTextEdit* txtLuogo = new QTextEdit();
    QTextEdit* txtTag = new QTextEdit();
    QCheckBox* check = new QCheckBox();
    QCheckBox* checkTag = new QCheckBox();
    QPushButton* addEvent = new QPushButton(tr("Aggiungi Evento"));

    eventLayout->addWidget(inizio);
    eventLayout->addWidget(start);
    eventLayout->addWidget(fine);
    eventLayout->addWidget(end);
    eventLayout->addWidget(rep);
    eventLayout->addWidget(check);
    eventLayout->addWidget(nome);
    eventLayout->addWidget(txtNome);
    eventLayout->addWidget(desc);
    eventLayout->addWidget(txtDesc);
    eventLayout->addWidget(luogo);
    eventLayout->addWidget(txtLuogo);
    eventLayout->addWidget(tags);
    eventLayout->addWidget(checkTag);
    eventLayout->addWidget(addEvent);
}

void NewEvent::changedSel(int index) {
    deleteLayout(eventLayout);

    switch(index){
        case 0:
           initAllenamento();
            break;
        case 1:
            initCompleanno();
            break;
        case 2:
            initMeeting();
            break;
        case 3:
            initPromemoria();
            break;
    }
}
