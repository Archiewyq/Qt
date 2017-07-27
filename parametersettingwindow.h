#ifndef PARAMETERSETTINGWINDOW_H
#define PARAMETERSETTINGWINDOW_H

#include <QDialog>
#include "ui_parametersettingwindow.h"

namespace Ui {
class ParameterSettingWindow;
}

class ParameterSettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterSettingWindow(QWidget *parent = 0);
    void setFlag(int8_t x);
    void setName();
    void refresh();
    ~ParameterSettingWindow();

private slots:
    void slotSpinBoxChange();

    void slotEditShow();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ParameterSettingWindow *ui;
    int8_t pFlag;                               //通道标记
    QList<QLineEdit*> edit1;
    QList<QLineEdit*> edit2;
};

#endif // PARAMETERSETTINGWINDOW_H
