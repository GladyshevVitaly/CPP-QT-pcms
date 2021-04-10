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
        {//Ошибка не удалось открыть файл
            pmyclMainwindow->AddProtocolLine("ОШИБКА! Не удалось открыть файл настроек");
            QMessageBox *pqtclErrorMessage = new QMessageBox(QMessageBox::Critical, QObject::tr("Ошибка"),
                                                             QObject::tr("Не удалось открыть файл настроек. Прекратить выполнение?"), QMessageBox::Yes|QMessageBox::No);
            pqtclErrorMessage->setButtonText(QMessageBox::Yes, QObject::tr("Да"));
            pqtclErrorMessage->setButtonText(QMessageBox::No, QObject::tr("Нет"));
            int iRez = pqtclErrorMessage->exec();
            delete pqtclErrorMessage;
            if (iRez == QMessageBox::Yes)
            {
                if (pmyclMainwindow->qtclProtocolFile.isOpen())
                {
                        pmyclMainwindow->AddProtocolLine("Закрыт модуль управления питанием pcms из состава");
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
                pmyclMainwindow->AddProtocolLine("Из файла PCMSOptions.dat прочитанны следующие параметры:", true, true, false);
                for (int i = 0; i < 10; i++)
                {
                    pmyclMainwindow->qtclOptionsStream>>pmyclMainwindow->pstModem[i].qtclModemIP;
                    if (pmyclMainwindow->pstModem[i].qtclModemIP != "")
                    {
                        pmyclMainwindow->AddProtocolLine(QString("   Панели %1 сопоставлен IP адрес: %2").arg(i+1).arg(pmyclMainwindow->pstModem[i].qtclModemIP), false, true, false);
                        pmyclMainwindow->pstModem[i].iModemStatus = 1;
                        pmyclMainwindow->pstPanel[i].pqtclLabelIP->setText(QString::number(i + 1) + " IP: " + pmyclMainwindow->pstModem[i].qtclModemIP);
                        pmyclMainwindow->pstPanel[i].pqtclCheckBox->setChecked(true);
                        pmyclMainwindow->SetModemOffSt(i);
                        pmyclMainwindow->SetCh1OffSt(i);
                        pmyclMainwindow->SetCh2OffSt(i);
                        pmyclMainwindow->pstPanel[i].pqtclCheckBox->setEnabled(true);
                        if (i == pmyclMainwindow->iActualModem)
                        {
                            pmyclMainwindow->ui->label_ModemIP->setText(tr("IP адрес: ") + pmyclMainwindow->pstModem[i].qtclModemIP);
                            pmyclMainwindow->EnableButtons();
                        }
                    }
                }
                pmyclMainwindow->qtclOptionsStream>>pmyclMainwindow->qtmapOptions;
                QMap<QString, int>::Iterator qtiterCount = pmyclMainwindow->qtmapOptions.begin();
                pmyclMainwindow->AddProtocolLine("Переменные:", false, true, false);
                for (int i = 0; i < pmyclMainwindow->iOptCount; i++)
                    pmyclMainwindow->AddProtocolLine(QString("   %1: %2").arg(qtiterCount.key()).arg(qtiterCount.value()), false, true, false);
                pmyclMainwindow->AddProtocolLine("", false, true, false);
            }
            else
                pmyclMainwindow->AddProtocolLine("Файл настроек пуст. Невозможно прочитать настройки из файла");
        }
//    }
//    else
//        pmyclMainwindow->AddProtocolLine("Невозможно прочитать настройки из файла");
}
//------------------------------------------------------------------------------
/*Form_About::~Form_About()
{
    delete ui;
}*/
//------------------------------------------------------------------------------
