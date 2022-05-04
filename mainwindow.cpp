#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon windowIcon = QIcon(":/images/toolbar/computer.png");
    setWindowIcon(windowIcon);

    systemTrayIcon = new QSystemTrayIcon(windowIcon, this);
    createTrayMenu();
    systemTrayIcon->setVisible(true);
    systemTrayIcon->setToolTip("Universal remote controller");
    systemTrayIcon->show();

    createToolBar();

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)),
             this, SLOT(clicked1(const QModelIndex &)));

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
    commands = new QList<Command*>();
    FileUtils *fileUtils = new FileUtils();
    fileUtils->loadCommands(*commands);
    settings = fileUtils->readSettings();
    delete fileUtils;
    addDefaultsIfNotExists();
    if (!settings.strPort.isEmpty() && !settings.strPort.isEmpty()) {
        actStartServer->setEnabled(true);
    }
    if (model == nullptr) {
        model = new CommandsTableModel(ui->tableView);
    }
    model->assignData(commands);
    ui->tableView->setModel(model);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    setWindowState(Qt::WindowMinimized);
    hide();
}

void MainWindow::changeEvent(QEvent *e)
{
    switch (e->type())
    {
        case QEvent::WindowStateChange:
        {
            if (this->windowState() & Qt::WindowMinimized)
            {
                hide();
            }
            break;
        }
        default:
            break;
    }
    QMainWindow::changeEvent(e);
}

MainWindow::~MainWindow()
{
    saveCommands();
    if (commands != nullptr) {
        qDeleteAll(*commands);
        commands->clear();
        delete commands;
    }
    if (model != nullptr) {
        delete model;
    }
    if (udpSocket != nullptr) {
        udpSocket->close();
        delete udpSocket;
    }
    delete ui;
}

void MainWindow::openSettings()
{
    SettingsDialog *settingsDialog = new SettingsDialog(this);
    settingsDialog->setSettings(settings);
    if (settingsDialog->exec() == QDialog::Accepted) {
        settings.strIP = settingsDialog->getIP();
        settings.strPort = settingsDialog->getPort();
        dataEdited = true;
        if (!settings.strPort.isEmpty() && !settings.strPort.isEmpty()) {
            actStartServer->setEnabled(true);
        } else {
            actStartServer->setEnabled(false);
        }
    }
    delete settingsDialog;
}

void MainWindow::addCommand()
{
    AddCommandDialog *command = new AddCommandDialog(this, nullptr);
    if (command->exec() == QDialog::Accepted) {
        dataEdited = true;
        commands->append(command->getCommand());
        model->refreshData();
    }
    delete command;
}

void MainWindow::removeCommand()
{
    if (commands == nullptr || commands->isEmpty()) {
        return;
    }
    if (commands->at(selectedRow)->title.endsWith("(default)")) {
        QMessageBox::warning(this,
            tr("Remove command"),
            tr("You cannot remove default command."),
            QMessageBox::Ok);
        return;
    }
    commands->removeAt(selectedRow);
    model->refreshData();
    dataEdited = true;
}

void MainWindow::editCommand()
{
    if (commands == nullptr || commands->isEmpty()) {
        return;
    }
    AddCommandDialog *command = new AddCommandDialog(this, commands->at(selectedRow));
    if (command->exec() == QDialog::Accepted) {
        command->getCommand();
        model->refreshData();
        dataEdited = true;
    }
    delete command;
}

void MainWindow::startServer()
{
    saveCommands();
    actStartServer->setEnabled(false);
    actStopServer->setEnabled(true);
    actAddCommand->setEnabled(false);
    actEditCommand->setEnabled(false);
    actRemoveCommand->setEnabled(false);
    actSettings->setEnabled(false);

    if (udpSocket == nullptr) {
        udpSocket = new QUdpSocket(this);
        connect(udpSocket, SIGNAL(readyRead()), SLOT(slotProcessDatagrams()));
    }
    udpSocket->bind(settings.strPort.toInt());
    systemTrayIcon->setIcon(QIcon(":/images/toolbar/ball_green.png"));
}

void MainWindow::stopServer()
{
    if (udpSocket != nullptr) {
        udpSocket->close();
    }
    actStartServer->setEnabled(true);
    actStopServer->setEnabled(false);
    actAddCommand->setEnabled(true);
    actEditCommand->setEnabled(true);
    actRemoveCommand->setEnabled(true);
    actSettings->setEnabled(true);
    systemTrayIcon->setIcon(QIcon(":/images/toolbar/computer.png"));
}

void MainWindow::about()
{
    AboutDialog *about = new AboutDialog(this);
    about->exec();
    delete about;
}

void MainWindow::clicked1(const QModelIndex &index)
{
    selectedRow = index.row();
}

void MainWindow::slotProcessDatagrams()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(baDatagram.data(), baDatagram.size());
    } while(udpSocket->hasPendingDatagrams());
    QString code;
    QTextStream in(&baDatagram, QIODevice::ReadOnly);
    in >> code;
    qDebug() << code;
    int count = commands->size();
    for (int i = 0; i < count; i++) {
        Command *cmd = commands->at(i);
        if (code.compare(cmd->code) == 0) {
            QProcess::startDetached(cmd->command);
            break;
        }
    }
}

void MainWindow::createToolBar()
{
    actSettings = new QAction(QIcon(":/images/toolbar/settings.png"), tr("Server settings ..."), this);
    connect(actSettings, SIGNAL(triggered()), this, SLOT(openSettings()));

    actAddCommand = new QAction(QIcon(":/images/toolbar/add.png"), tr("Add command ..."), this);
    connect(actAddCommand, SIGNAL(triggered()), this, SLOT(addCommand()));

    actEditCommand = new QAction(QIcon(":/images/toolbar/edit.png"), tr("Edit command"), this);
    connect(actEditCommand, SIGNAL(triggered()), this, SLOT(editCommand()));

    actRemoveCommand = new QAction(QIcon(":/images/toolbar/remove.png"), tr("Remove command"), this);
    connect(actRemoveCommand, SIGNAL(triggered()), this, SLOT(removeCommand()));

    actStartServer = new QAction(QIcon(":/images/toolbar/ball_green.png"), tr("Start listen"), this);
    connect(actStartServer, SIGNAL(triggered()), this, SLOT(startServer()));

    actStopServer = new QAction(QIcon(":/images/toolbar/ball_red.png"), tr("Stop listen"), this);
    connect(actStopServer, SIGNAL(triggered()), this, SLOT(stopServer()));

    actAbout = new QAction(QIcon(":/images/toolbar/about.png"), tr("About program ..."), this);
    connect(actAbout, SIGNAL(triggered()), this, SLOT(about()));

    actStopServer->setEnabled(false);
    actStartServer->setEnabled(false);

    ui->mainToolBar->addAction(actSettings);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actAddCommand);
    ui->mainToolBar->addAction(actEditCommand);
    ui->mainToolBar->addAction(actRemoveCommand);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actStartServer);
    ui->mainToolBar->addAction(actStopServer);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actAbout);
}

void MainWindow::quitApp()
{
    saveCommands();
    QApplication::quit();
}

void MainWindow::openApp()
{
    show();
    activateWindow();
    raise();
    setFocus();
    setWindowState(Qt::WindowState::WindowActive);
}

void MainWindow::createTrayMenu()
{
    QMenu *trayMenu = new QMenu(this);

    QAction* action = new QAction(tr("Open remote controller"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(openApp()));
    trayMenu->addAction(action);

    action = new QAction(tr("Quit"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(quitApp()));
    trayMenu->addAction(action);

    systemTrayIcon->setContextMenu(trayMenu);
}

void MainWindow::saveCommands()
{
    if (dataEdited) {
        FileUtils *fileUtils = new FileUtils();
        fileUtils->saveCommands(*commands);
        fileUtils->saveSettings(settings);
        delete fileUtils;
    }
}

void MainWindow::addDefaultsIfNotExists()
{
    if (!isCommandExixts("Volume up (default)")) {
        Command *cmd = new Command();
        cmd->title = "Volume up (default)";
        cmd->code = "4001";
        commands->append(cmd);
    }
    if (!isCommandExixts("Volume down (default)")) {
        Command *cmd = new Command();
        cmd->title = "Volume down (default)";
        cmd->code = "4002";
        commands->append(cmd);
    }
    if (!isCommandExixts("Power off (default)")) {
        Command *cmd = new Command();
        cmd->title = "Power off (default)";
        cmd->code = "1000";
        commands->append(cmd);
    }
    if (!isCommandExixts("Next (default)")) {
        Command *cmd = new Command();
        cmd->title = "Next (default)";
        cmd->code = "2000";
        commands->append(cmd);
    }
    if (!isCommandExixts("Prev (default)")) {
        Command *cmd = new Command();
        cmd->title = "Prev (default)";
        cmd->code = "2001";
        commands->append(cmd);
    }
    if (!isCommandExixts("Play (default)")) {
        Command *cmd = new Command();
        cmd->title = "Play (default)";
        cmd->code = "2002";
        commands->append(cmd);
    }
    if (!isCommandExixts("Pause (default)")) {
        Command *cmd = new Command();
        cmd->title = "Pause (default)";
        cmd->code = "2003";
        commands->append(cmd);
    }
}

bool MainWindow::isCommandExixts(QString title)
{
    int count = commands->size();
    for (int i = 0; i < count; i++) {
        Command *cmd = commands->at(i);
        if (title.compare(cmd->title) == 0) {
            return true;
        }
    }
    return false;
}
