#ifndef ADDCOMMANDDIALOG_H
#define ADDCOMMANDDIALOG_H

#include <QDialog>

#include "commands.h"

namespace Ui {
class AddCommandDialog;
}

class AddCommandDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit AddCommandDialog(QWidget *parent = 0, Command *cmd = nullptr);
        ~AddCommandDialog();
        Command* getCommand();

    private:
        Ui::AddCommandDialog *ui;
        Command *cmd = nullptr;

};

#endif // ADDCOMMANDDIALOG_H
