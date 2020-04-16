#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <list>
#include <cstddef> // std::size_t

#include <iostream> // test

#include "invalidinterval.h"

enum RBTreeColor{BLACK, RED};

// i valori di maxBoundValue e minBoundValue sono necessari per la gestione di intervalli aperti
// consideriamo intervalli del tipo [a, b] o (-infty, b] o [a, +infty)

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
class IntervalTree {
private:
    class Interval {
    public:
        BoundType _lowBound, _highBound;
        Interval(const BoundType& = minBoundValue, const BoundType& = maxBoundValue);
        // Interval& operator=(const Interval&) il funzionamento del costruttore di copia sarebbe uguale a quello standard

        bool overlaps(const Interval&) const;
        bool operlapsExclusive(const Interval&) const;
        bool isPoint() const;
        bool within(const Interval&) const;
        BoundType size() const;
        bool operator==(const Interval&) const;
    };

    class Node {
    public:
        DataType _info;
        Interval _interval;
        BoundType _maxBoundChild;
        Node *_parent, *_right, *_left;
        RBTreeColor _color;

        Node(const DataType&, const Interval& = Interval(), RBTreeColor = BLACK,
               Node* = nullptr, Node* = nullptr, Node* = nullptr);
        ~Node();

        bool isRight() const;
        bool isLeft() const;
        bool isRoot() const;
    };

    Node* _root;
    std::size_t _size;

    void insert_fixup(Node*);
    void left_rotate(Node*);
    void right_rotate(Node*);
    void transplant(Node*, Node*);
    void delete_fixup(Node*);
public:

    class BaseIterator {
        friend class IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>;
    private:
        Node* _node;
        BaseIterator(Node*);
    public:
        BaseIterator();
        DataType& operator*() const;
        DataType& operator->() const;
        BaseIterator& operator++();
        BaseIterator& operator--();
        bool operator==(const BaseIterator&) const;
        bool operator!=(const BaseIterator&) const;
        BaseIterator& right();
        BaseIterator& left();
        BaseIterator& parent();
    };

    // member functions
    IntervalTree();
    IntervalTree(const IntervalTree&);
    IntervalTree& operator=(const IntervalTree&);
    ~IntervalTree();

    // Iterators
    BaseIterator begin() const;
    BaseIterator end() const;
   //  ConstIterator cbegin() const;
   //  ConstIterator cend() const;

    // Capacity
    bool empty() const;
    std::size_t size() const;

    // Element access
    DataType& front();
    const DataType& front() const;
    DataType& back();
    const DataType& back() const;

    // Modifiers
    void clear();
    BaseIterator insert(const DataType&, const BoundType&, const BoundType&);
    BaseIterator erase(const BaseIterator&);

    // Operations
    std::list<DataType*> intersects(const BoundType&, const BoundType&) const;
    DataType* intervalSearch(const BoundType&, const BoundType&) const;
};

// Interval class
template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::Interval(const BoundType& lowBound, const BoundType& highBound)
    : _lowBound(lowBound), _highBound(highBound) {}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::overlaps(const Interval& i) const {
    return _lowBound <= i._highBound && i._lowBound <= _highBound;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::operlapsExclusive(const Interval& i) const {
    return _lowBound < i._highBound && i._lowBound < _highBound;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::isPoint() const {
    return _lowBound == _highBound;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
BoundType IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::size() const {
    return _highBound - _lowBound;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::within(const Interval& i) const {
    return _lowBound >= i._lowBound && _highBound <= i._highBound;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Interval::operator==(const Interval& i) const {
    return _lowBound == i._lowBound && _highBound == i._highBound;
}

// Node class
template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Node::Node(const DataType& info,
       const Interval& interval, RBTreeColor color, Node* parent, Node* right, Node* left)
    : _info(info), _interval(interval), _color(color), _parent(parent), _right(right), _left(left) {}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Node::isRight() const {
    return _parent && _parent->_right == this;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Node::isLeft() const {
    return _parent && _parent->_left == this;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
bool IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Node::isRoot() const {
    return !_parent;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::Node::~Node() {
    delete _left;
    delete _right;
}

// Iterator class


// Interval Tree class
template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::IntervalTree()
    : _root(nullptr), _size(0) {
    std::cout << "Albero creato con successo" << std::endl;
}

template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
IntervalTree<DataType, BoundType, minBoundValue, maxBoundValue>::~IntervalTree() {
    std::cout << "Albero eliminato con successo" << std::endl;
    delete _root;
}

#endif // INTERVALTREE_H
