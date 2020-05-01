#ifndef UNORDEREDMULTIMAP_H
#define UNORDEREDMULTIMAP_H

#include "vector.h"

template<class Key, class Value>
class UnorderedMultimap {
private:
    class Node {
    public:
        Node *_right, *_left, *_parent;
        Key _key;
        Vector<Value> _data;

        Node(const Key&, Node* = nullptr, Node* = nullptr, Node* = nullptr); // fatto
        ~Node(); // fatto

        bool isLeft() const; // fatto // no controlli su parent
        bool isRight() const;  // fatto // no controlli su parent
        bool isRoot() const; // fatto
    };

    Node *_root;

    unsigned int _bucketSize; // numero di chiavi
    unsigned int _elementSize; // numero totale di elementi

    static Node* copyTree(Node*); // fatto
    static Node* successor(Node*); // da controllare
    static Node* predecessor(Node*); // da controllare
    static Node* create_bucket(const Key&); // fatto
public:

    template<bool constness>
    class BaseIterator {
        friend class UnorderedMultimap;
    private:
        Node* _ptr;
        bool _pastTheEnd;
        BaseIterator(Key*, bool = false);

    public:
        typedef typename std::conditional<constness, const Key*, Key*>::type pointer;
        typedef typename std::conditional<constness, const Key&, Key&>::type reference;
        typedef typename std::conditional<constness, Key, Key>::type value_type;

        reference operator*() const; // fatto
        pointer operator->() const; // fatto

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

    using LocalIterator = typename Vector<Value>::Iterator;
    using LocalConstIterator = typename Vector<Value>::ConstIterator;

    UnorderedMultimap(); // fatto
    UnorderedMultimap(const UnorderedMultimap&); // fatto
    ~UnorderedMultimap(); // fatto

    // capacity
    bool empty() const; // fatto
    unsigned int size() const; // fatto

    // iterators
    Iterator begin(); // ritorna un iteratore al primo bucket
    ConstIterator begin() const;
    ConstIterator cbegin() const;

    Iterator end(); // ritorna un iteratore all'ultimo bucket
    ConstIterator end() const;
    ConstIterator cend() const;

    // buckets
    unsigned int bucket_count() const; // fatto
    unsigned int bucket_size(const Key&) const; // fatto

    LocalIterator begin(const Key&); // ritorna un iteratore al primo elemento del bucket con chiave Key
    LocalConstIterator begin(const Key&) const;
    LocalConstIterator cbegin(const Key&) const;

    LocalIterator end(const Key&); // ritorna un iteratore al past the end del bucket con chiave key
    LocalConstIterator end(const Key&) const;
    LocalConstIterator cend(const Key&) const;

    // insert
    Iterator insert(const Key&, const Value&); // fatto // ritorna un iterator al bucket in cui è stato inserito l'elemento
    LocalIterator insert(const Iterator&, const Value&); // fatto // ritorna l'iteratore all'elemento inserito

    // delete all bucket
    Iterator erase(const Iterator&);
    unsigned int erase(const Key&);

    void clear(); // fatto
    void swap(UnorderedMultimap&); // fatto

    // delete element inside bucket
    LocalIterator erase(Iterator, LocalIterator);
    LocalIterator erase(Iterator, LocalIterator, LocalIterator);

    // search
    Iterator find(const Key&) const; // fatta
};

/**
  * Iterator
  */
template<typename K, typename V>
template<bool C>
UnorderedMultimap<K, V>::BaseIterator<C>::BaseIterator(T* ptr) : _ptr(ptr) {}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>::reference
UnorderedMultimap<K, V>::BaseIterator<C>::operator*() const {
    return _ptr->_key;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>::pointer
UnorderedMultimap<K, V>::BaseIterator<C>::operator->() const {
    return &(_ptr->_key);
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>&
UnorderedMultimap<K, V>::BaseIterator<C>::operator++() {
    _ptr = successor(_ptr);
    return *this;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>
UnorderedMultimap<K, V>::BaseIterator<C>::operator++(int) {
    auto it = *this;
    _ptr = successor(_ptr);
    return it;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>&
UnorderedMultimap<K, V>::BaseIterator<C>::operator--() {
    _ptr = predecessor(_ptr);
    return *this;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>
UnorderedMultimap<K, V>::BaseIterator<C>::operator--(int) {
    auto it = *this;
    _ptr = predecessor(_ptr);
    return it;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator<(const BaseIterator& it) const {
    return _ptr->_key < it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator>(const BaseIterator& it) const {
    return _ptr->_key > it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator<=(const BaseIterator& it) const {
    return_ptr->_key <= it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator>=(const BaseIterator& it) const {
    return _ptr->_key >= it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator==(const BaseIterator& it) const {
    return _ptr->_key == it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator!=(const BaseIterator& it) const {
    return _ptr->_key != it._ptr->_key;
}


/**
 * Node
 */

template<class K, class V>
UnorderedMultimap<K, V>::Node::Node(const K& key, Node* parent, Node* right, Node* left)
    : _key(key), _right(right), _left(left), _parent(parent) {}

template<class K, class V>
UnorderedMultimap<K, V>::Node::~Node() {
    delete _right;
    delete _left;
}

template<class K, class V>
bool UnorderedMultimap<K, V>::Node::isLeft() const {
    return _parent->_left = this;
}

template<class K, class V>
bool UnorderedMultimap<K, V>::Node::isRight() const {
    return _parent->_right == this;
}

template<class K, class V>
bool UnorderedMultimap<K, V>::Node::isRoot() const {
    return !_parent;
}

/**
 * Unordered Multimap
 */

template<class K, class V>
Node* copyTree(Node* n) {
    if(n)
        return new Node(n->_key, n->_data, copyTree(n->_left), copyTree(n->_right));
    return nullptr;
}

template<class K, class V>
UnorderedMultimap<K, V>::UnorderedMultimap()
    : _root(nullptr), _elementSize(0), _bucketSize(0){}

template<class K, class V>
UnorderedMultimap<K, V>::~UnorderedMultimap() {
    delete _root;
}

template<class K, class V>
UnorderedMultimap<K, V>::UnorderedMultimap(const UnorderedMultimap& um)
    : _root(copyTree(um._root)), _elementSize(um._elementSize), _bucketSize(um._bucketSize) {}


template<class K, class V>
unsigned int UnorderedMultimap<K, V>::empty() const {
    return _elementSize == 0;
}

template<class K, class V>
unsigned int UnorderedMultimap<K, V>::size() const {
    return _elementSize;
}

template<class K, class V>
unsigned int UnorderedMultimap<K, V>::bucket_count() const {
    return _bucketSize;
}

template<class K, class V>
unsigned int UnorderedMultimap<K, V>::bucket_size(const Key& k) const {
    Iterator it = find(k);
    return it._ptr ? it._ptr->_data.size() : 0;
}

template<class K, class V>
Iterator UnorderedMultimap<K, V>::find(const Key& k) const {
    Node *ptr = _root;
    while(ptr && ptr->_key != k) {
        if(ptr->_key < k)
            ptr = ptr->_left;
        else
            ptr = ptr->_right;
    }

    return Iterator(ptr);
}

// ritorna un iterator al bucket in cui è stato inserito l'elemento
template<class K, class V>
UnorderedMultimap<K, V>::Iterator insert(const K& key, const V& value) {
    Iterator it = find(key);

    // se non esiste un bucket con quella chiave, lo aggiugo
    if(!it->_ptr) {
        it->_ptr = create_bucket(key);
        _bucketSize++;
    }

    // aggiungo l'elemento
    it->_ptr->_data.push_back(value);
    _elementSize++;
}

template<class K, class V>
LocalIterator insert(const Iterator& it, const Value& v) {
    it->_ptr->_data.push_back(v);
    _elementSize++;
    return --it->_ptr->data.end();
}

template<class K, class V>
void UnorderedMultimap<K, V>::clear() {
    _bucketSize = 0;
    _elementSize = 0;
    delete _root;
}

template<class K, class V>
void UnorderedMultimap<K, V>::swap(UnorderedMultimap& um) {
    Node* auxRoot = _root;
    unsigned int auxBucketSize = _bucketSize,
        auxElementSize = _elementSize;

    _root = um._root;
    _bucketSize = um._bucketSize;
    _elementSize = um._elementSize;

    um._root = auxRoot;
    um._bucketSize = auxBucketSize;
    um._elementSize = auxElementSize;
}

// PRE = la chiave k non esiste nell'albero
template<class K, class V>
typename UnorderedMultimap<K, V>::Node
UnorderedMultimap<K, V>::create_bucket(const Key& k) {
    Node *current = _root,
        *parent = _nullptr;

    while(current) {
        parent = current;

        if(current->_key < k)
            current = current->_left;
        else
            current = current->_right;
    }

    Node* aux = new Node(k, parent);

    if(parent) {
        if(key < parent->_key)
            parent->_left = aux;
        else
            parent->_right = aux;
    }

    return aux;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Node*
successor(Node* n) {
    if(n->_right) {
        n = n->_right;
        while(n->_left)
            n = n->_left;
        return n;
    }

    Node *parent = n->_parent;
    while(parent && n->isRight()) {
        n = parent;
        parent = parent->_parent;
    }

    return parent;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Node*
predecessor(Node* n) {
    if(n->_left) {
        while(n->_right)
            n = n->_right;
    } else {
        Node* parent = n->_parent;
        while(parent && n->isLeft()) {
            n = parent;
            parent = parent->_parent;
        }
        n = parent;
    }

    return n;
}


#endif // UNORDEREDMULTIMAP_H
