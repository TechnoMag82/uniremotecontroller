#include "fileutils.h"

FileUtils::FileUtils()
{
    commandsPath = QDir::homePath() + "/.remotecontrol/commands.cfg";
    settingsPath = QDir::homePath() + "/.remotecontrol/settings.cfg";
}

void FileUtils::loadCommands(QList<Command*> &commandList)
{
    if (QFile::exists(commandsPath)) {
        QFile textDB(commandsPath);
        if (textDB.open(QIODevice::ReadOnly | QIODevice::Text) == true)
        {
            qDebug() << "Loading commands ...";
            QTextStream inDB(&textDB);
            inDB.setCodec("UTF-8");
            while (inDB.atEnd() != true)
            {
                QStringList data = inDB.readLine(0).split(";");
                Command *cmd = new Command();
                cmd->title = data[0];
                cmd->code = data[1];
                cmd->command = data[2];
                commandList.append(cmd);
            }
            textDB.close();
        }
    }
}

void FileUtils::saveCommands(QList<Command *> &commandList)
{
    qDebug() << "Save commands ...";
    createDir();
    QFile textFile(commandsPath);
    textFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate);
    QTextStream outText(&textFile);
    outText.setCodec("UFT-8");
    int count = commandList.size();
    for (int i = 0; i < count; i++) {
        outText << commandList.at(i)->title << ";" << commandList.at(i)->code << ";" << commandList.at(i)->command << endl;
    }
    textFile.close();
}

Settings FileUtils::readSettings()
{
    Settings settings;
    if (QFile::exists(settingsPath)) {
           QFile textFile(settingsPath);
           textFile.open(QIODevice::ReadOnly| QIODevice::Text);
           QTextStream inText(&textFile);
           settings.strIP = inText.readLine(0);
           settings.strPort = inText.readLine(0);
           textFile.close();
    }
    return settings;
}

void FileUtils::saveSettings(Settings settings)
{
    createDir();
    QFile textFile(settingsPath);
    textFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate);
    QTextStream outText(&textFile);
    outText.setCodec("UFT-8");
    outText << settings.strIP << endl;
    outText << settings.strPort << endl;
    textFile.close();
}

void FileUtils::createDir()
{
    QString commandsDir = QDir::homePath() + "/.remotecontrol/";
    QDir dir(commandsDir);
    if (!dir.exists(commandsDir)) {
        dir.mkdir(commandsDir);
    }
}

