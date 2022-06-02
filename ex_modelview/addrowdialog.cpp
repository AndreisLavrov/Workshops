#include "addrowdialog.h"
#include "ui_addrowdialog.h"

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);
    
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void AddRowDialog::saveAddedRow()
{
    newRow.push_back(ui->IDLineEdit->text());
    newRow.push_back(ui->PClassLineEdit->text());
    newRow.push_back(ui->survivedLineEdit->text());
    newRow.push_back(ui->nameLineEdit->text());
    newRow.push_back(ui->sexLineEdit->text());
    newRow.push_back(ui->ageLineEdit->text());
    // other fields
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    
    accept();
}


AddRowDialog::~AddRowDialog()
{
    delete ui;
}
