#include "form_about.h"
#include "ui_form_about.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QApplication *pqtclPcms;
extern MainWindow *pmyclMainwindow;
//------------------------------------------------------------------------------
Form_About::Form_About(QWidget *parent) :
        QDialog(parent, Qt::WindowTitleHint|Qt::WindowSystemMenuHint),
    ui(new Ui::Form_About)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(5);
    ui->verticalLayout->setSpacing(5);

/*    QPixmap imgNIIIS;
    imgNIIIS.load(":/images/Images/niiis_logo.bmp");
    QSize qtclSize(72, 72);
    QPixmap imgNIIISScaled = imgNIIIS.scaled(qtclSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labelImage->setPixmap(imgNIIISScaled);
    ui->labelImage->resize(imgNIIISScaled.size()); */

//pmyclMainwindow->SetLabelModemStatus(QString("%1").arg(pmyclMainwindow->ui->frame_Actual->height()));  //>pstPanel[0].pqtclPanel->height()));

    pmyclMainwindow->qtclOptionsFile.setFileName("PCMSOptions.dat");
//    if (pmyclMainwindow->qtclOptionsFile.exists())
//    {
        if (!pmyclMainwindow->qtclOptionsFile.open(QIODevice::ReadWrite))
        {//������ �� ������� ������� ����
            pmyclMainwindow->AddProtocolLine("������! �� ������� ������� ���� ��������");
            QMessageBox *pqtclErrorMessage = new QMessageBox(QMessageBox::Critical, QObject::tr("������"),
                                                             QObject::tr("�� ������� ������� ���� ��������. ���������� ����������?"), QMessageBox::Yes|QMessageBox::No);
            pqtclErrorMessage->setButtonText(QMessageBox::Yes, QObject::tr("��"));
            pqtclErrorMessage->setButtonText(QMessageBox::No, QObject::tr("���"));
            int iRez = pqtclErrorMessage->exec();
            delete pqtclErrorMessage;
            if (iRez == QMessageBox::Yes)
            {
                if (pmyclMainwindow->qtclProtocolFile.isOpen())
                {
                        pmyclMainwindow->AddProtocolLine("������ ������ ���������� �������� pcms �� �������");
                        pmyclMainwindow->qtclProtocolFile.close();
                }
                exit(0);
            }
        }
        else
        {
            pmyclMainwindow->qtclOptionsStream.setDevice(&pmyclMainwindow->qtclOptionsFile);
            if (pmyclMainwindow->qtclOptionsFile.size())
            {
                pmyclMainwindow->AddProtocolLine("�� ����� PCMSOptions.dat ���������� ��������� ���������:", true, true, false);
                for (int i = 0; i < 10; i++)
                {
                    pmyclMainwindow->qtclOptionsStream>>pmyclMainwindow->pstModem[i].qtclModemIP;
                    if (pmyclMainwindow->pstModem[i].qtclModemIP != "")
                    {
                        pmyclMainwindow->AddProtocolLine(QString("   ������ %1 ����������� IP �����: %2").arg(i+1).arg(pmyclMainwindow->pstModem[i].qtclModemIP), false, true, false);
                        pmyclMainwindow->pstModem[i].iModemStatus = 1;
                        pmyclMainwindow->pstPanel[i].pqtclLabelIP->setText(QString::number(i + 1) + " IP: " + pmyclMainwindow->pstModem[i].qtclModemIP);
                        pmyclMainwindow->pstPanel[i].pqtclCheckBox->setChecked(true);
                        pmyclMainwindow->SetModemOffSt(i);
                        pmyclMainwindow->SetCh1OffSt(i);
                        pmyclMainwindow->SetCh2OffSt(i);
                        pmyclMainwindow->pstPanel[i].pqtclCheckBox->setEnabled(true);
                        if (i == pmyclMainwindow->iActualModem)
                        {
                            pmyclMainwindow->ui->label_ModemIP->setText(tr("IP �����: ") + pmyclMainwindow->pstModem[i].qtclModemIP);
                            pmyclMainwindow->EnableButtons();
                        }
                    }
                }
                pmyclMainwindow->qtclOptionsStream>>pmyclMainwindow->qtmapOptions;
                QMap<QString, int>::Iterator qtiterCount = pmyclMainwindow->qtmapOptions.begin();
                pmyclMainwindow->AddProtocolLine("����������:", false, true, false);
                for (int i = 0; i < pmyclMainwindow->iOptCount; i++)
                    pmyclMainwindow->AddProtocolLine(QString("   %1: %2").arg(qtiterCount.key()).arg(qtiterCount.value()), false, true, false);
                pmyclMainwindow->AddProtocolLine("", false, true, false);
            }
            else
                pmyclMainwindow->AddProtocolLine("���� �������� ����. ���������� ��������� ��������� �� �����");
        }
//    }
//    else
//        pmyclMainwindow->AddProtocolLine("���������� ��������� ��������� �� �����");
}
//------------------------------------------------------------------------------
/*Form_About::~Form_About()
{
    delete ui;
}*/
//------------------------------------------------------------------------------
