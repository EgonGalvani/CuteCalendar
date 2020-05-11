#include "newevent.h"



NewEvent::NewEvent(QDialog *parent) :
    QDialog(parent) {

   mainLayout = new QVBoxLayout();
   selLayout = new QVBoxLayout();
   eventLayout = new QVBoxLayout();

   mainLayout->setAlignment(Qt::AlignTop);
   initComboBox();




   setMinimumSize(QSize(500,600));

   setLayout(mainLayout);

}

NewEvent::~NewEvent() {

}



void NewEvent::initComboBox()

{


    selEvento = new QComboBox();
    selEvento->addItem("Allenamento");
    selEvento->addItem("Compleanno");
    selEvento->addItem("Meeting");
    selEvento->addItem("Promemoria");

    connect(selEvento, SIGNAL(currentIndexChanged(int)), this , SLOT(changedSel(int)) );

    selLayout->setAlignment(Qt::AlignTop);
    selLayout->addWidget(selEvento);
    mainLayout->addLayout(selLayout);

}




void NewEvent::initAllenamento()
{
  //  deleteWidget(eventLayout);
    QLabel* inizio= new QLabel(tr("Inizio"));
    QLabel* fine= new QLabel(tr("Fine"));
    QLabel* nome= new QLabel(tr("Nome"));
    QLabel* desc= new QLabel(tr("Descrizione"));
    QLabel* luogo= new QLabel(tr("Luogo"));
    QTimeEdit* start= new QTimeEdit();
    QTimeEdit* end= new QTimeEdit();
    QTextEdit* txtNome = new QTextEdit();
    QTextEdit* txtDesc = new QTextEdit();
    QTextEdit* txtLuogo = new QTextEdit();
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
    eventLayout->addWidget(addEvent);

    mainLayout->addLayout(eventLayout);

}

void NewEvent::initCompleanno()
{
    //deleteWidget(eventLayout);

}

void NewEvent::initMeeting()
{
    //deleteWidget(eventLayout);

}

void NewEvent::initPromemoria()
{
    //deleteWidget(eventLayout);

}




void NewEvent::changedSel(int index)
{
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
