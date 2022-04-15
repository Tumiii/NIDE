#ifndef FOUNDLINE_H
#define FOUNDLINE_H

#include <QDialog>

namespace Ui {
class foundLine;
}

class foundLine : public QDialog
{
    Q_OBJECT

public:
    explicit foundLine(QWidget *parent = nullptr);
    ~foundLine();
signals:
    void sendFoundLine(QString);
private slots:
    void on_pushButton_clicked();

private:
    Ui::foundLine *ui;
};

#endif // FOUNDLINE_H
