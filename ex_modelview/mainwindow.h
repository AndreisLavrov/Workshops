#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTransposeProxyModel>
#include "examplemodel.h"
#include <QSortFilterProxyModel>
#include "customproxymodel.h"
#include "customproxymodel1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
   void loadFile();
   void addRowSlot();
   void on_spinBox_valueChanged(int arg1);
   void on_removeRowButton_clicked();

   void on_pushButton_4_clicked();

   void on_horizontalSlider_valueChanged(int value);

   void on_horizontalSlider_2_valueChanged(int value);

private:
    size_t _shownDetailsColumn;
    ExampleModel *_exampleModel;
    QSortFilterProxyModel *proxyModel;
    Ui::MainWindow *ui;
    CustomProxyModel *proxyModelPrice;
    CustomProxyModel *proxyModelYear;
};
#endif // MAINWINDOW_H
