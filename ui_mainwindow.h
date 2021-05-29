/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *newFile;
    QAction *openFile;
    QAction *saveFile;
    QAction *saveOther;
    QAction *searchAndReplace;
    QAction *bianyi;
    QAction *Process;
    QAction *byAndProcess;
    QAction *copy;
    QAction *cut;
    QAction *paste;
    QAction *selAll;
    QAction *biteTheDust;
    QAction *debug;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *line;
    QTextBrowser *WelcomeBrowser;
    QTextBrowser *consoleShow;
    QTreeWidget *fileTree;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1013, 726);
        newFile = new QAction(MainWindow);
        newFile->setObjectName(QStringLiteral("newFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/IIIIcon/Icon/newFile .png"), QSize(), QIcon::Normal, QIcon::Off);
        newFile->setIcon(icon);
        openFile = new QAction(MainWindow);
        openFile->setObjectName(QStringLiteral("openFile"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/IIIIcon/Icon/openFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFile->setIcon(icon1);
        saveFile = new QAction(MainWindow);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/IIIIcon/Icon/saveFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveFile->setIcon(icon2);
        saveOther = new QAction(MainWindow);
        saveOther->setObjectName(QStringLiteral("saveOther"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/IIIIcon/Icon/SSave.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveOther->setIcon(icon3);
        searchAndReplace = new QAction(MainWindow);
        searchAndReplace->setObjectName(QStringLiteral("searchAndReplace"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/IIIIcon/Icon/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        searchAndReplace->setIcon(icon4);
        bianyi = new QAction(MainWindow);
        bianyi->setObjectName(QStringLiteral("bianyi"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/IIIIcon/Icon/bianyi.png"), QSize(), QIcon::Normal, QIcon::Off);
        bianyi->setIcon(icon5);
        Process = new QAction(MainWindow);
        Process->setObjectName(QStringLiteral("Process"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/IIIIcon/Icon/Process.png"), QSize(), QIcon::Normal, QIcon::Off);
        Process->setIcon(icon6);
        byAndProcess = new QAction(MainWindow);
        byAndProcess->setObjectName(QStringLiteral("byAndProcess"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/IIIIcon/Icon/bianyiAndProcess.png"), QSize(), QIcon::Normal, QIcon::Off);
        byAndProcess->setIcon(icon7);
        copy = new QAction(MainWindow);
        copy->setObjectName(QStringLiteral("copy"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/IIIIcon/Icon/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        copy->setIcon(icon8);
        cut = new QAction(MainWindow);
        cut->setObjectName(QStringLiteral("cut"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/IIIIcon/Icon/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        cut->setIcon(icon9);
        paste = new QAction(MainWindow);
        paste->setObjectName(QStringLiteral("paste"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/IIIIcon/Icon/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        paste->setIcon(icon10);
        selAll = new QAction(MainWindow);
        selAll->setObjectName(QStringLiteral("selAll"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/new/IIIIcon/Icon/selAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        selAll->setIcon(icon11);
        biteTheDust = new QAction(MainWindow);
        biteTheDust->setObjectName(QStringLiteral("biteTheDust"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/new/IIIIcon/Icon/biteTheDust.png"), QSize(), QIcon::Normal, QIcon::Off);
        biteTheDust->setIcon(icon12);
        debug = new QAction(MainWindow);
        debug->setObjectName(QStringLiteral("debug"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/new/IIIIcon/Icon/debug.png"), QSize(), QIcon::Normal, QIcon::Off);
        debug->setIcon(icon13);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 1, 1);

        WelcomeBrowser = new QTextBrowser(centralWidget);
        WelcomeBrowser->setObjectName(QStringLiteral("WelcomeBrowser"));

        gridLayout->addWidget(WelcomeBrowser, 0, 1, 1, 1);

        consoleShow = new QTextBrowser(centralWidget);
        consoleShow->setObjectName(QStringLiteral("consoleShow"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(consoleShow->sizePolicy().hasHeightForWidth());
        consoleShow->setSizePolicy(sizePolicy);
        consoleShow->setMaximumSize(QSize(16777215, 180));

        gridLayout->addWidget(consoleShow, 2, 1, 1, 1);

        fileTree = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        fileTree->setHeaderItem(__qtreewidgetitem);
        fileTree->setObjectName(QStringLiteral("fileTree"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(200);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fileTree->sizePolicy().hasHeightForWidth());
        fileTree->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(fileTree, 0, 0, 3, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1013, 26));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(18);
        toolBar->setFont(font);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(newFile);
        toolBar->addAction(openFile);
        toolBar->addAction(saveFile);
        toolBar->addAction(saveOther);
        toolBar->addSeparator();
        toolBar->addAction(copy);
        toolBar->addAction(cut);
        toolBar->addAction(paste);
        toolBar->addAction(selAll);
        toolBar->addAction(biteTheDust);
        toolBar->addSeparator();
        toolBar->addAction(searchAndReplace);
        toolBar->addSeparator();
        toolBar->addAction(bianyi);
        toolBar->addAction(Process);
        toolBar->addAction(byAndProcess);
        toolBar->addAction(debug);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "NCNDIDE", Q_NULLPTR));
        newFile->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266", Q_NULLPTR));
        openFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        saveFile->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
        saveOther->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", Q_NULLPTR));
        searchAndReplace->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\346\233\277\346\215\242", Q_NULLPTR));
        bianyi->setText(QApplication::translate("MainWindow", "\347\274\226\350\257\221", Q_NULLPTR));
        Process->setText(QApplication::translate("MainWindow", "\350\277\220\350\241\214", Q_NULLPTR));
        byAndProcess->setText(QApplication::translate("MainWindow", "\347\274\226\350\257\221\350\277\220\350\241\214", Q_NULLPTR));
        copy->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266", Q_NULLPTR));
        cut->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207", Q_NULLPTR));
        paste->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264", Q_NULLPTR));
        selAll->setText(QApplication::translate("MainWindow", "\345\205\250\351\200\211", Q_NULLPTR));
        biteTheDust->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", Q_NULLPTR));
        debug->setText(QApplication::translate("MainWindow", "debug", Q_NULLPTR));
        WelcomeBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt; font-weight:600; color:#000000;\"> \346\254\242\350\277\216</span><span style=\" font-size:36pt; color:#000000;\">\344\275\277\347\224\250\346\255\244IDE</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; color:#000000;\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; color:#000000;\">  </span><span s"
                        "tyle=\" font-size:20pt; font-weight:600; color:#000000;\">\347\202\271\345\207\273</span><span style=\" font-size:20pt; color:#000000;\">\345\267\246\344\270\212\350\247\222\342\200\234</span><span style=\" font-size:20pt; font-weight:600; text-decoration: underline; color:#000000;\">\346\226\260\345\273\272\346\226\207\344\273\266</span><span style=\" font-size:20pt; color:#000000;\">\342\200\235\346\210\226\342\200\234</span><span style=\" font-size:20pt; font-weight:600; text-decoration: underline; color:#000000;\">\346\211\223\345\274\200\346\226\207\344\273\266</span><span style=\" font-size:20pt; color:#000000;\">\342\200\235\345\274\200\345\247\213\347\274\226\347\250\213\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; color:#000000;\">  </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><s"
                        "pan style=\" font-size:20pt; color:#000000;\">  </span><span style=\" font-size:14pt; color:#000000;\">\350\257\245IDE\345\214\205\345\220\253</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\346\226\260\345\273\272</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\346\211\223\345\274\200</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\344\277\235\345\255\230</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\345\217\246\345\255\230\344\270\272</span><span style=\" font-size:14pt; color:#000000;\">\346\226\207\344\273\266\345\212\237\350\203\275\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\345\244\215\345\210\266</span><span style=\""
                        " font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\347\262\230\350\264\264</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\345\211\252\345\210\207</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\345\205\250\351\200\211</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\346\222\244\351\224\200</span><span style=\" font-size:14pt; color:#000000;\">\345\212\237\350\203\275\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\346\237\245\346\211\276\346\233\277\346\215\242</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underl"
                        "ine; color:#000000;\">\350\267\263\350\275\254\350\241\214\345\217\267</span><span style=\" font-size:14pt; color:#000000;\">\345\212\237\350\203\275\357\274\214\344\273\245\345\217\212</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\347\274\226\350\257\221\350\277\220\350\241\214</span><span style=\" font-size:14pt; color:#000000;\">\345\212\237\350\203\275\357\274\233\345\267\246\347\252\227\345\217\243\346\230\276\347\244\272\345\267\245\344\275\234\346\226\207\344\273\266\344\270\255\347\232\204</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\346\226\207\344\273\266\346\240\221\347\212\266\345\233\276</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214\344\270\213\347\252\227\345\217\243\350\277\224\345\233\236\347\274\226\350\257\221\345\231\250\347\232\204</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\350\277\220\350\241\214\347\273\223\346\236\234\346\210\226\351\224\231\350\257\257\346"
                        "\217\220\347\244\272</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214\346\255\244Qscintilla\347\274\226\350\276\221\345\231\250\345\205\267\345\244\207</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\350\241\214\345\217\267\347\224\237\346\210\220</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\350\207\252\345\212\250\346\216\222\347\211\210</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\345\207\275\346\225\260\346\212\230\345\217\240</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoration: underline; color:#000000;\">\345\205\263\351\224\256\350\257\215\351\253\230\344\272\256</span><span style=\" font-size:14pt; color:#000000;\">\357\274\214</span><span style=\" font-size:14pt; text-decoratio"
                        "n: underline; color:#000000;\">\346\263\250\351\207\212\351\232\220\350\227\217</span><span style=\" font-size:14pt; color:#000000;\">\347\255\211\345\212\237\350\203\275\357\274\214\350\257\246\347\273\206\345\206\205\345\256\271\345\217\257\350\256\277\351\227\256\347\224\250\346\210\267\344\275\277\347\224\250\346\226\207\346\241\243\343\200\202</span></p></body></html>", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
