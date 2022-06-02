#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTransposeProxyModel>
#include "examplemodel.h"

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
    
   // void on_removeRowButton_clicked();

private:
    size_t _shownDetailsColumn;
    ExampleModel *_exampleModel;
    QTransposeProxyModel *_transposeModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
