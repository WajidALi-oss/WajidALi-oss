#include "gui_shell.h"
#include "shell_core.h"
#include <QString>

ShellGUI::ShellGUI(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);

    label = new QLabel("Enter command:");
    input = new QLineEdit(this);
    output = new QTextEdit(this);
    QPushButton* runButton = new QPushButton("Run", this);

    output->setReadOnly(true);

    layout->addWidget(label);
    layout->addWidget(input);
    layout->addWidget(runButton);
    layout->addWidget(output);

    connect(runButton, &QPushButton::clicked, this, &ShellGUI::executeCommand);
}

void ShellGUI::executeCommand() {
    QString cmd = input->text();
    if (cmd.trimmed().isEmpty()) return;

    std::string result = run_command(cmd.toStdString()); // call your C++ logic
    output->append(">> " + cmd);
    output->append(QString::fromStdString(result));

    input->clear();
}

