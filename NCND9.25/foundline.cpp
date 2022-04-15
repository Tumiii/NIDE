#include "foundline.h"
#include "ui_foundline.h"

foundLine::foundLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::foundLine)
{
    ui->setupUi(this);
}

foundLine::~foundLine()
{
    delete ui;
}

void foundLine::on_pushButton_clicked()
{
    emit(sendFoundLine(ui->lineEdit->text()));
}
