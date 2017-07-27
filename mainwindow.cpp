#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "externdata.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Valeo");
    this->setFixedSize(510,290);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    QList <QPushButton*> btnList = this->findChildren<QPushButton*>();
    qDebug()<<btnList.size();
    for(QList<QPushButton*>::size_type i=0; i!=btnList.size(); i++)
        connect(btnList.at(i),SIGNAL(clicked()),this,SLOT(slotButtonClick()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotButtonClick()
{
    uint16_t i,len=0;
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if("pushButton" == btn->objectName())
    {
        this->close();
        allsettingw.show();
        allsettingw.exec();
        this->show();
    }
    else if("pushButton_0" == btn->objectName())
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this,"关闭提示",QString("确认关闭？"),QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::No){

        }
        else if(button == QMessageBox::Yes){
            this->close();
        }
    }
    else if("pushButton_1" == btn->objectName())
    {
        QString fileName = QFileDialog::getSaveFileName(this,"save file","/","ini file(*.ini);;text file(*.txt);;All file(*.*)");
        if(!fileName.isNull())
        {
            QFile::remove(fileName);
            QSettings saveFile(fileName, QSettings::IniFormat);
            len = 35+QString::number(allTime).size()+QString::number(allCycle).size();      //每行结束两个空字符
            qDebug()<<"len="<<len;                                                          //每段结束两个空字符
            for(i=0; i<allCycle; i++)
            {
                qDebug()<<QString::number(i+1).size()<<" "<<QString::number(everyCycleTime[i]).size();
                len += (8+QString::number(i+1).size()+QString::number(everyCycleTime[i]).size());
            }
            len += 2;
            qDebug()<<"len="<<len;
            if(2 == QString::number(len).size())
                saveFile.setValue("Len/","00"+QString::number(len));
            else if(3 == QString::number(len).size())
                saveFile.setValue("Len/","0"+QString::number(len));
            else
                saveFile.setValue("Len/",QString::number(len));
            saveFile.setValue("AllSetting/AllTime",QString::number(allTime,10));
            saveFile.setValue("AllSetting/AllCycle",QString::number(allCycle,10));
            for(int8_t i=0; i<allCycle; i++)
            {
                saveFile.setValue("AllSetting/cycle"+QString::number(i+1),QString::number(everyCycleTime[i]));
            }
            for(int8_t j=0; j<allCycle; j++)
            {
                len = 0;
                for(int8_t i=0; i<6; i++)
                {
                    len += (13+QString::number(j+1).size()+2+6+QString::number(everycycledata[i][j].onCount).size()+2);
                    for(int8_t k=0; k<everycycledata[i][j].onCount; k++)
                    {
                        len += (3+QString::number(k+1).size()+QString::number(everycycledata[i][j].onTime[k][0]).size()+2);
                        len += (4+QString::number(k+1).size()+QString::number(everycycledata[i][j].onTime[k][1]).size()+2);
                        if(5 == i)
                            len += (5+QString::number(k+1).size()+QString::number(pwmDuty[j][k]).size()+2);
                    }
                    if(0 == j)
                    {
                        len += (11+QString::number(thresholddata[i].voltageMax).size()+2);
                        len += (11+QString::number(thresholddata[i].voltageMin).size()+2);
                        len += (11+QString::number(thresholddata[i].currentMax).size()+2);
                        len += (11+QString::number(thresholddata[i].currentMin).size()+2);
                        if(4 == i)
                        {
                            len += (10+QString::number(turnDuty).size()+2);
                            len += (10+QString::number(turnFreq).size()+2);
                        }
                        else if(5 == i)
                        {
                            len += (9+QString::number(pwmFreq).size()+2);
                        }
                    }
                    len += 2;
                }
                if(2 == QString::number(len).size()){
                    if(j+1<10)
                        saveFile.setValue("Len000"+QString::number(j+1)+"/1","00"+QString::number(len));
                    else if(j+1<100)
                        saveFile.setValue("Len00"+QString::number(j+1)+"/1","00"+QString::number(len));
                    else if(j+1<1000)
                        saveFile.setValue("Len0"+QString::number(j+1)+"/1","00"+QString::number(len));
                }
                else if(3 == QString::number(len).size()){
                    if(j+1<10)
                        saveFile.setValue("Len000"+QString::number(j+1)+"/1","0"+QString::number(len));
                    else if(j+1<100)
                        saveFile.setValue("Len00"+QString::number(j+1)+"/1","0"+QString::number(len));
                    else if(j+1<1000)
                        saveFile.setValue("Len0"+QString::number(j+1)+"/1","0"+QString::number(len));
                }
                else{
                    if(j+1<10)
                        saveFile.setValue("Len000"+QString::number(j+1)+"/1",QString::number(len));
                    else if(j+1<100)
                        saveFile.setValue("Len00"+QString::number(j+1)+"/1",QString::number(len));
                    else if(j+1<1000)
                        saveFile.setValue("Len0"+QString::number(j+1)+"/1",QString::number(len));
                }
                for(int8_t i=0; i<6; i++)
                {
                    saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/Count",QString::number(everycycledata[i][j].onCount));
                    for(int8_t k=0; k<everycycledata[i][j].onCount; k++)
                    {
                        saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/ON"+QString::number(k+1),QString::number(everycycledata[i][j].onTime[k][0]));
                        saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/OFF"+QString::number(k+1),QString::number(everycycledata[i][j].onTime[k][1]));
                        if(5 == i)
                            saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/Duty"+QString::number(k+1),QString::number(pwmDuty[j][k]));
                    }
                    if(0 == j){
                        saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/voltageMax",QString::number(thresholddata[i].voltageMax));
                        saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/voltageMin",QString::number(thresholddata[i].voltageMin));
                        saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/currentMax",QString::number(thresholddata[i].currentMax));
                        saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/currentMin",QString::number(thresholddata[i].currentMin));
                        if(4 == i){
                            saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/turn-duty",QString::number(turnDuty));
                            saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/turn-freq",QString::number(turnFreq));
                        }
                        else if(5 == i)
                            saveFile.setValue("Cycle"+QString::number(j+1)+"-data"+QString::number(i+1)+"/pwm-freq",QString::number(pwmFreq));
                    }
                }
            }
//            for(int8_t i=0; i<6; i++)
//            {
//                len = 0;
//                for(int8_t j=0; j<allCycle; j++)
//                {
//                    len += (13+QString::number(j+1).size()+2+11+QString::number(everycycledata[i][j].onCount).size()+2);
//                    for(int8_t k=0; k<everycycledata[i][j].onCount; k++){
//                        len += (3+QString::number(k+1).size()+QString::number(everycycledata[i][j].onTime[k][0]).size()+2);
//                        len += (4+QString::number(k+1).size()+QString::number(everycycledata[i][j].onTime[k][1]).size()+2);
//                    }
//                    len += 2;
//                }
//                saveFile.setValue("Len"+QString::number(i+1)+"/1",QString::number(len));
//                for(int8_t j=0; j<allCycle; j++)
//                {
//                    saveFile.setValue("Data"+QString::number(i+1)+"-cycle"+QString::number(j+1)+"/cycleCount",QString::number(everycycledata[i][j].onCount));
//                    for(int8_t k=0; k<everycycledata[i][j].onCount; k++)
//                    {
//                        saveFile.setValue("Data"+QString::number(i+1)+"-cycle"+QString::number(j+1)+"/ON"+QString::number(k+1),QString::number(everycycledata[i][j].onTime[k][0]));
//                        saveFile.setValue("Data"+QString::number(i+1)+"-cycle"+QString::number(j+1)+"/OFF"+QString::number(k+1),QString::number(everycycledata[i][j].onTime[k][1]));
//                        if(i == 5)
//                            saveFile.setValue("Data"+QString::number(i+1)+"-cycle"+QString::number(j+1)+"/Duty"+QString::number(k+1),QString::number(pwmDuty[j][k]));
//                    }
//                }
//                saveFile.setValue("Data"+QString::number(i+1)+"-threshold/voltageMax",QString::number(thresholddata[i].voltageMax));
//                saveFile.setValue("Data"+QString::number(i+1)+"-threshold/voltageMin",QString::number(thresholddata[i].voltageMin));
//                saveFile.setValue("Data"+QString::number(i+1)+"-threshold/currentMax",QString::number(thresholddata[i].currentMax));
//                saveFile.setValue("Data"+QString::number(i+1)+"-threshold/currentMin",QString::number(thresholddata[i].currentMin));
//                if(i == 4){
//                    saveFile.setValue("Data"+QString::number(i+1)+"-turn/duty",QString::number(turnDuty));
//                    saveFile.setValue("Data"+QString::number(i+1)+"-turn/freq",QString::number(turnFreq));
//                }
//                else if(i == 5)
//                    saveFile.setValue("Data"+QString::number(i+1)+"-pwm/freq",QString::number(pwmFreq));
//            }
            QMessageBox::information(this,"提示","保存成功！");
        }
        else
        {
            QMessageBox::information(this,"提示","未保存！");
        }
    }
    else
    {
        for(int8_t i=1; i<=6; i++){
            if("pushButton_"+QString::number(i)+"1" == btn->objectName())
            {
                this->close();
                paraSettingw.setFlag(i);
                paraSettingw.setName();
                paraSettingw.refresh();
                paraSettingw.show();
                paraSettingw.exec();
                this->show();
            }
            else if("pushButton_"+QString::number(i)+"2" == btn->objectName())
            {
                this->close();
                thresholdSettingw.setFlag(i);
                thresholdSettingw.setName();
                thresholdSettingw.show();
                thresholdSettingw.exec();
                this->show();
            }
        }
    }
}
