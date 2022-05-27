#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include "examplemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    examplemodel = new ExampleModel(this);
    ui->tableView->setModel(examplemodel);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadFileSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "..", "Data (*.csv)");

    delete examplemodel;

    examplemodel = new ExampleModel(this);
    examplemodel->fillDataTableFromFile(fileName);

     ui->tableView->setModel(examplemodel);

}


