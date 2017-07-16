#include "dialog_setting.h"
#include "ui_dialog_setting.h"

Dialog_Setting::Dialog_Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Setting)
{
    ui->setupUi(this);
}

Dialog_Setting::~Dialog_Setting()
{
    delete ui;
}

void Dialog_Setting::on_pushButtonUDP_clicked()
{
    int port = ui->lineEdi_UDP->text().toInt();
    emit setPort(port);
}

void Dialog_Setting::on_pushButton_Femur_AP_clicked()
{
    emit loadData_Femur_AP();
}

void Dialog_Setting::on_pushButton_Femur_Lat_clicked()
{
    emit loadData_Femur_Lat();
}

void Dialog_Setting::on_pushButton_Tibia_AP_clicked()
{
    emit loadData_Tibia_AP();
}

void Dialog_Setting::on_pushButton_Tibia_Lat_clicked()
{
    emit loadData_Tibia_Lat();
}

void Dialog_Setting::on_pushButton_InitMarker_clicked()
{
	QList<QString> Name;
	Name.clear();
    Name.push_back (ui->lineEdi_NameFemur->text());
    Name.push_back(ui->lineEdi_NameTibia->text());
    Name.push_back(ui->lineEdi_NameXspot->text());
    Name.push_back( ui->lineEdi_NameTipTool->text());
    Name.push_back( ui->lineEdi_NameRobot->text());
    emit InitMarkerName(Name);
}

void Dialog_Setting::on_radioButton_TypeofNDI_clicked()
{
    ui->lineEdi_UDP->setText("5555");
    emit setTypeofDevice(Type_NDI);
}

void Dialog_Setting::on_radioButton_TypeofTracker_clicked()
{
    ui->lineEdi_UDP->setText("5302");
    emit setTypeofDevice(Type_Tracker);
}
