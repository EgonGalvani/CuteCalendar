#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <QTime>

class Time {
private:
    static unsigned int SECONDS_IN_DAY;
    unsigned int _sec;
public:

    /**
     * @brief Costruttore di default della classe Time. I campi dell'oggetto vengono inizializzati in modo
     *  da indicare l'orario attuale
     */
    Time();

    /**
     * @brief Costruttore a tre parametri della classe Time, rispettivamente: ore, minuti e secondi
     */
    Time(unsigned short, unsigned short, unsigned short = 0);

    /**
      * @brief Conversione implicita QTime => Time
      */
    Time(const QTime&);

    /**
     * @brief Metodo che permette di aggiungere un certo numero di ore all'orario
     */
    void addHours(unsigned int);

    /**
     * @brief Metodo che permette di aggiungere un certo numero di minuti all'orario
     */
    void addMinutes(unsigned int);

    /**
     * @brief Metodo che permette di aggiungere un certo numero di secondi all'orario
     */
    void addSeconds(unsigned int);

    /**
     * @brief Permette di ottenere le ore dell'orario memorizzato
     * @return ore dell'orario
     */
    unsigned short hour() const;

    /**
     * @brief Permette di ottenere i minuti dell'orario memorizzato
     * @return minuti dell'orario
     */
    unsigned short minute() const;

    /**
     * @brief Permette di ottenere i secondi dell'orario memorizzato
     * @return secondi dell'orario
     */
    unsigned short second() const;

    /**
     * @brief Permette di ottenere il numero di secondi passati dalla mezzanotte del giorno precendente
     * @return secondi passati dalla mezzanotte del giorno precedente
     */
    unsigned int secSinceStartOfDay() const;

    /**
     * @brief Permette di ottenere una stringa che rappresenta l'orario memorizzato; la funzione richiede il passaggio di un formato
     *  che sarà seguito per la formazione della stringa richiesta
     * @return una stringa che rappresenta l'orario memorizzato
     */
    std::string toString(const std::string& = "hh:mm:ss") const;

    /**
     * @brief Operatore di disuguaglianza
     * @return true sse i due orari sono diversi
     */
    bool operator!=(const Time&) const;

    /**
     * @brief Operatore di uguaglianza
     * @return true sse i due orari coincidono
     */
    bool operator==(const Time&) const;

    /**
     * @brief Operatore di minore
     * @return true sse l'orario memorizzato è minore di quello indicato
     */
    bool operator<(const Time&) const;

    /**
     * @brief Operatore di minore o uguale
     * @return true sse l'orario memorizzato è minore o coincide con quello indicato
     */
    bool operator<=(const Time&) const;

    /**
     * @brief Operatore di maggiore
     * @return true sse l'orario memorizzato è maggiore di quello indicato
     */
    bool operator>(const Time&) const;

    /**
     * @brief Operatore di maggiore o uguale
     * @return true sse l'orario memorizzato è maggiore o coincide con quello indicato
     */
    bool operator>=(const Time&) const;

    /**
     * @brief Operatore di somma
     * @return un orario ottenuto dalla somma dei due considerati
     */
    Time operator+(const Time&) const;

    /**
     * @brief Operatore di sottrazione
     * @return un orario ottenuto dalla sottrazione dei due considerati
     */
    Time operator-(const Time&) const;

    /**
      * @brief Conversione esplicita Time => QTime
      */
    operator QTime() const;
};

/**
 * @brief Operatore di output
 * @return permette di fare l'output dell'orario, nel formato: hh:mm:ss
 */
std::ostream& operator<<(std::ostream&, const Time&);

/**
 * @brief Operatore di input
 * @return permette di fare l'input di un orario; esso si deve trovare nel formato hh:mm:ss
 */
std::istream& operator>>(std::istream&, Time&);


#endif // TIME_H
