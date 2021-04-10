#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "form_about.h"
#include "formoptions.h"
#include "sleeplength.h"

#include <QtNetwork>

#define defPort 8080

extern Form_About *pmyclFormAbout;
extern FormOptions *pmyclFormOptions;
extern SleepLength *pmyclFormSleepLength;
extern QApplication *pqtclPcms;
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::MSWindowsFixedSizeDialogHint|Qt::WindowMinimizeButtonHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    ui->horizontalLayout->setMargin(2);
    ui->horizontalLayout->setSpacing(2);
    ui->horizontalLayout_2->setMargin(2);
    ui->tabWidget->setCurrentIndex(0);
    ui->verticalLayout->setMargin(2);
    ui->verticalLayout->setSpacing(1);
    ui->verticalLayout_2->setMargin(0);
    ui->verticalLayout_2->setSpacing(0);
    ui->menuBar->setHidden(true);

    qtstrApplicationPath = QApplication::applicationDirPath();
    if (!qtdirProtocol.exists(qtstrApplicationPath + "/Protocols"))
        qtdirProtocol.mkdir(qtstrApplicationPath + "/Protocols");
    qtdirProtocol.setPath(qtstrApplicationPath + "/Protocols");
    QDir::setCurrent(qtstrApplicationPath);

    iOptCount = 1;
    qtmapOptions.insert("AutoCheck", 1);
    iActualModem = 0;
    pstModem = new Modem[10];
    for (int i = 0; i < 10; i++)
    {
        pstModem[i].qtclModemIP = "";
        pstModem[i].iModemStatus = 0;
        pstModem[i].bCh1Status = false;
        pstModem[i].bCh2Status = false;
        pstModem[i].bConnect = false;
        pstModem[i].bTimeout = false;
    }
    pstPanel = new Panel[10];
    pstPanel[0].pqtclPanel = ui->frame_Md_01;           pstPanel[1].pqtclPanel = ui->frame_Md_02;
    pstPanel[2].pqtclPanel = ui->frame_Md_03;           pstPanel[3].pqtclPanel = ui->frame_Md_04;
    pstPanel[4].pqtclPanel = ui->frame_Md_05;           pstPanel[5].pqtclPanel = ui->frame_Md_06;
    pstPanel[6].pqtclPanel = ui->frame_Md_07;           pstPanel[7].pqtclPanel = ui->frame_Md_08;
    pstPanel[8].pqtclPanel = ui->frame_Md_09;           pstPanel[9].pqtclPanel = ui->frame_Md_10;
    pstPanel[0].pqtclLabelImg = ui->label_Im_01;        pstPanel[1].pqtclLabelImg = ui->label_Im_02;
    pstPanel[2].pqtclLabelImg = ui->label_Im_03;        pstPanel[3].pqtclLabelImg = ui->label_Im_04;
    pstPanel[4].pqtclLabelImg = ui->label_Im_05;        pstPanel[5].pqtclLabelImg = ui->label_Im_06;
    pstPanel[6].pqtclLabelImg = ui->label_Im_07;        pstPanel[7].pqtclLabelImg = ui->label_Im_08;
    pstPanel[8].pqtclLabelImg = ui->label_Im_09;        pstPanel[9].pqtclLabelImg = ui->label_Im_10;
    pstPanel[0].pqtclLabelIP = ui->label_IP_01;         pstPanel[1].pqtclLabelIP = ui->label_IP_02;
    pstPanel[2].pqtclLabelIP = ui->label_IP_03;         pstPanel[3].pqtclLabelIP = ui->label_IP_04;
    pstPanel[4].pqtclLabelIP = ui->label_IP_05;         pstPanel[5].pqtclLabelIP = ui->label_IP_06;
    pstPanel[6].pqtclLabelIP = ui->label_IP_07;         pstPanel[7].pqtclLabelIP = ui->label_IP_08;
    pstPanel[8].pqtclLabelIP = ui->label_IP_09;         pstPanel[9].pqtclLabelIP = ui->label_IP_10;
    pstPanel[0].pqtclLabelCh1 = ui->label_C1_01;        pstPanel[1].pqtclLabelCh1 = ui->label_C1_02;
    pstPanel[2].pqtclLabelCh1 = ui->label_C1_03;        pstPanel[3].pqtclLabelCh1 = ui->label_C1_04;
    pstPanel[4].pqtclLabelCh1 = ui->label_C1_05;        pstPanel[5].pqtclLabelCh1 = ui->label_C1_06;
    pstPanel[6].pqtclLabelCh1 = ui->label_C1_07;        pstPanel[7].pqtclLabelCh1 = ui->label_C1_08;
    pstPanel[8].pqtclLabelCh1 = ui->label_C1_09;        pstPanel[9].pqtclLabelCh1 = ui->label_C1_10;
    pstPanel[0].pqtclLabelCh1Im = ui->label_I1_01;      pstPanel[1].pqtclLabelCh1Im = ui->label_I1_02;
    pstPanel[2].pqtclLabelCh1Im = ui->label_I1_03;      pstPanel[3].pqtclLabelCh1Im = ui->label_I1_04;
    pstPanel[4].pqtclLabelCh1Im = ui->label_I1_05;      pstPanel[5].pqtclLabelCh1Im = ui->label_I1_06;
    pstPanel[6].pqtclLabelCh1Im = ui->label_I1_07;      pstPanel[7].pqtclLabelCh1Im = ui->label_I1_08;
    pstPanel[8].pqtclLabelCh1Im = ui->label_I1_09;      pstPanel[9].pqtclLabelCh1Im = ui->label_I1_10;
    pstPanel[0].pqtclLabelCh2 = ui->label_C2_01;        pstPanel[1].pqtclLabelCh2 = ui->label_C2_02;
    pstPanel[2].pqtclLabelCh2 = ui->label_C2_03;        pstPanel[3].pqtclLabelCh2 = ui->label_C2_04;
    pstPanel[4].pqtclLabelCh2 = ui->label_C2_05;        pstPanel[5].pqtclLabelCh2 = ui->label_C2_06;
    pstPanel[6].pqtclLabelCh2 = ui->label_C2_07;        pstPanel[7].pqtclLabelCh2 = ui->label_C2_08;
    pstPanel[8].pqtclLabelCh2 = ui->label_C2_09;        pstPanel[9].pqtclLabelCh2 = ui->label_C2_10;
    pstPanel[0].pqtclLabelCh2Im = ui->label_I2_01;      pstPanel[1].pqtclLabelCh2Im = ui->label_I2_02;
    pstPanel[2].pqtclLabelCh2Im = ui->label_I2_03;      pstPanel[3].pqtclLabelCh2Im = ui->label_I2_04;
    pstPanel[4].pqtclLabelCh2Im = ui->label_I2_05;      pstPanel[5].pqtclLabelCh2Im = ui->label_I2_06;
    pstPanel[6].pqtclLabelCh2Im = ui->label_I2_07;      pstPanel[7].pqtclLabelCh2Im = ui->label_I2_08;
    pstPanel[8].pqtclLabelCh2Im = ui->label_I2_09;      pstPanel[9].pqtclLabelCh2Im = ui->label_I2_10;
    pstPanel[0].pqtclCheckBox = ui->checkBox_01;        pstPanel[1].pqtclCheckBox = ui->checkBox_02;
    pstPanel[2].pqtclCheckBox = ui->checkBox_03;        pstPanel[3].pqtclCheckBox = ui->checkBox_04;
    pstPanel[4].pqtclCheckBox = ui->checkBox_05;        pstPanel[5].pqtclCheckBox = ui->checkBox_06;
    pstPanel[6].pqtclCheckBox = ui->checkBox_07;        pstPanel[7].pqtclCheckBox = ui->checkBox_08;
    pstPanel[8].pqtclCheckBox = ui->checkBox_09;        pstPanel[9].pqtclCheckBox = ui->checkBox_10;

    ptptstrCommand = new QString * [16];
    ptptstrCommand[ 0] = new QString("Включить питание канала 1 (Id 51)");
    ptptstrCommand[ 1] = new QString("Ответ на Id 51. Подтверждение команды включить питание канала 1");
    ptptstrCommand[ 2] = new QString("Отключить питание канала 1 (Id 53)");
    ptptstrCommand[ 3] = new QString("Ответ на Id 53. Подтверждение команды отключить питание канала 1");
    ptptstrCommand[ 4] = new QString("Перевести модем Астерис в режим непрерывного обмена (Id 55)");
    ptptstrCommand[ 5] = new QString("Ответ на Id 55. Подтверждение команды перевести модем Астерис в режим непрерывного обмена");
    ptptstrCommand[ 6] = new QString("Перевести модем Астерис в режим пониженного потребления (Id 57)");
    ptptstrCommand[ 7] = new QString("Ответ на Id 57. Подтверждение команды перевести модем Астерис в режим пониженного потребления");
    ptptstrCommand[ 8] = new QString("Широковещательная команда эхозапрос (Id 59)");
    ptptstrCommand[ 9] = new QString("Ответ на Id 59. Подтверждение широковещательной команды эхозапрос");
    ptptstrCommand[10] = new QString("Программирование длительности нахождения в состоянии сна в режиме пониженного потребления");
    ptptstrCommand[11] = new QString("Ответ на Id 61. Подтверждение команды программирования длительности нахождения в состоянии сна");
    ptptstrCommand[12] = new QString("Включить питание канала 2 (Id 63)");
    ptptstrCommand[13] = new QString("Ответ на Id 63. Подтверждение команды включить питание канала 2");
    ptptstrCommand[14] = new QString("Отключить питание канала 2 (Id 65)");
    ptptstrCommand[15] = new QString("Ответ на Id 65. Подтверждение команды отключить питание канала 2");

    QPalette qtclTemp;
    qtclTemp.setColor(QPalette::Window, 0xA5CAF0);   //QPalette::Active,       //qtclTemp.setBrush(QPalette::Window, QBrush(Qt::green, Qt::DiagCrossPattern));
    pstPanel[0].pqtclPanel->setPalette(qtclTemp);       //pqtclPcms->setStyle(new QWindowsStyle);
    qtclTemp.setColor(QPalette::Window, 0x00F0F0F0);
    for (int i  = 1; i < 10; i++)
        pstPanel[i].pqtclPanel->setPalette(qtclTemp);

    pqtwdLabelClock = new QLabel(this);
    QTime qtclNowTime = QTime::currentTime();
    pqtwdLabelClock->setText(tr("Время: ") + qtclNowTime.toString());

    ptqttmrConnect = new QTimer(this);
    connect(ptqttmrConnect, SIGNAL(timeout()), SLOT(slotConnect()));
    ptqttmrTimeout = new QTimer(this);
    connect(ptqttmrTimeout, SIGNAL(timeout()), SLOT(slotTimeout()));
    pqtclTimerClock = new QTimer(this);
    connect(pqtclTimerClock, SIGNAL(timeout()), SLOT(slotClockCount()));
    pqtclTimerClock->setInterval(1000);
    pqtclTimerClock->start();

    QLabel *wdgLabelVers;
    wdgLabelVers = new QLabel(this);
    wdgLabelVers->setText(tr("Версия: 0.15"));

    statusBar()->addWidget(wdgLabelVers);
    statusBar()->addWidget(pqtwdLabelClock);
    ui->statusBar->setSizeGripEnabled(false);

    QPixmap qtclPixmapOptions;
    qtclPixmapOptions.load(":/images/Images/preferences32_h.bmp");
    QColor qtclTempColor(0xFE, 0x00, 0xFE, 0xFF);
    qtclPixmapOptions.setMask(qtclPixmapOptions.createMaskFromColor(qtclTempColor, Qt::MaskInColor));
    QPixmap qtclPixmapAbout(":/images/Images/watermark_32_h.bmp");
    qtclPixmapAbout.setMask(qtclPixmapAbout.createHeuristicMask());
    ui->mainToolBar->addAction(qtclPixmapOptions, tr("Инициализация панели"), this, SLOT(slotFormOptionsShow()));
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(qtclPixmapAbout, tr("О программе"), this, SLOT(slotFormAboutShow()));
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->mainToolBar->setIconSize(QSize(32, 32));

    QFont qtclTempFont("Courier New");
    ui->textEditLog->setFont(qtclTempFont);
    ui->textEditLog->setFontPointSize(10);
    ui->textEditLog->setFontWeight(50);

    qtclImOut48.load(":/images/Images/stop_48_d.bmp");
    qtclImOut48.setMask(qtclImOut48.createHeuristicMask());
    qtclImOff48.load(":/images/Images/stop_48_h.bmp");
    qtclImOff48.setMask(qtclImOff48.createHeuristicMask());
    qtclImOn48.load(":/images/Images/connect32_h.bmp");
    qtclImOn48.setMask(qtclImOn48.createHeuristicMask());
    QSize qtclSizeMainS(48, 48);
    qtclImOn48 = qtclImOn48.scaled(qtclSizeMainS, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    qtclImOut32.load(":/images/Images/stop_32_d.bmp");
    qtclImOut32.setMask(qtclImOut32.createHeuristicMask());
    qtclImOff32.load(":/images/Images/stop_32.bmp");
    qtclImOff32.setMask(qtclImOff32.createHeuristicMask());
    qtclImOn32.load(":/images/Images/connect32_h.bmp");
    qtclImOn32.setMask(qtclImOn32.createHeuristicMask());
    qtclImOut24.load(":/images/Images/stop24_d.bmp");
    qtclImOut24.setMask(qtclImOut24.createHeuristicMask());
    qtclImOff24.load(":/images/Images/stop24.bmp");
    qtclImOff24.setMask(qtclImOff24.createHeuristicMask());
    qtclImOn24.load(":/images/Images/connect24.bmp");
    qtclImOn24.setMask(qtclImOn24.createHeuristicMask());

    ui->label_Img->resize(48, 48);
    ui->label_Ch1Im->resize(32, 32);
    ui->label_Ch2Im->resize(32, 32);

    for (int i = 0; i < 10; i++)
    {
        pstPanel[i].pqtclLabelImg->resize(32, 32);
        pstPanel[i].pqtclLabelCh1Im->resize(24, 24);
        pstPanel[i].pqtclLabelCh2Im->resize(24, 24);
        SetModemOutSt(i);
        SetCh1OutSt(i);
        SetCh2OutSt(i);
    }

    QDateTime qtclNow = QDateTime::currentDateTime();
    QString qtclFileName = qtdirProtocol.absolutePath();
    qtclFileName += qtclNow.toString("/yyyyMMdd_hhmmss_");
    qtclFileName += QObject::tr("Protocol.txt");
    qtclProtocolFile.setFileName(qtclFileName);     //    qtclProtocolFile.setFileName(QObject::tr("Protocol.txt"));
    if (!qtclProtocolFile.open(QIODevice::ReadWrite|QIODevice::Append))
    {//Ошибка не удалось открыть файл
        QMessageBox *pqtclErrorMessage = new QMessageBox(QMessageBox::Critical,
                                                         QObject::tr("Ошибка"),
                                                         QObject::tr("Не удалось открыть файл протокола. Прекратить выполнение?"),
                                                         QMessageBox::Yes|QMessageBox::No);
        pqtclErrorMessage->setButtonText(QMessageBox::Yes, QObject::tr("Да"));
        pqtclErrorMessage->setButtonText(QMessageBox::No, QObject::tr("Нет"));
        int iRez = pqtclErrorMessage->exec();
        delete pqtclErrorMessage;
        if (iRez == QMessageBox::Yes)
            exit(0);
    }
    qtclProtocolStream.setDevice(&qtclProtocolFile);
    AddProtocolLine("Запущен модуль управления питанием pcms");

    pqtclExchSock = new QUdpSocket(this);
    pqtclExchSock->bind(defPort, QUdpSocket::ShareAddress);
    connect(ui->pushButtonAirOn, SIGNAL(clicked()), this, SLOT(slotModemAirOn()));
    connect(ui->pushButtonAirOff, SIGNAL(clicked()), this, SLOT(slotModemAirOff()));
    connect(ui->pushButtonCh1PowerOn, SIGNAL(clicked()), this, SLOT(slotModemCh1PowerOn()));
    connect(ui->pushButtonCh1PowerOff, SIGNAL(clicked()), this, SLOT(slotModemCh1PowerOff()));
    connect(ui->pushButtonCh2PowerOn, SIGNAL(clicked()), this, SLOT(slotModemCh2PowerOn()));
    connect(ui->pushButtonCh2PowerOff, SIGNAL(clicked()), this, SLOT(slotModemCh2PowerOff()));
    connect(ui->pushButtonSleepLength, SIGNAL(clicked()), this, SLOT(slotSleepLength()));
    connect(ui->pushButtonConnectOff, SIGNAL(clicked()), this, SLOT(slotConnectOff()));
    connect(pqtclExchSock, SIGNAL(readyRead()), this, SLOT(slotReadDatagrams()));
    for (int i = 0; i < 10; i++)
    {
        pstPanel[i].pqtclPanel->installEventFilter(this);
/*        pstPanel[i].pqtclLabelIP->installEventFilter(this);
        pstPanel[i].pqtclLabelImg->installEventFilter(this);
        pstPanel[i].pqtclLabelCh1->installEventFilter(this);
        pstPanel[i].pqtclLabelCh1Im->installEventFilter(this);
        pstPanel[i].pqtclLabelCh2->installEventFilter(this);
        pstPanel[i].pqtclLabelCh2Im->installEventFilter(this);*/
        pstPanel[i].pqtclCheckBox->installEventFilter(this);
    }
    connect(this, SIGNAL(signalMouseClick(int )), SLOT(slotPanelClick(int )));
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    if (pstPanel)
        delete[] pstPanel;
    if (pstModem)
        delete[] pstModem;

    for (int i = 0; i < 16; i++)
        delete ptptstrCommand[i];
    delete ptptstrCommand;
    delete pqtclExchSock;

    if (qtclProtocolFile.isOpen())
    {
        qtclProtocolStream<<QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate)<<tr(" Закрыт модуль управления питанием pcms из состава СОИ")<<"\r\n\r\n";
        qtclProtocolFile.close();
    }
    if (qtclOptionsFile.isOpen())
        qtclOptionsFile.close();

    //delete ui;
}
//------------------------------------------------------------------------------
bool MainWindow::eventFilter(QObject *qtclTarget, QEvent *qtclEvent)
{
    for (int i = 0; i < 10; i++)
        if (qtclTarget == pstPanel[i].pqtclPanel || qtclTarget == pstPanel[i].pqtclLabelIP || qtclTarget == pstPanel[i].pqtclLabelImg ||
                qtclTarget == pstPanel[i].pqtclLabelCh1 || qtclTarget == pstPanel[i].pqtclLabelCh1Im || qtclTarget == pstPanel[i].pqtclLabelCh2 ||
                qtclTarget == pstPanel[i].pqtclLabelCh2Im || qtclTarget == pstPanel[i].pqtclCheckBox)
        {
//            if (qtclTarget == pstPanel[i].pqtclCheckBox)
//                AddProtocolLine(QString("%1").arg(qtclEvent->type()));
            if (qtclEvent->type() == QEvent::MouseButtonPress)
                emit signalMouseClick(i);
        }
    return false;        //AddProtocolLine(QString("%1").arg(qtclEvent->type()));
}
//------------------------------------------------------------------------------
void MainWindow::slotClockCount()
{
    QTime qtclNowTime = QTime::currentTime();
    pqtwdLabelClock->setText(tr("Время: ") + qtclNowTime.toString());
}
//------------------------------------------------------------------------------
void MainWindow::slotFormAboutShow()
{
    pmyclFormAbout->show();
}
//------------------------------------------------------------------------------
void MainWindow::slotFormOptionsShow()
{
    pmyclFormOptions->show();
}
//------------------------------------------------------------------------------
void MainWindow::AddProtocolLine(QString ProtocolLine, bool bDate, bool bFirstEnter, bool bSecondEnter)
{
    QDateTime qtdateNow = QDateTime::currentDateTime();
    if (bDate)
    {
        qtclProtocolStream<<qtdateNow.toString(Qt::SystemLocaleShortDate)<<" ";
        ui->textEditLog->insertPlainText(qtdateNow.toString(Qt::SystemLocaleShortDate) + " ");
    }
    qtclProtocolStream<<tr(ProtocolLine.toAscii());
    ui->textEditLog->insertPlainText(tr(ProtocolLine.toAscii()));
    if (bFirstEnter)
    {
        qtclProtocolStream<<"\r\n";//endl;
        ui->textEditLog->insertPlainText("\r\n");
    }
    if (bSecondEnter)
    {
        qtclProtocolStream<<"\r\n";
        ui->textEditLog->insertPlainText("\r\n");
    }
    qtclProtocolStream.flush();
}
//------------------------------------------------------------------------------
void MainWindow::SetLabelModemStatus(QString qtclArg)
{
    ui->label_ModemIP->setText(qtclArg);
}
//------------------------------------------------------------------------------
void MainWindow::SendCommands(qint8 i8Id, int iSourceModem, bool bButton, int iParametr)
{
    QByteArray qtclData; //qtclData.resize(6);
    if (i8Id == 0x3D)
    {
        qtclData.fill(0, 10);
        qtclData[0] = 0xc0;
        qtclData[4] = i8Id;
        *(int *)((qtclData.data() + 6)) = iParametr;
    }
    else
    {
        qtclData.fill(0, 6);
        qtclData[0] = 0xc0;
        qtclData[4] = i8Id;
    }
    if(bButton&&ui->checkBox_Broadcast->isChecked())
    {
        for(int i = 0; i < 10; i++)
            if((pstPanel[i].pqtclCheckBox->isChecked())&&(pstModem[i].qtclModemIP.size()))
                SendACommand(qtclData, i8Id, i, bButton);
    }
    else
        SendACommand(qtclData, i8Id, iSourceModem, bButton);
}
//------------------------------------------------------------------------------
void MainWindow::SendACommand(QByteArray &qtclData, qint8 i8Id, int iSourceModem, bool bButton)
{
    if (pqtclExchSock->writeDatagram(qtclData, qtclData.size(), QHostAddress(pstModem[iSourceModem].qtclModemIP), defPort) != -1)
    {
        AddProtocolLine("На модем " + pstPanel[iSourceModem].pqtclLabelIP->text() + " Выдана команда: " + *ptptstrCommand[i8Id - 51], true, true, false);
        QPalette qtclTemp;
        if(iActualModem == iSourceModem)
            qtclTemp.setColor(QPalette::Window, 0xA5CAF0);
        else
            qtclTemp.setColor(QPalette::Window, 0x00F0F0F0);
        pstPanel[iSourceModem].pqtclPanel->setPalette(qtclTemp);
        if (i8Id == 0x3D)
            AddProtocolLine(QString("     Байты команды: %1, %2, %3, %4, %5, %6, %7, %8, %9, %10").arg((quint8)qtclData[0], 0, 16).arg((quint8)qtclData[1], 0, 16).arg((quint8)qtclData[2], 0, 16)
              .arg((quint8)qtclData[3], 0, 16).arg((quint8)qtclData[4], 0, 16).arg((quint8)qtclData[5], 0, 16).arg((quint8)qtclData[6], 0, 16).arg((quint8)qtclData[7], 0, 16)
              .arg((quint8)qtclData[8], 0, 16).arg((quint8)qtclData[9], 0, 16), false);
        else
            AddProtocolLine(QString("     Байты команды: %1, %2, %3, %4, %5, %6").arg((quint8)qtclData[0], 0, 16).arg((quint8)qtclData[1], 0, 16).arg((quint8)qtclData[2], 0, 16)
              .arg((quint8)qtclData[3], 0, 16).arg((quint8)qtclData[4], 0, 16).arg((quint8)qtclData[5], 0, 16), false);
        if((i8Id == 0x37)&&bButton)
        {
            pstModem[iSourceModem].bConnect = true;
            if(!ptqttmrConnect->isActive())
                ptqttmrConnect->start(10000);
        }
        pstModem[iSourceModem].iTimeoutCounter = 25;
        pstModem[iSourceModem].bTimeout = true;
        if(!ptqttmrTimeout->isActive())
            ptqttmrTimeout->start(100);
    }
    else
    {
        AddProtocolLine("Ошибка отправки команды на модем " + pstPanel[iSourceModem].pqtclLabelIP->text() + "! Команда: " + *ptptstrCommand[i8Id - 51]);
        QPalette qtclTemp;
        qtclTemp.setColor(QPalette::Window, Qt::darkYellow);
        pstPanel[iSourceModem].pqtclPanel->setPalette(qtclTemp);
        if (iActualModem == iSourceModem)
        {
            QMessageBox *pqtclErrorMessage;
            pqtclErrorMessage = new QMessageBox(QMessageBox::Critical, QObject::tr("Ошибка ethernet"),
                QObject::tr("Ошибка отправки команды на модем!"), QMessageBox::Ok);
            delete pqtclErrorMessage;
        }
    }
}
//------------------------------------------------------------------------------
void MainWindow::slotModemAirOn()
{
    SendCommands(0x37, iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::slotModemCh1PowerOn()
{
    SendCommands(0x33, iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::slotModemCh1PowerOff()
{
    SendCommands(0x35, iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::slotModemCh2PowerOn()
{
    SendCommands(0x3f, iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::slotModemCh2PowerOff()
{
    SendCommands(0x41, iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::slotModemAirOff()
{
    SendCommands(0x39, iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::slotSleepLength()
{
    pmyclFormSleepLength->show();
}
//------------------------------------------------------------------------------
void MainWindow::slotConnectOff()
{
    QPalette qtclTemp;
    if(ui->checkBox_Broadcast->isChecked())
    {
        for(int i = 0; i < 10; i++)
            if(pstPanel[i].pqtclCheckBox->isChecked())
            {
                pstModem[i].bConnect = false;
                if(iActualModem == i)
                    qtclTemp.setColor(QPalette::Window, 0xA5CAF0);
                else
                    qtclTemp.setColor(QPalette::Window, 0x00F0F0F0);
                pstPanel[i].pqtclPanel->setPalette(qtclTemp);
            }
    }
    else
    {
        pstModem[iActualModem].bConnect = false;
        qtclTemp.setColor(QPalette::Window, 0xA5CAF0);
        pstPanel[iActualModem].pqtclPanel->setPalette(qtclTemp);
    }
}
//------------------------------------------------------------------------------
void MainWindow::slotReadDatagrams()
{
    while(pqtclExchSock->hasPendingDatagrams())
    {
        QByteArray qtclDatagram;
        qint64 qiSize = pqtclExchSock->pendingDatagramSize();
        qtclDatagram.resize(qiSize);
        QHostAddress qtclSource;
        quint16 usSenderPort;
        pqtclExchSock->readDatagram(qtclDatagram.data(), qtclDatagram.size(), &qtclSource, &usSenderPort);
        AddProtocolLine("Получен кадр ethernet c IP: " + qtclSource.toString(), true, true, false);
        AddProtocolLine("   Байты:", false, false, false);
        int i;
        for(i = 0; i < qtclDatagram.size(); i++)
            AddProtocolLine(QString(" %1").arg((quint8)qtclDatagram[i], 0, 16), false, false, false);
        for(i = 0; i < 10; i++)
        {
            if (qtclSource.toString() == pstModem[i].qtclModemIP)
            {
                AddProtocolLine("   Получен кадр ethrnet от радиомодема " + pstPanel[i].pqtclLabelIP->text(), false, true, false);
                if ((quint8)qtclDatagram[0] == 0xC0)
                {
                    AddProtocolLine(QString("     Id: %1").arg((quint8)qtclDatagram[4]), false, true, false);
                    AddProtocolLine("     Длина: " + QString::number(qiSize), false);   //AddProtocolLine(QString("     Длина: %1").arg(qiSize), false);
                    pstModem[i].bTimeout = false;
                    QPalette qtclTemp;
                    qtclTemp.setColor(QPalette::Window, 0xC0DCC0);
                    pstPanel[i].pqtclPanel->setPalette(qtclTemp);
                    switch((quint8)qtclDatagram[4])
                    {
                    case 0x34:  //id 52 Подтверждение команды включить питание первого канала
                        pstModem[i].iModemStatus = 2;
                        pstModem[i].bConnect = false;
                        pstModem[i].bCh1Status = true;
                        break;
                    case 0x36:  //id 54 Подтверждение команды отключить питание первого канала
                        pstModem[i].bCh1Status = false;
                        break;
                    case 0x38:  //id 56 Подтверждение команды перевести радиомодем в режим обмена
                        pstModem[i].iModemStatus = 2;
                        pstModem[i].bConnect = false;
                        break;
                    case 0x3A:  //id 58 Подтверждение команды перевести радиомодем в режим поиниженного потребления
                        pstModem[i].iModemStatus = 1;
                        pstModem[i].bCh1Status = false;
                        pstModem[i].bCh2Status = false;
                        break;
                    case 0x40:  //id 64 Подтверждение команды включить питание второго канала
                        pstModem[i].iModemStatus = 2;
                        pstModem[i].bConnect = false;
                        pstModem[i].bCh2Status = true;
                        break;
                    case 0x42:  //id 66 Подтверждение команды отключить питание второго канала
                        pstModem[i].bCh2Status = false;
                        break;
                    }
                    SetPanelStatus(i);
                }
                else
                    AddProtocolLine("      Полученный кадр не является подтверждением команды", false);
            }
        }
    }
}
//------------------------------------------------------------------------------
void MainWindow::SetModemOutSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelImg->setPixmap(qtclImOut32);
    if (iNumber == iActualModem)
        ui->label_Img->setPixmap(qtclImOut48);
}
//------------------------------------------------------------------------------
void MainWindow::SetModemOffSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelImg->setPixmap(qtclImOff32);
    if (iNumber == iActualModem)
        ui->label_Img->setPixmap(qtclImOff48);
}
//------------------------------------------------------------------------------
void MainWindow::SetModemOnSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelImg->setPixmap(qtclImOn32);
    if (iNumber == iActualModem)
        ui->label_Img->setPixmap(qtclImOn48);
}
//------------------------------------------------------------------------------
void MainWindow::SetCh1OutSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelCh1Im->setPixmap(qtclImOut24);
    if (iNumber == iActualModem)
        ui->label_Ch1Im->setPixmap(qtclImOut32);
}
//------------------------------------------------------------------------------
void MainWindow::SetCh1OffSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelCh1Im->setPixmap(qtclImOff24);
    if (iNumber == iActualModem)
        ui->label_Ch1Im->setPixmap(qtclImOff32);
}
//------------------------------------------------------------------------------
void MainWindow::SetCh1OnSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelCh1Im->setPixmap(qtclImOn24);
    if (iNumber == iActualModem)
        ui->label_Ch1Im->setPixmap(qtclImOn32);
}
//------------------------------------------------------------------------------
void MainWindow::SetCh2OutSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelCh2Im->setPixmap(qtclImOut24);
    if (iNumber == iActualModem)
        ui->label_Ch2Im->setPixmap(qtclImOut32);
}
//------------------------------------------------------------------------------
void MainWindow::SetCh2OffSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelCh2Im->setPixmap(qtclImOff24);
    if (iNumber == iActualModem)
        ui->label_Ch2Im->setPixmap(qtclImOff32);
}
//------------------------------------------------------------------------------
void MainWindow::SetCh2OnSt(int iNumber)
{
    pstPanel[iNumber].pqtclLabelCh2Im->setPixmap(qtclImOn24);
    if (iNumber == iActualModem)
        ui->label_Ch2Im->setPixmap(qtclImOn32);
}
//------------------------------------------------------------------------------
void MainWindow::slotPanelClick(int iPanel)
{
    iPrevActualModem = iActualModem;
    iActualModem = iPanel;
    QPalette qtclTemp;
    qtclTemp.setColor(QPalette::Window, 0x00F0F0F0);
    pstPanel[iPrevActualModem].pqtclPanel->setPalette(qtclTemp);
    pstPanel[iPrevActualModem].pqtclPanel->setFrameShadow(QFrame::Raised);
    qtclTemp.setColor(QPalette::Window, 0xA5CAF0);
    pstPanel[iActualModem].pqtclPanel->setPalette(qtclTemp);
    pstPanel[iActualModem].pqtclPanel->setFrameShadow(QFrame::Sunken);
    ui->label_ModemNumber->setText(tr("Модем № ") + QString("%1").arg(iActualModem + 1));
    SetPanelStatus(iActualModem);
}
//------------------------------------------------------------------------------
void MainWindow::SetPanelStatus(int iPanel)
{
    switch(pstModem[iPanel].iModemStatus)
    {
    case 0:
        SetModemOutSt(iPanel);
        SetCh1OutSt(iPanel);
        SetCh2OutSt(iPanel);
        if(iPanel == iActualModem)
        {
            ui->label_ModemIP->setText(tr("IP адрес: Нет"));
            DisableButtons();
        }
        break;
    case 1:
        SetModemOffSt(iPanel);
        pstPanel[iPanel].pqtclCheckBox->setEnabled(true);
        if(pstModem[iPanel].bCh1Status)
            SetCh1OnSt(iPanel);
        else
            SetCh1OffSt(iPanel);
        if(pstModem[iPanel].bCh2Status)
            SetCh2OnSt(iPanel);
        else
            SetCh2OffSt(iPanel);
        if(iPanel == iActualModem)
        {
            ui->label_ModemIP->setText(tr("IP адрес: ") + pstModem[iPanel].qtclModemIP);
            EnableButtons();
        }
        break;
    case 2:
        SetModemOnSt(iPanel);
        pstPanel[iPanel].pqtclCheckBox->setEnabled(true);
        if(pstModem[iPanel].bCh1Status)
            SetCh1OnSt(iPanel);
        else
            SetCh1OffSt(iPanel);
        if(pstModem[iPanel].bCh2Status)
            SetCh2OnSt(iPanel);
        else
            SetCh2OffSt(iPanel);
        if(iPanel == iActualModem)
        {
            ui->label_ModemIP->setText(tr("IP адрес: ") + pstModem[iPanel].qtclModemIP);
            EnableButtons();
        }
        break;
    }
}
//------------------------------------------------------------------------------
void MainWindow::EnableButtons()
{
    ui->pushButtonAirOn->setEnabled(true);
    ui->pushButtonCh1PowerOn->setEnabled(true);
    ui->pushButtonCh1PowerOff->setEnabled(true);
    ui->pushButtonCh2PowerOn->setEnabled(true);
    ui->pushButtonCh2PowerOff->setEnabled(true);
    ui->pushButtonAirOff->setEnabled(true);
    ui->pushButtonSleepLength->setEnabled(true);
    ui->pushButtonConnectOff->setEnabled(true);
}
//------------------------------------------------------------------------------
void MainWindow::DisableButtons()
{
    ui->pushButtonAirOn->setEnabled(false);
    ui->pushButtonCh1PowerOn->setEnabled(false);
    ui->pushButtonCh1PowerOff->setEnabled(false);
    ui->pushButtonCh2PowerOn->setEnabled(false);
    ui->pushButtonCh2PowerOff->setEnabled(false);
    ui->pushButtonAirOff->setEnabled(false);
    ui->pushButtonSleepLength->setEnabled(false);
    ui->pushButtonConnectOff->setEnabled(false);
}
//------------------------------------------------------------------------------
void MainWindow::slotConnect()
{
    bool bJ = true;
    for (int i = 0; i < 10; i++)
        if (pstModem[i].bConnect)
        {
            SendCommands(0x37, i, false);
            bJ = false;
        }
    if (bJ)
        ptqttmrConnect->stop();
}
//------------------------------------------------------------------------------
void MainWindow::slotTimeout()
{
    int i;
    for (i = 0; i < 10; i++)
        if ((!--pstModem[i].iTimeoutCounter)&&(pstModem[i].bTimeout))
        {
            QPalette qtclTemp;
            qtclTemp.setColor(QPalette::Window, Qt::magenta);
            pstPanel[i].pqtclPanel->setPalette(qtclTemp);
            AddProtocolLine("Ошибка доставки команды на модем " + pstPanel[i].pqtclLabelIP->text());
            pstModem[i].bTimeout = false;
        }
    for (i = 0; i < 10; i++)
        if (pstModem[i].bTimeout)
            return;
    ptqttmrTimeout->stop();
}
//------------------------------------------------------------------------------
