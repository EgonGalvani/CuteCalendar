#ifndef VECTOR_H
#define VECTOR_H

#include <limits>
#include <stdexcept>
#include <iostream> // TODO: togliere cout di test
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
       friend class IntervalTree;
   private:
       T* _ptr;
       BaseIterator(T* = nullptr); // fatto

   public:
       typedef typename std::conditional<constness, const T*, T*>::type pointer;
       typedef typename std::conditional<constness, const T&, T&>::type reference;
       typedef typename std::conditional<constness, T, T>::type value_type;

       reference operator*() const;  // fatto
       reference operator[](unsigned int) const; // fatto
       pointer operator->() const; // fatto

       BaseIterator& operator+=(int); // fatto // no controllo sui bound
       BaseIterator& operator-=(int); // fatto // no controllo sui bound
       BaseIterator operator+(int); // fatto // no controllo sui bound
       BaseIterator operator-(int); // fatto // no controllo sui bound
       BaseIterator& operator++(); // fatto
       BaseIterator operator++(int); // fatto
       BaseIterator& operator--(); // fatto
       BaseIterator operator--(int); // fatto

       bool operator<(const BaseIterator&) const; // fatto
       bool operator>(const BaseIterator&) const; // fatto
       bool operator<=(const BaseIterator&) const; // fatto
       bool operator>=(const BaseIterator&) const; // fatto
       bool operator==(const BaseIterator&) const; // fatto
       bool operator!=(const BaseIterator&) const; // fatto
    };

    using Iterator = BaseIterator<false>;
    using ConstIterator = BaseIterator<true>;

    // costruttori
    // explicit Vector(const ConstIterator&, const ConstIterator&);
    explicit Vector(unsigned int =0, const T& = T()); // fatto
    Vector(const Vector&); // fatto

    // distruttori
    ~Vector(); // fatto

    // assegnazione
    Vector& operator=(const Vector&); // fatto

    // iterators
    Iterator begin(); // fatto
    ConstIterator begin() const; // fatto
    ConstIterator cbegin() const; // fatto

    Iterator end(); // fatto
    ConstIterator end() const; // fatto
    ConstIterator cend() const; // fatto

    // capacity
    bool empty() const; // fatto
    unsigned int size() const; // fatto
    unsigned int capacity() const; // fatto
    void reserve(unsigned int); // fatto
    void resize(unsigned int, const T& = T()); // fatto
    static unsigned int max_size(); // fatto

    // element access
    T& front(); // fatto
    const T& front() const; // fatto
    T& back(); // fatto
    const T& back() const; // fatto
    T& at(unsigned int); // fatto
    const T& at(unsigned int) const; // fatto
    T& operator[](unsigned int); // fatto  // no controlli sui bound
    const T& operator[](unsigned int) const; // fatto  // no controlli sui bound

    // modifiers
    void push_back(const T&); // fatto
    void pop_back(); // fatto
    Iterator insert(const ConstIterator&, const T&);
    Iterator insert(const ConstIterator&, unsigned int, const T &);
    Iterator erase(const ConstIterator&);
    Iterator erase(const ConstIterator&, const ConstIterator&);
    void swap(Vector&); // fatto
    void clear(); // fatto

    // search
    Iterator find(const T&);
    ConstIterator find(const T&) const;

    bool operator==(const Vector&) const; // fatto
    bool operator!=(const Vector&) const; // fatto
    bool operator<(const Vector&) const; // fatto
    bool operator>(const Vector&) const; // fatto
    bool operator<=(const Vector&) const; // fatto
    bool operator>=(const Vector&) const; // fatto
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
Vector<T>::BaseIterator<C>::operator+(int pos) {
    return BaseIterator<C>(_ptr+pos);
}

template<typename T>
template<bool C>
typename Vector<T>::template BaseIterator<C>
Vector<T>::BaseIterator<C>::operator-(int pos) {
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
    : _vector(size ? new T[size] : nullptr), _size(size), _capacity(size) {

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
    // if(newCapacity > max_size())
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

/* If n is smaller than the current container size, the content is reduced to its first n elements,
 * removing those beyond (and destroying them).

    If n is greater than the current container size, the content is expanded by inserting at the end
    as many elements as needed to reach a size of n. If val is specified, the new elements are initialized
    as copies of val, otherwise, they are value-initialized.

    If n is also greater than the current container capacity, an automatic reallocation of the allocated storage
    space takes place.
*/
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

    if(_size == _capacity) _capacity *= 2;
    unsigned int pos = static_cast<unsigned int>(position._ptr - _vector);

    T* aux = new T[_capacity];
    for(unsigned int i = 0; i < pos; i++)
        aux[i] = _vector[i];
    aux[pos] = t;

    for(unsigned int i = pos; i < _size; i++)
        aux[i+1] = _vector[i];

    delete[] _vector;
    _size++;
    _vector = aux;

    return new Iterator(aux+pos);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::insert(const ConstIterator& position, unsigned int number, const T& t) {

}

template<typename T>
typename Vector<T>::Iterator Vector<T>::erase(const ConstIterator& position) {

}

// elimina gli elementi in [first, last)
template<typename T>
typename Vector<T>::Iterator Vector<T>::erase(const ConstIterator& first, const ConstIterator& last) {
    unsigned int number = static_cast<unsigned int>(last - first);

    _size -= number;
} // ritorna un iteratore alla nuova posizione di last

template<typename T>
void Vector<T>::clear() {
    delete[] _vector;
    _capacity = _size = 0;
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
