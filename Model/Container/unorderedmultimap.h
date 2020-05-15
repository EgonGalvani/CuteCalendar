#ifndef UNORDEREDMULTIMAP_H
#define UNORDEREDMULTIMAP_H

#include "vector.h"

#include <stdexcept>

template<class Key, class Value>
class UnorderedMultimap {
private:
    class Node {
    public:
        Node *_right, *_left, *_parent;
        Key _key;
        Vector<Value> _data;

        /**
         * @brief costruttore di Node
         * @param k: chiave del nodo
         * @param parent: nodo padre di quello corrente (usato per permettere iteratori bidirezionali)
         * @param left: nodo che corrisponde al figlio sinistro
         * @param right: nodo che corrisponde al figlio destro
         */
        Node(const Key& k, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr);

        /**
          * distruttore standard
          */
        ~Node() = default;

        /**
         * @brief verifica se il nodo è figlio sinistro del padre. Non vengono fatti controlli
         *  sull'effettiva esistenza del padre.
         * @return true sse il nodo corrente è sinistro destro di suo padre
         */
        bool isLeft() const;

        /**
         * @brief verifica se il nodo è figlio destro del padre. Non vengono fatti controlli
         *  sull'esistenza del padre
         * @return true sse il nodo corrente è figlio destro di suo padre
         */
        bool isRight() const;

        /**
         * @brief verifica se il nodo corrente è radice dell'albero, cioè se _root == nullptr
         * @return true sse il nodo corrente è radice dell'albero
         */
        bool isRoot() const;
    };

    Node *_root;

    /**
     * @brief numero di chiavi (bucket) presenti all'interno del'albero
     */
    unsigned int _bucketSize;

    /**
     * @brief numero di elementi totali presenti nel container
     */
    unsigned int _elementSize;

    /**
     * @brief copia profonda di un albero radicato in n
     * @param n: radice dell'albero che si vuole copiare
     * @return un puntatore al nuovo albero creato
     */
    static Node* copyTree(Node* n);

    /**
     * @brief permette di individuare il nodo successivo in una vista in-order dell'albero
     * @param n: nodo di cui si vuole trovare il successor
     * @return puntatore al successor di n
     */
    static Node* successor(Node* n);

    /**
     * @brief permette di individuare il nodo precedente in una vista in-order dell'albero
     * @param n: nodo di cui si vuole trovare il predecessor
     * @return puntatore al predecessor di n
     */
    static Node* predecessor(Node* n);

    /**
     * @brief permette di introdurre un nuovo elemento (bucket) nell'albero, che presenta come
     *  chiave il valore di k
     * @param n: radice dell'albero di interesse
     * @param k: chiave che si vuole aggiungere all'albero
     * @return un puntatore al nuovo bucket creato
     */
    static Node* create_bucket(Node* n, const Key& k);

    /**
     * @brief permette di individuare il minimo dell'albero radicato in n
     * @param n: radice dell'albero di cui si vuole trovare il minimo
     * @return un puntatore al nodo che rappresenta il minimo dell'albero radicato in n
     */
    static Node* tree_minimum(Node* n);

    /**
     * @brief permette di individuare il massimo dell'albero radicato in n
     * @param n: radice dell'albero di cui si vuole trovare il massimo
     * @return un puntatore al nodo che rappresenta il massimo dell'albero radicato in n
     */
    static Node* tree_maximum(Node* n);

    /**
     * @brief permette di sostituire il nodo u con il nodo v. Si occupa di aggiornare la
     *  relazione con il padre, e non con i figli (( auqesto do)a questo dovrà pensare la funzione
     *  chiamante)
     * @param u: nodo da sostituire
     * @param v: nodo che va a sostituire u
     */
    void transplant(Node* u, Node* v);

    /**
     * @brief permette l'eliminazione di un albero
     * @param n: radice dell'albero da eliminare
     */
    static void delete_tree(Node* n);
public:

    template<bool constness>
    class BaseIterator {
        friend class UnorderedMultimap;
    private:
        Node* _ptr;
        bool _pastTheEnd;
        BaseIterator(Node*, bool = false);

    public:
        typedef typename std::conditional<constness, const Key*, Key*>::type pointer;
        typedef typename std::conditional<constness, const Key&, Key&>::type reference;
        typedef typename std::conditional<constness, Key, Key>::type value_type;

        /**
         * @brief peremtte di ottenere un riferimento (costante o meno a seconda dell'iteratore)
         *  alla chiave del bucket corrente
         * @return un riferimento alla chiave del bucket riferito dall'iteratore
         */
        reference operator*() const;

        /**
         * @brief peremtte di ottenere un puntatore (costante o meno a seconda dell'iteratore)
         *  alla chiave del bucket corrente
         * @return un puntatore alla chiave del bucket riferito dall'iteratore
         */
        pointer operator->() const;

        /**
         * @brief incremento prefisso, permette di ottenere un iteratore al nodo successivo secondo
         *  una vista in-order dell'albero
         * @return riferimento all'iteratore incrementato
         */
        BaseIterator& operator++();

        /**
         * @brief incremento postfisso, permette di incrementare un iteratore secondo
         *  una vista in-order dell'albero
         * @return iteratore prima di essere incrementato
         */
        BaseIterator operator++(int);

        /**
         * @brief decremento postfisso, permette di decrementare un iteratore secondo
         *  una vista in-order dell'albero
         * @return riferimento all'iteratore decrementato
         */
        BaseIterator& operator--();

        /**
         * @brief decremento postfisso, permette di decrementare un iteratore secondo
         *  una vista in-order dell'albero
         * @return iteratore prima di essere decrementato
         */
        BaseIterator operator--(int);

        /**
         * @brief Operatore di minore
         * @param it: iteratore da confrontare con quello attuale
         * @return true sse l'iteratore attuale precede it secondo una vista in-order
         */
        bool operator<(const BaseIterator& it) const;

        /**
         * @brief operatore di maggiore
         * @param it: iteratore da confrontare con quello attuale
         * @return true sse l'iteratore attuale segue it secondo una vista in-order
         */
        bool operator>(const BaseIterator& it) const;

        /**
         * @brief operatore di minore o uguale
         * @param it: iteratore da confrontare con quello attuale
         * @return true sse l'iteratore attuale precede o coincide con it secondo una vista in-order
         */
        bool operator<=(const BaseIterator& it) const;

        /**
         * @brief operatore di maggiore o uguale
         * @param it: iteratore da confrontare con quello attuale
         * @return true sse l'iteratore attuale segue o coincide con it secondo una vista in-order
         */
        bool operator>=(const BaseIterator& it) const;

        /**
         * @brief operatore di uguaglianza
         * @param it: iteratore da confrontare con quello attuale
         * @return true sse i due iteratori si riferiscono al medesimo bucket
         */
        bool operator==(const BaseIterator& it) const;

        /**
         * @brief operatore di disuguaglianza
         * @param it: iteratore da confrontare con quello attuale
         * @return sse i due iteratori si riferiscono a due bucket distinti
         */
        bool operator!=(const BaseIterator& it) const;
     };

    /**
     * @brief: iteratori sulle chiavi del container
     */
    using Iterator = BaseIterator<false>;
    using ConstIterator = BaseIterator<true>;

    /**
     * @brief: iteratori sugli elementi di una chiave
     */
    using LocalIterator = typename Vector<Value>::Iterator;
    using LocalConstIterator = typename Vector<Value>::ConstIterator;

    /**
     * @brief UnorderedMultimap
     */
    UnorderedMultimap();

    /**
     * @brief UnorderedMultimap
     */
    UnorderedMultimap(const UnorderedMultimap&);

    /**
      *
      */
    ~UnorderedMultimap();

    /**
     * @brief permette di verificare che il contenitore sia vuoto, cioè che il numero di elementi _elementSize
     *  sia uguale a 0 (NOTA: è possibile che in questo caso siano comunque presenti dei bucket all'interno dell'albero,
     *  che comunque saranno vuoti)
     * @return true sse il contenitore è vuoto
     */
    bool empty() const;

    /**
     * @brief permette di verificare il numero di elementi presenti nel container (_elementSize)
     * @return numero di elementi del container
     */
    unsigned int size() const;

    /**
     * @brief permette di ottenere un iteratore alla prima chiave dell'albero, se l'albero è
     *  vuoto allora viene ritornato un iteratore che coincide con il past-the-end
     * @return iteratore al primo bucket dell'albero
     */
    Iterator begin();

    /**
     * @brief permette di ottenere un iteratore costante alla prima chiave dell'albero, se l'albero è
     *  vuoto allora viene ritornato un iteratore che coincide con il past-the-end
     * @return iteratore costante al primo bucket dell'albero
     */
    ConstIterator begin() const;

    /**
     * @brief permette di ottenere un iteratore costante alla prima chiave dell'albero, se l'albero è
     *  vuoto allora viene ritornato un iteratore che coincide con il past-the-end
     * @return iteratore costante al primo bucket dell'albero
     */
    ConstIterator cbegin() const;

    /**
     * @brief permette di ottenere un iteratore al bucket successivo all'ultimo bucket dell'albero
     * @return iteratore past-the-end
     */
    Iterator end();

    /**
     * @brief permette di ottenere un iteratore costante al bucket successivo all'ultimo bucket dell'albero
     * @return iteratore costante past-the-end
     */
    ConstIterator end() const;

    /**
     * @brief permette di ottenere un iteratore costante al bucket successivo all'ultimo bucket dell'albero
     * @return iteratore costante past-the-end
     */
    ConstIterator cend() const;

    /**
     * @brief permette di individurare i numero di chiavi presenti all'interno dell'albero
     * @return il numero di bucket dell'albero
     */
    unsigned int bucket_count() const;

    /**
     * @brief permette di identificare il numero di elementi del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return numero di elementi del bucket con chiave k, se non è presente allora ritorna 0
     */
    unsigned int bucket_size(const Key& k) const;

    /**
     * @brief permette di individurare un iteratore al primo elemento del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return iteratore al primo elemento del bucket con chiave k
     */
    LocalIterator begin(const Key& k);

    /**
     * @brief permette di individurare un iteratore costante al primo elemento del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return iteratore costante al primo elemento del bucket con chiave k
     */
    LocalConstIterator begin(const Key& k) const;

    /**
     * @brief permette di individurare un iteratore costante al primo elemento del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return iteratore costante al primo elemento del bucket con chiave k
     */
    LocalConstIterator cbegin(const Key& k) const;

    /**
     * @brief permette di individurare un iteratore all'elemento successivo all'ultimo elemento del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return iteratore all'elemento successovo all'ultimo elemento del bucket con chiave k
     */
    LocalIterator end(const Key& k);

    /**
     * @brief permette di individurare un iteratore costante all'elemento successivo all'ultimo elemento del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return iteratore costante all'elemento successovo all'ultimo elemento del bucket con chiave k
     */
    LocalConstIterator end(const Key& k) const;

    /**
     * @brief permette di individurare un iteratore costante all'elemento successivo all'ultimo elemento del bucket con chiave k
     * @param k: chiave del bucket di interesse
     * @return iteratore costante all'elemento successovo all'ultimo elemento del bucket con chiave k
     */
    LocalConstIterator cend(const Key& k) const;

    /**
     * @brief permette di inserire un nuovo valore nel bucket con chiave v; se il bucket non è presente allora viene creato
     * @param k: chiave del bucket in cui inserire il valore
     * @param v: valore da inserire
     * @return iteratore al bucket in cui è stato inserito i valore
     */
    Iterator insert(const Key& k, const Value& v);

    /**
     * @brief permette di inserire un elemento all'interno di uno specifico bucket, di cui si ha già un iteratore
     * @param it: iteratore al bucket in cui inserire l'elemento v
     * @param v: valore del nuovo elmento da inserire
     * @return iteratore all'elemento inserito
     */
    LocalIterator insert(const Iterator& it, const Value& v);

    /**
     * @brief permette di eliminare un bucket dal container (inclusi tutti gli elmenti da lui gestiti)
     * @param it: iteratore al bucket di interesse
     * @return iteratore al bucket che ha rimpiazzato quello considerato
     */
    Iterator erase(Iterator it);

    /**
     * @brief permette di eliminare un bucket dal container (inclusi tutti gli elmenti da lui gestiti)
     * @param k: chiave del bucket da eliminare
     * @return numero di elementi che erano presenti all'interno del bucket (e che quindi sono stati eliminati)
     */
    unsigned int erase(const Key& k);

    /**
     * @brief permette di eliminare tutti gli elementi del container
     */
    void clear();

    /**
     * @brief permette di scambiare gli elementi tra due container
     * @param um: unorderedMultimap con cui scambiare gli elementi
     */
    void swap(UnorderedMultimap& um);

    /**
     * @brief permette di eliminare un elmento presente all'interno di un determinato bucket
     * @param it: bucket considerato
     * @param lit: elemento da eliminare
     * @return:
     *  - se il bucket ha ancora qualche elemento, allora un iteratore al bucket stesso
     *  - se gli elementi del bucket sono finiti, il bucket viene rimosso e viene ritornato
     *   un iteratore al bucket successivo
     */
    Iterator erase(Iterator it, LocalIterator lit);

    /**
     * @brief permette di eliminare un intervallo di elementi all'interno di un determinato bucket
     * @param it: bucket considerato
     * @param lit_first: primo elemento da eliminare
     * @param lit_last: elemento successivo all'utlimo da eliminare
     * @return:
     *  - se il bucket ha ancora qualche elemento, allora un iteratore al bucket stesso
     *  - se gli elementi del bucket sono finiti, il bucket viene rimosso e viene ritornato
     *   un iteratore al bucket successivo
     */
    Iterator erase(Iterator it, LocalIterator lit_first, LocalIterator lit_last);

    /**
     * @brief permette di ricercare un bucket con chiave k all'interno dell'albero
     * @param k: chiave da ricerca
     * @return un iteratore al bucket con chiave k
     */
    Iterator find(const Key& k) const;
};

/**
  * Iterator
  */
template<typename K, typename V>
template<bool C>
UnorderedMultimap<K, V>::BaseIterator<C>::BaseIterator(Node* ptr, bool pastTheEnd)
    : _ptr(ptr), _pastTheEnd(pastTheEnd) {}

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

    if(_ptr && !_pastTheEnd) {

        Node* aux = successor(_ptr);
        if(!aux) {
            _ptr++;
            _pastTheEnd = true;
        } else
            _ptr = aux;
    }

    return *this;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>
UnorderedMultimap<K, V>::BaseIterator<C>::operator++(int) {
    auto it = *this;
    operator++();
    return it;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>&
UnorderedMultimap<K, V>::BaseIterator<C>::operator--() {
    if(_ptr) {
        if(_pastTheEnd) {
            _pastTheEnd = false;
            _ptr--;
        } else
            _ptr = predecessor(_ptr);
    }

    return *this;
}

template<typename K, typename V>
template<bool C>
typename UnorderedMultimap<K, V>::template BaseIterator<C>
UnorderedMultimap<K, V>::BaseIterator<C>::operator--(int) {
    auto it = *this;
    operator--();
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
    return _ptr->_key <= it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator>=(const BaseIterator& it) const {
    return _ptr->_key >= it._ptr->_key;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator==(const BaseIterator& it) const {
    return _ptr == it._ptr;
}

template<typename K, typename V>
template<bool C>
bool UnorderedMultimap<K, V>::BaseIterator<C>::operator!=(const BaseIterator& it) const {
    return _ptr != it._ptr;
}


/**
 * Node
 */

template<class K, class V>
UnorderedMultimap<K, V>::Node::Node(const K& key, Node* parent, Node* right, Node* left)
    : _right(right), _left(left), _parent(parent), _key(key) {}

template<class K, class V>
bool UnorderedMultimap<K, V>::Node::isLeft() const {
    return _parent->_left == this;
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
typename UnorderedMultimap<K, V>::Node*
UnorderedMultimap<K, V>::copyTree(Node* n) {
    if(n) {
        Node* n = new Node(n->_key, n->_data, copyTree(n->_left), copyTree(n->_right));

        if(n->_left)
            n->_left->_parent = n;
        if(n->_right)
            n->_left->_parent = n;

        return n;
    }

    return nullptr;
}

template<class K, class V>
UnorderedMultimap<K, V>::UnorderedMultimap()
    : _root(nullptr), _bucketSize(0), _elementSize(0) {}

template<class K, class V>
UnorderedMultimap<K, V>::~UnorderedMultimap() {
    delete_tree(_root);
}

template<class K, class V>
UnorderedMultimap<K, V>::UnorderedMultimap(const UnorderedMultimap& um)
    : _root(copyTree(um._root)), _elementSize(um._elementSize), _bucketSize(um._bucketSize) {}


template<class K, class V>
bool UnorderedMultimap<K, V>::empty() const {
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
unsigned int UnorderedMultimap<K, V>::bucket_size(const K& k) const {
    Iterator it = find(k);
    return it._ptr ? it._ptr->_data.size() : 0;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::find(const K& k) const {

    Node *ptr = _root;
    while(ptr && ptr->_key != k) {
        if(k < ptr->_key)
            ptr = ptr->_left;
        else
            ptr = ptr->_right;
    }

    return Iterator(ptr);
}

// ritorna un iterator al bucket in cui è stato inserito l'elemento
template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::insert(const K& key, const V& value) {
    Iterator it = find(key);

    // se non esiste un bucket con quella chiave, lo aggiugo
    if(!it._ptr) {
        it._ptr = create_bucket(_root, key);
        _bucketSize++;

        if(!_root)
            _root = it._ptr;
    }

    // aggiungo l'elemento
    it._ptr->_data.push_back(value);
    _elementSize++;
    return it;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalIterator
UnorderedMultimap<K, V>::insert(const Iterator& it, const V& v) {
    if(!it._ptr)
        throw std::logic_error("Trying to add element on null bucket!");
    it._ptr->_data.push_back(v);
    _elementSize++;
    return --it._ptr->_data.end();
}

template<class K, class V>
void UnorderedMultimap<K, V>::clear() {
    _bucketSize = 0;
    _elementSize = 0;
    delete_tree(_root);
    _root = nullptr;
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
typename UnorderedMultimap<K, V>::Node*
UnorderedMultimap<K, V>::create_bucket(Node* root, const K& k) {
    Node *current = root,
        *parent = nullptr;

    while(current) {
        parent = current;

        if(k < current->_key)
            current = current->_left;
        else current = current->_right;
    }

    Node* aux = new Node(k, parent);

    if(parent) {
        if(k < parent->_key)
            parent->_left = aux;
        else
            parent->_right = aux;
    }

    return aux;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalIterator
UnorderedMultimap<K, V>::begin(const K& k) {
    Iterator it = find(k);
    return it._ptr->_data.begin();
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalConstIterator
UnorderedMultimap<K, V>::begin(const K& k) const {
    Iterator it = find(k);
    return it._ptr->_data.cbegin();
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalConstIterator
UnorderedMultimap<K, V>::cbegin(const K& k) const {
    Iterator it = find(k);
    return it._ptr->_data.cbegin();
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalIterator
UnorderedMultimap<K, V>::end(const K& k) {
    Iterator it = find(k);
    return it._ptr->_data.end();
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalConstIterator
UnorderedMultimap<K, V>::end(const K& k) const {
    Iterator it = find(k);
    return it._ptr->_data.cend();
}

template<class K, class V>
typename UnorderedMultimap<K, V>::LocalConstIterator
UnorderedMultimap<K, V>::cend(const K& k) const {
    Iterator it = find(k);
    return it._ptr->_data.cend();
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::erase(Iterator it, LocalIterator lit) {
    if(!it._ptr)
        throw std::logic_error("Trying to erase elements from null bucket");
    _elementSize--;
    it._ptr->_data.erase(lit);

    // se non ho più elementi, elimino il bucket
    if(it._ptr->_data.empty())
        return erase(it);

    return it;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::erase(Iterator it, LocalIterator lit_first, LocalIterator lit_last) {
    if(!it._ptr)
        throw std::logic_error("Trying to erase elements from null bucket");
    unsigned int previousSize = it._ptr->_data.size();
    it._ptr->_data.erase(lit_first, lit_last);
    _elementSize -= previousSize - it._ptr->_data.size();

    // se non ho più elementi elimino il bucket
    if(it._ptr->_data.empty())
        return erase(it);

    return it;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::begin() {
    if(!_root)
        return end();
    return Iterator(tree_minimum(_root));
}

template<class K, class V>
typename UnorderedMultimap<K, V>::ConstIterator
UnorderedMultimap<K, V>::begin() const {
    if(!_root)
        return cend();

    return ConstIterator(tree_minimum(_root));
}

template<class K, class V>
typename UnorderedMultimap<K, V>::ConstIterator
UnorderedMultimap<K, V>::cbegin() const {
    if(!_root)
        return cend();
    return ConstIterator(tree_minimum(_root));
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::end() {
    return Iterator(tree_maximum(_root)+1, true);
}

template<class K, class V>
typename UnorderedMultimap<K, V>::ConstIterator
UnorderedMultimap<K, V>::end() const {
    return ConstIterator(tree_maximum(_root)+1, true);
}

template<class K, class V>
typename UnorderedMultimap<K, V>::ConstIterator
UnorderedMultimap<K, V>::cend() const {
    return ConstIterator(tree_maximum(_root)+1, true);
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Iterator
UnorderedMultimap<K, V>::erase(Iterator it) {
    if(!it._ptr || it._pastTheEnd)
        throw std::logic_error("Trying to erase null bucket");

    Node* z = it._ptr, *w = nullptr;
    if(!z->_left) {
        w = z->_right;
        transplant(z, z->_right);
    } else if(!z->_right) {
        w = z->_left;
        transplant(z, z->_left);
    } else {
        Node* y = tree_minimum(z->_right);
        w = y;

        if(y->_parent != z) {
            transplant(y, y->_right);
            y->_right = z->_right;
            y->_right->_parent = y;
        }

        transplant(z, y);
        y->_left = z->_left;
        y->_left->_parent = y;
    }

    _bucketSize--;
    _elementSize -= it._ptr->_data.size();
    delete it._ptr;
    return Iterator(w);
}

template<class K, class V>
unsigned int UnorderedMultimap<K, V>::erase(const K& k) {
    Iterator it = find(k);
    if(it._ptr) {
        unsigned int size = it._ptr->_data.size();
        erase(it); // ci pensa lui ad aggiornare la _bucketSize ed _elementSize

        return size;
    }

    return 0;
}


template<class K, class V>
typename UnorderedMultimap<K, V>::Node*
UnorderedMultimap<K, V>::successor(Node* n) {
    if(n->_right)
        return tree_minimum(n->_right);

    Node *parent = n->_parent;
    while(parent && n->isRight()) {
        n = parent;
        parent = parent->_parent;
    }
    return parent;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Node*
UnorderedMultimap<K, V>::predecessor(Node* n) {
    if(n->_left)
        return tree_maximum(n->_left);

    Node* parent = n->_parent;
    while(parent && n->isLeft()) {
        n = parent;
        parent = parent->_parent;
    }
    return parent;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Node*
UnorderedMultimap<K, V>::tree_minimum(Node* n) {
    while(n && n->_left)
        n = n->_left;
    return n;
}

template<class K, class V>
typename UnorderedMultimap<K, V>::Node*
UnorderedMultimap<K, V>::tree_maximum(Node* n) {
    while(n && n->_right)
        n = n->_right;
    return n;
}

template<class K, class V>
void UnorderedMultimap<K, V>::delete_tree(Node* n) {
    if(n) {
        if(n->_left)
            delete_tree(n->_left);
        if(n->_right)
            delete_tree(n->_right);

        delete n;
    }
}

// sostituisco v ad u, non aggiorna v.left e v.right, questo è compito della procedura che chiama transplant
template<class K, class V>
void UnorderedMultimap<K, V>::transplant(Node* u, Node* v) {
    if(u->isRoot())
        _root = v;
    else if(u->isLeft())
        u->_parent->_left = v;
    else u->_parent->_right = v;

    if(v)
        v->_parent = u->_parent;
}

#endif // UNORDEREDMULTIMAP_H
