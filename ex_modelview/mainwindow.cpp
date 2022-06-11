#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "aboutdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));
    QObject::connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->menuAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    
    _exampleModel = new ExampleModel(this);

    proxyModel = new QSortFilterProxyModel(this);

    proxyModelPrice = new CustomProxyModel(this);

    proxyModelYear = new CustomProxyModel1(this);

    proxyModel->setSourceModel(_exampleModel);

    proxyModelPrice->setSourceModel(proxyModel);

    proxyModelYear->setSourceModel(proxyModelPrice);

    ui->tableView->setModel(proxyModelYear);

    ui->tableView->setSortingEnabled(true);


    proxyModel->setFilterKeyColumn(1);
    
    _shownDetailsColumn = 0;


    /*proxyModelPrice = new CustomProxyModel(this);

    proxyModelPrice->setSourceModel(proxyModel);
    ui->tableView->setModel(proxyModelPrice);

    proxyModelYear = new CustomProxyModel(this);

    proxyModelYear->setSourceModel(proxyModel);
    ui->tableView->setModel(proxyModelYear);*/



}


void MainWindow::loadFile()
{
    delete _exampleModel;
    
    _exampleModel = new ExampleModel(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->fillDataTableFromFile(fileName);
    
    proxyModel->setSourceModel(_exampleModel);



    _shownDetailsColumn = 0;
}


void MainWindow::showAbout()
{
    AboutDialog d;
    d.exec();
}

void MainWindow::addRowSlot()
{
    AddRowDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _exampleModel->appendRow(d.newRow);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int value)
{

}


void MainWindow::on_removeRowButton_clicked()
{
    QString name = ui ->lineEdit->text();
    bool success = _exampleModel->removeRow(name);
    if(!success)
    {
        QMessageBox::warning(this, "Warning", "Failed Deleted");
    }

}


void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File", ".../", "Data (*.csv)");
    _exampleModel->saveDataToFile(fileName);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    proxyModelPrice->setFilterMinimumPrice(value);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    proxyModelYear->setFilterMinimumYear(value);
}



