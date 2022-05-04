#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QDir>

#include "commands.h"
#include "settingsstruct.h"

class FileUtils
{
    public:
        FileUtils();
        void loadCommands(QList<Command*> &commandList);
        void saveCommands(QList<Command*> &commandList);
        Settings readSettings();
        void saveSettings(Settings settings);

    private:
        QString commandsPath;
        QString settingsPath;
        void createDir();
};

#endif // FILEUTILS_H
