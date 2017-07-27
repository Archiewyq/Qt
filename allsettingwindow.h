#ifndef ALLSETTINGWINDOW_H
#define ALLSETTINGWINDOW_H

#include <QDialog>

namespace Ui {
class AllSettingWindow;
}

class AllSettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AllSettingWindow(QWidget *parent = 0);
    ~AllSettingWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void slotSpinBoxChange();
    void slotSpinBox2Change();

private:
    Ui::AllSettingWindow *ui;
    int32_t everyCycleTimeTemp[100];
};

#endif // ALLSETTINGWINDOW_H
