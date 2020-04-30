#ifndef UNORDEREDMULTIMAP_H
#define UNORDEREDMULTIMAP_H

#include "vector.h"

template<class Key, class Value>
class UnorderedMultimap {
private:
    class Node {
    public:
        Node *_right, *_left;
        Key _key;
        Vector<Value> _data;

        Node(const Key&, Node* = nullptr, Node* = nullptr); // fatto
        ~Node(); // fatto
    };

    Node *_root;

    unsigned int _bucketSize; // numero di chiavi
    unsigned int _elementSize; // numero totale di elementi

    static Node* copyTree(Node*);
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

        BaseIterator();

        reference operator*() const;
        reference operator[](unsigned int) const;
        pointer operator->() const;

        BaseIterator& operator+=(int); // no controllo sui bound
        BaseIterator& operator-=(int); // no controllo sui bound
        BaseIterator operator+(int); // no controllo sui bound
        BaseIterator operator-(int); // no controllo sui bound
        BaseIterator& operator++();
        BaseIterator operator++(int);
        BaseIterator& operator--();
        BaseIterator operator--(int);

        bool operator<(const BaseIterator&) const;
        bool operator>(const BaseIterator&) const;
        bool operator<=(const BaseIterator&) const;
        bool operator>=(const BaseIterator&) const;
        bool operator==(const BaseIterator&) const;
        bool operator!=(const BaseIterator&) const;
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
    unsigned int bucket_size(const Key&) const; // da ricontrollare

    LocalIterator begin(const Key&); // ritorna un iteratore al primo elemento del bucket con chiave Key
    LocalConstIterator begin(const Key&) const;
    LocalConstIterator cbegin(const Key&) const;

    LocalIterator end(const Key&); // ritorna un iteratore al past the end del bucket con chiave key
    LocalConstIterator end(const Key&) const;
    LocalConstIterator cend(const Key&) const;

    // insert
    Iterator insert(const Key&, const Value&); // ritorna un iterator al bucket in cui è stato inserito l'elemento
    LocalIterator insert(const Iterator&, const Value&); // ritorna l'iteratore all'elemento inserito

    // delete all bucket
    Iterator erase(const Iterator&);
    unsigned int erase(const Key&);

    void clear();
    void swap(const UnorderedMultimap&);

    // delete element inside bucket
    LocalIterator erase(Iterator, LocalIterator);
    LocalIterator erase(Iterator, LocalIterator, LocalIterator);

    // search
    Iterator find(const Key&) const;
};

/**
 * Node
 */

template<class K, class V>
UnorderedMultimap<K, V>::Node::Node(const K& key, Node* right, Node* left)
    : _key(key), _right(right), _left(left) {
}

template<class K, class V>
UnorderedMultimap<K, V>::Node::~Node() {
    delete _right;
    delete _left;
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
    return it._ptr->_data.size();
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

template<class K, class V>
void UnorderedMultimap<K, V>::clear() {
    _bucketSize = 0;
    _elementSize = 0;
    delete _root;
}

template<class K, class V>
void UnorderedMultimap<K, V>::swap(const UnorderedMultimap& um) {
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


#endif // UNORDEREDMULTIMAP_H
