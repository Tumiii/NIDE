#include "debugthread.h"

DebugThread::DebugThread(QString p, std::vector<int> b, std::vector<QString> v, QProcess *pro){
    program = p;
    cmd = "gdb " + p + ".exe --silent";
    breakpoints = b;
    var = v;
    op = "";
    process = pro;
    flag = true;
    updateFlag = false;
    sigFault = false;
}

DebugThread::DebugThread(QString p, std::vector<int> b, std::vector<QString> v){
    program = p;
    cmd = "gdb " + p + ".exe --silent";
    breakpoints = b;
    var = v;
    op = "";
    flag = true;
    updateFlag = false;
    sigFault = false;
}

void DebugThread::run(){
    process = new QProcess();
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(read()));
    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(read()));

    //开启cmd窗口，gdb调试
    process->start(cmd.toStdString().data());
    process->waitForFinished(500);

    //提示开启
    emit updateSignal("Debug starting...", "orange");

    if(process->waitForStarted(5000))
    {//成功开启
        //打断点
        for(std::vector<int>::iterator it = breakpoints.begin(); it != breakpoints.end(); it++){
            cmd = "break " + program + ".c:" + QString::number(*it) + "\r\n";
            process->write(cmd.toStdString().data());
            process->waitForFinished(500);
        }

        emit updateSignal("Debug has started.", "orange");

        //开始调试
        process->write("r\r\n");
        process->waitForFinished(500);

        //第一个断点处获取变量值，更新
        for(std::vector<QString>::iterator it = var.begin(); it != var.end(); it++)
        {
            cmd = "p " + (*it) + "\r\n";
            process->write(cmd.toStdString().data());
            process->waitForFinished(500);
            retMsg = retMsg.mid(retMsg.indexOf("="));
            emit updateSignal((*it) + " " + retMsg, "black"); //原来没有

            /*
            if(updateFlag)
            {
                if(retMsg.indexOf("=") > -1)
                {
                    retMsg = retMsg.mid(retMsg.indexOf("="));
                    emit updateSignal((*it) + " " + retMsg, "black");
                }
                else
                    emit updateSignal((*it) + " : cannot find", "black");
            }
            */
        }

        updateFlag = false;

        while(flag)
        {
            if(op == "c" || op == "s" || op=="n")
            {
                op += "\r\n";

                //操作
                process->write(op.toStdString().data());
                process->waitForFinished(500);

                //获取变量值，更新
                for(std::vector<QString>::iterator it = var.begin(); it != var.end(); it++)
                {
                    cmd = "p " + (*it) + "\r\n";
                    process->write(cmd.toStdString().data());
                    process->waitForFinished(500);
                    retMsg = retMsg.mid(retMsg.indexOf("=")); //
                    emit updateSignal((*it) + " " + retMsg, "black"); //

                    /*
                    if(updateFlag)
                    {
                        if(retMsg.indexOf("=") > -1)
                        {
                            retMsg = retMsg.mid(retMsg.indexOf("="));
                            emit updateSignal((*it) + " " + retMsg, "black");
                        }
                        else
                            emit updateSignal((*it) + " : cannot find", "black");
                    }
                    */

                }

                //清空操作
                updateFlag = false;
                op = "";
            }
            else if(op == "q"){
                //操作
                process->write("q\r\n");
                process->write("y\r\n");
                process->write("exit\r\n");

                //更新
                emit updateSignal("Debug terminated.", "orange");

                //关闭process，退出thread
                process->close();
                break;
            }
            else
                continue;
        }
    }
    else{
        emit updateSignal("Start gdb failed.", "red");
        emit quitSignal();
    }
}

void DebugThread::handleContinue(){
    op = "c";
}
void DebugThread::handleStep(){
    op = "s";
}
void DebugThread::handleNext(){
    op = "n";
}
void DebugThread::handleQuit(){
    op = "q";
}
void DebugThread::read(){
    while(process->canReadLine()){
        QString tmp = QString(process->readLine());
        qDebug()<<">>>>>>>>>>>>>>>"<<tmp;

        //调试“正常”退出
        if(tmp.indexOf("exited normally]") > -1
                || tmp.indexOf("__register_frame_info") > -1){
            emit updateSignal("Debug ended.", "orange");
            emit quitSignal();
            flag = false;
            process->kill();
        }

        //接收到系统中断信号，e.g.SIGSEGV
        if(tmp.indexOf("Program received signal") > -1){
            emit updateSignal(tmp, "red");
            emit updateSignal("Debug ended.", "orange");
            emit quitSignal();
            flag = false;
            sigFault = true;
            process->kill();
        }

        //输出断点出的变量值
        if(tmp.indexOf("$") > -1){
            retMsg = tmp;
        }

        //输出行号
        if(tmp.indexOf("\t\t") > -1){
            updateFlag = true;
            if(!sigFault){
                if(tmp.indexOf("(gdb)") < 0){
                    qDebug()<<"###### debugthread: "<<tmp.left(tmp.indexOf("\t\t")).toInt();
                    emit updateLineNumber(tmp.left(tmp.indexOf("\t\t")).toInt());
                    //emit updateSignal(tmp.left(tmp.indexOf("\t\t")), "green");
                }
                else{
                    while(tmp.indexOf("(gdb)") > -1)
                        tmp.replace("(gdb)", "");
                    qDebug()<<"###### debugthread: "<<tmp.left(tmp.indexOf("\t\t")).toInt();
                    emit updateLineNumber(tmp.left(tmp.indexOf("\t\t")).toInt());
                    //emit updateSignal(tmp.left(tmp.indexOf("\t\t")), "green");
                }
            }
        }

//        //输出行号
//        if(tmp.indexOf(program+".c:") > -1){
//            updateFlag = true;
//            if(!sigFault)
//                emit updateSignal("line " + tmp.right(3) + ":","green");
//        }
    }
}
