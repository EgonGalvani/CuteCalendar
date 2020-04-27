#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <stdexcept>

template<typename T>
class DeepPtr {
private:
    T* _ptr;
public:
    explicit DeepPtr(T* = nullptr);
    DeepPtr(const DeepPtr&);
    ~DeepPtr();
    DeepPtr& operator=(const DeepPtr&);
    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;

    void swap(DeepPtr&);

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
        _ptr = p._ptr ? (*p)->clone() : nullptr;
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
