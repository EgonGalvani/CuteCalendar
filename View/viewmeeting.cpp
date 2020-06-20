#include <stdexcept>

#include "viewmeeting.h"
#include "Model/Hierarchy/meeting.h"

#include <regex>
#include <QMessageBox>

bool ViewMeeting::isEmail(const std::string& email) {
   // define a regular expression
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

   // try to match the string with the regular expression
   return std::regex_match(email, pattern);
}

ViewMeeting::ViewMeeting(QWidget *parent)
    : ModView(parent), emailLineEdit(new EnterLineEdit(this)), emailList(new QListWidget(this)) {

    emailLineEdit->setPlaceholderText("Inserisci un'email e premi invio");

    inizio= new QTimeEdit(this);
    fine= new QTimeEdit(this);
    alert = new QSpinBox(this);
    checkRep= new QCheckBox("Ripeti notifica una seconda volta", this);

    alert->setRange(5,60);
    alert->setSingleStep(5);

    inizio->setTime(QTime::currentTime());
    if(inizio->time().hour()<23)
        fine->setTime(inizio->time().addSecs(3600));
    else fine->setTime(QTime::fromString("23:59:00"));

    emailLabel= new QLabel("Emails", this);
    alertL= new QLabel("Notifica prima dell'evento: (in minuti)", this);
    start = new QLabel("Inizio", this);
    end = new QLabel("Fine", this);

    mainLayout->addWidget(start);
    mainLayout->addWidget(inizio);
    mainLayout->addWidget(end);
    mainLayout->addWidget(fine);
    mainLayout->addWidget(alertL);
    mainLayout->addWidget(alert);
    mainLayout->addWidget(checkRep);
    mainLayout->addWidget(emailLabel);
    mainLayout->addWidget(emailLineEdit);
    mainLayout->addWidget(emailList);

    connect(emailLineEdit, SIGNAL(enterKeyPressed()), this, SLOT(addEmail()));
}

bool ViewMeeting::hasEmail(const QString& email) const {
    bool found = false;
    for(int i = 0; i < emailList->count() && !found; i++)
        found = emailList->item(i)->text() == email;
    return found;
}

std::vector<std::string> ViewMeeting::getEmails() const
{
    std::vector<std::string> retEmails;
    for(int i = 0; i < emailList->count(); i++)
        retEmails.push_back(emailList->item(i)->text().toStdString());

    return retEmails;
}

void ViewMeeting::addEmail() {
    QString email = emailLineEdit->text().trimmed();
    if(email.isEmpty())
        QMessageBox::critical(this, QString("Error"), "Il campo non può essere vuoto");
    else
        if(!isEmail(email.toStdString()))
            QMessageBox::critical(this, QString("Error"), "Inserire una email valida");
        else if(hasEmail(email))
            QMessageBox::critical(this, QString("Error"), "Email già presente nella lista");
        else {
            emailList->addItem(new QListWidgetItem(email, emailList));
            emailLineEdit->clear();
        }
}

void ViewMeeting::setEnabled(bool b) {
    ModView::setEnabled(b);
    emailLineEdit->setReadOnly(!b);
    emailList->setEnabled(b);
    inizio->setEnabled(b);
    fine->setEnabled(b);
    alert->setEnabled(b);
    checkRep->setEnabled(b);
}

// Salvataggio delle modifiche apportate dall'utente nell'iteratore passato
void ViewMeeting::pushSaves(const Model::It& it) const {
    ModView::pushSaves(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        QString error = "";
        if (checkPushable(error)){
            currEve->setStartTime(inizio->time());
            currEve->setEndTime(fine->time());

            QTime t2 = QTime(inizio->time()).addSecs(alert->value()*(-60));

            currEve->setAlertTime(t2);
            currEve->setRepeat(checkRep->isChecked());

            for(auto email : getEmails())
                currEve->addPartecipant(email);
        }else
            throw std::logic_error(error.toStdString());
    } else
        throw std::logic_error("Tipo errato per la modifica di una view meeting");
}

// Caricamento del contenuto delle evento nella view
void ViewMeeting::fillView(const Model::It& it) {
    ModView::fillView(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());

        QTime currInizio = QTime(inizio->time());
        QTime currAlert = QTime(currEve->getAlertTime());
        int secs = currInizio.secsTo(currAlert);

        alert->setValue(secs/-60);
        checkRep->setChecked(currEve->doesRepeat());

        for(auto email : currEve->getPartecipants()){
            if(!hasEmail(QString::fromStdString(email)))
            emailList->addItem(QString::fromStdString(email));
        }
    } else
        throw std::logic_error("Tipo errato per essere mostrato in una view meeting");
}

//Controllo errori nella view prima del salvataggio
bool ViewMeeting::checkPushable(QString& err) const {
    bool ritorno=ModView::checkPushable(err);

    if(!inizio->time().isValid()){
        ritorno=false;
        err+="Il campo Inizio non è valido.\n";
    }

    if(!fine->time().isValid()){
        ritorno=false;
        err+="Il campo Fine non è valido.\n" ;
    }

    if(!(inizio->time() < fine->time())){
        ritorno=false;
        err+="Il campo Inizio deve essere minore di Fine.\n";
    }

    if(emailList->count()==0){
        ritorno=false;
        err+="Il campo emails non può essere vuoto.\n";
    }

    if(alert->value()<5){
        ritorno=false;
        err+="Il minimo valore per il campo Alert accettato è 5.\n";
    }

    return ritorno;
}

/**Funzione che crea un evento Meeting e lo ritorna
@param date: data nella quale viene creato l'evento
**/
Meeting *ViewMeeting::createEvent(const QDate& date) {
    QString error = "";
    if(checkPushable(error)){
        QTime t2 = QTime(inizio->time()).addSecs(alert->value()*-60);
        return new Meeting(getEmails(),inizio->time(),fine->time(), t2, checkRep->isChecked() , txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(date),checkTag->getTags());
    }else
        throw std::logic_error(error.toStdString());
}
