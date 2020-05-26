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

ViewMeeting::ViewMeeting(QDate date,QWidget *parent)
    : ModView(date, parent), emailLineEdit(new EnterLineEdit(this)), emailList(new QListWidget(this)) {

    emailLineEdit->setPlaceholderText("Inserisci un'email e premi invio");

    inizio= new QTimeEdit(this);
    fine= new QTimeEdit(this);
    alert = new QTimeEdit(this);
    checkRep= new QCheckBox("Ripeti avviso all'inizio dell'evento", this);

    emailLabel= new QLabel("Emails", this);
    alertL= new QLabel("Notifica", this);
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

void ViewMeeting::pushSaves(Model::It it) {
    ModView::pushSaves(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        currEve->setStartTime(inizio->time());
        currEve->setEndTime(fine->time());
        currEve->setAlertTime(alert->time());
        currEve->setRepeat(checkRep->isChecked());

        //Conversione EditText -> vector
    } else
        throw std::logic_error("Tipo errato per la modifica di una view meeting");
}

void ViewMeeting::fillView(Model::It it) {
    ModView::fillView(it);

    Meeting* currEve = dynamic_cast<Meeting*>(&**it);
    if(currEve) {
        inizio->setTime(currEve->getStartTime());
        fine->setTime(currEve->getEndTime());
        alert->setTime(currEve->getAlertTime());
        checkRep->setChecked(currEve->doesRepeat());
        //conversione vector-> EditText

    } else
        throw std::logic_error("Tipo errato per essere mostrato in una view meeting");
}

Meeting *ViewMeeting::createEvent()
{
    //manca emails e data
    Meeting* ritorno = new Meeting(checkTag->getTags(),inizio->time(),fine->time(), alert->time() , checkRep->isChecked() , txtNome->text().toStdString(),txtDesc->toPlainText().toStdString(),txtLuogo->text().toStdString(),Date(12,12,2000),checkTag->getTags());
    return ritorno;
}
