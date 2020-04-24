#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <list>
#include <cstddef>
#include <stdexcept>
#include <iostream> // TODO: togliere cout di test

/**
 * @brief Tipo enum utilizzato per indicare il colore delle foglie di un albero rosso-nero
 */
enum RBTreeColor{BLACK, RED};

template<class DT, class BT>
class IntervalTree {
private:

    /**
     * @brief Classe usata per la rappresentazione dell'intervallo associato ad ogni nodo
     */
    class Interval {
    public:
        /**
         * @brief i due estremi dell'intervallo considerato
         */
        BT _lowBound, _highBound;

        /**
         * @brief Costruttore dell'intervallo, necessita dei due estremi dell'intervallo stesso
         */
        Interval(const BT&, const BT&); // TODO: aggiungere eccezioni se minBound > maxBound

        /**
         * @brief Verifica se l'intervallo attuale si interseca con un intervallo dato
         * @return true sse i due intervalli si intersecano
         */
        bool overlaps(const Interval&) const;

        /**
         * @brief Verifica se l'intervallo attuale si interseca con un intervallo dato (estremi esclusi)
         * @return true sse i due intervalli si intersecano (estremi esclusi)
         */
        bool operlapsExclusive(const Interval&) const;

        /**
         * @brief Verifica se l'intervallo attuale coincide con un punto
         * @return true sse i due estremi dell'intervallo coincidono
         */
        bool isPoint() const;

        /**
         * @brief within
         * @return
         */
        bool within(const Interval&) const;

        /**
         * @brief Calcola la dimensione dell'intervallo
         * @return la dimensione dell'intervallo
         */
        BT size() const;

        /**
         * @brief Verifica se i due intervalli coincidono
         * @return true sse i due intervalli presentano gli stessi estremi
         */
        bool operator==(const Interval&) const;
    };

    /**
     * @brief Classe usata per la rappresentazione di un nodo dell'albero
     */
    class Node {
    public:
        /**
         * @brief Informazione contenuta nel nodo
         */
        DT _info;

        /**
         * @brief Intervallo associato al nodo considerato
         */
        Interval _interval;

        /**
         * @brief Massimo estremo tra gli intervalli del nodo attuale e dei nodi dell'albero radicato in esso
         */
        BT _maxBoundChild;

        /**
         * @brief Poichè la struttura si basa su un albero rosso-nero, allora ad ogni foglia è associato un colore
         */
        RBTreeColor _color;

        /**
         * @brief Padre e figli del nodo attuale. Se il nodo non presenta uno di essi, allora questo è posto a nullptr
         */
        Node *_parent, *_right, *_left;

        /**
         * @brief Costruttore della classe Node, richiede: dell'informazione da contenere, di un intervallo ed eventualmente
         *  di un colore, di un padre, figlio destro e sinistro.
         */
        Node(const DT&, const Interval& = Interval(), RBTreeColor = RED,
               Node* = nullptr, Node* = nullptr, Node* = nullptr);

        /**
          * @brief Distruttore del nodo corrente, innesca la distruzione dell'intero albero radicato in esso
          */
        ~Node();

        /**
         * @brief Verifica se il nodo attuale è figlio destro del relativo padre
         * @return true sse il nodo attuale è figlio destro
         */
        bool isRight() const;

        /**
         * @brief Verifica se il nodo attuale è figlio sinistro del relativo padre
         * @return true sse il nodo attuale è figlio sinistro
         */
        bool isLeft() const;

        /**
         * @brief Verifica se il nodo attuale è la radice dell'albero
         * @return true sse il nodo non ha padre
         */
        bool isRoot() const;

        /**
         * @brief La chiave di ogni nodo è rappresentata dall'estremo sinistro dell'intervallo a lui associato
         * @return la chiave del nodo
         */
        BT getKey() const;
    };

    /**
     * @brief Puntatore alla radice dell'albero
     */
    Node* _root;

    /**
     * @brief Numero di nodi che costituiscono l'albero
     */
    std::size_t _size;

    /**
     * @brief Procedura di fix necessaria a seguito di un inserimento, per mantenere le proprietà di un albero
     *  rosso-nero
     */
    void insert_fixup(Node*);

    /**
     * @brief Procedura di rotazione sinistra di un nodo
     */
    void left_rotate(Node*);

    /**
     * @brief Procedura di rotazione destra di un nodo
     */
    void right_rotate(Node*);

    /**
     * @brief Procedura di sostituzione di un nodo con un altro
     */
    void transplant(Node*, Node*);

    /**
     * @brief Procedura di eliminazione di un nodo dall'albero
     */
    void delete_node(Node*);

    /**
     * @brief Procedura di fix necessaria a seguito dell'eliminazione di un nodo dell'albero, si occupa di mantenere
     *  le proprietà di un albero rosso-nero
     */
    void delete_fixup(Node*);

    /**
     * @brief Procedura di fix necessaria a seguito di una modifica all'albero, si occupa di aggiornare i campi
     *  _maxBoundChild dei nodi
     */
    void recalculate_max(Node*);

public:

    /**
     * @brief Classe di base utilizzata per la creazione di iteratori, la variabile booleana indicata nel template
     *  permette di utilizzare tale classe per la creazione sia di iteratori normali sia di iteratori costanti
     */
    template<bool constness>
    class BaseIterator {
        friend class IntervalTree;
    private:

        /**
         * @brief Nodo riferito dall'iteratore corrente
         */
        Node* _node;

        /**
         * @brief Indica se l'iteratore si trova nello stato di "past the end"
         */
        bool _pastTheEnd;

        /**
         * @brief Costruttore privato dell'iteratore, richiede: il nodo a cui puntare e se lo stato da considerare si
         *  past the end
         */
        BaseIterator(Node*, bool = false);
    public:

        /**
         * @brief Tipo definito per indicare un puntatore, il quale potrà essere costante o meno a seconda
         *  dell'iteratore considerato
         */
        typedef typename std::conditional<constness, const DT*, DT*>::type pointer;

        /**
         * @brief Tipo definito per indicare un riferimento, il quale potrà essere costante o meno a seconda
         *  dell'iteratore considerato
         */
        typedef typename std::conditional<constness, const DT&, DT&>::type reference;

        /**
         * @brief Costruttore di default dell'iteratore, imposta _node a nullptr e _pastTheEnd a false
         */
        BaseIterator();

        /**
         * @brief Operatore di dereferenziazione
         * @return un riferimento alla variabile puntata da _node.
         *  Non viene fatto alcun tipo di controllo riguardo ad un possibile nullptr
         */
        reference operator*() const;

        /**
         * @brief Operatore di ->
         * @return un puntatore alla variabile puntata da _node.
         */
        pointer operator->() const;

        /**
         * @brief Operatore di incremento prefisso. In particolare l'iteratore viene incrementato seguendo una vista
         *  in-order dell'albero
         * @return un riferimento all'iteratore avanzato di 1
         */
        BaseIterator& operator++();

        /**
         * @brief Operatore di incremento postfisso. In particolare l'iteratore viene incrementato seguendo una vista
         *  in-order dell'albero
         * @return TODO
         */
        BaseIterator operator++(int);

        /**
         * @brief Operatore di incremento prefisso. In particolare l'iteratore viene decrementato seguendo una vista
         *  in-order dell'albero
         * @return un riferimento all'iteratore decrementato di 1
         */
        BaseIterator& operator--();

        /**
         * @brief Operatore di incremento postfisso. In particolare l'iteratore viene decrementato seguendo una vista
         *  in-order dell'albero
         * @return TODO
         */
        BaseIterator operator--(int);

        /**
         * @brief Operatore di uguaglianza
         * @return true sse i due iteratori considerati stanno puntando alla medesima area di memoria
         */
        bool operator==(const BaseIterator&) const;

        /**
         * @brief Operatore di disuguaglianza
         * @return true sse i due iteratori considerati stanno puntando a due aree di memoria distinte
         */
        bool operator!=(const BaseIterator&) const;

        /**
         * @brief Accesso al figlio destro del nodo riferito dall'iteratore
         * @return un iteratore al figlio destro del nodo riferito dall'iteratore.
         *  Non viene eseguito alcun tipo di controllo sulla sua effettiva esistenza.
         */
        BaseIterator right() const;

        /**
         * @brief Accesso al figlio sinistro del nodo riferito dall'iteratore
         * @return un iteratore al figlio sinistro del nodo riferito dall'iteratore.
         *  Non viene eseguito alcun tipo di controllo sulla sua effettiva esistenza.
         */
        BaseIterator left() const;

        /**
         * @brief Accesso al padre del nodo riferito dall'iteratore
         * @return un iteratore al padre del nodo riferito dall'iteratore.
         *  Non viene eseguito alcun tipo di controllo sulla sua effettiva esistenza.
         */
        BaseIterator parent() const;
    };

    /**
     *  Definizio del tipo Iterator, tramite utilizzo della classe templetizzata BaseIterator
     */
    using Iterator = BaseIterator<false>;

    /**
     * Definizione del tipo ConstIterator, tramite utilizzo della classe templetizzata BaseIterator
     */
    using ConstIterator = BaseIterator<true>;

    /**
     * @brief Costruttore di default di IntervalTree, pone _root = nullptr e _size = 0
     */
    IntervalTree();

    /**
     * @brief Costruttore di copia di IntervalTree. La copia viene gestita in maniera profonda
     */
    IntervalTree(const IntervalTree&);

    /**
     * @brief Operatore di assegnazione
     * @return un riferimento alla struttura IntervalTree appena creata
     */
    IntervalTree& operator=(const IntervalTree&);

    /**
      * @brief Distruttore di IntervalTree. Viene distrutta la radice, che a sua volta innesca la distruzione
      *     dell'intero albero
      */
    ~IntervalTree();

    /**
     * @brief Permette di ottenre un iteratore al primo elemento del contenitore
     * @return un iteratore al primo elemento del contenitore (secondo una vista in-order)
     */
    Iterator begin() const;

    /**
     * @brief Permette di ottenere un iteratore che rappresenta la fine del contenitore
     * @return un iteratore alla fine del contenitore (dopo una vista in-order)
     */
    Iterator end() const;

    /**
     * @brief Permette di ottenre un iteratore costante al primo elemento del contenitore
     * @return un iteratore costante al primo elemento del contenitore (secondo una vista in-order)
     */
    ConstIterator cbegin() const;

    /**
     * @brief Permette di ottenere un iteratore costante che rappresenta la fine del contenitore
     * @return un iteratore costante alla fine del contenitore (dopo una vista in-order)
     */
    ConstIterator cend() const;

    /**
     * @brief Verifica se l'albero è vuoto
     * @return true sse l'albero è vuoto, cioè se _size == 0
     */
    bool empty() const;

    /**
     * @return il numero di elementi dell'albero, cioè _size
     */
    std::size_t size() const;

    /**
     * @brief Permette di ottenere un riferimento al primo elemento dell'albero (secondo una vista in-order)
     * @return un riferimento al primo elemento dell'albero.
     *  Non viene fatto alcun controllo sulla sua effettiva esistenza
     */
    DT& front();

    /**
     * @brief Permette di ottenere un riferimento al primo elemento dell'albero (secondo una vista in-order)
     * @return un riferimento al primo elemento dell'albero.
     *  Non viene fatto alcun controllo sulla sua effettiva esistenza
     */
    const DT& front() const;

    /**
     * @brief Permette di ottenere un riferimento all'utlimo elemento dell'albero (secondo una vista in-order)
     * @return un riferimento all'ultimo elemento dell'albero.
     *  Non viene fatto alcun controllo sulla sua effettiva esistenza
     */
    DT& back();

    /**
     * @brief Permette di ottenere un riferimento costante all'ultimo elemento dell'albero (secondo una vista in-order)
     * @return un riferimento costante all'ultimo elemento dell'albero.
     *  Non viene fatto alcun controllo sulla sua effettiva esistenza
     */
    const DT& back() const;

    /**
     * @brief Metodo che si occupa di "ripulire" l'albero, cioè di eliminare tutti i suoi elementi e di conseguenza
     *  impostare la _size a 0
     */
    void clear();

    /**
     * @brief Procedura di inserimento di un nuovo elemento all'interno dell'albero. Vengono richieste le informazioni per la creazione
     *  dell'intervallo e dell'oggeto da associare al nuovo nodo
     * @return un iteratore al nuovo nodo inserito
     */
    Iterator insert(const DT&, const BT&, const BT&);

    /**
     * @brief erase
     * @return
     */
    Iterator erase(const Iterator&);

    /**
     * @brief Permette di identificare tutti gli intervalli dell'albero che intersecano un intervallo dato
     * @return una lista di iteratori a tutti i nodi dell'albero i cui intervalli si intersecano con un intervallo dato
     */
    std::list<Iterator> findAll(const BT&, const BT&) const;

    /**
     * @brief Permette di identificare un intervallo dell'albero che interseca un intervallo dato
     * @return un iteratore a un nodo dell'albero il cui intervallo si interseca con un intervallo dato
     */
    Iterator find(const BT&, const BT&) const;

private:

    /**
      * @brief Funzione ricorsiva usata come aiuto per l'individuazione degli intervalli che si intersecano con un intervallo dato
      * @return una lista di iteratori ai nodi apparteneti all'albero radicato nel nodo passato come parametro e i cui intervalli
      *     si intersecano a un intervallo dato
      */
    static std::list<Iterator> findAllHelper(Node*, const Interval&);
};

// Interval class
template<class DT, class BT>
IntervalTree<DT, BT>::Interval::Interval(const BT& lowBound, const BT& highBound)
    : _lowBound(lowBound), _highBound(highBound) {

    if(_lowBound > _highBound)
        throw std::logic_error("In an interval low bound must be less than or equal to high bound");
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Interval::overlaps(const Interval& i) const {
    return _lowBound <= i._highBound && i._lowBound <= _highBound;
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Interval::operlapsExclusive(const Interval& i) const {
    return _lowBound < i._highBound && i._lowBound < _highBound;
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Interval::isPoint() const {
    return _lowBound == _highBound;
}

template<class DT, class BT>
BT IntervalTree<DT, BT>::Interval::size() const {
    return _highBound - _lowBound;
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Interval::within(const Interval& i) const {
    return _lowBound >= i._lowBound && _highBound <= i._highBound;
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Interval::operator==(const Interval& i) const {
    return _lowBound == i._lowBound && _highBound == i._highBound;
}


// Node class
template<class DT, class BT>
IntervalTree<DT, BT>::Node::Node(const DT& info,
       const Interval& interval, RBTreeColor color, Node* parent, Node* right, Node* left)
    : _info(info), _interval(interval), _maxBoundChild(interval._highBound), _color(color),
        _parent(parent), _right(right), _left(left) {}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Node::isRight() const {
    return _parent && _parent->_right == this;
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Node::isLeft() const {
    return _parent && _parent->_left == this;
}

template<class DT, class BT>
BT IntervalTree<DT, BT>::Node::getKey() const {
    return _interval._lowBound;
}

template<class DT, class BT>
bool IntervalTree<DT, BT>::Node::isRoot() const {
    return !_parent;
}

template<class DT, class BT>
IntervalTree<DT, BT>::Node::~Node() {
    delete _left;
    delete _right;
}

// BaseIterator class
template<class DT, class BT>
template<bool C>
IntervalTree<DT, BT>::BaseIterator<C>::BaseIterator()
    : _node(nullptr), _pastTheEnd(false){}

template<class DT, class BT>
template<bool C>
IntervalTree<DT, BT>::BaseIterator<C>::BaseIterator(Node* n, bool pastTheEnd)
    : _node(n), _pastTheEnd(pastTheEnd) {}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>::reference
IntervalTree<DT, BT>::BaseIterator<C>::operator*() const {
    return _node->_info;
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>::pointer
IntervalTree<DT, BT>::BaseIterator<C>::operator->() const {
    return &(_node->_info);
}

template<class DT, class BT>
template<bool C>
bool IntervalTree<DT, BT>::BaseIterator<C>::operator==(const BaseIterator& it) const {
    return _node == it._node; // confronto le aree di memoria
}

template<class DT, class BT>
template<bool C>
bool IntervalTree<DT, BT>::BaseIterator<C>::operator!=(const BaseIterator& it) const {
    return _node != it._node;
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>
IntervalTree<DT, BT>::BaseIterator<C>::right() const {
    return BaseIterator(_node->_right);
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>
IntervalTree<DT, BT>::BaseIterator<C>::left() const {
    return BaseIterator(_node->_left);
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>
IntervalTree<DT, BT>::BaseIterator<C>::parent() const {
    return BaseIterator(_node->_parent);
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>&
IntervalTree<DT, BT>::BaseIterator<C>::operator++() {

    if(_node) {
        if(!_pastTheEnd) {

            if(_node->_right) {
                _node = _node->_right;
                while(_node->_left)
                    _node = _node->_left;
            } else {
                Node *parent = _node->_parent,
                     *tmpNode = _node;
                while(parent && tmpNode->isRight()) {
                    tmpNode = parent;
                    parent = parent->_parent;
                }

                if(!parent) {
                  _pastTheEnd = true;
                  _node++;
                } else
                    _node = parent;
            }
        }
    }

    return *this;
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>
IntervalTree<DT, BT>::BaseIterator<C>::operator++(int) {
    BaseIterator aux = *this;
    operator++();
    return aux;
}

// NOTA: non vengono fatti controlli nel caso in cui si faccia
// il -- del minimo => si finisce con _node = nullptr
template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>&
IntervalTree<DT, BT>::BaseIterator<C>::operator--() {
    if(_node) {
        if(_pastTheEnd) {
            _pastTheEnd = false;
            _node--;
        } else {
            // trovo il predecessore

            if(_node->_left) {
                while(_node->_right)
                    _node = _node->_right;
            } else {
                Node* parent = _node->_parent;
                while(parent && _node->isLeft()) {
                    _node = parent;
                    parent = parent->_parent;
                }
                _node = parent;
            }
        }
    }

    return *this;
}

template<class DT, class BT>
template<bool C>
typename IntervalTree<DT, BT>::template BaseIterator<C>
IntervalTree<DT, BT>::BaseIterator<C>::operator--(int) {
    BaseIterator aux = *this;
    operator--();
    return aux;
}

// Interval Tree class
template<class DT, class BT>
IntervalTree<DT, BT>::IntervalTree() : _root(nullptr), _size(0) {}

// Interval Tree - Capacity
template<class DT, class BT>
bool IntervalTree<DT, BT>::empty() const {
    return _size == 0;
}

template<class DT, class BT>
std::size_t IntervalTree<DT, BT>::size() const {
    return _size;
}

// Interval Tree - Modifiers
template<class DT, class BT>
void IntervalTree<DT, BT>::clear() {
    delete _root;
    _size = 0;
}

template<class DT, class BT>
void IntervalTree<DT, BT>::left_rotate(Node* x) {
       std::cout << "Left rotate" << std::endl;

    if(!x->_right) {
     //   return;
    std::cout << "Caso" << std::endl;
     }

    Node* y = x->_right;
    x->_right = y->_left;

    if(y->_left)
        y->_left->_parent = x;
    y->_parent = x->_parent;
    if(!x->_parent)
        _root = y;
    else if(x->isLeft())
        x->_parent->_left = y;
    else
        x->_parent->_right = y;

    y->_left = x;
    x->_parent = y;

    // TODO: refactor
    if (x->_left && x->_right)
           x->_maxBoundChild = std::max(x->_interval._highBound, std::max(x->_left->_maxBoundChild, x->_right->_maxBoundChild));
       else if (x->_left)
           x->_maxBoundChild = std::max(x->_interval._highBound, x->_left->_maxBoundChild);
       else if (x->_right)
           x->_maxBoundChild = std::max(x->_interval._highBound, x->_right->_maxBoundChild);
       else
           x->_maxBoundChild = x->_interval._highBound;

       if (y->_right)
           y->_maxBoundChild = std::max(y->_interval._highBound, std::max(y->_right->_maxBoundChild, x->_maxBoundChild));
       else
           y->_maxBoundChild = std::max(y->_interval._highBound, x->_maxBoundChild);
}

template<class DT, class BT>
void IntervalTree<DT, BT>::right_rotate(Node* y) {
    std::cout << "Right rotate" << std::endl;
    if(!y->_right) {
        std::cout << "Caso" << std::endl;
       //  return;
    }

    Node* x = y->_left;
      y->_left = x->_right;

      if (x->_right)
          x->_right->_parent = y;

      x->_parent= y->_parent;
      if (!y->_parent)
          _root = x;
      else if (y->isLeft())
          y->_parent->_left = x;
      else
          y->_parent->_right = x;

      x->_right = y;
      y->_parent = x;

      // TODO: refactor
     if (y->_left && y->_right)
         y->_maxBoundChild = std::max(y->_interval._highBound, std::max(y->_left->_maxBoundChild, y->_right->_maxBoundChild));
     else if (y->_left)
         y->_maxBoundChild = std::max(y->_interval._highBound, y->_left->_maxBoundChild);
     else if (y->_right)
         y->_maxBoundChild = std::max(y->_interval._highBound, y->_right->_maxBoundChild);
     else
         y->_maxBoundChild = y->_interval._highBound;

     if (x->_left)
         x->_maxBoundChild = std::max(x->_interval._highBound, std::max(x->_left->_maxBoundChild, y->_maxBoundChild));
     else
         x->_maxBoundChild = std::max(x->_interval._highBound, y->_maxBoundChild);
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::Iterator
    IntervalTree<DT, BT>::insert(const DT& data, const BT& lowBound, const BT& highBound) {

    Node *x = _root,
         *y = nullptr,
         *z = new Node(data, Interval(lowBound, highBound));

    // inserisco il nuovo nodo mantenendo le caratteristiche di un BST
    while(x) {
        y = x;
        if(lowBound < x->_interval._lowBound)
            x = x->_left;
        else
            x = x->_right;
    }

    z->_parent = y;
    if(!y)
        _root = z;
    else if(lowBound < y->_interval._lowBound)
       y->_left = z;
    else y->_right = z;

    std::cout << "Inserito, inizio il fixup..." << std::endl;
    // fix per mantenere le caratteristiche di un RBTree
     insert_fixup(z);
    std::cout << "Passato fixup" << std::endl;
    // fix per il massimo in ogni nodo (IntervalTree)
    recalculate_max(z);
    std::cout << "Calcolato il massimo" << std::endl;

    _size++;
    return Iterator(z);
}

template<class DT, class BT>
void IntervalTree<DT, BT>::insert_fixup(Node* z) {

    while(z->_parent && z->_parent->_parent && z->_parent->_color == RED) {
        Node *parent = z->_parent,
             *anchestor = parent->_parent;

        std::cout << "Sono entrato nel ciclo del fixup" << std::endl;

        if(parent->isLeft()) {
            Node* y = anchestor->_right;
            std::cout << "Primo ramo dell'if" << std::endl;

            if(y && y->_color == RED) {
                parent->_color = BLACK;
                y->_color = BLACK;
                anchestor->_color = RED;
                z = anchestor;
            } else{
                if(z->isRight()) {
                    z = parent;
                    left_rotate(z);
                }

                parent->_color = BLACK;
                anchestor->_color = RED;
                right_rotate(anchestor);
            }
        } else {
            Node* y = anchestor->_left;

            if(y && y->_color == RED) {
                parent->_color = BLACK;
                y->_color = BLACK;
                anchestor->_color = RED;
                z = anchestor;
            } else{
                if(z->isLeft()) {
                    z = parent;
                    right_rotate(z);
                }

                parent->_color = BLACK;
                anchestor->_color = RED;
                left_rotate(anchestor);
            }
        }
    }

    _root->_color = BLACK;
}

// ripercorro al contrario l'albero aggiornando il massimo
// finchè non trovo un nodo con max maggiore del nodo corrente --> il massimo in questo caso sarà dato
// dall'altro figlio = non devo aggiornare più niente
template<class DT, class BT>
void IntervalTree<DT, BT>::recalculate_max(Node* z) {
    Node* tmp = z->_parent;
    while(tmp && tmp->_maxBoundChild <= z->_maxBoundChild) {
        if(tmp->_left && tmp->_left->_maxBoundChild > tmp->_maxBoundChild)
            tmp->_maxBoundChild = tmp->_left->_maxBoundChild;
        if(tmp->_right && tmp->_right->_maxBoundChild > tmp->_maxBoundChild)
            tmp->_maxBoundChild = tmp->_right->_maxBoundChild;

        tmp = tmp->_parent;
    }
}

template<class DT, class BT>
void IntervalTree<DT, BT>::transplant(Node* u, Node* v) {
    if(u->isRoot())
           _root = v;
    else if(u->isLeft())
        u->_parent->_left = v;
    else u->_parent->_right = v;

    if(v)
        v->_parent = u->_parent;
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::Iterator
    IntervalTree<DT, BT>::erase(const Iterator& it) {

    // controllo se it._node != nullptr

    Iterator next = it;
    // TODO next++;

    delete_node(it._node);

    return next;
}

// PRE = z != nullptr
template<class DT, class BT>
void IntervalTree<DT, BT>::delete_node(Node* z) {
   /* Node* y;
    if(!z->_left || !z->_right)
        y = z;
    else y = successor(z); // ?

    Node* x;
    if(!y->_left)
        x = y->_right;
    else
        x = y->_left;

    if(x)
        x->_parent = y->_parent;

    if(!y->_parent)
        _root = x;
    else if(y->isLeft())
        y->_parent->_left = x;
    else y->_parent->_right = x;

    if(y->_color == BLACK)
        delete_fixup(x);

    delete y;
    _size--; */
}

template<class DT, class BT>
std::list<typename IntervalTree<DT, BT>::Iterator>
IntervalTree<DT, BT>::findAll(const BT& lowBound, const BT& highBound) const {
    return findAllHelper(_root, Interval(lowBound, highBound));
}

template<class DT, class BT>
std::list<typename IntervalTree<DT, BT>::Iterator>
IntervalTree<DT, BT>::findAllHelper(Node* n, const Interval& i) {

    std::list<Iterator> matches;

    if(!n)
        return matches;

    // se il lowBound dell'intervallo è > del punto più a destra nell'albero che ha per radice n
    //  --> in tale albero non ci sono intervalli che lo intersecano
    if(i._lowBound > n->_maxBoundChild)
        return matches;

    // cerco a sinistra
    if(n->_left)
        matches.splice(matches.end(), findAllHelper(n->_left, i)); // splice funziona in O(1)

    if(n->_interval.overlaps(i))
        matches.push_back(Iterator(n)); // O(1)

    // se il punto più a destra dell'intervallo (highBound) è a sinistra del punto
    // più a sinistra della root, allora non ci possono essere intersezioni con i figli di sinistra
    if(i._highBound >=  n->_interval._lowBound && n->_right)
        matches.splice(matches.end(), findAllHelper(n->_right, i));

    return matches;
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::Iterator IntervalTree<DT, BT>::find(const BT& lowBound, const BT& highBound) const {
    Interval i(lowBound, highBound);
    Node* x = _root;

    while(x && !i.overlaps(x->_interval)) {
        if(x->_left && x->_left->_maxBoundChild >= i._lowBound)
            x = x->_left;
        else
            x = x->_right;
    }

    return Iterator(x);
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::Iterator
IntervalTree<DT, BT>::begin() const {
    Node* n = _root;
    while(n && n->_left)
        n = n->_left;
    return Iterator(n);
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::Iterator
IntervalTree<DT, BT>::end() const {
    Node* n = _root;
    while(n && n->_right)
        n = n->_right;

    if(!n)
        return Iterator(n);
    return Iterator(n+1, true);
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::ConstIterator
IntervalTree<DT, BT>::cbegin() const {
    Node* n = _root;
    while(n && n->_left)
        n = n->_left;
    return ConstIterator(n);
}

template<class DT, class BT>
typename IntervalTree<DT, BT>::ConstIterator
IntervalTree<DT, BT>::cend() const {
    Node* n = _root;
    while(n && n->_right)
        n = n->_right;

    if(!n)
        return ConstIterator(n);
    return ConstIterator(n+1, true);
}

template<class DT, class BT>
DT& IntervalTree<DT, BT>::front() {
    return *begin();
}

template<class DT, class BT>
const DT& IntervalTree<DT, BT>::front() const {
    return *cbegin();
}

template<class DT, class BT>
DT& IntervalTree<DT, BT>::back() {
    return *(--end());
}

template<class DT, class BT>
const DT& IntervalTree<DT, BT>::back() const {
    return *(--cend());
}


template<class DT, class BT>
IntervalTree<DT, BT>::~IntervalTree() {
    delete _root;
}

#endif // INTERVALTREE_H
