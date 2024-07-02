#include "calculator.h"
#include "./ui_calculator.h"

double calcVal = 0.0;
bool addTriggered = false;
bool mulTriggered = false;
bool divTriggered = false;
bool subTriggered = false;
bool modTriggered = false;
bool decTriggered = false;

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

    ui->Display->setText("");
    QPushButton *numButtons[11];
    for(int i =0;i < 11;i++) {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumPressed()));
    }

    connect(ui->Add,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Sub,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Mul,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Div,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Modulo,SIGNAL(released()),this,SLOT(MathButtonPressed()));

    connect(ui->Result,SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    connect(ui->Clear,SIGNAL(released()),this,SLOT(ClearButtonPressed()));
    connect(ui->Remove,SIGNAL(released()),this,SLOT(RemoveButtonPressed()));
    connect(ui->Decimal,SIGNAL(released()),this,SLOT(DecimalButtonPressed()));
}

calculator::~calculator()
{
    delete ui;
}

void calculator::NumPressed() {
    QPushButton *button = (QPushButton *) sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    QString newVal = displayVal + butVal;
    ui->Display->setText(newVal);
}

void calculator::MathButtonPressed() {
    addTriggered = false;
    mulTriggered = false;
    divTriggered = false;
    subTriggered = false;
    modTriggered = false;
    decTriggered = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *) sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"/",Qt::CaseInsensitive) == 0) {
        divTriggered = true;
    }
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive) == 0) {
        mulTriggered = true;
    }
    else if(QString::compare(butVal,"+",Qt::CaseInsensitive) == 0) {
        addTriggered = true;
    }
    else if(QString::compare(butVal,"-",Qt::CaseInsensitive) == 0) {
        subTriggered = true;
    }
    else if(QString::compare(butVal,"%",Qt::CaseInsensitive) == 0) {
        modTriggered = true;
    }

    ui->Display->setText("");
}

void calculator::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTriggered || subTriggered || mulTriggered || divTriggered || modTriggered) {
        if(addTriggered) {
            solution = calcVal + dblDisplayVal;
        } else if(subTriggered) {
            solution = calcVal - dblDisplayVal;
        } else if(mulTriggered) {
            solution = calcVal * dblDisplayVal;
        } else if(divTriggered) {
            solution = calcVal / dblDisplayVal;
        } else if(modTriggered) {
            solution = (calcVal * dblDisplayVal) / 100;
        }
    }
    calcVal = solution;
    if(modTriggered) {
        ui->Display->setText(QString::number(solution,'2',2));
    } else {
        ui->Display->setText(QString::number(solution));
    }
}

void calculator::ClearButtonPressed() {
    calcVal = 0.0;
    addTriggered = false;
    mulTriggered = false;
    divTriggered = false;
    subTriggered = false;
    modTriggered = false;

    ui->Display->setText(QString::number(calcVal));
}

void calculator::RemoveButtonPressed() {
    QString displayVal = ui->Display->text();
    if(displayVal != "") {
        if((displayVal.last(1)) == ".") {
            decTriggered = false;
        }
        displayVal.chop(1);
        ui->Display->setText(displayVal);
    }
}

void calculator::DecimalButtonPressed() {
    QString displayval = ui->Display->text();
    if(displayval.toDouble() == displayval.toInt() && (displayval!="") ) {
        decTriggered = false;
    }
    if(!decTriggered) {
        if(displayval == "") {
        ui->Display->setText("0.");
        } else {
        ui->Display->setText(displayval+".");
        }
        decTriggered = true;
    }
}
