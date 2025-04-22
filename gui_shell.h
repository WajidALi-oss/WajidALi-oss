#ifndef GUI_SHELL_H
#define GUI_SHELL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class ShellGUI : public QWidget {
    Q_OBJECT

public:
    explicit ShellGUI(QWidget* parent = nullptr);

private slots:
    void executeCommand();

private:
    QLabel* label;
    QLineEdit* input;
    QTextEdit* output;
};

#endif // GUI_SHELL_H
