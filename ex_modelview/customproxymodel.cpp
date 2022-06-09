#include "customproxymodel.h"

CustomProxyModel::CustomProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    maxPrice = 83;
    minPrice = 0;
}


bool CustomProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex indexPrice = sourceModel()->index(sourceRow, 3, sourceParent);

    return priceInRange(sourceModel()->data(indexPrice).toDouble());
}

bool CustomProxyModel::priceInRange(double price) const
{
    return price >= minPrice && price < maxPrice;
}

void CustomProxyModel::setFilterMinimumPrice(double price)
{
    minPrice = price;
    invalidateFilter();
}

void CustomProxyModel::setFilterMaximumPrice(double price)
{
    maxPrice = price;
    invalidateFilter();
}
