#include "examplemodel.h"

ExampleModel::ExampleModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant ExampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool ExampleModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int ExampleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    // FIXME: Implement me!
}

int ExampleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    // FIXME: Implement me!
}

QVariant ExampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    // FIXME: Implement me!
    return QVariant();
}

bool ExampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ExampleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}
