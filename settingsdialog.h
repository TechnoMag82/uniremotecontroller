#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "settingsstruct.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit SettingsDialog(QWidget *parent = 0);
        void setSettings(Settings settings);
        ~SettingsDialog();
        QString getIP();
        QString getPort();

    private:
        Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
