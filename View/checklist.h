#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <QListWidget>
#include <vector>
#include <QWidget>
#include <vector>

class CheckList : public QListWidget {
private:
    bool hasItem(const QString& label) const;
public:
    CheckList(QWidget* = nullptr);
    void addItem(const QString &label, bool = false);
    std::vector<std::pair<std::string, bool>> getStatus() const;

     ~CheckList() = default;
};

#endif // CHECKLIST_H
