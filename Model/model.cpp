#include "model.h"

bool Model::hasEvent(const Date& d) const {
    return _data.bucket_size(d) > 0;
}

Model::It Model::insertEvent(Event* e) {
    const Date eventDate = e->getDate();

    /* NOTA: quando il deepptr (temporaneo anonimo) viene distrutto
        allora viene distrutto anche l'evento e. Nell'iteratore ci sarà
        un oggetto ottenuto tramite una clone. Per questo è necessario mem*/
    auto bucketIt = _data.insert(eventDate, DeepPtr<Event>(e));
    return --_data.end(*bucketIt);
}

void Model::removeEvent(const It& it) {
    _data.erase(_data.find( (*it)->getDate()), it);
}

std::vector<Model::It> Model::getEvents(const Date &d) {
    std::vector<It> its;

    if(hasEvent(d))
        for(It it = _data.begin(d); it != _data.end(d); it++)
            its.push_back(it);
    return its;
}

void Model::serialize(QJsonObject &json) const{

    int i = 0;
    //itero la mappa
    for (auto it = _data.begin();it!=_data.end();++it,++i) {
        auto key = *it;
        QJsonArray arrayEvent = QJsonArray();
        QString stringaEventi = QString();
        arrayEvent.push_back(QString::fromStdString(key.toString()));
        //Itero il vettore
        for (auto vit = _data.begin(key);vit!=_data.end(key);++vit ) {
            QJsonObject eventjson = QJsonObject();
            (*(*vit)).serialize(eventjson);
            arrayEvent.push_back(eventjson);
        }
        //Ogni riga sarà ID progressivo {data,evento1,evento2...,eventoN}
        json[QString::number(i)] = arrayEvent;
    }
}

void Model::parse(QJsonObject &json)  {

    //Prima prendo la lista delle chiavi


    QStringList k = json.keys();
    QStringList keys = json.keys();
    //itero le chiavi,keyit poi è QList<QString>, dereferenziando ottengo qstring che uso per
    //"accedere" al json
    for (auto keyit = keys.begin();keyit!=keys.end();++keyit) {
        QJsonArray item = json[*keyit].toArray();
        Date data;
        for (auto it = item.begin();it!=item.end();++it) {
            if (it==item.begin()) {
                //Forse aggiungere su date
                std::istringstream temp = std::istringstream((*it).toString().toStdString());
                temp>>data;
            }else {
                QJsonObject tmp = (*it).toObject();
                Factory f1 = Factory(tmp);
                _data.insert(data,DeepPtr<Event>(f1.parse()));
            }
        }

    }

}


