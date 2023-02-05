#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "calculate.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

/**
 * @brief calulator 
 * 
 */
class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    QString calcVal = "0";
    QString infix_expression = "0";
    database db;

    QString trigfuncTO = "";
    QString trigActingOn = "";
    bool waiting_for_closeB = false;
    bool have_to_evaluate_trig = false;
    Calculate calculate;
    QString Evaluate_trig_expres();

private slots:
    void NumPressed();
    void BracketPressed();
    void TrigPressed();
    void MathButtonPressed();
    void BackspacePressed();
    void ClearPressed();
    void EqualPressed();
    void on_Hide_clicked();
    void on_EngrMode_clicked();
    void on_Bhistory_clicked();
    void on_hideHistory_clicked();
};
#endif // CALCULATOR_H
