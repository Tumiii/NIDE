#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>
#include <QProcess>

#include <vector>

#include "debugthread.h"

class DebugDialog : public QDialog
{
    Q_OBJECT

public:
    DebugDialog();
    void setProgram(QString);
    void setBreakpoints(std::vector<int>);
    void showProperties();
    void initProperties();

signals:
    void signalUpdateMarker(int);
    void signalClearMarker();

private slots:
    void slotRun();
    void slotQuit();
    void slotAddVar();
    void updatePrint(QString, QString);
    void updateMarker(int);

private:
    QGridLayout *layout;
    QVBoxLayout *vbLayout;

    QPushButton *nextBtn;//单步跳过
    QPushButton *stepBtn;//单步进入
    QPushButton *continueBtn;//继续执行
    QPushButton *runBtn;//开始调试
    QPushButton *quitBtn;//退出
    QPushButton *addVarBtn;//添加变量
    QLineEdit *inputVar;//变量输入
    QTextEdit *printArea;//输出部分，只读

    void initWidgets();
    void bindSignals();

    QString program;
    std::vector<int> breakpoints;
    std::vector<QString> var;

    QProcess *process;
    DebugThread *dthread;
};

#endif // DEBUGDIALOG_H
