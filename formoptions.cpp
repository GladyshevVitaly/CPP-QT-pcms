#include "formoptions.h"
#include "ui_formoptions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

extern MainWindow *pmyclMainwindow;
//------------------------------------------------------------------------------
FormOptions::FormOptions(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint|Qt::WindowSystemMenuHint),
    ui(new Ui::FormOptions)
{
    ui->setupUi(this);
    this->setFixedSize(382, 160);

    ui->lineEdit->setText(pmyclMainwindow->pstModem[pmyclMainwindow->iActualModem].qtclModemIP);
    connect(ui->pushButton_Modem, SIGNAL(pressed()), SLOT(OnPressButtonIP()));
    connect(ui->pushButton_CleanPanel, SIGNAL(pressed()), SLOT(OnPressButtonCleanPanel()));
}
//------------------------------------------------------------------------------
/*FormOptions::~FormOptions()
{
    delete ui;
}*/
//------------------------------------------------------------------------------
void FormOptions::OnPressButtonIP()
{
    QMessageBox *pqtclMessage = new QMessageBox(this);
    pqtclMessage->setIcon(QMessageBox::Information);
    pqtclMessage->addButton(QMessageBox::Ok);
//Проверка на соответствие формату IP адреса
    pqtclMessage->setWindowTitle(tr("Ошибка"));
    if (ui->lineEdit->text().length() > 15) {
        pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Превышена длина"));
        ExecMessage(pqtclMessage);
        return;
    }
    if (!ui->lineEdit->text().at(0).isDigit()) {
        pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Начинается не с цифры"));
        ExecMessage(pqtclMessage);
        return;
    }
    int iDCnt = 0, iPCnt = 0, iIP[4] = {0, 0, 0, 0}, iIPIndex = 0;
    QString qtclTempIp;
    for (int iVar = 0; iVar < ui->lineEdit->text().length(); ++iVar) {
        if ((!(ui->lineEdit->text().at(iVar).isDigit()))&&(ui->lineEdit->text().at(iVar) != '.')) {
            pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Недопустимый символ"));
            ExecMessage(pqtclMessage);
            return;
        }
        if (ui->lineEdit->text().at(iVar).isDigit()) {
            iDCnt++;
            if (iDCnt > 3) {
                pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Слишком длинное числовое поле"));
                ExecMessage(pqtclMessage);
                return;
            }
        }
        if (ui->lineEdit->text().at(iVar) == '.') {
            iPCnt++;
            if (iPCnt > 3) {
                pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Слишком много разделителей"));
                ExecMessage(pqtclMessage);
                return;
            }
            if (!iDCnt) {
                pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Два подряд идущих разделителя"));
                ExecMessage(pqtclMessage);
                return;
            }
            qtclTempIp = ui->lineEdit->text();
            qtclTempIp.remove(0, (iVar - iDCnt));
            qtclTempIp.chop(qtclTempIp.size() - iDCnt);
            bool bRez;
            iIP[iIPIndex] = qtclTempIp.toInt(&bRez, 10);
            if (iIP[iIPIndex] > 255) {
                pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Значение числового поля больше 255"));
                ExecMessage(pqtclMessage);
                return;
            }
            iIPIndex++;
            iDCnt = 0;
        }
    }
    if (iPCnt < 3) {
        pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Недостаточно числовых полей"));
        ExecMessage(pqtclMessage);
        return;
    }
    if (!iDCnt) {
        pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Не оканчивается числовым полем"));
        ExecMessage(pqtclMessage);
        return;
    }
    qtclTempIp = ui->lineEdit->text();
    qtclTempIp.remove(0, (qtclTempIp.size() - iDCnt));
    bool bRez;
    iIP[iIPIndex] = qtclTempIp.toInt(&bRez, 10);
    if (iIP[iIPIndex] > 255) {
        pqtclMessage->setText(tr("Заданный параметр не является IP адресом. Значение числового поля больше 255"));
        ExecMessage(pqtclMessage);
        return;
    }
    for (int i = 0; i < 10; i++)    //Проверка, используется ли данный IP адрес
        if ((ui->lineEdit->text() == pmyclMainwindow->pstModem[i].qtclModemIP)&&(i != pmyclMainwindow->iActualModem)){
            pqtclMessage->setText(tr("Заданный IP адрес уже используется"));
            ExecMessage(pqtclMessage);
            return;
        }
    pmyclMainwindow->pstModem[pmyclMainwindow->iActualModem].qtclModemIP = ui->lineEdit->text();
//Реакция интерфейса и сохранение в файл
    pmyclMainwindow->pstModem[pmyclMainwindow->iActualModem].iModemStatus = 1;
    pmyclMainwindow->pstPanel[pmyclMainwindow->iActualModem].pqtclLabelIP->setText(QString::number(pmyclMainwindow->iActualModem + 1) + " IP: " + ui->lineEdit->text());
    pmyclMainwindow->ui->label_ModemIP->setText(tr("IP адрес: ") + ui->lineEdit->text());
    pmyclMainwindow->SetModemOffSt(pmyclMainwindow->iActualModem);
    pmyclMainwindow->SetCh1OffSt(pmyclMainwindow->iActualModem);
    pmyclMainwindow->SetCh2OffSt(pmyclMainwindow->iActualModem);
    pmyclMainwindow->EnableButtons();
    pmyclMainwindow->pstPanel[pmyclMainwindow->iActualModem].pqtclCheckBox->setEnabled(true);
    pmyclMainwindow->pstPanel[pmyclMainwindow->iActualModem].pqtclCheckBox->setChecked(true);
    pmyclMainwindow->qtclOptionsFile.seek(0);
    for (int i = 0; i < 10; i++)
        pmyclMainwindow->qtclOptionsStream<<pmyclMainwindow->pstModem[i].qtclModemIP;
    pmyclMainwindow->qtclOptionsStream<<pmyclMainwindow->qtmapOptions;
    pmyclMainwindow->qtclOptionsFile.flush();
    pmyclMainwindow->AddProtocolLine("Панели № " + QString::number(pmyclMainwindow->iActualModem + 1) + " задан IP адрес модема: " + pmyclMainwindow->pstModem[pmyclMainwindow->iActualModem].qtclModemIP);
    pqtclMessage->setWindowTitle(tr("Задание адреса"));
    pqtclMessage->setText(tr("IP адрес задан успешно"));
    this->hide();
    ExecMessage(pqtclMessage);
//    QString qtclButtonName = sender()->objectName();
//    qtclButtonName = qtclButtonName.remove(0, 11);
//QMap<QString, QString>::Iterator qtiterD = qtmapIP.begin();
//for (; qtiterD != qtmapIP.end(); ++qtiterD)  //Проверка, используется ли адрес на других каналах
//    pmyclFormMain->AddProtocolLine("key: " + qtiterD.key() + " value: " + qtiterD.value());
}
//------------------------------------------------------------------------------
void FormOptions::OnPressButtonCleanPanel()
{//Реакция интерфейса и сохранение в файл
    pmyclMainwindow->pstModem[pmyclMainwindow->iActualModem].qtclModemIP = "";
    pmyclMainwindow->pstModem[pmyclMainwindow->iActualModem].iModemStatus = 0;
    pmyclMainwindow->pstPanel[pmyclMainwindow->iActualModem].pqtclLabelIP->setText(QString::number(pmyclMainwindow->iActualModem + 1) + tr(" IP: Нет"));
    pmyclMainwindow->ui->label_ModemIP->setText(tr("IP адрес: Нет"));
    pmyclMainwindow->SetModemOutSt(pmyclMainwindow->iActualModem);
    pmyclMainwindow->SetCh1OutSt(pmyclMainwindow->iActualModem);
    pmyclMainwindow->SetCh2OutSt(pmyclMainwindow->iActualModem);
    pmyclMainwindow->DisableButtons();
    pmyclMainwindow->pstPanel[pmyclMainwindow->iActualModem].pqtclCheckBox->setChecked(false);
    pmyclMainwindow->qtclOptionsFile.seek(0);
    for (int i = 0; i < 10; i++)
        pmyclMainwindow->qtclOptionsStream<<pmyclMainwindow->pstModem[i].qtclModemIP;
    pmyclMainwindow->qtclOptionsStream<<pmyclMainwindow->qtmapOptions;
    pmyclMainwindow->qtclOptionsFile.flush();
    pmyclMainwindow->AddProtocolLine("Панель № " + QString::number(pmyclMainwindow->iActualModem + 1) + " очищена");
    this->hide();
}
//------------------------------------------------------------------------------
void FormOptions::ExecMessage(QMessageBox *pqtclMessage)
{
    pqtclMessage->exec();
    //delete pqtclMessage;
}
//------------------------------------------------------------------------------
