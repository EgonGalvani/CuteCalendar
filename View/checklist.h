#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <QListWidget>
#include <vector>
#include <QWidget>
#include <vector>

// widget per la gestione di una checklist, ogni item della lista
// è formato da una stringa di testo e una checkbox
class CheckList : public QListWidget {
private:

    // controlla se un item con una label specifica è presente nella lista
    bool hasItem(const QString& label) const;
public:
    CheckList(QWidget* = nullptr);

    // aggiunge un item nella lista
    void addItem(const QString &label, bool = false);

    // ottiene un vettore che rappresenta la lista di item della checkbox
    std::vector<std::pair<std::string, bool>> getStatus() const;

     ~CheckList() = default;
};

#endif // CHECKLIST_H
