#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include<QDebug>

namespace Ui {
class Dialog;
}

class replace : public QDialog
{
    Q_OBJECT

public:
    explicit replace(QWidget *parent = 0);
    QString replaceText;
    ~replace();
signals:
    void sendFoundText(QString,int,int);
    void sendReplaceText(QString,QString,int,int);
    void sendReplaceAll(QString,QString,int,int);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void onEndFound(int);

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    int findNumber;
    bool caseSensitive;     //区分大小写标识符
    QString findText;       //查询内容
       //替换内容
};

#endif // DIALOG_H
