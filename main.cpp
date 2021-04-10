#include "mainwindow.h"
#include "form_about.h"
#include "formoptions.h"
#include "sleeplength.h"

#include <QApplication>
#include <QTextCodec>
#include <QtGui>

MainWindow *pmyclMainwindow;
Form_About *pmyclFormAbout;
FormOptions *pmyclFormOptions;
SleepLength *pmyclFormSleepLength;
QApplication *pqtclPcms;
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication qtclPcms(argc, argv);
    pqtclPcms = &qtclPcms;

    QFont qtclFont;
    qtclFont.fromString("Arial");
    qtclFont.setPointSize(11);
    qtclFont.setBold(true);
    qtclPcms.setFont(qtclFont);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
//    QPixmap qtclFactory;    //qtclSoir.setWindowIcon(QIcon(":/ico/Images/FACTORY.ICO"));
//    qtclFactory.load(":/images/Images/FACTORY.bmp");
//    qtclFactory.setMask(qtclFactory.createHeuristicMask());
//    qtclPcms.setWindowIcon(qtclFactory);
    qtclPcms.setWindowIcon(QPixmap(":/images/Images/FACTORY.bmp"));

    MainWindow myclMainwindow;
    pmyclMainwindow = &myclMainwindow;
    myclMainwindow.move((QApplication::desktop()->width() - myclMainwindow.width()) / 2,  (QApplication::desktop()->height() - myclMainwindow.height()) / 2);
    myclMainwindow.show();
    
    FormOptions myclFormOptions(&myclMainwindow);
    pmyclFormOptions = &myclFormOptions;

    SleepLength myclFormSleepLength(&myclMainwindow);
    pmyclFormSleepLength = &myclFormSleepLength;

    Form_About myclFormAbout(&myclMainwindow);    //если унаследовано, то центрируется относительно предка
    pmyclFormAbout = &myclFormAbout;

    return qtclPcms.exec();
}
//------------------------------------------------------------------------------
