#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QBitmap>
#include <QtGui>

class QUdpSocket;

namespace Ui {
class MainWindow;
}
//------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddProtocolLine(QString ProtocolLine = "", bool bDate = true, bool bFirstEnter = true, bool bSecondEnter = true);
    void SetLabelModemStatus(QString qtclArg);
    void SetModemOutSt(int iNumber);
    void SetModemOffSt(int iNumber);
    void SetModemOnSt(int iNumber);
    void SetCh1OutSt(int iNumber);
    void SetCh1OffSt(int iNumber);
    void SetCh1OnSt(int iNumber);
    void SetCh2OutSt(int iNumber);
    void SetCh2OffSt(int iNumber);
    void SetCh2OnSt(int iNumber);
    virtual bool eventFilter(QObject *qtclTarget, QEvent *qtclEvent);
    void EnableButtons();
    void DisableButtons();
    void SendCommands(qint8 i8Id, int iSourceModem, bool bButton = true, int iParametr = 0);

    Ui::MainWindow *ui;

    QFile qtclProtocolFile;
    QTextStream qtclProtocolStream;
    QFile qtclOptionsFile;
    QDataStream qtclOptionsStream;
    QMap<QString, int> qtmapOptions;
    int iOptCount;
    QTimer *ptqttmrConnect;
    QTimer *ptqttmrTimeout;
    QString **ptptstrCommand;

    struct Panel
    {
        QFrame *pqtclPanel;
        QLabel *pqtclLabelImg;
        QLabel *pqtclLabelIP;
        QLabel *pqtclLabelCh1;
        QLabel *pqtclLabelCh1Im;
        QLabel *pqtclLabelCh2;
        QLabel *pqtclLabelCh2Im;
        QCheckBox *pqtclCheckBox;
    } *pstPanel;
    struct Modem
    {
        QString qtclModemIP;
        int iModemStatus;
        bool bCh1Status;
        bool bCh2Status;
        bool bConnect;
        bool bTimeout;
        int iTimeoutCounter;
    } *pstModem;
    int iActualModem;
    int iPrevActualModem;
    QString qtstrApplicationPath;
    QDir qtdirProtocol;

signals:
    void signalMouseClick(int i);

public slots:
    void slotClockCount();
    void slotFormAboutShow();
    void slotFormOptionsShow();
    void slotModemAirOn();
    void slotModemCh1PowerOn();
    void slotModemCh1PowerOff();
    void slotModemCh2PowerOn();
    void slotModemCh2PowerOff();
    void slotModemAirOff();
    void slotSleepLength();
    void slotConnectOff();
    void slotReadDatagrams();
    void slotPanelClick(int iPanel);
    void slotConnect();
    void slotTimeout();
    
private:
    void SetPanelStatus(int iPanel);
    void SendACommand(QByteArray &qtclData, qint8 i8Id, int iSourceModem, bool bButton = true);
    QLabel *pqtwdLabelClock;
    QTimer *pqtclTimerClock;
    QUdpSocket *pqtclExchSock;
    QPixmap qtclImOut48;
    QPixmap qtclImOff48;
    QPixmap qtclImOn48;
    QPixmap qtclImOut32;
    QPixmap qtclImOff32;
    QPixmap qtclImOn32;
    QPixmap qtclImOut24;
    QPixmap qtclImOff24;
    QPixmap qtclImOn24;
};
//------------------------------------------------------------------------------
#endif // MAINWINDOW_H
