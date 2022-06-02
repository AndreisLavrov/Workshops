#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include <QFileDialog>
#include "form.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    QObject::connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));
    QObject::connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    
    _exampleModel = new ExampleModel(this);
    ui->tableView->setModel(_exampleModel);
    
    _transposeModel = new QTransposeProxyModel(this);
    _transposeModel->setSourceModel(_exampleModel);
    ui->tableDetailsView->setModel(_transposeModel);
    for (int i = 1; i < _transposeModel->columnCount(); ++i)
    {
        ui->tableDetailsView->hideColumn(i);
    }
    _shownDetailsColumn = 0;
}


void MainWindow::loadFile()
{
    delete _exampleModel;
    
    _exampleModel = new ExampleModel(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->fillDataTableFromFile(fileName);
    
    ui->tableView->setModel(_exampleModel);
    _transposeModel->setSourceModel(_exampleModel);
    for (int i = 1; i < _transposeModel->columnCount(); ++i)
    {
        ui->tableDetailsView->hideColumn(i);
    }
    _shownDetailsColumn = 0;
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
    ui->tableDetailsView->hideColumn(_shownDetailsColumn);
    _shownDetailsColumn = value;
    ui->tableDetailsView->setColumnHidden(value, false);
}


/*void MainWindow::on_removeRowButton_clicked()
{
    Form d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _exampleModel->appendRow(d.newRow);
    }
}*/

