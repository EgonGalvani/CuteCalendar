#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <list>
#include <cstddef> // std::size_t

#include <iostream> // test

#include "invalidinterval.h"

enum RBTreeColor{BLACK, RED};

// i valori di maxBV e minBV sono necessari per la gestione di intervalli aperti
// consideriamo intervalli del tipo [a, b] o (-infty, b] o [a, +infty)
// DT -> DataType, BT -> BoundType, minBV -> min bound value, maxBV -> max bound value

template<class DT, class BT, BT minBV, BT maxBV>
class IntervalTree {
private:
    class Interval {
    public:
        BT _lowBound, _highBound;
        Interval(const BT& = minBV, const BT& = maxBV);
        // Interval& operator=(const Interval&) il funzionamento del costruttore di copia sarebbe uguale a quello standard

        bool overlaps(const Interval&) const;
        bool operlapsExclusive(const Interval&) const;
        bool isPoint() const;
        bool within(const Interval&) const;
        BT size() const;
        bool operator==(const Interval&) const;
    };

    class Node {
    public:
        DT _info;
        Interval _interval;
        BT _maxBoundChild;
        Node *_parent, *_right, *_left;
        RBTreeColor _color;

        Node(const DT&, const Interval& = Interval(), RBTreeColor = BLACK,
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
        friend class IntervalTree<DT, BT, minBV, maxBV>;
    private:
        Node* _node;
        BaseIterator(Node*);
    public:
        BaseIterator();
        DT& operator*() const;
        DT* operator->() const;
        BaseIterator& operator++(); // TODO
        BaseIterator& operator--(); // TODO
        bool operator==(const BaseIterator&) const; // SI RIFERISCE ALL'AREA DI MEMORIA, NON ALL'OGGETTO PUNTATO
        bool operator!=(const BaseIterator&) const;
        BaseIterator right() const;
        BaseIterator left() const;
        BaseIterator parent() const;
    };

    // member functions
    IntervalTree(); // O(1)
    IntervalTree(const IntervalTree&);
    IntervalTree& operator=(const IntervalTree&);
    ~IntervalTree(); // O(n)

    // Iterators
    BaseIterator begin() const;
    BaseIterator end() const;
   //  ConstIterator cbegin() const;
   //  ConstIterator cend() const;

    // Capacity
    bool empty() const; // O(1)
    std::size_t size() const; // O(1)

    // Element access
    DT& front();
    const DT& front() const;
    DT& back();
    const DT& back() const;

    // Modifiers
    void clear();
    BaseIterator insert(const DT&, const BT&, const BT&);
    BaseIterator erase(const BaseIterator&);

    // Operations
    std::list<DT*> intersects(const BT&, const BT&) const;
    DT* intervalSearch(const BT&, const BT&) const;
};

// Interval class
template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::Interval::Interval(const BT& lowBound, const BT& highBound)
    : _lowBound(lowBound), _highBound(highBound) {}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Interval::overlaps(const Interval& i) const {
    return _lowBound <= i._highBound && i._lowBound <= _highBound;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Interval::operlapsExclusive(const Interval& i) const {
    return _lowBound < i._highBound && i._lowBound < _highBound;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Interval::isPoint() const {
    return _lowBound == _highBound;
}

template<class DT, class BT, BT minBV, BT maxBV>
BT IntervalTree<DT, BT, minBV, maxBV>::Interval::size() const {
    return _highBound - _lowBound;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Interval::within(const Interval& i) const {
    return _lowBound >= i._lowBound && _highBound <= i._highBound;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Interval::operator==(const Interval& i) const {
    return _lowBound == i._lowBound && _highBound == i._highBound;
}

// Node class
template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::Node::Node(const DT& info,
       const Interval& interval, RBTreeColor color, Node* parent, Node* right, Node* left)
    : _info(info), _interval(interval), _color(color), _parent(parent), _right(right), _left(left) {}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Node::isRight() const {
    return _parent && _parent->_right == this;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Node::isLeft() const {
    return _parent && _parent->_left == this;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::Node::isRoot() const {
    return !_parent;
}

template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::Node::~Node() {
    delete _left;
    delete _right;
}

// BaseIterator class
template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::BaseIterator()
    : _node(nullptr) {}

template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::BaseIterator(Node* n)
    : _node(n) {}

template<class DT, class BT, BT minBV, BT maxBV>
DT& IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::operator*() const {
    return *_node;
}

template<class DT, class BT, BT minBV, BT maxBV>
DT* IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::operator->() const {
    return _node;
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::operator==(const BaseIterator& it) const {
    return _node == it._node; // confronto le aree di memoria
}

template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::operator!=(const BaseIterator& it) const {
    return _node != it._node;
}

template<class DT, class BT, BT minBV, BT maxBV>
typename IntervalTree<DT, BT, minBV, maxBV>::BaseIterator IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::right() const {
    return BaseIterator(_node->_right);
}

template<class DT, class BT, BT minBV, BT maxBV>
typename IntervalTree<DT, BT, minBV, maxBV>::BaseIterator IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::left() const {
    return BaseIterator(_node->_left);
}

template<class DT, class BT, BT minBV, BT maxBV>
typename IntervalTree<DT, BT, minBV, maxBV>::BaseIterator IntervalTree<DT, BT, minBV, maxBV>::BaseIterator::parent() const {
    return BaseIterator(_node->_parent);
}

// Interval Tree class
template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::IntervalTree() : _root(nullptr), _size(0) {}

// Interval Tree - Capacity
template<class DT, class BT, BT minBV, BT maxBV>
bool IntervalTree<DT, BT, minBV, maxBV>::empty() const {
    return _size == 0;
}

template<class DT, class BT, BT minBV, BT maxBV>
std::size_t IntervalTree<DT, BT, minBV, maxBV>::size() const {
    return _size;
}

// Interval Tree - Modifiers
template<class DT, class BT, BT minBV, BT maxBV>
void IntervalTree<DT, BT, minBV, maxBV>::clear() {
    delete _root;
    _size = 0;
}

template<class DT, class BT, BT minBV, BT maxBV>
typename IntervalTree<DT, BT, minBV, maxBV>::BaseIterator
    IntervalTree<DT, BT, minBV, maxBV>::insert(const DT&, const BT&, const BT&) {

    return BaseIterator();
}

template<class DT, class BT, BT minBV, BT maxBV>
typename IntervalTree<DT, BT, minBV, maxBV>::BaseIterator
    IntervalTree<DT, BT, minBV, maxBV>::erase(const BaseIterator& it) {

    return BaseIterator();
}


template<class DT, class BT, BT minBV, BT maxBV>
IntervalTree<DT, BT, minBV, maxBV>::~IntervalTree() {
    delete _root;
}

#endif // INTERVALTREE_H
