#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomProxyModel(QObject *parent = nullptr);

    double filterMinimumPrice() const { return minPrice; }
    void setFilterMinimumPrice(double fare);

    double filterMaximumPrice() const { return maxPrice; }
    void setFilterMaximumPrice(double price);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
//    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool priceInRange(double Price) const;

    double minPrice;
    double maxPrice;
};


#endif // CUSTOMPROXYMODEL_H
