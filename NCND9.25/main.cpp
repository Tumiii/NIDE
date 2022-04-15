#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QTime>
#include <QTranslator>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QPixmap pix(":/new/IIIIcon/Icon/loading.gif");
    QSplashScreen splash(pix);
    QLabel splashlabel(&splash);
    QMovie splashgif(":/new/IIIIcon/Icon/loading.gif");
    splashlabel.setMovie(&splashgif);
    splashgif.start();
    splash.show();


    QElapsedTimer t;
    t.start();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int test =qrand()%8;
    while(test<3)
    {
        test =qrand()%8;
    }
    while(t.elapsed()<test*1000)
    {
        QCoreApplication::processEvents();
    }

    QTranslator translator;
           translator.load(QString(":/new/IIIIcon/Icon/qscintilla_cs.qm"));
           a.installTranslator(&translator);
           QTranslator translator2;
           translator2.load(QString(":/new/IIIIcon/Icon/qt_zh_CN.qm"));
           a.installTranslator(&translator2);

    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
