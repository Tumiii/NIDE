#include "debugdialog.h"
#include "debugthread.h"

DebugDialog::DebugDialog(){
    initWidgets();
    bindSignals();

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

void DebugDialog::initWidgets(){
    //初始化控件
    nextBtn = new QPushButton("单步跳过");
    stepBtn = new QPushButton("单步进入");
    continueBtn = new QPushButton("继续执行");
    runBtn = new QPushButton("开始调试");
    quitBtn = new QPushButton("结束调试");
    addVarBtn = new QPushButton("添加查看");
    inputVar = new QLineEdit();
    printArea = new QTextEdit();

    //未开始调试前c, n, s, q是无效的
    nextBtn->setEnabled(false);
    continueBtn->setEnabled(false);
    quitBtn->setEnabled(false);
    stepBtn->setEnabled(false);

    //输出部分只读
    printArea->setReadOnly(true);

    //布局
    layout = new QGridLayout();

    layout->setRowStretch(0,3);
    layout->setRowStretch(1,14);
    layout->setColumnStretch(0,20);
    layout->setColumnMinimumWidth(1,3);
    layout->setSpacing(10);

    layout->addWidget(inputVar,0,0);
    layout->addWidget(addVarBtn,0,1);
    layout->addWidget(printArea,1,0);

    vbLayout = new QVBoxLayout();
    vbLayout->addWidget(runBtn);
    vbLayout->addWidget(stepBtn);
    vbLayout->addWidget(nextBtn);
    vbLayout->addWidget(continueBtn);
    vbLayout->addWidget(quitBtn);
    //vbLayout->setSpacing(5);

    layout->addLayout(vbLayout,1,1);

    setMinimumHeight(300);
    setMinimumWidth(600);
    setLayout(layout);
}

void DebugDialog::initProperties(){
    inputVar->setText("");
    inputVar->setPlaceholderText("在此输入查看的变量");
    printArea->clear();
    printArea->append("<p><font color = black>---debug output---</font></p>");
    var.clear();
}

void DebugDialog::bindSignals(){
    connect(addVarBtn, &QPushButton::clicked, this, &DebugDialog::slotAddVar);
    connect(runBtn, &QPushButton::clicked, this, &DebugDialog::slotRun);
    connect(quitBtn, &QPushButton::clicked, this, &DebugDialog::slotQuit);
}

void DebugDialog::setProgram(QString p){
    this->program = p;
    QString name;
    if(p == "")
        name = "untitled";
    else
        name = p;
    setWindowTitle("Debug - " + name);
}

void DebugDialog::setBreakpoints(std::vector<int> b){
    this->breakpoints = b;
}

void DebugDialog::slotRun(){
    //已经确定编译完成
    nextBtn->setEnabled(true);
    continueBtn->setEnabled(true);
    quitBtn->setEnabled(true);
    stepBtn->setEnabled(true);
    runBtn->setEnabled(false);
    addVarBtn->setEnabled(false);

//    process = new QProcess();

    //dthread = new DebugThread(program, breakpoints, var, process);
    dthread = new DebugThread(program, breakpoints, var);

//    process->moveToThread(dthread);
    connect(dthread, &DebugThread::finished, dthread, &QObject::deleteLater);

    connect(dthread, &DebugThread::updateSignal, this, &DebugDialog::updatePrint);
    connect(dthread, &DebugThread::quitSignal, this, &DebugDialog::slotQuit);
    connect(dthread, &DebugThread::updateLineNumber, this, &DebugDialog::updateMarker);
    connect(stepBtn, &QPushButton::clicked, dthread, &DebugThread::handleStep);
    connect(nextBtn, &QPushButton::clicked, dthread, &DebugThread::handleNext);
    connect(continueBtn, &QPushButton::clicked, dthread, &DebugThread::handleContinue);
    connect(quitBtn, &QPushButton::clicked, dthread, &DebugThread::handleQuit);
    dthread->start();
}

void DebugDialog::slotQuit(){
    addVarBtn->setEnabled(true);
    nextBtn->setEnabled(false);
    continueBtn->setEnabled(false);
    quitBtn->setEnabled(false);
    runBtn->setEnabled(true);
    stepBtn->setEnabled(false);
    emit signalClearMarker();
}

void DebugDialog::slotAddVar(){
    QString toAddVar = inputVar->text();
    if(toAddVar == ""){
        QMessageBox msg(NULL);

        msg.setWindowTitle("Add Watch");
        msg.setText("No input");
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);

        msg.setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
        msg.setWindowFlags(msg.windowFlags() &~ Qt::WindowMinMaxButtonsHint);//禁用最大化最小化
        msg.exec();
    }
    else{
        var.push_back(toAddVar);
        printArea->append("<p><font color = blue>Add Watch: " + toAddVar + "</font></p>");
        QScrollBar *scrollbar = printArea->verticalScrollBar();
        if (scrollbar)
            scrollbar->setSliderPosition(scrollbar->maximum());
        inputVar->setText("");
    }
}

void DebugDialog::showProperties(){
    qDebug()<<"debug dialog properties";
    qDebug()<<"program: "<<program;
    for(std::vector<int>::iterator it = breakpoints.begin(); it != breakpoints.end(); ){
        qDebug()<<*it;
        it++;
    }
    qDebug()<<"end of breakpoints";
    for(std::vector<QString>::iterator it = var.begin(); it != var.end(); ){
        qDebug()<<*it;
        it++;
    }
    qDebug()<<"end of var";
}

void DebugDialog::updatePrint(QString retMsg, QString color){
    printArea->append("<p><font color = " + color + ">" + retMsg + "</font></p>");
    QScrollBar *scrollbar = printArea->verticalScrollBar();
    if (scrollbar)
        scrollbar->setSliderPosition(scrollbar->maximum());
}

void DebugDialog::updateMarker(int num){
    qDebug()<<"###### debugdialog: "<<num;
    emit signalUpdateMarker(num);
}
