#ifndef TAG_PICKER_H
#define TAG_PICKER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <vector>

class EnterLineEdit : public QLineEdit {
    Q_OBJECT

public:
    virtual void keyPressEvent(QKeyEvent*);

signals:
    void enterKeyPressed();
};

class TagPicker : public QWidget {
    Q_OBJECT

private:
    EnterLineEdit *txtEdit;
    QListWidget *list;
    bool enabled;

public:
    TagPicker(QWidget* = nullptr);

    std::vector<std::string> getTags() const;
    void addTag(const std::string&);
    void addTags(const std::vector<std::string>&);

    bool isEnabled() const;
    void setEnabled(bool);

private slots:
    void addNewTag();
    void deleteTag(QListWidgetItem*);
};

#endif // TAG_PICKER_H
