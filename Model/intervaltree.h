#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <list>
#include <cstddef> // std::size_t

enum RBTreeColor{BLACK, RED};

// i valori di maxBoundValue e minBoundValue sono necessari per la gestione di intervalli aperti
template<class DataType, class BoundType, BoundType minBoundValue, BoundType maxBoundValue>
class IntervalTree {
private:
    class Interval {
    public:
        BoundType _lowBound, _highBound;
        Interval(const BoundType& = minBoundValue, const BoundType& = maxBoundValue);
    };

    class Node {
    public:
        DataType _info;
        Interval _interval;
        BoundType _maxBoundChild;
        Node* _parent, _right, _left;
        RBTreeColor _color;

        Node(const DataType&, const Interval& = Interval(), RBTreeColor = RBTreeColor.BLACK,
               Node* = nullptr, Node* = nullptr, Node* = nullptr);
    };

    nodo* root;
    std::size_t size;

    void insert_fixup(nodo*);
    void left_rotate(nodo*);
    void right_rotate(nodo*);
    void transplant(nodo*, nodo*);
    void delete_fixup(nodo*);
public:

    class Iterator {

    };

    class ConstIterator {

    };

    // member functions
    IntervalTree();
    IntervalTree(const IntervalTree&);
    IntervalTree& operator=(const IntervalTree&);
    ~IntervalTree();

    // Iterators
    Iterator begin() const;
    Iterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

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
    Iterator insert(const DataType&, const BoundType&, const BoundType&);
    Iterator erase(const Iterator&);

    // Operations
    std::list<DataType*> intersects(const BoundType&, const BoundType&) const;
    DataType* intervalSearch(const BoundType&, const BoundType&) const;
};

// Interval class
/*Interval(const BoundType& lowBound = minBoundValue,
           const BoundType& highBound = maxBoundValue)
    : _lowBound(lowBound), _highBound(highBound) {}*/

// Node class
/*Node(const DataType& info, const Interval& interval = Interval(), RBTreeColor color = RBTreeColor.BLACK,
       Node* parent = nullptr, Node* right = nullptr, Node* left = nullptr)
    : _info(info), _interval(interval), _color(color), _parent(parent),
        _right(right), _left(left) {}*/

// Iterator class


// Interval class

#endif // INTERVALTREE_H
