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

        Node();
        ~Node();
    };

    Node *_root,
         *_parent,
         *_begin,
         *_end;
    unsigned int _bucketSize;
    unsigned int _elementSize; // all elements
public:
    template<bool constness>
    class BaseIterator {
        friend class UnorderedMultimap;
    private:
        T* _ptr;
        bool _pastTheEnd;
        BaseIterator(T*, bool = false);

    public:
        typedef typename std::conditional<constness, const DT*, DT*>::type pointer;
        typedef typename std::conditional<constness, const DT&, DT&>::type reference;
        typedef typename std::conditional<constness, DT, DT>::type value_type;
        typedef typename BaseIterator<constness> self_type;

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

    using LocalIterator = Vector<Value>::Iterator;
    using LocalConstIterator = Vector<Value>::ConstIterator;

    UnorderedMultimap();
    ~UnorderedMultimap();

    // capacity
    bool empty() const;
    unsigned int size() const;

    // iterators
    Iterator begin(); // ritorna un iteratore al primo bucket
    ConstIterator begin() const;
    ConstIterator cbegin() const;

    Iterator end(); // ritorna un iteratore all'ultimo bucket
    ConstIterator end() const;
    ConstIterator cend() const;

    // buckets
    unsigned int bucket_count() const;
    unsigned int bucket_size(const Key&) const;

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

    // delete element inside bucket
    LocalIterator erase(Iterator, LocalIterator);
    LocalIterator erase(Iterator, LocalIterator, LocalIterator);

    // search
    Iterator find(const Key&) const;

#endif // UNORDEREDMULTIMAP_H
