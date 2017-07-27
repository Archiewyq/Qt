#include "mainwindow.h"
#include <QApplication>
#include "externdata.h"

int32_t allTime;
int8_t  allCycle;
int32_t everyCycleTime[100];
struct  everyCycleData everycycledata[6][100];
int8_t  turnDuty;
int16_t turnFreq;
int8_t  pwmDuty[100][20];
int16_t pwmFreq;
struct  thresholdData thresholddata[6];

void Init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Init();
    w.show();

    return a.exec();
}

void Init(){
    allTime = 0;
    allCycle = 0;
    for(int8_t i=0; i<100; i++)
        everyCycleTime[i] = 0;
    for(int8_t i=0; i<6; i++)
        for(int8_t j=0; j<100; j++){
            everycycledata[i][j].onCount = 0;
            for(int8_t m=0; m<20; m++){
                everycycledata[i][j].onTime[m][0] = 0;
                everycycledata[i][j].onTime[m][1] = 0;
            }
        }
    turnDuty = 0;
    turnFreq = 0;
    for(int8_t i=0; i<100; i++)
        for(int8_t j=0; j<20; j++)
            pwmDuty[i][j] = 0;
    pwmFreq = 0;
    for(int8_t i=0; i<6;i++)
        thresholddata[i] = {
            0,
            0,
            0,
            0
        };
}
