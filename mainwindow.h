#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parametersettingwindow.h"
#include "thresholdsettingwindow.h"
#include "allsettingwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotButtonClick();

private:
    Ui::MainWindow *ui;
    AllSettingWindow allsettingw;
    ParameterSettingWindow paraSettingw;
    ThresholdSettingWindow  thresholdSettingw;

};

#endif // MAINWINDOW_H
