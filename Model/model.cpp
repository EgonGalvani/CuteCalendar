#include "model.h"

// controllo se sono presenti eventi per la data considerata
bool Model::hasEvent(const Date& d) const {
    return _data.bucket_size(d) > 0;
}

// inserisco un nuovo evento nel model
Model::It Model::insertEvent(Event* e) {
    /* quando il deepptr (temporaneo anonimo) viene distrutto
        allora viene chiamato il distruttore virtuale dell'evento e.
        Nell'iteratore ci sarà un oggetto ottenuto tramite una clone */
    auto bucketIt = _data.insert(e->getDate(), DeepPtr<Event>(e));
    return --_data.end(*bucketIt);
}

// rimuovo un evento
void Model::removeEvent(const It& it) {
    _data.erase(_data.find( (*it)->getDate()), it);
}

// ottengo tutti gli eventi pianificati per una determinata data
std::vector<Model::It> Model::getEvents(const Date &d) {
    std::vector<It> its;

    if(hasEvent(d))
        for(It it = _data.begin(d); it != _data.end(d); it++)
            its.push_back(it);
    return its;
}

// serializzazione del model in json
void Model::serialize(QJsonObject &json) const{

    //itero la mappa
    for (auto it = _data.begin();it!=_data.end();++it) {
        auto key = *it;
        QJsonArray arrayEvent = QJsonArray();
        //Itero il vettore
        for (auto vit = _data.begin(key);vit!=_data.end(key);++vit ) {
            QJsonObject eventjson = QJsonObject();
            (*(*vit)).serialize(eventjson);
            arrayEvent.push_back(eventjson);
        }
        //Ogni riga sarà ID progressivo {data,evento1,evento2...,eventoN}
        json[QString::fromStdString(key.toString())] = arrayEvent;
    }
}

// parsing di un model da json
void Model::parse(QJsonObject &json)  {

    //Prima prendo la lista delle chiavi
    QStringList k = json.keys();
    QStringList keys = json.keys();
    //itero le chiavi,keyit poi è QList<QString>, dereferenziando ottengo qstring che uso per
    //"accedere" al json
    for (auto keyit = keys.begin();keyit!=keys.end();++keyit) {
        QJsonArray item = json[*keyit].toArray();
        Date data;
        std::istringstream temp = std::istringstream((*keyit).toStdString());
        temp>>data;
        for (auto it = item.begin();it!=item.end();++it) {
            QJsonObject tmp = (*it).toObject();
            Factory f1 = Factory(tmp);
            _data.insert(data,DeepPtr<Event>(f1.parse()));
        }
    }
}

// serializzazione del model e salvataggio su file
void Model::saveInFile(const QString & path) const {
    QJsonObject obj;
    serialize(obj);
    QJsonDocument doc = QJsonDocument(obj);
    try {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(doc.toJson());
    }catch (...) {}
}

// lettura dei dati del model da file e relativo parsing
void Model::loadFromFile(const QString & path) {
    QFile loadFile(path);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    parse(json);
}


