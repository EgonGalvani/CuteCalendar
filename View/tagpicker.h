#ifndef TAG_PICKER_H
#define TAG_PICKER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <vector>
#include "enterlineedit.h"

// widget utilizzato per l'inserimento dei tag di interesse
class TagPicker : public QWidget {
    Q_OBJECT

private:
    EnterLineEdit *txtEdit;
    QListWidget *list;
    bool enabled;

public:
    TagPicker(QWidget* = nullptr);

    // gestione dei tag selezionati dall'utente
    std::vector<std::string> getTags() const;
    void addTag(const std::string&);
    void addTags(const std::vector<std::string>&);

    // gestione dello stato del widget
    bool isEnabled() const;
    void setEnabled(bool);

private slots:
    void addNewTag();
    void deleteTag(QListWidgetItem*);
};

#endif // TAG_PICKER_H
