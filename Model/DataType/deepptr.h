#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <stdexcept>

template<typename T>
class DeepPtr {
private:
    T* _ptr;
public:

    /* costruttore che non crea una copia profonda, si occupa semplicemente
        di gestire il puntatore passato */
    explicit DeepPtr(T* = nullptr);

    // costruttore di copia profonda
    DeepPtr(const DeepPtr&);

    // distruzione polimorfa, viene sfruttato il distruttore virtuale di T
    // cioè nel caso di questo progetto: di Event e classi da lui derivate
    ~DeepPtr();

    // operatore di assegnazione profonda
    DeepPtr& operator=(const DeepPtr&);

    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;

    void swap(DeepPtr&);

    // vengono confrontati gli indirizzi delle aree di memoria puntate, e non il contenuto
    bool operator==(const DeepPtr&) const;
    bool operator!=(const DeepPtr&) const;
};

template<typename T>
DeepPtr<T>::DeepPtr(T* ptr) : _ptr(ptr) {}

template<typename T>
DeepPtr<T>::DeepPtr(const DeepPtr& p)
    : _ptr(p._ptr ? (*p)->clone() : nullptr) {}

template<typename T>
DeepPtr<T>::~DeepPtr() {
    delete _ptr;
}

template<typename T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& p) {
    if(this != &p) {
        delete _ptr;
        _ptr = p._ptr ? p._ptr->clone() : nullptr;
    }

    return *this;
}

template<typename T>
T& DeepPtr<T>::operator*() {
    if(!_ptr) throw std::runtime_error("NullPtrException while dereferencing smart pointer");
    return *_ptr;
}

template<typename T>
const T& DeepPtr<T>::operator*() const {
    if(!_ptr) throw std::runtime_error("NullPtrException while dereferencing smart pointer");
    return *_ptr;
}

template<typename T>
T* DeepPtr<T>::operator->() {
    if(!_ptr) throw std::runtime_error("NullPtrException while dereferencing smart pointer");
    return _ptr;
}

template<typename T>
const T* DeepPtr<T>::operator->() const {
    if(!_ptr) throw std::runtime_error("NullPtrException while dereferencing smart pointer");
    return _ptr;
}

template<typename T>
void DeepPtr<T>::swap(DeepPtr& p) {
    T* tmp = _ptr;
    _ptr = p._ptr;
    p._ptr = tmp;
}

template<typename T>
bool DeepPtr<T>::operator==(const DeepPtr& p) const {
    return _ptr == p;
}

template<typename T>
bool DeepPtr<T>::operator!=(const DeepPtr& p) const {
    return _ptr != p;
}

#endif // SMARTPTR_H
