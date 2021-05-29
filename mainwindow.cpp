#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debugdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //判断代码编辑区是否被更改
    keyPressEater=new MyKeyPressEater;
    createEditor();
    createMenu();
    setconnect();
    breakpoint();
    isChanged=false;
    isComp=false;
    powerShell=new QProcess(this);
    pathList=new QList<Node>();
    ui->fileTree->setColumnCount(1); //设置列数
    ui->fileTree->setHeaderLabel(tr("文件名")); //设置头的标题
    //设置状态栏标签，显示光标行列位置
    label = new QLabel(this);
    ui->statusBar->addPermanentWidget(label);

}
void MainWindow::breakpoint()
{
    //断点设置区域
    //https://qscintilla.com/symbol-margin/
    editor->setMarginsBackgroundColor(QColor("#bbfaae"));
    editor->setMarginMarkerMask(1, 0x02);
    editor->markerDefine(QsciScintilla::Circle, 1);//断点形状大小
    editor->setMarkerBackgroundColor(QColor("#ee1111"), 1);//断点颜色
    //2.3单步执行显示区域
    editor->setMarginType(2, QsciScintilla::SymbolMargin);
    editor->setMarginLineNumbers(2, false);
    editor->setMarginWidth(2, 20);
    editor->setMarginSensitivity(2, false);
    editor->setMarginMarkerMask(2, 0x04);
    editor->markerDefine(QsciScintilla::RightArrow, 2);
    editor->setMarkerBackgroundColor(QColor("#eaf593"), 2);

}

void MainWindow::setconnect()
{
    //编译功能
    connect(compComp,SIGNAL(triggered()),this,SLOT(compCode()));
    connect(runComp,SIGNAL(triggered()),this,SLOT(runCode()));
    //编辑功能
    connect(copyEdit,SIGNAL(triggered()),this,SLOT(onCopyEdit()));
    connect(pasteEdit,SIGNAL(triggered()),this,SLOT(onPasteEdit()));
    connect(cutEdit,SIGNAL(triggered()),this,SLOT(onCutEdit()));
    connect(allselectEdit,SIGNAL(triggered()),this,SLOT(onAllSelect()));
    connect(revocationEdit,SIGNAL(triggered()),this,SLOT(onRevocationEdit()));
    connect(findline,SIGNAL(triggered()),this,SLOT(onFindLine()));
    //文件功能
    connect(newFile,SIGNAL(triggered()),this,SLOT(onNew()));
    connect(openFile,SIGNAL(triggered()),this,SLOT(onOpen()));
    connect(saveFile,SIGNAL(triggered()),this,SLOT(onSave()));
    connect(saveAsFile, SIGNAL(triggered()), this, SLOT(onSaveAs()));
    //设置状态栏标签，显示光标行列位置
    connect(editor,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(showCursorPosition(int,int)));
    //点击替换弹出窗口的信号槽链接
    connect(this->replaceEdit,SIGNAL(triggered()),this,SLOT(openReplace()));
    //键盘监听
    connect(keyPressEater, SIGNAL(keyPressSiganl_puncComplete(int)), this, SLOT(handlePuncComplete(int)));
    connect(keyPressEater,SIGNAL(mouseRightFunc()),this,SLOT(mouserright()));
    connect(editor,SIGNAL(indicatorReleased (int, int, Qt::KeyboardModifiers)),this,SLOT(jumpDefination(int,int,Qt::KeyboardModifiers)));
    connect(editor,SIGNAL(textChanged()),this,SLOT(recordPos()));
    //断点设置区域
    //https://qscintilla.com/symbol-margin/
    connect(editor, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),this,SLOT(on_margin_clicked(int, int, Qt::KeyboardModifiers)));
     //2.3单步执行显示区域
    connect(editor, SIGNAL(textChanged()),this, SLOT(documentWasModified()));//点击断点区域 绑定有关断点的函数
    //更新单步执行
    connect(&debugDialog, SIGNAL(signalUpdateMarker(int)), this, SLOT(updateLineNumberSlot(int)));
    connect(&debugDialog, SIGNAL(signalClearMarker()), this, SLOT(clearMarker()));
    //文本发生改变引发操作
    connect(editor,SIGNAL(textChanged()),this,SLOT(onChanged()));

}
//创建菜单栏
void MainWindow::createMenu()
{
    //设置菜单栏
    //文件功能菜单
    fileMenu=this->menuBar()->addMenu("文件");
    newFile=new QAction("新建文件",this);
    newFile->setShortcut(tr("ctrl+n"));
    fileMenu->addAction(newFile);
    fileMenu ->addSeparator();

    openFile = new QAction("打开文件",this);
    fileMenu ->addAction(openFile);
    openFile ->setShortcut(tr("ctrl+o"));
    fileMenu ->addSeparator();

    saveFile = new QAction("保存文件",this);
    fileMenu ->addAction(saveFile);
    saveFile ->setShortcut(tr("ctrl+s"));
    fileMenu ->addSeparator();

    saveAsFile = new QAction("另存文件",this);
    fileMenu ->addAction(saveAsFile);
    saveAsFile ->setShortcut(tr("ctrl+shift+s"));
    fileMenu ->addSeparator();

    //编辑功能菜单
    editMenu = this->menuBar()->addMenu("编辑");
    copyEdit = new QAction("复制",this);
    copyEdit ->setShortcut(tr("ctrl+c"));
    editMenu ->addAction(copyEdit);
    editMenu ->addSeparator();

    pasteEdit = new QAction("粘贴",this);
    pasteEdit ->setShortcut(tr("ctrl+v"));
    editMenu ->addAction(pasteEdit);
    editMenu ->addSeparator();

    cutEdit = new QAction("剪切",this);
    cutEdit ->setShortcut(tr("ctrl+x"));
    editMenu ->addAction(cutEdit);
    editMenu ->addSeparator();

    allselectEdit = new QAction("全选",this);
    allselectEdit ->setShortcut(tr("ctrl+a"));
    editMenu ->addAction(allselectEdit);
    editMenu ->addSeparator();

    revocationEdit = new QAction("撤销",this);
    revocationEdit ->setShortcut(tr("ctrl+z"));
    editMenu ->addAction(revocationEdit);
    editMenu ->addSeparator();

    replaceEdit = new QAction("替换",this);
    replaceEdit->setShortcut(tr("ctrl+f"));
    editMenu ->addAction(replaceEdit);
    editMenu ->addSeparator();

    findline=new QAction("查找行",this);
    findline->setShortcut(tr("ctrl+l"));
    editMenu ->addAction(findline);
    editMenu ->addSeparator();

    annotateHideAct=new QAction("隐藏/显示",this);
    annotateHideAct->setShortcut(tr("F8"));
    editMenu ->addAction(annotateHideAct);
    connect(annotateHideAct,SIGNAL(triggered()),this,SLOT(annotate_hide_and_show()));

    allFormattingAct=new QAction("格式化",this);
    allFormattingAct->setShortcut(tr("F3"));
    editMenu ->addAction(allFormattingAct);
    connect(allFormattingAct, SIGNAL(triggered()), this, SLOT(Formatting_All()));
    //编译功能菜单
    compMenu=this->menuBar()->addMenu("编译");
    compComp=new QAction("编译",this);
    compComp->setShortcut(tr("ctrl+b"));
    compMenu->addAction(compComp);
    compMenu->addSeparator();

    runComp=new QAction("运行",this);
    runComp->setShortcut(tr("ctrl+r"));
    compMenu->addAction(runComp);

    compMenu->addSeparator();

    debugAct = new QAction(("debug"),this);
    debugAct->setShortcut(tr("F5"));
    compMenu->addAction(debugAct);
    connect(debugAct, SIGNAL(triggered()), this, SLOT(debugSlot()));


}
//创建代码编辑区
void MainWindow::createEditor()
{

    editor=new QsciScintilla(ui->centralWidget);
    editor->setGeometry(280,12,700,420);
    editor->setMarginType(0,QsciScintilla::NumberMargin);//设置编号为0的页边显示行号
    editor->setMarginLineNumbers(0,true);//对该页边启用行号
    editor->setMarginWidth(0,35);
    editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);
    QsciLexer *textLexer;
    textLexer = new QsciLexerCPP;
    textLexer->setColor(QColor(Qt:: green),QsciLexerCPP::CommentLine);              //设置自带的注释行为绿色
    textLexer->setColor(QColor(Qt:: yellow),QsciLexerCPP::KeywordSet2);             //设置自定义关键字的颜色为黄色
    editor->setLexer(textLexer);
    editor->installEventFilter(keyPressEater);
    QsciAPIs *apis = new QsciAPIs(textLexer);
    apis->add(QString("move"));//可自行添加
    apis->add(QString("moive"));
    if(apis->load(QString(":/new/IIIIcon/Icon/apis")))
        qDebug()<<"读取成功";
    else
        qDebug()<<"读取失败";
    //在这里可以添加自定义的自动完成函数
    //apis->add(QString("func_name(arg_1,arg_2) function info"));
    apis->prepare();
    //设置自动完成所有项
    editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    //设置大小写敏感
    editor->setAutoCompletionCaseSensitivity(true);
    editor->setAutoCompletionFillupsEnabled(true);
    //每输入1个字符就出现自动完成的提示
    editor->setAutoCompletionThreshold(1);
    //开启自动缩进
    editor->setAutoIndent(true);
    //设置缩进的显示方式
    editor->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);
    //显示选中的行号
    editor->setCaretLineVisible(true);
    //显示选中行号的背景色
    editor->setCaretLineBackgroundColor(Qt::lightGray);
    //左侧行号显示的背景色
    editor->setMarginsBackgroundColor(Qt::gray);
    //设置括号匹配
    editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    QSizePolicy sizePolicy = editor->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    editor->setSizePolicy(sizePolicy);
    QSizePolicy sizePolicy1 = editor->sizePolicy();
    sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    //设置函数折叠

    editor->setSizePolicy(sizePolicy1);
    editor->setMarginType(1, QsciScintilla::SymbolMargin);
    editor->setMarginLineNumbers(1, false);
    editor->setMarginWidth(1, 20);
    editor->setMarginSensitivity(1, true);
    editor->setMarginType(3, QsciScintilla::SymbolMargin);
    editor->setMarginLineNumbers(3, false);
    editor->setMarginWidth(3, 15);
    editor->setMarginSensitivity(3, true);
    editor->setFolding(QsciScintilla::BoxedTreeFoldStyle, 3);
    ui->gridLayout->addWidget(editor,0,1);

    editor->setAutoIndent(true);
    //设置缩进的显示方式
    editor->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);
    //设置编辑区
    editor->setFont(QFont("14"));//到时候试一下是否可以
    //键盘监听
    editor->hide();//暂时隐藏编辑部件
}

void MainWindow::documentWasModified(){
    setWindowModified(editor->isModified());
}

//显示光标位置
void MainWindow::showCursorPosition(int rowNum,int columnNum)
{
    editor->getCursorPosition(&rowNum,&columnNum);
    //qDebug()<<columnNum<<rowNum;
    label->setText(tr("%1行 %2列").arg(rowNum).arg(columnNum));
}
//判断是否文本更改
void MainWindow::onChanged()
{
    isChanged=true;
}
//打开文件
void MainWindow::onOpen()
{
    if(isChanged==true)
    {
        messageBoxOpen();
    }
   deleteTree();
   filePath =  QFileDialog::getOpenFileName(this,"打开","","C(*.c)");
   if(filePath.isEmpty()) return ;//考虑用户选择取消的情景
   FILE *p = fopen(filePath.toStdString().data(),"r");
   if(p == NULL) return ;
    QString str;
    while(!feof(p))
    {
        char buf[1024] = {0};
        fgets(buf,sizeof(buf),p);
        str += buf;
    }
    fclose(p);
    editor->setText(str);
    //改成----------------》
    isChanged=false;
    QString tmpFilePath=filePath.section('/',0,-2);
    if(findPath(filePath)!=0)
    {
        //qDebug()<<"1111";
        qDebug()<<isChanged<<2;
        return;
    }
    else if(findPath(tmpFilePath)!=0)
    {
        qDebug()<<isChanged<<1;
        return;
    }
    else
    {
        qDebug()<<isChanged;
        showTree();
    }

    ui->WelcomeBrowser->hide();
    editor->show();
    showTreeFunc();
    qDebug()<<pathList->length();
    addFunctionTree();
}
//保存文件
void MainWindow::onSave()
{

    if(filePath.isEmpty())
    {
        filePath = QFileDialog::getSaveFileName(this,"保存文件","","(*.c)");
    }
    if(!filePath.isEmpty())
    {
        FILE *p = fopen(filePath.toStdString().data(),"w");
        if(p == NULL) return ;
        QString str = editor->text();
        isComp=true;
        isChanged=false;
        fputs(str.toStdString().data(),p);
        fclose(p);
        ui->consoleShow->insertPlainText("保存成功\n");
    }
}
//另存文件
void MainWindow::onSaveAs()
{
    if(filePath.isEmpty())
    {
        filePath = QFileDialog::getSaveFileName(this,"另存文件","","(*.c)");
    }
    if(!filePath.isEmpty())
    {
        filePath = QFileDialog::getSaveFileName(this,"另存文件","","(*.c)");
        FILE *p = fopen(filePath.toStdString().data(),"w");
        if(p == NULL) return ;
        QString str = editor->text();
        fputs(str.toStdString().data(),p);
        fclose(p);
        ui->consoleShow->insertPlainText("保存成功\n");
        QString tmpFilePath=filePath.section('/',0,-2);
        if(findPath(tmpFilePath)!=0)
        {
            for(int i=0;i<pathList->length();i++)
            {
                if(pathList->at(i).path==filePath.section('/',0,-2))
                {
                    addTreeNode(pathList->at(i).pathNode,filePath);
                }
            }
        }
    }
}
//新建文件
void MainWindow::onNew()
{
    filePath = QFileDialog::getSaveFileName(this,"新建文件","","(*.c)");
    if(filePath.isEmpty()) return ;//考虑用户选择取消的情景
    if(isChanged == true)
    {
        onSave();
        isChanged = false;
    }
    isChanged=true;
    //filePath = "";
    editor->setText("");
    FILE *p = fopen(filePath.toStdString().data(),"w");
    if(p == NULL) return ;
    QString str = editor->text();
    fputs(str.toStdString().data(),p);
    fclose(p);
    QString tmpFilePath=filePath.section('/',0,-2);
    if(findPath(filePath)!=0)
    {
        return;
    }
    else if(findPath(tmpFilePath)!=0)
    {
        for(int i=0;i<pathList->length();i++)
        {
            if(pathList->at(i).path==filePath.section('/',0,-2))
            {
                addTreeNode(pathList->at(i).pathNode,filePath);
            }
        }
    }
    else
    {
        showTree();
    }

    ui->WelcomeBrowser->hide();
    editor->show();
}
//预编译
void MainWindow::precomp()
{
    FILE *p = fopen(filePath.toStdString().data(),"r");
    if(p==NULL)
    {
        return;
    }
    //qDebug()<<filePath;
    QString cmd=filePath+".c";
    FILE *p1 = fopen(cmd.toStdString().data(),"w");
    if(p1==NULL)
    {
        return;
    }
    QString str;
    while(!feof(p))
    {
        char buf[1024]={0};
        fgets(buf,sizeof(buf),p);
        str += buf;
    }
    if(str=="")
    {
        QMessageBox::warning(this,"警告","文件为空，无法编译！");
        isComp=false;
        //******
        fputs(str.toStdString().data(),p1);
        fclose(p);
        fclose(p1);
        return;
    }
    isComp=true;
    fputs(str.toStdString().data(),p1);
    fclose(p);
    fclose(p1);
}
//提醒是否保存
void MainWindow::messageBoxOpen()
{
    QMessageBox messageBox(QMessageBox::NoIcon,"保存文件", "文件尚未保存，是否保存？",QMessageBox::Yes | QMessageBox::No, NULL);
        int result=messageBox.exec();
        switch (result)
        {
        case QMessageBox::Yes:
            isChanged=false;
            onSave();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
}

//编译功能---***
bool MainWindow::compCode()
{
    if(isChanged==true)
    {
        messageBoxOpen();
        //onSave();
    }
    precomp();
    if(isComp==false)
    {
        return false;
    }
    isComp=false;
    QString cmd;
    QString tmpFilePath=filePath;
    //qDebug()<<filePath<<"1";
    tmpFilePath.remove(-2,2);
    const char *s=tmpFilePath.toStdString().data();
    cmd.sprintf("cmd /c gcc -g -fexec-charset=GBK -o %s.exe %s.c",s,s);
    qDebug()<<cmd;
    QString cmdd;
    cmdd.sprintf("正在生成文件：%s.exe...",s);
    QString cmddd;
    cmddd.sprintf("cmd /c gcc -g -fexec-charset=GBK -o %s.c.exe %s.c.c",s,s);
    powerShell->start(cmd);
    powerShell->waitForFinished(-1);
    QByteArray out = powerShell->readAllStandardOutput();
    QByteArray outError = powerShell->readAllStandardError();
    if(outError!="")
    {
        ui->consoleShow->insertPlainText(QString::fromLocal8Bit(outError)+"\n");
        ui->consoleShow->insertPlainText("---------------------------------------------------------------\n");
        return false;
    }
    ui->consoleShow->insertPlainText("success!"+QString::fromLocal8Bit(out)+"\n");
    powerShell->close();
    qDebug()<<"cmd::"<<cmddd;
    powerShell->start(cmddd);
    powerShell->waitForFinished(-1);
    powerShell->close();
    ui->consoleShow->insertPlainText(cmdd+"\n");
    //删除临时文件
    qDebug()<<filePath;
    cmd=filePath+".c";
//    remove(cmd.toStdString().data());
    ui->consoleShow->insertPlainText("---------------------------------------------------------------\n");
    return true;
}

//运行功能---***
void MainWindow::runCode()
{
    compCode();
    QString tmpFilePath=filePath;
    tmpFilePath.remove(-2,2);
    QString cmd="cmd /c "+tmpFilePath+".exe && pause";
    system(cmd.toStdString().data());
}
//打开替换界面
void MainWindow::openReplace()
{

    replace *r=new replace();
    r->setWindowTitle("替换");
    connect(r,SIGNAL(sendFoundText(QString,int,int)),this,SLOT(onFoundEdit(QString,int,int)));
    connect(r,SIGNAL(sendReplaceText(QString,QString,int,int)),this,SLOT(onReplaceEdit(QString,QString,int,int)));
    connect(this,SIGNAL(sendEndFound(int)),r,SLOT(onEndFound(int)));
    connect(r,SIGNAL(sendReplaceAll(QString,QString,int,int)),this,SLOT(onReplaceAll(QString,QString,int,int)));
    r->show();
}
//复制
void MainWindow::onCopyEdit()
{
    editor->copy();
}

//粘贴
void MainWindow::onPasteEdit()
{
    editor->paste();
}

//剪切
void MainWindow::onCutEdit()
{
    editor->cut();
}

//全选
void MainWindow::onAllSelect()
{
    editor->selectAll();
}

//撤销
void MainWindow::onRevocationEdit()
{
    editor->undo();
}
//查找
void MainWindow::onFoundEdit(QString foundText,int op,int number)
{
    //qDebug()<<"nihao";
    if (foundText.trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("警告"), tr("输入框为空"));
    }
    else
    {
        if(number==0){
            editor->setCursorPosition(1,0);
        }
        if(op==0)
        {
            if(editor->findFirst(foundText,false,false,false,true))
            {

                QPalette palette = editor->palette();
                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
                editor->setPalette(palette);
            }
            else
            {
                if(number!=0)
                {
                    QMessageBox::information(this, tr("查找"), tr("已经查找完毕"));
                    number=0;
                    emit sendEndFound(0);
                }
                else
                {
                    QMessageBox::information(this,tr("查找"),tr("没有找到该字符串"));
                }
            }
        }
        else
        {
            if(editor->findFirst(foundText,false,true,false,true))
            {

                QPalette palette = editor->palette();
                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
                editor->setPalette(palette);
            }
            else
            {
                if(number!=0)
                {
                    QMessageBox::information(this, tr("查找"), tr("已经查找完毕"));
                    number=0;
                    emit sendEndFound(0);
                }
                else
                {
                    QMessageBox::information(this,tr("查找"),tr("没有找到该字符串"));
                }
            }
        }

    }
}

//替换
void MainWindow::onReplaceEdit(QString foundText,QString replaceText,int op,int number)
{
    if(number!=0)
    {
        editor->replace(replaceText);
    }

    if(number==0){
        editor->setCursorPosition(0,0);
    }
    if (foundText.trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("警告"), tr("输入框为空"));
    }
    else
    {
        if(op==0)
        {
            if(editor->findFirst(foundText,false,false,false,false))
            {

                QPalette palette = editor->palette();
                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
                editor->setPalette(palette);
            }
            else
            {
                if(number==0)
                    QMessageBox::information(this,tr("结果"),tr("没有查询到相关内容"),QMessageBox::Yes);
                if(number>0)
                {
                    emit sendEndFound(0);
                    QMessageBox::information(this,tr("结果"),tr("已经替换完最后一个"),QMessageBox::Yes);
                    number++;
                }
            }
        }
        else
        {
            if(editor->findFirst(foundText,false,false,false,true))
            {

                QPalette palette = editor->palette();
                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
                editor->setPalette(palette);
                number++;
            }
            else
            {
                QMessageBox::information(this,tr("结果"),tr("没有查询到相关内容"),QMessageBox::Yes);
                if(number>0)
                {
                    emit sendEndFound(0);
                }
            }
        }
    }
}

//替换所有
void MainWindow::onReplaceAll(QString foundText,QString replaceText,int op,int number)
{
    qDebug()<<number;
    if(number==0){
        editor->setCursorPosition(0,0);
    }
    if(op==0)
    {
        while(editor->findFirst(foundText,false,false,false,false))
        {
            editor->replace(replaceText);
        }
        number+=1;
    }
    else
    {
        qDebug()<<"hh";
        while(editor->findFirst(foundText,false,true,false,false))
        {
            editor->replace(replaceText);
        }

    }
    if(number>0)
    {
        emit sendEndFound(0);

    }
    QMessageBox::information(this,tr("结果"),tr("全部替换完成"),QMessageBox::Yes);

}
//显示树状资源
void MainWindow::showTree()
{
    QStringList fileShow=filePath.split('/');
    stableParent=filePath.section('/',0,-3);
    //qDebug()<<stableParent;
    int index=fileShow.length();
    //qDebug()<<"1";
    QString parentName=fileShow[index-2];
    //qDebug()<<"2";
    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->fileTree,QStringList(parentName));
    QString fiile=filePath.section('/',0,-2);
    node *tmp=new node();
    tmp->path=fiile;
    tmp->pathNode=imageItem1;
    pathList->append(*tmp);
    //qDebug()<<fiile<<3;
    connect(ui->fileTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(openFilter(QTreeWidgetItem*,int)));
    allFile(imageItem1,fiile);
    ui->fileTree->expandAll(); //结点全部展开
}

//遍历添加
QFileInfoList MainWindow::allFile(QTreeWidgetItem *root,QString path)         //参数为主函数中添加的item和路径名
{

    /*添加path路径文件*/
    QDir dir(path);          //遍历各级子目录
    QDir dir_file(path);    //遍历子目录中所有文件
    dir_file.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);        //获取当前所有文件
    dir_file.setSorting(QDir::Name);
    QFileInfoList list_file = dir_file.entryInfoList();
    for (int i = 0; i < list_file.size(); ++i)
    {       //将当前目录中所有文件添加到treewidget中
        QFileInfo fileInfo = list_file.at(i);
        //qDebug()<<fileInfo.absoluteFilePath()<<fileInfo.absoluteDir()<<fileInfo.absolutePath()<<1;
        QString name2=fileInfo.fileName();
        if(name2.right(2)==".c")
        {

            QTreeWidgetItem* child = new QTreeWidgetItem(QStringList()<<name2);
            node *tmp=new node();
            tmp->path=fileInfo.absoluteFilePath();
            tmp->pathNode=child;
            pathList->append(*tmp);
            //child->setIcon(0, QIcon(":/file/image/link.ico"));
            child->setCheckState(1, Qt::Checked);
            root->addChild(child);
        }
    }
    QFileInfoList file_list=dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);   //获取当前所有目录
    for(int i = 0; i != folder_list.size(); i++)         //自动递归添加各目录到上一级目录
    {

             QString namepath = folder_list.at(i).absoluteFilePath();    //获取路径
             QFileInfo folderinfo= folder_list.at(i);
             QString name=folderinfo.fileName();      //获取目录名
             QTreeWidgetItem* childroot = new QTreeWidgetItem(QStringList()<<name);
             //childroot->setIcon(0, QIcon(":/file/image/link.ico"));
             childroot->setCheckState(1, Qt::Checked);
             root->addChild(childroot);              //将当前目录添加成path的子项
             QFileInfoList child_file_list = allFile(childroot,namepath);          //进行递归
             file_list.append(child_file_list);
             file_list.append(name);
     }
    return file_list;
}
//点击树状资源打开相应文件
void MainWindow::openFilter(QTreeWidgetItem *item,int index)
{
    bool flag=true;
    for(int i=0;i<pathList->length();i++)
    {
        qDebug()<<pathList->at(i).path.section("/",-1)<<item->text(0);
        if(pathList->at(i).path.section("/",-1)==item->text(0))
        {
            flag=false;
            break;
        }
    }
    if(!flag)
    {
        if(isChanged==true)
        {
            messageBoxOpen();
        }
        deleteTree();
        /*得到文件路径*/
        QStringList fileName;
        QTreeWidgetItem *itemfile=item; //获取被点击的item
        while(itemfile!=NULL)
        {
            fileName<<itemfile->text(0); //获取itemfile名称
            itemfile=itemfile->parent(); //将itemfile指向父item
        }
        QString strpath;
        //cout<<filepath.size()<<endl;
        for(int i=(fileName.size()-1);i>=0;i--) //QStringlist类filepath反向存着初始item的路径
        { //将filepath反向输出，相应的加入’/‘
            strpath+=fileName.at(i);
            if(i!=0)
                strpath+="/";
        }
        filePath=stableParent+'/'+strpath;
        //qDebug()<<filePath<<"1";
        FILE *p = fopen(filePath.toStdString().data(),"r");
        if(p == NULL) return ;
        QString str;
        //qDebug()<<"1";
        while(!feof(p))
        {
            char buf[1024] = {0};
            fgets(buf,sizeof(buf),p);
            str += buf;
        }
        fclose(p);
        editor->setText(str);
        isChanged = false;
        showTreeFunc();
        qDebug()<<pathList->length();
        addFunctionTree();
    }
    else
    {
        //跳转函数
        qDebug()<<"jump is ok "<<item->text(0);
        jumpToFunc(item->text(0));
    }
}
//遍历绝对路径是否存在
int MainWindow::findPath(QString tmppath)
{
    QString path=tmppath;
    for(int i=0;i<pathList->length();i++)
    {
        if(pathList->at(i).path==path)
        {
            return -1;
        }
    }
    return 0;
}
//如果在已有父节点增加文件即增加节点的操作

void MainWindow::addTreeNode(QTreeWidgetItem *parentNode,QString name)
{
    QString path=name;
    QTreeWidgetItem* child = new QTreeWidgetItem(QStringList()<<path.section('/',-1));
    node *tmp=new node();
    tmp->path=path;
    tmp->pathNode=child;
    parentNode->addChild(child);
    pathList->append(*tmp);
}
MainWindow::~MainWindow()
{
    if(powerShell)
    {
        powerShell->terminate();
        powerShell->waitForFinished();
    }
    delete ui;
}

void MainWindow::on_newFile_triggered()//新建
{
    onNew();
}

void MainWindow::on_openFile_triggered()//打开
{
    onOpen();
}


void MainWindow::on_saveFile_triggered()//保存
{
    onSave();
}

void MainWindow::on_saveOther_triggered()//另存为
{
    onSaveAs();
}


void MainWindow::on_searchAndReplace_triggered()//查找替换
{
    openReplace();
}

void MainWindow::on_bianyi_triggered()//编译
{
    compCode();
}


void MainWindow::on_Process_triggered()//运行
{
    runCode();
}

void MainWindow::on_byAndProcess_triggered()//编译运行
{
    compCode();
    runCode();

}

void MainWindow::on_copy_triggered()//复制
{
    onCopyEdit();
}

void MainWindow::on_cut_triggered()//剪切
{
    onCutEdit();
}

void MainWindow::on_paste_triggered()//粘贴
{
    onPasteEdit();
}

void MainWindow::on_selAll_triggered()//全选
{
    onAllSelect();
}

void MainWindow::on_biteTheDust_triggered()//撤销 //Killer queen!The third bomb-Bite the Dust!
{
    onRevocationEdit();
}

//监听键盘输入
bool MyKeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug()<<"key::::::"<<keyEvent->key();
        if(keyEvent->key() == 40 || keyEvent->key() == 91 || keyEvent->key() == 123
                || keyEvent->key() == 34 || keyEvent->key() == 39||keyEvent->key() ==59
                ||keyEvent->key() ==Qt::Key_Enter||keyEvent->key() ==Qt::Key_Return){
            //qDebug("Ate key press %d", keyEvent->key());
            emit keyPressSiganl_puncComplete(keyEvent->key());
            return true;
        }
        else return QObject::eventFilter(obj, event);
    }

    else {

        return QObject::eventFilter(obj, event);
    }
}
void MainWindow::lineFormatting(int linenum){//传入行号
    QList<QString> keyword_table;
    keyword_table<<"+"<<"-"<<"*"<<"/"<<"("<<")"<<"="<<"<"<<">"<<","<<";";
    int sum_indexnum=0;//这一行总字符数

    sum_indexnum=editor->text(linenum).size();
    for(int indexnum=0;indexnum<sum_indexnum;indexnum++){//默认一行不超过200个字符
        editor->setSelection(linenum,indexnum,linenum,indexnum+1);
        for(int i=0;i<keyword_table.size();i++){
            if(editor->selectedText()=="+"){//+=、++单独处理
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" "||editor->selectedText()=="+");//先看是否已有空格或+，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" "||editor->selectedText()=="+"||editor->selectedText()=="=");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
            else if(editor->selectedText()=="-"){//-=、--单独处理
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" "||editor->selectedText()=="-");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" "||editor->selectedText()=="-"||editor->selectedText()=="="||editor->selectedText()==">");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
            else if(editor->selectedText()=="="){//+=,-=,*=,/=单独处理
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" "||editor->selectedText()=="-"||editor->selectedText()=="+"||editor->selectedText()=="*"||editor->selectedText()=="/");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" ");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
            else if(editor->selectedText()==">"){//->单独处理
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" "||editor->selectedText()=="-");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" ");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
            else if(editor->selectedText()=="*"){//*=单独处理
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" ");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" "||editor->selectedText()=="=");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
            else if(editor->selectedText()=="/"){// /=单独处理
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" ");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" "||editor->selectedText()=="=");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
            else if(editor->selectedText()==keyword_table[i]){
                editor->setSelection(linenum,indexnum-1,linenum,indexnum);//先加左边空格
                if(editor->selectedText()==" ");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                editor->setSelection(linenum,indexnum+1,linenum,indexnum+2);//再加右边空格
                if(editor->selectedText()==" ");//先看是否已有空格，防止重复添加
                else {
                    editor->insertAt(" ",linenum,indexnum+1);
                    indexnum++;
                    sum_indexnum++;
                    //last_indexnum=indexnum;
                }
                break;
            }
        }
    }
    for(int i=sum_indexnum;i>=0;i--){
        editor->setSelection(linenum,i,linenum,i+1);
        if(editor->selectedText()==";"){
            this->editor->setCursorPosition(linenum, i+2);
            return;
        }
    }
}
//行首缩进
void MainWindow::Line_Indent(int linenum,int flag){//传入的是敲回车的行，要缩进的是下一行
    int sum_indexnum=0;//这一行总字符数
    int tab_num=0;//这一行的前置空格数
    int tab_num_new=0;//下一行需要添加的前置空格数，因为或许前面已经有了
    sum_indexnum=editor->text(linenum).size();
    QString temp=editor->text(linenum);
    tab_num=temp.count("\t");
    if(flag==1)
        tab_num++;//新的{要额外缩进
    if(flag==-1)
        tab_num--;//新的{要额外缩进
    tab_num_new=tab_num-editor->text(linenum+1).count("\t");
    qDebug()<<tab_num;
    for(int i=0;i<tab_num_new;i++){
        this->editor->insertAt(tr("\t"),linenum+1,i);
    }
    this->editor->setCursorPosition(linenum+1, tab_num);
}
//回车规范
void MainWindow::Enter_Formatting(int linenum){//行回车规范
    int sum_indexnum=0;//这一行总字符数
    sum_indexnum=editor->text(linenum).size();
    for(int i=0;i<sum_indexnum;i++){//顺便添加头文件规范功能
        editor->setSelection(linenum,i,linenum,i+1);
        if(editor->selectedText()=="#"){
            editor->setSelection(linenum,i+8,linenum,i+9);
            if(editor->selectedText()!=" ")
                this->editor->insertAt(tr(" "),linenum,i+8);
            this->editor->setCursorPosition(linenum+1, 0);
            return;
        }
    }

     QString temp=editor->text(linenum);
     qDebug()<<temp.size();
     //editor->setSelection(linenum,indexnum-1,linenum,indexnum);
     if(temp.at(temp.size()-2)=='{')//字符串末尾是回车，倒数第二应该是{
     {   Line_Indent(linenum,1);
        // if(editor->text(linenum+1).at(editor->text(linenum+1).size()-1)=='}')//这里是为了分辨是在创建{}还是统一检查规范
         this->editor->insert(tr("\n"));
         Line_Indent(linenum+1,-1);
         Line_Indent(linenum,1);
     }
     else
         Line_Indent(linenum,0);

}
//添加括号
void MainWindow::handlePuncComplete(int key){
    //qDebug("handleBraceComplete %d", key);
    qDebug()<<"nnannannann";
    this->editor->getCursorPosition(&cursorLine, &cursorIndex);
    switch (key) {
    case 34://"
        this->editor->insert(tr("\"\""));
        qDebug()<<"nmbhhhhh";
        break;
    case 39://'
        this->editor->insert(tr("''"));
        break;
    case 40://(
        this->editor->insert(tr("()"));
        break;
    case 91://[
        this->editor->insert(tr("[]"));
        break;
    case 123://{
        this->editor->insert(tr("{}"));
        //Formatting_All();
        break;
    case Qt::Key_Enter://两个键都是监听回车
    case Qt::Key_Return:
        this->editor->insert(tr("\n"));
        Enter_Formatting(cursorLine);
        return;
     case 59://;
        this->editor->insert(tr(";"));
        lineFormatting(cursorLine);
        return;

    default:
        break;
    }
    this->editor->setCursorPosition(cursorLine, cursorIndex+1);
}
//函数跳转
void MainWindow::jumpDefination(int line,int index, Qt::KeyboardModifiers  state){
     editor->setCursorPosition(line,index + 2);
    if(QApplication::keyboardModifiers ()  == Qt::ControlModifier){
        QString name = editor->wordAtLineIndex(line,index),text = editor->text(),textLine = editor->text(line);
        QRegExp re;
        if(textLine.count("{") || textLine.count(";")==0 || textLine.indexOf(QRegExp(name+"\\s*\\(")) == -1)
            re.setPattern(name);
        else
            re .setPattern(name + "\\s*\\([^\\)]*\\)\\s*\\{");
        int pos = text.indexOf(re);

        if(pos != -1){
            int l,i;
            editor->lineIndexFromPosition(pos,&l,&i);
            editor->setCursorPosition(l,i);

        }

    }
}
//打开查找行
void MainWindow::onFindLine()
{
    foundLine *f=new foundLine();
    f->setWindowTitle("查找行");
    connect(f,SIGNAL(sendFoundLine(QString)),this,SLOT(onFoundLine(QString)));
    f->show();
}

//查找行
void MainWindow::onFoundLine(QString line)
{
    int l=line.toInt();
    int a=editor->lines();
    bool isDigital=line.contains(QRegExp("^\\d+$"));
    if(l>a)
    {
        QMessageBox::information(this,tr("查找"),tr("超出最大行号"));
    }
    if(isDigital)
    {
        editor->setCursorPosition(l-1,0);

        this->activateWindow();
    }
    else
    {
        QMessageBox::information(this,tr("查找"),tr("输入格式有误！"));
    }
}
void MainWindow::recordPos(){
    if(isAnnotationHide){
        int line,index;
        editor->getCursorPosition(&line,&index);
        int pos = editor->positionFromLineIndex(line,index);
        if(!annotate.empty()) {
          for(int i=0;i<annotate.size();i++){
              if(pos < annotate[i].pos)
                  annotate[i].pos++;
          }
        }
    }
}
//隐藏显示注释
void MainWindow::annotate_hide_and_show() {
    if(!isAnnotationHide){//隐藏
        int line = 0, index = 0, vectorSize = 0;
        QString text = editor->text();
        antt temp;

        QRegExp re_several("/\\*((?!\\*/).)*\\*/"), re_single("//[^\\n\\r]*");
        text = editor->text();
        int pos_several = text.indexOf(re_several), pos_single = text.indexOf(re_single);
        while (pos_several >= 0 || pos_single >= 0) {
            if (pos_several != -1 && (pos_several < pos_single || pos_single == -1)) {
                editor->lineIndexFromPosition(pos_several, &line, &index);
                int lineto, indexto;
                editor->lineIndexFromPosition(pos_several + re_several.matchedLength(), &lineto, &indexto);
                temp.pos = pos_several; temp.an = re_several.cap(0);
                if (lineto != line)
                    indexto += 2;

                annotate.push_back(temp); vectorSize++;
                qDebug() << "pos:" << pos_several;
                qDebug() << "delete annotate:" << annotate[vectorSize - 1].an;

                editor->setSelection(line, index, lineto, indexto);
                editor->removeSelectedText();

                QString textLine = editor->text(line);
                if (textLine.indexOf(QRegExp("^[\\n\\r]$")) != -1) {
                    //只要有用户输入的不在注释范围内的空白字符那么就不会删除这一行。
                    //换行符除非与/**/的结尾连在一起，不然也不会删除
                    annotate[vectorSize - 1].pos;
                    annotate[vectorSize - 1].an.append("\n");
                    editor->setSelection(line, 0, line, 1);
                    editor->removeSelectedText();
                }

                text = editor->text();
                pos_single = text.indexOf(re_single, pos_several);
                pos_several = text.indexOf(re_several, pos_several);
            }

            if (pos_single != -1 && (pos_several > pos_single || pos_several == -1)) {
                qDebug() << re_single.capturedTexts();
                editor->lineIndexFromPosition(pos_single, &line, &index);//获取行列
                //把注释放到vector变量里
                temp.pos = pos_single; temp.an = re_single.cap(0); annotate.push_back(temp); vectorSize++;
                qDebug() << "delete annotate:" << annotate[vectorSize - 1].an;
                qDebug() << "pos:" << pos_single;
                qDebug() << "vector pos:" << annotate[vectorSize - 1].pos;
                editor->setSelection(line, index, line, index + re_single.cap(0).size());
                editor->removeSelectedText();//选定删除（没有找到删除函数，但是剪切一样可以)
                QString textLine = editor->text(line);

                if (textLine.indexOf(QRegExp("^[\\n\\r]$")) != -1) {
                    //只要有用户输入的不在注释范围内的空白字符那么就不会删除这一行。
                    //换行符除非与/**/的结尾连在一起，不然也不会删除
                    annotate[vectorSize - 1].an += "\n";
                    editor->setSelection(line, 0, line, 1);
                    editor->removeSelectedText();
                }

                text = editor->text();//重新获取删除后的文本
                qDebug() << "text:" << text;
                pos_several = text.indexOf(re_several, pos_single);
                pos_single = text.indexOf(re_single, pos_single);//继续查找
            }
        }

        for (int i = 0; i < annotate.size(); i++) {
            qDebug() << "pos:" << annotate[i].pos << "  " << "annotate:" << annotate[i].an;
        }
        isAnnotationHide = true;
        return;
    }


    if (isAnnotationHide) {//显示
        if (!annotate.empty()) {
            int line, index;
            for (int i = annotate.size() - 1; i >= 0; i--) {

                if (i != annotate.size() - 1) qDebug() << "text:" << editor->text(0, annotate[i].pos);
                editor->lineIndexFromPosition(annotate[i].pos, &line, &index);
                editor->insertAt(annotate[i].an, line, index);
            }
        }
        annotate.clear();
        isAnnotationHide = false;
        return;
    }
}



//断电标记

void MainWindow::on_margin_clicked(int margin, int line, Qt::KeyboardModifiers state)
{
    Q_UNUSED(state);

    if (margin == 1) {
        if (editor->markersAtLine(line) != 0) {//当前位置有断点 去掉
            editor->markerDelete(line, 1);
            for(std::vector<int>::iterator it = breakpoints.begin(); it != breakpoints.end(); ){
                if(*it == line + 1)
                    it = breakpoints.erase(it);
                else
                   ++it;
            }
            for(std::vector<int>::iterator it = breakpoints.begin(); it != breakpoints.end(); ){
                qDebug()<<*it;
                it++;
            }
            qDebug()<<"end";
            debugDialog.setBreakpoints(breakpoints);
        }
        else {//当前位置无断点 添加
            editor->markerAdd(line, 1);
            breakpoints.push_back(line + 1);//从1开始
            for(std::vector<int>::iterator it = breakpoints.begin(); it != breakpoints.end(); ){
                qDebug()<<*it;
                it++;
            }
            qDebug()<<"end";
            debugDialog.setBreakpoints(breakpoints);
        }
    }
}
//点击debug信号槽
void MainWindow::debugSlot(){
    if(!compCode())
        return;
    debugDialog.setProgram(filePath);//这里需要当前文件名
    debugDialog.setBreakpoints(breakpoints);
    debugDialog.initProperties();
    debugDialog.show();
    //debugDialog.showProperties(); //debug需要的信息
}

//单步执行标记
void MainWindow::updateLineNumberSlot(int num){
    qDebug()<<"###### mianwindow: "<<num;
    clearMarker();
    editor->markerAdd(num - 1, 2);
}


//清除单步执行标记

void MainWindow::clearMarker(){
    QString tmp = editor->text();
    int n = tmp.size();
    int idx,lne;
    editor->lineIndexFromPosition(n,&lne,&idx);
    for(int i = 0; i < lne + 2; i++)
        editor->markerDelete(i, 2);
}
//格式化
void MainWindow::Formatting_All(){
    int index_from,index_to,line_from,line_to;
    editor->selectAll();
    editor->getSelection(&line_from,&index_from,&line_to,&index_to);
    for(int i=0;i<line_to;i++){
        lineFormatting(i);
    }
    for(int i=0;i<line_to-1;i++){
        if(editor->text(i).at(editor->text(i).size()-2)=='{')//字符串末尾是回车，倒数第二才应该是{
            Line_Indent(i,1);
        else if(editor->text(i+1).at(editor->text(i+1).size()-2)=='}')
            Line_Indent(i,-1);
        else
            Line_Indent(i,0);
    }
}
//收集函数名
void MainWindow::showTreeFunc()
{
    funcList.clear();
    int line,index;
    QString text = editor->text();
    qDebug()<<"QTExt:"<<text;
    QRegExp re("([a-zA-Z_]\\w*)\\s*(?=(\\([^\\)]*\\)?)\\s*\\n*\\r*\\{)");
    int pos=0;
    while((pos=re.indexIn(text,pos))!=-1)
    {
        editor->lineIndexFromPosition(pos, &line, &index);
        pos+=re.matchedLength();

        QString result=re.cap(0);
        qDebug()<<"result:::"<<result;
        result=result.split(" ")[0];
        qDebug()<<"result:::split:::"<<result;
        if(result=="if"||result=="for"||result=="switch"||result=="while"||result=="else")
            continue;
        QString allResult=editor->text(line);
        qDebug()<<"allResult:::"<<allResult;
        result=editor->text(line).split("(")[0];
        qDebug()<<"result:::split:::text:::"<<result;
        func temp;
        temp.an=result;
        temp.line=line;
        temp.index=index;
        funcList<<temp;
    }
    QListIterator<func> iterator(funcList);
    while (iterator.hasNext()) {
        func temp=iterator.next();
        qDebug()<<"funcName: "<<temp.an<<"  funcLine: "<<temp.line<<"  funcIndex: "<<temp.index;
    }
}
//添加函数树
void MainWindow::addFunctionTree()
{
    QTreeWidgetItem *parentNode;
    qDebug()<<filePath;
    for(int i=0;i<pathList->length();i++)
    {
        if(pathList->at(i).path==filePath)
        {
            qDebug()<<pathList->at(i).path;
            parentNode=pathList->at(i).pathNode;
        }
    }
    qDebug()<<"THIS";
    qDebug()<<parentNode;
    for(int i=0;i<funcList.length();i++)
    {
        qDebug()<<"Second";
        QTreeWidgetItem *funcNode=new QTreeWidgetItem(QStringList()<<funcList.at(i).an);
        qDebug()<<"FIRST";
        funcNode->setCheckState(1,Qt::Checked);
        qDebug()<<"Third";
        parentNode->addChild(funcNode);
        qDebug()<<"Third1";
    }
}
//删除之前的函数树
void MainWindow::deleteTree()
{
    if(filePath=="")
    {
        return;
    }
    else
        {
            qDebug()<<"DeleteTree"<<filePath;
            QTreeWidgetItem *parentNode;
            for(int i=0;i<pathList->length();i++)
            {
                if(pathList->at(i).path==filePath)
                {
                    parentNode=pathList->at(i).pathNode;
                }
            }
            //qDebug()<<"PARENTnode count:"<<parentNode->text(0)<<parentNode->childCount();
            int cnt=parentNode->childCount();
            for(int i=cnt-1;i>=0;i--)
            {
                QTreeWidgetItem *tmpNode=parentNode->child(i);
                qDebug()<<"first time:"<<tmpNode->text(0);
                parentNode->removeChild(tmpNode);
                qDebug()<<"second time:"<<tmpNode->text(0);
                delete tmpNode;
            }
        }
}
//debug信号
void MainWindow::on_debug_triggered()//debug
{
    debugSlot();
}
//行号跳转
void MainWindow::jumpToFunc(QString funcName)
{
    if(funcName.indexOf("*")>=0)
    {
        funcName.replace("*","\\*");
    }
    QRegExp re(funcName+"\\s*(?=(\\([^\\)]*\\)?)\\s*\\n*\\r*\\{)");
    int pos=0;
    int line,index;
    QString text = editor->text();
    qDebug()<<"re:::"<<re;
    pos=text.indexOf(re);
    if(pos!=-1)
    {
        editor->lineIndexFromPosition(pos, &line, &index);
        qDebug()<<"line::"<<line;
        qDebug()<<"index::"<<index;
        qDebug()<<"text:::"<<re.cap(0);
        pos+=re.matchedLength();
        editor->activateWindow();
        editor->setCursorPosition(line,index);
    }
}

