#define MAINWINDOW_H
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QLabel>
#include <QTextCursor>
#include <QTextCodec>
#include <QDebug>
#include <QString>
#include <QMenu>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
#include<QMessageBox>
#include "replace.h"
#include <QFileDialog>
#include <QProcess>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include<Qsci/qsciscintilla.h>
#include<Qsci/qsciapis.h>
#include<Qsci/qscilexercpp.h>
#include <QFileDialog>
#include <QList>
#include <QFileInfoList>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QMovie>
#include<QPoint>
#include "foundline.h"
#include "debugdialog.h"
#include "debugthread.h"


QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE
typedef struct Node
{
    QString path;
    QTreeWidgetItem *pathNode;
}node;
struct antt{
    int pos;
    QString an;
};
struct func{
    int line;
    int index;
    QString an;
};
namespace Ui {
class MainWindow;
}
class MyKeyPressEater : public QObject
{
    Q_OBJECT

signals:
    void keyPressSiganl_puncComplete(int);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QFileInfoList allFile(QTreeWidgetItem *,QString);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QsciScintilla *editor;
    QLabel *label;          //状态栏中设置的光标行列
    QString filePath;       //文件路径名
    QProcess *powerShell;
    QString stableParent;   //定义虚拟固定文件夹
    QList<Node> *pathList;
    bool isChanged;
    bool isComp;
    MyKeyPressEater *keyPressEater;
    //文件菜单
    QMenu *fileMenu;        //文件菜单
    QAction *newFile;       //新建文件菜单项
    QAction *openFile;      //打开文件菜单项
    QAction *saveFile;      //保存文件菜单项
    QAction *saveAsFile;    //另存文件菜单项

    //编辑菜单
    QMenu *editMenu;        //编辑菜单
    QAction *copyEdit;      //编辑菜单的复制按钮
    QAction *pasteEdit;     //粘贴按钮
    QAction *cutEdit;       //剪切按钮
    QAction *allselectEdit; //全选按钮
    QAction *revocationEdit;//撤销按钮
    QAction *replaceEdit;   //替换按钮
    QAction *findline;      //查找行
    QAction *annotateHideAct;
    QAction *allFormattingAct;
    QMenu *helpMenu;   //帮助菜单

    QList<func> funcList;
    bool isAnnotationHide;

    std::vector<antt> annotate;
    //光标位置
    int cursorLine;
    int cursorIndex;
    void Line_Indent(int linenum,int flag);
    void lineFormatting(int linenumber);
    //编译菜单
    QMenu *compMenu;   //编译菜单
    QAction *compComp;   //编译按钮
    QAction *runComp;   //运行按钮
    QAction *debugAct;   //debug按钮

    void precomp();

    void showTree();
    int findPath(QString);
    void addTreeNode(QTreeWidgetItem *,QString);
    void messageBoxOpen();
    void jumpToFunc(QString);

    //debug


    std::vector<int> breakpoints;//断点集合
    DebugDialog debugDialog;//debug窗口
    void createEditor();
    void createMenu();
    void setconnect();
    void breakpoint();
signals:
    void sendEndFound(int);

private slots:
    void showCursorPosition(int,int);  //光标位置
    void onChanged();
    void openReplace();         //打开替换界面
    bool compCode();            //编译代码
    //void onReadOutput();
    //void onReadError();
    void runCode();             //运行代码
    void onOpen();
    void onSave();
    void onSaveAs();
    void onNew();
    void onCopyEdit();
    void onPasteEdit();
    void onCutEdit();
    void onAllSelect();
    void onRevocationEdit();
    void onFoundEdit(QString,int,int);
    void onReplaceEdit(QString,QString,int,int);
    void onReplaceAll(QString,QString,int,int);
    void openFilter(QTreeWidgetItem*,int);




    void on_newFile_triggered();
    void on_openFile_triggered();
    void on_saveFile_triggered();
    void on_saveOther_triggered();
    void on_searchAndReplace_triggered();
    void on_bianyi_triggered();
    void on_Process_triggered();
    void on_byAndProcess_triggered();
    void on_copy_triggered();
    void on_cut_triggered();
    void on_paste_triggered();
    void on_selAll_triggered();
    void on_biteTheDust_triggered();
    void handlePuncComplete(int);
    void jumpDefination(int line,int index, Qt::KeyboardModifiers state);
    void onFindLine();
    void onFoundLine(QString);
    void annotate_hide_and_show();
    void recordPos();
    void Enter_Formatting(int linenum);

    void debugSlot();
    void on_margin_clicked(int margin, int line, Qt::KeyboardModifiers state);
    void on_debug_triggered();

    void documentWasModified();
    void updateLineNumberSlot(int num);
    void clearMarker();
    void Formatting_All();
    void showTreeFunc();
    void addFunctionTree();
    void deleteTree();

};
