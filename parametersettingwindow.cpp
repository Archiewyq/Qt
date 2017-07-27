#include "parametersettingwindow.h"
#include "ui_parametersettingwindow.h"
#include "externdata.h"
#include <QMessageBox>
#include <QDebug>


ParameterSettingWindow::ParameterSettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParameterSettingWindow)
{
    ui->setupUi(this);
    this->setFixedSize(420,725);
    this->setWindowTitle("通道参数设置");
    edit1 = ui->layoutWidget_3->findChildren<QLineEdit*>();             //获取ON/OFF输入框
    edit2 = ui->layoutWidget_2->findChildren<QLineEdit*>();             //获取占空比输入框

    for(QList<QLineEdit*>::size_type i=0; i!=edit1.size(); i++){
        edit1.at(i)->setValidator(new QIntValidator(0,MAXTIME,this));
    }
    for(QList<QLineEdit*>::size_type i=0; i!=edit2.size(); i++){
        edit2.at(i)->setValidator(new QIntValidator(0,100,this));
    }
    ui->lineEdit_duty->setValidator(new QIntValidator(0,100,this));
    ui->lineEdit_freq5->setValidator(new QIntValidator(0,MAXFREQ5,this));
    ui->lineEdit_freq6->setValidator(new QIntValidator(0,MAXFREQ6,this));
    ui->lineEdit0->setEnabled(false);

    connect(ui->spinBox_0,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChange()));
    connect(ui->spinBox_1,SIGNAL(valueChanged(int)),this,SLOT(slotEditShow()));
}

ParameterSettingWindow::~ParameterSettingWindow()
{
    delete ui;
}

void ParameterSettingWindow::slotSpinBoxChange()
{
    if(ui->spinBox_0->value() != 0){
        ui->label_1->setText("第"+QString::number(ui->spinBox_0->value())+"周期");
        ui->lineEdit0->setText(QString::number(everyCycleTime[ui->spinBox_0->value()-1],10));
        everycycledata[this->pFlag-1][ui->spinBox_0->value()-1].onCount = ui->spinBox_1->value();
        for(int8_t i=0; i<everycycledata[this->pFlag-1][ui->spinBox_0->value()-1].onCount; i++){
            everycycledata[this->pFlag-1][ui->spinBox_0->value()-1].onTime[i][0] = edit1.at(2*i)->text().toInt();
            everycycledata[this->pFlag-1][ui->spinBox_0->value()-1].onTime[i][1] = edit1.at(2*i+1)->text().toInt();
            if(this->pFlag == 6){
                pwmDuty[ui->spinBox_0->value()-1][i] = edit2.at(i)->text().toInt();
            }
        }
    }
    for(int8_t i=0; i<edit1.size(); i++)
        edit1.at(i)->setText("36000000");
    for(int8_t i=0; i<edit2.size(); i++)
        edit2.at(i)->setText("36000000");
}
void ParameterSettingWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this,"关闭提示",QString("确认设置？"),QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::No){
    }
    else if(button == QMessageBox::Yes){
        if(this->pFlag == 5){
            turnDuty = ui->lineEdit_duty->text().toInt();
            turnFreq = ui->lineEdit_freq5->text().toInt();
            qDebug()<<"占空比:"<<turnDuty<<"频率:"<<turnFreq;
        }
        else if(this->pFlag == 6){
            pwmFreq = ui->lineEdit_freq6->text().toInt();
            qDebug()<<"频率:"<<pwmFreq;
        }
        this->close();
    }
}

void ParameterSettingWindow::on_pushButton_2_clicked()
{
    this->close();
}

void ParameterSettingWindow::setFlag(int8_t x)
{
    this->pFlag = x;
}

void ParameterSettingWindow::setName()
{
    if(this->pFlag<=4)
        ui->label->setText("通道"+QString::number(this->pFlag));
    else if(this->pFlag == 5)
        ui->label->setText("转向灯通道");
    else if(this->pFlag == 6)
        ui->label->setText("PWM通道");
}

void ParameterSettingWindow::refresh()
{
    ui->lineEdit0->setText(QString::number(everyCycleTime[ui->spinBox_0->value()-1]));
    ui->spinBox_0->setMaximum(allCycle);
    if(this->pFlag<5){
        ui->layoutWidget_2->hide();
        ui->layoutWidget_9->hide();
        ui->layoutWidget_7->hide();
        ui->layoutWidget_4->hide();
    }
    else if(this->pFlag == 5){
        ui->layoutWidget_9->show();
        ui->layoutWidget_4->show();
        ui->layoutWidget_2->hide();
        ui->layoutWidget_7->hide();
    }
    else if(this->pFlag == 6){
        ui->layoutWidget_2->show();
        ui->layoutWidget_7->show();
        ui->layoutWidget_9->hide();
        ui->layoutWidget_4->hide();
    }
    for(int8_t i=0; i<edit1.size(); i++)
        edit1.at(i)->setText("0");
    for(int8_t i=0; i<edit2.size(); i++)
        edit2.at(i)->setText("0");
    ui->spinBox_0->setValue(0);
    ui->spinBox_1->setValue(20);
}

void ParameterSettingWindow::slotEditShow()
{
    for(QList<QLineEdit*>::size_type i=0; i!=edit1.size(); i++){
        if(i<ui->spinBox_1->value()*2)
            edit1.at(i)->setEnabled(true);
        else
            edit1.at(i)->setEnabled(false);
    }
    for(QList<QLineEdit*>::size_type i=0; i!=edit2.size(); i++){
        if(i<ui->spinBox_1->value())
            edit2.at(i)->setEnabled(true);
        else
            edit2.at(i)->setEnabled(false);
    }
}
