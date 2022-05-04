#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

void SettingsDialog::setSettings(Settings settings)
{
    ui->editIP->setText(settings.strIP);
    ui->editPort->setText(settings.strPort);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getIP()
{
    return ui->editIP->text();
}

QString SettingsDialog::getPort()
{
    return ui->editPort->text();
}
