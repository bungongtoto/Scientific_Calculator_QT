#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->widget_history->hide();
    ui->Engr->hide();
    ui->Display->setText(calcVal);
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++){
        QString butName = "B"+QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Dot, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Bopen, SIGNAL(released()),this, SLOT(BracketPressed()));
    connect(ui->Bclose, SIGNAL(released()),this, SLOT(BracketPressed()));
    connect(ui->Power, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Backspace, SIGNAL(released()),this, SLOT(BackspacePressed()));
    connect(ui->Clear, SIGNAL(released()),this, SLOT(ClearPressed()));
    connect(ui->Equal, SIGNAL(released()),this, SLOT(EqualPressed()));
    connect(ui->Bsin, SIGNAL(released()),this, SLOT(TrigPressed()));
    connect(ui->Bcos, SIGNAL(released()),this, SLOT(TrigPressed()));
    connect(ui->Btan, SIGNAL(released()),this, SLOT(TrigPressed()));
    connect(ui->Bsinh, SIGNAL(released()),this, SLOT(TrigPressed()));
    connect(ui->Bcosh, SIGNAL(released()),this, SLOT(TrigPressed()));
    connect(ui->Btanh, SIGNAL(released()),this, SLOT(TrigPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton*button = (QPushButton*)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if ((displayVal=="0")||(displayVal== "0.0")){
        ui->Display->setText(butVal);
        infix_expression = butVal;
    }else{
        QString newVal = displayVal +butVal;
        ui->Display->setText(newVal);
        if(have_to_evaluate_trig){
            trigActingOn += butVal;
        }else{
            infix_expression += butVal;
        }
    }
}

void Calculator::MathButtonPressed(){
        QPushButton *button = (QPushButton *)sender();
        QString butVal = button->text();
        QString displayVal = ui->Display->text();
        ui->Display->setText(displayVal + butVal);

        if(have_to_evaluate_trig){
            trigActingOn += butVal;
        }else{
            infix_expression += butVal;
        }
}

QString Calculator::Evaluate_trig_expres(){
    calculate.convert_infix_to_postfix(trigActingOn.toStdString());
    calculate.Evaluate_postfix();
    double value = stod(calculate.get_answer());
    value = value * (3.1415926535897932384626433832795/180);
    cout << value << "\n" << sin(value) << endl;
    double Rvalue = 0.0;

    if (trigfuncTO == "sin ( )"){
        Rvalue = sin(value);
    }else if (trigfuncTO == "cos ( )"){
        Rvalue = cos(value);
    }else if (trigfuncTO == "tan ( )"){
        Rvalue = tan(value);
    }else if (trigfuncTO == "sinh ( )"){
        Rvalue = sinh(value);
    }else if (trigfuncTO == "cosh ( )"){
        Rvalue = cosh(value);
    }else if (trigfuncTO == "tanh ( )"){
        Rvalue = tanh(value);
    }

    cout << Rvalue << endl;
    trigActingOn = "";
    trigfuncTO = "";
    string sRvalue = to_string(Rvalue);
    cout << sRvalue << endl;
    QString toReturn = QString::fromStdString(sRvalue);
    return toReturn;
}

void Calculator::BracketPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    ui->Display->setText(displayVal + butVal);

    if (butVal == ")"){
        if(have_to_evaluate_trig){
            QString temp = Evaluate_trig_expres();
          infix_expression +=  temp;
          have_to_evaluate_trig = false;
        }else{
            infix_expression += butVal;
        }
    }else {
        infix_expression += butVal;
    }
}

void Calculator::TrigPressed(){
    have_to_evaluate_trig = true;
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    trigfuncTO = butVal;
    string toprint = trigfuncTO.toStdString();
    cout << toprint << endl;

    butVal.chop(1);
    QString displayVal = ui->Display->text();
    if ((displayVal=="0")||(displayVal== "0.0")){
        ui->Display->setText(butVal);

    }else{
        QString newVal = displayVal +butVal;
        ui->Display->setText(newVal);
    }
}


void Calculator::BackspacePressed(){
    QString displayVal = ui->Display->text();
    displayVal.chop(1);
    if(displayVal.isEmpty()){
        ui->Display->setText(calcVal);
    }else{
        ui->Display->setText(displayVal);
    }

    if(have_to_evaluate_trig){
        trigActingOn.chop(1);
    }else{
        infix_expression.chop(1);
    }
}

void Calculator::EqualPressed(){
   QString displayVal = ui->Display->text();
   calculate.convert_infix_to_postfix(infix_expression.toStdString());
   calculate.Evaluate_postfix();
   displayVal = displayVal +" = "+ QString::fromStdString(calculate.get_answer());
   db.add_record(displayVal);
   ui->Display->setText(displayVal);
   infix_expression = "0";
   infix_expression = displayVal;
}

void Calculator::ClearPressed(){
    ui->Display->setText(calcVal);
    infix_expression = "0";
    trigActingOn = "";
    trigfuncTO = "";
}

void Calculator::on_Hide_clicked()
{
    ui->Engr->hide();
}


void Calculator::on_EngrMode_clicked()
{
    ui->Engr->show();
}


void Calculator::on_Bhistory_clicked()
{
    ui->widget_history->show();
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(db.mydb);
    qry->prepare("select record_text from record");
    qry->exec();
    modal->setQuery(*qry);
    ui->listView->setModel(modal);
    qDebug()<< modal->rowCount();
}


void Calculator::on_hideHistory_clicked()
{
    ui->widget_history->hide();
}

