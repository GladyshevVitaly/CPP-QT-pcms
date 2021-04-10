#ifndef SLEEPLENGTH_H
#define SLEEPLENGTH_H

#include <QDialog>

namespace Ui {
class SleepLength;
}
//------------------------------------------------------------------------------
class SleepLength : public QDialog
{
    Q_OBJECT
    
public:
    explicit SleepLength(QWidget *parent = 0);
    //~SleepLength();
    
private:
    Ui::SleepLength *ui;

public slots:
    void SendLength();
};
//------------------------------------------------------------------------------
#endif // SLEEPLENGTH_H
