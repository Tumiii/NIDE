#include "replace.h"
#include "ui_replace.h"

replace::replace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    findNumber=0;
}

replace::~replace()
{
    delete ui;
}

void replace::on_pushButton_clicked()
{
    qDebug()<<"click";
    if(ui->checkBox->isChecked())
        emit sendFoundText(ui->foundEdit->text(),1,findNumber++);
    else
        emit sendFoundText(ui->foundEdit->text(),0,findNumber++);
}

void replace::on_pushButton_2_clicked()
{
    if(ui->checkBox->isChecked())
        emit sendReplaceText(ui->foundEdit->text(),ui->replaceEdit->text(),1,findNumber++);
    else
        emit sendReplaceText(ui->foundEdit->text(),ui->replaceEdit->text(),0,findNumber++);
}

void replace::onEndFound(int number)
{
    this->findNumber=number;
    qDebug()<<this->findNumber;
}

void replace::on_pushButton_3_clicked()
{
    if(ui->checkBox->isChecked())
        emit sendReplaceAll(ui->foundEdit->text(),ui->replaceEdit->text(),1,findNumber++);
    else
        emit sendReplaceAll(ui->foundEdit->text(),ui->replaceEdit->text(),0,findNumber++);
}
