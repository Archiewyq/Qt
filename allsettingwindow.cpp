#include "allsettingwindow.h"
#include "ui_allsettingwindow.h"
#include "externdata.h"
#include <QDebug>
#include <QMessageBox>

AllSettingWindow::AllSettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSettingWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400,210);
    this->setWindowTitle("总参数设置");
    ui->lineEdit->setValidator(new QIntValidator(0,MAXTIME,this));
    ui->lineEdit_1->setValidator(new QIntValidator(0,MAXTIME,this));
    ui->spinBox_2->setMaximum(0);
    for(int8_t i=0; i<100; i++)
        everyCycleTimeTemp[i] = 0;
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChange()));
    connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBox2Change()));
}

AllSettingWindow::~AllSettingWindow()
{
    delete ui;
}

void AllSettingWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this,"关闭提示",QString("确认设置？"),QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::No){
    }
    else if(button == QMessageBox::Yes){
        allTime = ui->lineEdit->text().toInt();             //保存总时长
        allCycle = ui->spinBox->value();                    //保存总周期数

        qDebug()<<"总时长："<<allTime<<endl;
        qDebug()<<"总周期："<<allCycle<<endl;
        for(int8_t i=0; i<allCycle; i++){                   //保存每个周期时长
            everyCycleTime[i] = everyCycleTimeTemp[i];
//            qDebug()<<"周期"<<i+1<<":"<<everyCycleTime[i];
        }
        everyCycleTime[ui->spinBox_2->value()-1] = ui->lineEdit_1->text().toInt();
        for(int8_t i=0; i<allCycle; i++)
            qDebug()<<"周期"<<i+1<<":"<<everyCycleTime[i];
        this->close();
    }
}

void AllSettingWindow::on_pushButton_2_clicked()
{
    this->close();
}

void AllSettingWindow::slotSpinBoxChange()
{
    if(ui->spinBox->value() != 0)
        ui->spinBox_2->setMaximum(ui->spinBox->value());
}

void AllSettingWindow::slotSpinBox2Change()
{
    ui->label_5->setText("第"+QString::number(ui->spinBox_2->value())+"总周期   ");
    if(ui->spinBox_2->value() != 0){
        everyCycleTimeTemp[ui->spinBox_2->value()-1] = ui->lineEdit_1->text().toInt();
        qDebug()<<ui->spinBox_2->value()<<ui->lineEdit_1->text().toInt();
    }
//    ui->lineEdit_1->setText("0");
}

