#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <QDate>

class Date {
private:
    unsigned short _year, _month, _day;
    static const int DAYS_OF_MONTH[12];
public:

    /**
     * @brief Costruttore di default di Date. L'oggetto è creato in modo da riferirsi alla data attuale
     */
    Date();

    /**
     * @brief Costruttore ad un parametro, che permette la conversione implicita QDate => Date
     * @param q: Qdate di cui si vuole ottenere un oggetto Date
     */
    Date(const QDate& q);

    /**
     * @brief Costruttore a tre parametri di Date, accetta rispetettivamente anno, mese e giorno
     */
    Date(unsigned short, unsigned short, unsigned short);

    /**
     * @brief Metodo che permette di ottenere il giorno della data memorizzata
     * @return il giorno della memorizzata
     */
    unsigned short day() const;

    /**
     * @brief Metodo che permette di ottenere il giorno della settimana della data memorizzata
     * @return un intero che va da 1 a 7 e indica il giorno della settimana della data
     */
    unsigned short dayOfWeek() const;

    /**
     * @brief Metodo che permette di ottenere il giorno dell'anno della data
     * @return il numero di giorni passati da inizio anno alla data memorizzata
     */
    unsigned short dayOfYear() const;

    /**
     * @brief Metodo che permette di ottenere il numero di giorni totali del mese della data
     * @return numero di giorni del mese della data
     */
    unsigned short daysInMonth() const;

    /**
     * @brief Metodo che permette di ottenere il numero di giorni dell'anno della data
     * @return giorni dell'anno della data
     */
    unsigned short daysInYear() const;

    /**
     * @brief Permette di ottenere il mese della data
     * @return mese della data
     */
    unsigned short month() const;

    /**
     * @brief Permette di ottenere l'anno della data
     * @return anno della data
     */
    unsigned short year() const;

    /**
     * @brief Permette di convertire la data in stringa. La funzione accetta una stringa che deve rappresentare
     *  il formato finale della data
     * @return la data sottoforma di stringa, nel formato richiesto
     */
    std::string toString(const std::string& = "dd/mm/yyyy") const;

    /**
     * @brief Operatore di disuguaglianza
     * @return true sse le due date considerate sono diverse
     */
    bool operator!=(const Date&) const;

    /**
     * @brief Operatore di uguaglianza
     * @return true sse le due date considerate coincidono
     */
    bool operator==(const Date&) const;

    /**
     * @brief Operatore di minore
     * @return true sse la data rappresentata dall'oggetto corrente è minore di quella passata
     */
    bool operator<(const Date&) const;

    /**
     * @brief Operatore di minore o uguale
     * @return true sse la data rappresentata dall'oggetto corrente è minore o coincide con quella passata
     */
    bool operator<=(const Date&) const;

    /**
     * @brief Operatore di maggiore
     * @return true sse la data rappresentata dall'oggetto corrente è maggiore di quella passata
     */
    bool operator>(const Date&) const;

    /**
     * @brief Operatore di maggiore o uguale
     * @return true sse la data rappresentata dall'oggetto corrente è maggiore o coincide con quella passata
     */
    bool operator>=(const Date&) const;

    /**
     * @brief Permette di verificare se un anno è bisestile o no
     * @return true sse l'anno indicato è bisestile
     */
    static bool isLeapYear(unsigned short);

    /**
     * @brief Permette di ottenere il numero di giorni di un determinato mese dell'anno
     * @return il numero di giorni del mese, controllando anche se l'anno indicato è bisestile o meno
     */
    static unsigned short daysInMonth(unsigned short, unsigned short);
};

/**
 * @brief Operatore di output
 * @return Permette di fare l'output della data, nel formato: giorno/mese/anno
 */
std::ostream& operator<<(std::ostream&, const Date&);

/**
 * @brief Operatore di input
 * @return Permette di fare l'input di una data, essa si deve trovare nel formato giorno/mese/anno
 */
std::istream& operator>>(std::ostream&, Date&);

#endif // DATE_H
