#ifndef THRESHOLDSETTINGWINDOW_H
#define THRESHOLDSETTINGWINDOW_H

#include <QDialog>
#include "ui_thresholdsettingwindow.h"

namespace Ui {
class ThresholdSettingWindow;
}

class ThresholdSettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdSettingWindow(QWidget *parent = 0);
    void setFlag(int8_t x);
    void setName();
    ~ThresholdSettingWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ThresholdSettingWindow *ui;
    uint8_t tFlag;                      //通道标记
    QList<QLineEdit*> edit;
};

#endif // THRESHOLDSETTINGWINDOW_H
