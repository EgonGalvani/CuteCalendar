#ifndef VECTOR_H
#define VECTOR_H

#include <limits>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Vector {
private:
    T* _vector;
    unsigned int _size;
    unsigned int _capacity;
public:

   template<bool constness>
   class BaseIterator {
       friend class Vector;
   private:
       T* _ptr;
       BaseIterator(T* = nullptr);

   public:
       typedef typename std::conditional<constness, const T*, T*>::type pointer;
       typedef typename std::conditional<constness, const T&, T&>::type reference;
       typedef typename std::conditional<constness, T, T>::type value_type;

       /**
        * @brief ritorna un riferimento (costante o meno a seconda del tipo di iteratore) all'elemento corrente
        * @return riferimento all'elemento corrente
        */
       reference operator*() const;

       /**
        * @brief ritorna un riferimento (costante o meno a seconda del tipo di iteratore) all'elemento che si trova
        *   a distanza dist da quello corrente. Non vengono eseguiti controlli sui bound.
        * @param dist: distanza dall'elemento desiderato
        * @return riferimento all'elemento che si trova a distanza diff da quello attuale.
        */
       reference operator[](unsigned int dist) const;

       /**
        * @brief ritorna un puntatore (costante o meno a seconda del tipo di iteratore) all'elemento corrente
        * @return puntatore all'elemento corrente
        */
       pointer operator->() const;

       /**
        * @brief fa avanzare di diff posizioni l'iteratore. Non vengono fatti controlli sui bound.
        * @param diff: numero di posizioni di cui far avanzare l'iteratore attuale
        * @return un riferimento all'iteratore attuale, avanzato di diff posizioni
        */
       BaseIterator& operator+=(int diff);

       /**
        * @brief fa retrocedere di diff posizioni l'iteratore. Non vengono fatti controlli sui bound.
        * @param diff: numero di posizioni di cui far retrocedere l'iteratore attuale
        * @return un riferimento all'iteratore attuale, retrocesso di diff posizioni
        */
       BaseIterator& operator-=(int);

       /**
        * @brief crea un iteratore avanzato di diff posizioni rispetto a quello attuale (che invece non subisce alcun
        *   tipo di modifica). Non vengono fatti controlli sui bound.
        * @param diff: numero di posizioni dall'iteratore attuale
        * @return un iteratore avanzato di diff posizioni rispetto a quello attuale
        */
       BaseIterator operator+(int diff) const;

       /**
        * @brief crea un iteratore retrocesso di diff posizioni rispetto a quello attuale (che invece non subisce alcun
        *   tipo di modifica). Non vengono fatti controlli sui bound.
        * @param diff: numero di posizioni dall'iteratore attuale
        * @return un iteratore retrocesso di diff posizioni rispetto a quello attuale
        */
       BaseIterator operator-(int diff) const;

       /**
        * @brief Operator di incremento prefisso: incremeta l'iteratore attuale e lo ritorna per riferimento.
        *  Non vengono fatti controlli sui bound.
        * @return un riferimento all'iteratore attuale incrementato
        */
       BaseIterator& operator++();

       /**
        * @brief Operator di incremento postfisso: incremeta l'iteratore attuale e ne ritorna un iteratore allo
        *   stato precedente. Non vengono fatti controlli sui bound.
        * @return l'iteratore prima di essere incrementato
        */
       BaseIterator operator++(int);

       /**
        * @brief Operator di decremento prefisso: decrementa l'iteratore attuale e lo ritorna per riferimento.
        *  Non vengono fatti controlli sui bound.
        * @return un riferimento all'iteratore attuale decrementato
        */
       BaseIterator& operator--();

       /**
        * @brief Operator di decremento postfisso: decrementa l'iteratore attuale e ne ritorna un iteratore allo
        *   stato precedente. Non vengono fatti controlli sui bound.
        * @return l'iteratore prima di essere decrementato
        */
       BaseIterator operator--(int);

       /**
        * @brief Operatore di minore
        * @param it: iteratore da confrontare con quello attuale
        * @return true sse l'iteratore attuale si riferisce ad un'area di memoria precedente a quella riferita da it
        */
       bool operator<(const BaseIterator& it) const;

       /**
        * @brief Operatore di maggiore
        * @param it: iteratore da confrontare con quello attuale
        * @return true sse l'iteratore attuale si riferisce ad un'area di memoria successiva a quella riferita da it
        */
       bool operator>(const BaseIterator& it) const;

       /**
        * @brief Operatore di minore o uguale
        * @param it: iteratore da confrontare con quello attuale
        * @return true sse l'iteratore attuale si riferisce ad un'area di memoria che precede o coincide con
        *   a quella riferita da it
        */
       bool operator<=(const BaseIterator& it) const;

       /**
        * @brief Operatore di maggiore o uguale
        * @param it: iteratore da confrontare con quello attuale
        * @return true sse l'iteratore attuale si riferisce ad un'area di memoria successiva o che coincide con
        *   quella riferita da it
        */
       bool operator>=(const BaseIterator& it) const;

       /**
        * @brief Operatore di uguaglianza
        * @param it: iteratore da confrontare con quello attuale
        * @return true sse i due iteratori si riferiscono al medesimo elemento del container
        */
       bool operator==(const BaseIterator& it) const;

       /**
        * @brief Operatore di disuguaglianza
        * @param it: iteratore da confrontare con quello attuale
        * @return true sse i due iteratori si riferiscono a due elementi distinti del container
        */
       bool operator!=(const BaseIterator& it) const;
    };

    using Iterator = BaseIterator<false>;
    using ConstIterator = BaseIterator<true>;

   /**
     * @brief Crea un oggetto di tipo vector, costituito da n occorrenze dell'oggetto t;
     *  in particolare il valore di n verrà associato alla _size e _capacity dell'oggetto.
     *  Si noti che se n == 0, allora la _capacity viene comunque posta a 1.
     * @param n: numero di elementi da inserire
     * @param t: valore che devono avere gli elementi inseriti
     */
    explicit Vector(unsigned int n=0, const T& t= T());

    /**
     * @brief Costruttore di copia profonda di Vector. Crea un oggetto con _size e _capacity
     *  coincidenti a quelle di v. La copia del campo _vector di v avviene in maniera profonda.
     * @param v: vettore da copiare
     */
    Vector(const Vector& v);

    /**
      * @brief Distruttore: si occupa di dealloccare _vector
      */
    ~Vector();

    /**
     * @brief Operatore di assegnazione. Si occupa di dealloccare il _vector dell'oggetto attuale
     *  e copiare (in maniera profonda) lo stato interno di v
     * @return un riferimento all'oggetto attuale, per permettere assegnazioni a cascata
     */
    Vector& operator=(const Vector& v);

    /**
     * @brief Ritorna un iteratore al primo elemento del vettore
     * @return un iteratore al primo elemento del vettore
     */
    Iterator begin();

    /**
     * @brief Ritorna un iteratore costante al primo elemento del vettore
     * @return un iteratore costante al primo elemento del vettore
     */
    ConstIterator begin() const;

    /**
     * @brief Ritorna un iteratore costante al primo elemento del vettore
     * @return un iteratore costante al primo elemento del vettore
     */
    ConstIterator cbegin() const;

    /**
     * @brief Ritorna un iteratore all'elemento successivo all'ultimo elemento del vettore
     * @return iteratore all'elemento successivo all'ultimo elemento del vettore
     */
    Iterator end();

    /**
     * @brief Ritorna un iteratore costnate all'elemento successivo all'ultimo elemento del vettore
     * @return iteratore costante all'elemento successivo all'ultimo elemento del vettore
     */
    ConstIterator end() const;

    /**
     * @brief Ritorna un iteratore costante all'elemento successivo all'ultimo elemento del vettore
     * @return iteratore costante all'elemento successivo all'ultimo elemento del vettore
     */
    ConstIterator cend() const;

    /**
     * @brief Verifica se il vettore è vuoto, cioè se _size == 0
     * @return true sse il vettore è vuoto
     */
    bool empty() const;

    /**
     * @brief Permette di ottenere il numero di elementi presenti all'interno del vettore
     * @return il numero di elementi del vettore (_size)
     */
    unsigned int size() const;

    /**
     * @brief Permette di ottenere la capacità attuale del vettore
     * @return la capacità del vettore (_capacity)
     */
    unsigned int capacity() const;

    /**
     * @brief Permette di richiedere di riservare lo spazio per memorizzare almeno n elementi.
     *  In particolare n, se maggiore di _capacity, andrà ad inidicare il nuovo valore di _capacity.
     *  ( solo nel caso appena indicato si assiste ad un ridimensionamento del vettore )
     */
    void reserve(unsigned int n);

    /**
     * @brief
     *  - Se n è più piccolo della _size attuale, il contenuto è ridotto ai primi n elementi
     *  - Se n è maggiore di _size, allora il vengono aggiunti gli elementi necessari per raggiungere n, i quali
     *      saranno tutti uguali a t
     *  - Se n è maggiore anche dell'attuale _capacity allora si innescherà una riallocazione automatica del vettore
     * @param n: nuova dimensione del vector
     * @param t: valore da associare ai nuovi elementi
     */
    void resize(unsigned int n, const T& t = T());

    /**
     * @brief Metodo utilizzato per identificare il numero massimo di elementi che il vector può contenere. Poichè sia per la
     *  _size che per la _capacity sono usate variabili di tipo: unsigned int, allora il valore coinciderà con il massimo valore
     *  rappresentabile da un unsigned int
     * @return il numero massimo di elementi memorizzabili correttamente all'interno del container
     */
    static unsigned int max_size();

    /**
     * @brief Ritorna un riferimento al primo elemento del vettore
     * @return riferimento al primo elemento del vettore
     */
    T& front();

    /**
     * @brief Ritorna un riferimento costante al primo elemento del vettore
     * @return riferimento costante al primo elemento del vettore
     */
    const T& front() const;

    /**
     * @brief Ritorna un riferimento all'ultimo elemento del vettore
     * @return riferimento all'ultimo elemento del vettore
     */
    T& back();

    /**
     * @brief Ritorna un riferimento costante all'ultimo elemento del vettore
     * @return riferimento costante all'ultimo elemento del vettore
     */
    const T& back() const;

    /**
     * @brief ritorna un riferimento all'elemento che si trova in posizione pos nel vettore.
     *  Fa controlli sui bound.
     * @param pos: posizione dell'elemento di interesse.
     * @return un riferimento all'elemento che si trova in posizione pos
     */
    T& at(unsigned int pos);

    /**
     * @brief ritorna un riferimento costante all'elemento che si trova in posizione pos nel vettore.
     *  Fa controlli sui bound.
     * @param pos: posizione dell'elemento di interesse.
     * @return un riferimento costante all'elemento che si trova in posizione pos
     */
    const T& at(unsigned int) const;

    /**
     * @brief ritorna un riferimento all'elemento che si trova in posizione pos nel vettore.
     *  Non fa alcun controllo sui bound.
     * @param pos: posizione dell'elemento di interesse.
     * @return un riferimento all'elemento che si trova in posizione pos
     */
    T& operator[](unsigned int pos);

    /**
     * @brief ritorna un riferimento costante all'elemento che si trova in posizione pos nel vettore.
     *  Non fa alcun controllo sui bound.
     * @param pos: posizione dell'elemento di interesse.
     * @return un riferimento costante all'elemento che si trova in posizione pos
     */
    const T& operator[](unsigned int pos) const;

    /**
     * @brief Inserisce una copia dell'elemento t all'interno del vettore
     */
    void push_back(const T& t);

    /**
     * @brief Rimuove l'ultimo elemento del vettore
     */
    void pop_back();

    /**
     * @brief Inserisce una copia dell'elemento t nella posizione indica dall'iteratore it
     *  (spostando di conseguenza gli elmenti successivi di una posizione in avanti)
     * @param it: iteratore che indica la posizione in cui inserire il nuovo elemento
     * @param t: valore da attribuire al nuovo elemento
     * @return un iteratore che punta al nuovo elemento inserito
     */
    Iterator insert(const ConstIterator& it, const T& t);

    /**
     * @brief Inserisce number copie dell'elemento t dalla posizione indica dall'iteratore it
     *  (spostando di conseguenza gli elmenti successivi di number posizioni in avanti)
     * @param it: iteratore che indica la posizione da cui inserire i nuovi elementi
     * @param number: numero di elementi da inserire
     * @param t: valore da attribuire ad ognuno dei nuovi elementi
     * @return un iteratore che punta al primo nuovo elemento inserito
     */
    Iterator insert(const ConstIterator& it, unsigned int number, const T& t);

    /**
     * @brief erase
     * @return
     */
    Iterator erase(const ConstIterator&);

    /**
     * @brief erase
     * @return
     */
    Iterator erase(const ConstIterator&, const ConstIterator&);

    /**
     * @brief Scambia lo stato del vettore attuale con quello del vettore v,
     *  andando ad aggiornare anche _size e _capacity
     */
    void swap(Vector& v);

    /**
     * @brief Rimuove tutti gli elementi del vettore, aggiornando di conseguenza anche
     *  _size e _capacity
     */
    void clear();

    /**
     * @brief Operatore di uguaglianza
     * @param v: vettore da confrontare con quello attuale
     * @return true sse i due vettori presentano la stessa _size e tutti i loro elementi coincidono
     */
    bool operator==(const Vector& v) const;

    /**
     * @brief Operatore di disuguaglianza
     * @param v: vettore da confrontare con quello attuale
     * @return true sse i due vettori presentano _size diverse o se alcuni dei loro elementi non coincidono
     */
    bool operator!=(const Vector& v) const;

    /**
     * @brief Operatore di minore
     * @param v: vettore da confrontare con quello attuale
     * @return se il vettore è minore rispetto a v secondo un confronto lessicografico
     */
    bool operator<(const Vector& v) const;

    /**
     * @brief Operatore di maggiore
     * @param v: vettore da confrontare con quello attuale
     * @return se il vettore è maggiore rispetto a v secondo un confronto lessicografico
     */
    bool operator>(const Vector& v) const;

    /**
     * @brief Operatore di minore o uguale
     * @param v: vettore da confrontare con quello attuale
     * @return se il vettore è minore o uguale a v secondo un confronto lessicografico
     */
    bool operator<=(const Vector& v) const;

    /**
     * @brief Operatore di maggiore o uguale
     * @param v: vettore da confrontare con quello attuale
     * @return se il vettore è maggiore o uguale a v secondo un confronto lessicografico
     */
    bool operator>=(const Vector& v) const;
};

/**
  * ITERATOR
  */
template<typename T>
template<bool C>
Vector<T>::BaseIterator<C>::BaseIterator(T* ptr) : _ptr(ptr) {}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>::reference
Vector<T>::BaseIterator<C>::operator*() const {
    return *_ptr;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>::reference
Vector<T>::BaseIterator<C>::operator[](unsigned int pos) const {
    return *(_ptr + pos);
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>::pointer
Vector<T>::BaseIterator<C>::operator->() const {
    return *_ptr;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>&
Vector<T>::BaseIterator<C>::operator+=(int pos) {
    _ptr += pos;
    return *this;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>&
Vector<T>::BaseIterator<C>::operator-=(int pos) {
    _ptr -= pos;
    return *this;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>
Vector<T>::BaseIterator<C>::operator+(int pos) const {
    return BaseIterator<C>(_ptr+pos);
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>
Vector<T>::BaseIterator<C>::operator-(int pos) const {
    return BaseIterator<C>(_ptr-pos);
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>&
Vector<T>::BaseIterator<C>::operator++() {
    _ptr++;
    return *this;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>
Vector<T>::BaseIterator<C>::operator++(int) {
    auto it = *this;
    _ptr++;
    return it;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>&
Vector<T>::BaseIterator<C>::operator--() {
    _ptr--;
    return *this;
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>
Vector<T>::BaseIterator<C>::operator--(int) {
    auto it = *this;
    _ptr--;
    return it;
}

template<typename T>
template<bool C>
bool Vector<T>::BaseIterator<C>::operator<(const BaseIterator& it) const {
    return _ptr < it._ptr;
}

template<typename T>
template<bool C>
bool Vector<T>::BaseIterator<C>::operator>(const BaseIterator& it) const {
    return _ptr > it._ptr;
}

template<typename T>
template<bool C>
bool Vector<T>::BaseIterator<C>::operator<=(const BaseIterator& it) const {
    return _ptr <= it._ptr;
}

template<typename T>
template<bool C>
bool Vector<T>::BaseIterator<C>::operator>=(const BaseIterator& it) const {
    return _ptr >= it._ptr;
}

template<typename T>
template<bool C>
bool Vector<T>::BaseIterator<C>::operator==(const BaseIterator& it) const {
    return _ptr == it._ptr;
}

template<typename T>
template<bool C>
bool Vector<T>::BaseIterator<C>::operator!=(const BaseIterator& it) const {
    return _ptr != it._ptr;
}

/**
 * VECTOR
 */
template<typename T>
Vector<T>::Vector(unsigned int size, const T& t)
    : _vector(size ? new T[size] : new T[1]), _size(size), _capacity(size ? size : 1) {

    for(unsigned int i = 0; i < size; i++)
        _vector[i] = t;
}

template<typename T>
Vector<T>::Vector(const Vector& v) :
    _vector(v.capacity() ? new T[v._capacity] : nullptr),
    _size(v._size),
    _capacity(v._capacity) {

    for(unsigned int i = 0; i < _size; i++)
        _vector[i] = v._vector[i];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
    if(this != &v) {
        delete _vector;
        _size = v._size;
        _capacity = v._capacity;
        _vector = new T[_capacity];

        for(unsigned int i = 0; i < _size; i++)
            _vector[i] = v._vector[i];
    }

    return *this;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::begin() {
    return Iterator(_vector);
}

template<typename T>
typename Vector<T>::ConstIterator Vector<T>::begin() const {
    return ConstIterator(_vector);
}

template<typename T>
typename Vector<T>::ConstIterator Vector<T>::cbegin() const {
    return ConstIterator(_vector);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::end() {
    return Iterator(_vector + _size);
}

template<typename T>
typename Vector<T>::ConstIterator Vector<T>::end() const {
    return ConstIterator(_vector + _size);
}

template<typename T>
typename Vector<T>::ConstIterator Vector<T>::cend() const {
    return ConstIterator(_vector + _size);
}

template<typename T>
Vector<T>::~Vector() {
    delete[] _vector;
}

template<typename T>
bool Vector<T>::empty() const {
    return _size == 0;
}

template<typename T>
unsigned int Vector<T>::size() const {
    return _size;
}

template<typename T>
unsigned int Vector<T>::capacity() const {
    return _capacity;
}

template<typename T>
void Vector<T>::reserve(unsigned int newCapacity) {
    // TODO if(newCapacity > max_size())
    //     throw length_error

    if(newCapacity > _capacity) {
        T* aux = new T[newCapacity];
        for(unsigned int i = 0; i < _size; i++)
            aux[i] = _vector[i];
        delete[] _vector;
        _vector = aux;
        _capacity = newCapacity;
    }
}

template<typename T>
void Vector<T>::resize(unsigned int newSize, const T& t) {
    if(newSize < _size)
        _size = newSize;
    else if(newSize <= _capacity){
        unsigned int diff = newSize - _size;
        for(unsigned int i = 0; i < diff; i++)
            _vector[_size+1] = t;
        _size = newSize;
    } else {
        T* aux = new T[newSize];

        for(unsigned int i = 0; i < newSize; i++) {
            if(i < _size)
                aux[i] = _vector[i];
            else aux[i] = t;
        }

        delete[] _vector;
        _size = _capacity = newSize;
    }
}

template<typename T>
unsigned int Vector<T>::max_size() {
    return std::numeric_limits<unsigned int>::max();
}

// element access
template<typename T>
T& Vector<T>::front() {
    return _vector[0];
}

template<typename T>
const T& Vector<T>::front() const {
    return _vector[0];
}

template<typename T>
T& Vector<T>::back() {
    return _vector[_size-1];
}

template<typename T>
const T& Vector<T>::back() const {
    return _vector[_size-1];
}

template<typename T>
T& Vector<T>::at(unsigned int pos) {
    if(pos > _size)
        throw std::out_of_range("Trying to access invalid element");

    return _vector[pos];
}

template<typename T>
const T& Vector<T>::at(unsigned int pos) const {
    if(pos > _size)
        throw std::out_of_range("Trying to access invalid element");

    return _vector[pos];
}

template<typename T>
T& Vector<T>::operator[](unsigned int pos) {
    return _vector[pos];
}

template<typename T>
const T& Vector<T>::operator[](unsigned int pos) const {
    return _vector[pos];
}

template<typename T>
void Vector<T>::push_back(const T& t) {
    if(_size == _capacity)
        reserve(_capacity*2); // la reserve si occupa già di modificare la _capacity

    _vector[_size++] = t;
}

template<typename T>
void Vector<T>::pop_back() {
    if(_size)
        _size--;
}

// inserisco l'elemento prima di quello inserito dal position
template<typename T> // ---> vedere di semplicemente traslare gli elementi
typename Vector<T>::Iterator Vector<T>::insert(const ConstIterator& position, const T& t) {
    return insert(position, 1, t);
}

// ritorna un iteratore al primo elemento inserito
template<typename T>
typename Vector<T>::Iterator Vector<T>::insert(const ConstIterator& position, unsigned int number, const T& t) {
    int pos = static_cast<unsigned int>(position._ptr - _vector);

    if(_size + number > _capacity) {
        _capacity = (_size + number) * 2;
        T* aux = new T[_capacity];

        // copio quelli precedenti
        for(unsigned int i = 0; i < pos; i++)
            aux[i] = _vector[i];

        // inserisco quelli da aggiungere
        for(unsigned int i = 0; i < number; i++)
            aux[pos+i] = t;

        // copio i rimanenti
        for(unsigned int i = pos; i < _size; i++)
            aux[i+1] = _vector[i];

        delete[] _vector;
        _size++;
        _vector = aux;
        return Iterator(aux+pos);
    }

    // sposto tutti gli elementi a dx di number
    for(int i = _size-1; i >= pos; i--)
        _vector[i+number] = _vector[i];

    // inserisco tutti gli elementi
    for(unsigned int i = 0; i < number; i++)
        _vector[pos+i] = t;
    _size++;

    return Iterator(_vector+pos);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::erase(const ConstIterator& position) {
    return erase(position, position+1);
}

// elimina gli elementi in [first, last)
template<typename T>
typename Vector<T>::Iterator Vector<T>::erase(const ConstIterator& first, const ConstIterator& last) {
    unsigned int number = static_cast<unsigned int>(last._ptr - first._ptr);
    unsigned int lastPosition = static_cast<unsigned int>(last._ptr - _vector);
    unsigned int firstPosition = static_cast<unsigned int>(first._ptr - _vector);

    // devo eliminare gli elmenti in [first, last)
    for(unsigned int i = lastPosition; i < _size; i++) {
        _vector[i-number] = _vector[i];
    }

    _size -= number;
    return Iterator(_vector+firstPosition);
} // ritorna un iteratore alla nuova posizione di last

template<typename T>
void Vector<T>::clear() {
    delete[] _vector;
    _size = 0;
    _capacity = 1;
    _vector = new T[1];
}

template<typename T>
void Vector<T>::swap(Vector & v) {
    unsigned int auxSize = v._size,
        auxCapacity = v._capacity;
    T* auxVector = v._vector;

    v._capacity = _capacity;
    v._size = _size;
    v._vector = _vector;

    _size = auxSize;
    _capacity = auxCapacity;
    _vector = auxVector;
}

template<typename T>
bool Vector<T>::operator==(const Vector& v) const {
    bool equal = _size == v._size;
    for(unsigned int  i = 0; i < _size && equal; i++)
        equal = _vector[i] == v._vector[i];
    return equal;
}

template<typename T>
bool Vector<T>::operator!=(const Vector& v) const {
    return !operator==(v);
}

template<typename T>
bool Vector<T>::operator<(const Vector& t) const {
    unsigned int minSize = std::min(_size, t._size);
    for(unsigned int i = 0; i < minSize; i++) {
        if(_vector[i] != t._vector[i])
            return _vector[i] < t._vector[i];
    }

    // sono uguali per il tratto comune -> è minore quello con dimensione minore
    return _size < t._size;
}

template<typename T>
bool Vector<T>::operator>(const Vector& t) const {
    return t < *this;
}

template<typename T>
bool Vector<T>::operator<=(const Vector& t) const {
    return !operator>(t);
}

template<typename T>
bool Vector<T>::operator>=(const Vector& t) const {
    return !operator<(t);
}

#endif // VECTOR_H
