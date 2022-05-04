#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QList>
#include <QUdpSocket>
#include <QByteArray>
#include <QTextStream>
#include <QProcess>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>

#include "aboutdialog.h"
#include "commands.h"
#include "settingsdialog.h"
#include "commandstablemodel.h"
#include "fileutils.h"
#include "addcommanddialog.h"
#include "settingsstruct.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent *event);
        void changeEvent(QEvent *e);

    private slots:
        void openSettings();
        void addCommand();
        void removeCommand();
        void editCommand();
        void startServer();
        void stopServer();
        void about();
        void clicked1(const QModelIndex &index);
        void slotProcessDatagrams();
        void quitApp();
        void openApp();

    private:
        Ui::MainWindow *ui;

        QList<Command*> *commands = nullptr;

        QAction *actSettings;
        QAction *actAddCommand;
        QAction *actRemoveCommand;
        QAction *actEditCommand;
        QAction *actStartServer;
        QAction *actStopServer;
        QAction *actAbout;

        QSystemTrayIcon *systemTrayIcon;

        CommandsTableModel *model = nullptr;

        QString homeDir;

        bool dataEdited = false;
        int selectedRow = -1;

        Settings settings;

        QUdpSocket *udpSocket = nullptr;

        void createToolBar();
        void createTrayMenu();
        void saveCommands();
        void addDefaultsIfNotExists();
        bool isCommandExixts(QString title);
};

#endif // MAINWINDOW_H
