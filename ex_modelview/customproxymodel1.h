#ifndef CUSTOMPROXYMODELnew_H
#define CUSTOMPROXYMODELnew_H

#include <QSortFilterProxyModel>

class CustomProxyModel1 : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomProxyModel1(QObject *parent = nullptr);

    double filterMinimumYear() const { return minYear; }
    void setFilterMinimumYear(double year);

    double filterMaximumYear() const { return maxYear; }
    void setFilterMaximumYear(double year);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
//    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool yearInRange(double Year) const;

    double minYear;
    double maxYear;
};


#endif // CUSTOMPROXYMODEL_H
