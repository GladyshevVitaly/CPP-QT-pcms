#include "sleeplength.h"
#include "ui_sleeplength.h"
#include "mainwindow.h"

extern MainWindow *pmyclMainwindow;
//------------------------------------------------------------------------------
SleepLength::SleepLength(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint|Qt::WindowSystemMenuHint),
    ui(new Ui::SleepLength)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(5);
    ui->verticalLayout->setSpacing(5);

    connect(ui->pushButtonSend, SIGNAL(clicked()), SLOT(SendLength()));
}
//------------------------------------------------------------------------------
/*SleepLength::~SleepLength()
{
    delete ui;
}*/
//------------------------------------------------------------------------------
void SleepLength::SendLength()
{
    bool bRes;
    int iTemp = ui->lineEdit->text().toInt(&bRes);
    if((bRes)&&(iTemp > 0)&&(iTemp <= 86400))
    {
        pmyclMainwindow->SendCommands(0x3D, pmyclMainwindow->iActualModem, true, iTemp);
        this->close();
    }
    else
    {
        QMessageBox *pqtclMessage = new QMessageBox;
        pqtclMessage->setIcon(QMessageBox::Information);
        pqtclMessage->addButton(QMessageBox::Ok);
        pqtclMessage->setText(tr("«адано недопустимое значение. ¬ведите длительность режима сна в секундах (0 < T <= 86400)"));
        pqtclMessage->exec();
    }
}
//------------------------------------------------------------------------------
