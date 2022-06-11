#include "examplemodel.h"
#include <QFile>
#include <QTextStream>

ExampleModel::ExampleModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ExampleModel::fillDataTableFromFile(QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();
    for (QString& item : firstline.split(",")) {
        headerList.append(item);
    }

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        int columnIdx = 0;
        for (QString& item : line.split(",")) {
            if (columnIdx == 0
             || columnIdx == 1
             || columnIdx == 5)
            {
                dataRow.append(item);
            }
            else if (columnIdx == 2)
            {
                dataRow.append(item.toDouble());
            }
            else
            {
                dataRow.append(item.toInt());
            }
            ++columnIdx;
        }
        dataTable.append(dataRow);
    }
    inputFile.close();
}


/*void ExampleModel::fillDataTableFromFile(QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();
    for (QString& item : firstline.split(",")) {
        headerList.append(item);
    }

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        
        QList<QVariant> dataRow;
        for (QString& item : line.split(",")) {
            dataRow.append(item);
        }
        dataTable.append(dataRow);
    }
    inputFile.close();
}*/

void ExampleModel::saveDataToFile(QString path)
{
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream outputStream(&outputFile);

    bool first = true;
    for (QString& item : headerList) {
        if(first)
        {
            outputStream << item;
            first = false;
        }
        else
        {
            outputStream << ",";
            outputStream << item;
        }
    }
    outputStream << "\n";

    for(QList<QVariant>& row : dataTable)
    {
        bool first = true;
        for (QVariant& item : row) {
            if(first)
            {
                outputStream << item.toString();
                first = false;
            }
            else
            {
                outputStream << ",";
                outputStream << item.toString();
            }
        }
        outputStream << "\n";

    }

    outputFile.close();
}

int ExampleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    return dataTable.size();
}

int ExampleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    if (dataTable.empty())
    {
        return 0;
    }
    
    return dataTable[0].size();
}

QVariant ExampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList[section];
    }
    return QVariant();
}

QVariant ExampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        return dataTable[row][col];
    }
    return QVariant();
}

bool ExampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        int row = index.row();
        int col = index.column();
        dataTable[row][col] = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}


Qt::ItemFlags ExampleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


void ExampleModel::appendRow(QList<QVariant> &row)
{
    size_t newRowNumber = rowCount();
    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
    dataTable.append(row);
    endInsertRows();
}

bool ExampleModel::removeRow(const QString &name)
{
    bool found;
    int idx = -1;
    for(int i = 0; i < dataTable.size(); ++i)
    {
        if(dataTable[i][0] == name)
        {
            found = true;
            idx = i;
        }
    }
    if(!found)
    {
        return false;
    }
    beginRemoveRows(QModelIndex(), idx, idx);
    dataTable.removeAt(idx);
    endRemoveRows();
}

