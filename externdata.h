#ifndef EXTERNDATA_H
#define EXTERNDATA_H

#define MAXTIME 36000000
#define MAXFREQ5 10000
#define MAXFREQ6 1000
#define MAXVOLTAGE 15
#define MAXCURRENT 5000

extern int32_t  allTime;
extern int8_t   allCycle;
extern int32_t  everyCycleTime[100];
struct everyCycleData{
    int8_t  onCount;
    int32_t onTime[20][2];
};
extern everyCycleData everycycledata[6][100];
extern int8_t   turnDuty;
extern int16_t  turnFreq;
extern int8_t   pwmDuty[100][20];
extern int16_t  pwmFreq;
struct thresholdData{
    int8_t  voltageMax;
    int8_t  voltageMin;
    int16_t currentMax;
    int16_t currentMin;
};
extern thresholdData thresholddata[6];

#endif // EXTERNDATA_H
