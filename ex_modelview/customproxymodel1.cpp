#include "customproxymodel1.h"

CustomProxyModel1::CustomProxyModel1(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    maxYear = 2020;
    minYear = 2000;
}


bool CustomProxyModel1::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex indexYear = sourceModel()->index(sourceRow, 3, sourceParent);

    return yearInRange(sourceModel()->data(indexYear).toDouble());
}

bool CustomProxyModel1::yearInRange(double year) const
{
    return year >= minYear && year < maxYear;
}

void CustomProxyModel1::setFilterMinimumYear(double year)
{
    minYear = year;
    invalidateFilter();
}

void CustomProxyModel1::setFilterMaximumYear(double year)
{
    maxYear = year;
    invalidateFilter();
}
