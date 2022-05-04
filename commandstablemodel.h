#ifndef COMMANDSTABLEMODEL_H
#define COMMANDSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDebug>
#include <QString>
#include <QObject>

#include "commands.h"

class CommandsTableModel : public QAbstractTableModel
{
    Q_OBJECT
    public:
        explicit CommandsTableModel(QObject *parent);
        ~CommandsTableModel();

        void assignData(QList<Command*> *commandList);
        void refreshData();

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QVariant headerData(int nSection, Qt::Orientation orientation, int nRole) const;
        bool setData(const QModelIndex& index, const QVariant& value, int nRole);

    private:
        QList<Command*> *commandList = nullptr;
        uint size = 0;
};

#endif // COMMANDSTABLEMODEL_H
