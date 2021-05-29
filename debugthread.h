#ifndef DEBUGTHREAD_H
#define DEBUGTHREAD_H

#include <QThread>
#include <QString>
#include <QProcess>
#include <QDebug>

#include <vector>

class DebugThread : public QThread
{
    Q_OBJECT
public:
    DebugThread(QString, std::vector<int>, std::vector<QString>, QProcess *);
    DebugThread(QString, std::vector<int>, std::vector<QString>);

signals:
    void updateSignal(QString info, QString color);
    void updateLineNumber(int);
    void quitSignal();

public slots:
    void handleContinue();
    void handleStep();
    void handleNext();
    void handleQuit();
    void read();

private:
    QString program;//程序名
    QString cmd;//指令
    QString op;//操作
    QString retMsg;
    std::vector<int> breakpoints;
    std::vector<QString> var;

    void run() Q_DECL_OVERRIDE;
    QProcess *process;
    bool flag;//判断进程是否继续运行
    bool updateFlag;//判断是否更新行号
    bool sigFault;//判断是否出现中断信号
};

#endif // DEBUGTHREAD_H
