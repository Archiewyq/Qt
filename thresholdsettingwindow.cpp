#include "thresholdsettingwindow.h"
#include "ui_thresholdsettingwindow.h"
#include "externdata.h"
#include <QMessageBox>
#include <QDebug>

ThresholdSettingWindow::ThresholdSettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdSettingWindow)
{
    ui->setupUi(this);
    this->setFixedSize(350,220);
    this->setWindowTitle("阈值设置");
//    edit = ui->layoutWidget->findChildren<QLineEdit*>();            //获取阈值编辑框
//    for(QList<QLineEdit*>::size_type i=0; i!=edit1.size(); i++)
//        edit.at(i)->setValidator(new QIntValidator(0,MAX,this));
    ui->lineEdit->setValidator(new QIntValidator(0,MAXVOLTAGE,this));ui->lineEdit_2->setValidator(new QIntValidator(0,MAXVOLTAGE,this));
    ui->lineEdit_3->setValidator(new QIntValidator(0,MAXCURRENT,this));ui->lineEdit_4->setValidator(new QIntValidator(0,MAXCURRENT,this));
}

ThresholdSettingWindow::~ThresholdSettingWindow()
{
    delete ui;
}

void ThresholdSettingWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this,"关闭提示",QString("确认设置？"),QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::No){
    }
    else if(button == QMessageBox::Yes){
        thresholddata[this->tFlag-1].voltageMax = ui->lineEdit->text().toInt();
        thresholddata[this->tFlag-1].voltageMin = ui->lineEdit_2->text().toInt();
        thresholddata[this->tFlag-1].currentMax = ui->lineEdit_3->text().toInt();
        thresholddata[this->tFlag-1].currentMin = ui->lineEdit_4->text().toInt();
        this->close();
    }
}

void ThresholdSettingWindow::on_pushButton_2_clicked()
{
    this->close();
}

void ThresholdSettingWindow::setFlag(int8_t x)
{
    this->tFlag = x;
}

void ThresholdSettingWindow::setName()
{
    if(this->tFlag <= 4)
        ui->label->setText("通道"+QString::number(this->tFlag));
    else if(this->tFlag == 5)
        ui->label->setText("转向灯通道");
    else if(this->tFlag == 6)
        ui->label->setText("PWM通道");
}
