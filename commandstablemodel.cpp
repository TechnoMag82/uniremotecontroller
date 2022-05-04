#include "commandstablemodel.h"

CommandsTableModel::CommandsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

CommandsTableModel::~CommandsTableModel()
{

}

void CommandsTableModel::assignData(QList<Command*> *commandList)
{
    beginResetModel();
    this->commandList = commandList;
    size = this->commandList->size();
    endResetModel();
}

void CommandsTableModel::refreshData()
{
    beginResetModel();
    size = commandList->size();
    endResetModel();
}

int CommandsTableModel::rowCount(const QModelIndex &parent) const
{
    return size;
}

int CommandsTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant CommandsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    Command *cmd = commandList->at(index.row());
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return cmd->title;
            case 1:
                return cmd->code;
            case 2:
                return cmd->command;
        }
    }
    return QVariant();
}

QVariant CommandsTableModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const
{
    if (nRole != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        switch (nSection) {
            case 0:
                return QString(tr("Title"));
            case 1:
                return QString(tr("Code"));
            case 2:
                return QString(tr("Command"));
        }
    }
}

bool CommandsTableModel::setData(const QModelIndex &index, const QVariant &value, int nRole)
{
    return false;
}
