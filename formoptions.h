#ifndef FORMOPTIONS_H
#define FORMOPTIONS_H

#include <QDialog>
#include <QtGui>
//------------------------------------------------------------------------------
namespace Ui {
class FormOptions;
}
//------------------------------------------------------------------------------
class FormOptions : public QDialog
{
    Q_OBJECT
//    QMap<QString, QLabel *> qtmapLabelPointers;
public:
    explicit FormOptions(QWidget *parent = 0);
    //~FormOptions();

public slots:
    void OnPressButtonIP();
    void OnPressButtonCleanPanel();
    
private:
    Ui::FormOptions *ui;
    void ExecMessage(QMessageBox *pqtclMessage);
};
//------------------------------------------------------------------------------
#endif // FORMOPTIONS_H
