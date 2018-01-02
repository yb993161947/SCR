#ifndef DIALOG_SETTING_H
#define DIALOG_SETTING_H

#include <QDialog>
#include "ui_dialog_setting.h"
#include "thread_get_ndi_marker.h"
namespace Ui {
class Dialog_Setting;
}

class Dialog_Setting : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog_Setting(QWidget *parent = 0);
    ~Dialog_Setting();

    void ReadSettingFile();

    void on_pushButton_Femur_AP_clicked();

    void on_pushButton_Femur_Lat_clicked();

    void on_pushButton_Tibia_AP_clicked();

    void on_pushButton_Tibia_Lat_clicked();
private slots:
    void on_pushButtonUDP_clicked();



    void on_pushButton_InitMarker_clicked();

    void on_radioButton_TypeofNDI_clicked();

    void on_radioButton_TypeofTracker_clicked();

public:
    Ui::Dialog_Setting *ui;
signals:
    void setPort(int);
    void loadData_Femur_AP();
    void loadData_Femur_Lat();
    void loadData_Tibia_AP();
    void loadData_Tibia_Lat();
    void InitMarkerName(QList<QString> Name);
    void setTypeofDevice(TypeofDevice type);
};

#endif // DIALOG_SETTING_H
