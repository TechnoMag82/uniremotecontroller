#include "addcommanddialog.h"
#include "ui_addcommanddialog.h"

AddCommandDialog::AddCommandDialog(QWidget *parent, Command *cmd) :
    QDialog(parent),
    ui(new Ui::AddCommandDialog)
{
    ui->setupUi(this);
    this->cmd = cmd;
    if (this->cmd != nullptr) {
        ui->editTitleCommad->setText(this->cmd->title);
        ui->editCodeCoomad->setText(this->cmd->code);
        ui->editCommand->setText(this->cmd->command);
        if (cmd->title.endsWith("(default)")) {
            ui->editTitleCommad->setEnabled(false);
            ui->editCodeCoomad->setEnabled(false);
        }
    }
}

AddCommandDialog::~AddCommandDialog()
{
    delete ui;
}

Command *AddCommandDialog::getCommand()
{
    if (cmd == nullptr) {
        cmd = new Command();
    }
    cmd->code = ui->editCodeCoomad->text();
    cmd->title = ui->editTitleCommad->text();
    cmd->command = ui->editCommand->text();
    return cmd;
}
