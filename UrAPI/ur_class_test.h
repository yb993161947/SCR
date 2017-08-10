#ifndef UR_CLASS_TEST_H
#define UR_CLASS_TEST_H

#define PI 3.1415926

#include "ui_ur_class_test.h"
#include "UR_interface.h"
//#include "getrobotinfothread.h"
#include "mythread.h"
#include <QDebug>
#include "QSettings"
class UR_interface;
//class GetRobotInfoThread;
class MyThread;
class UR_class_test : public QWidget
{
    Q_OBJECT

public:
    UR_class_test(QWidget *parent = 0);
	~UR_class_test();
    UR_interface *pUR5;
    MyThread *thread;
    //GetRobotInfoThread *pGetRobotInfoThread;
    bool GetRobotInfoThreadFlag;
    double TcpPos[6] ;
    double Jointangle[6];
    bool TechFlag;
    void Connect_UR();

private slots:


    void getUR_PosData();

	void UR_Home();

    void on_Base_Pose_X_Increase_pressed();

    void on_Base_Pose_Y_Increase_pressed();

    void on_Base_Pose_X_Decrease_pressed();

    void on_Base_Pose_X_Increase_released();

    void on_Base_Pose_X_Decrease_released();

    void on_Base_Pose_Y_Increase_released();

    void on_Base_Pose_Y_Decrease_pressed();

    void on_Base_Pose_Y_Decrease_released();

    void on_Base_Pose_Z_Increase_pressed();

    void on_Base_Pose_Z_Increase_released();

    void on_Base_Pose_Z_Decrease_pressed();

    void on_Base_Pose_Z_Decrease_released();


    void on_Base_Increase_pressed();

    void on_Base_Increase_released();

    void on_Base_Decrease_pressed();

    void on_Base_Decrease_released();

    void on_Shoulder_Increase_pressed();

    void on_Shoulder_Increase_released();

    void on_Shoulder_Decrease_pressed();

    void on_Shoulder_Decrease_released();

    void on_Elbow_Increase_pressed();

    void on_Elbow_Increase_released();

    void on_Elbow_Decrese_pressed();

    void on_Elbow_Decrese_released();

    void on_Wrist1_Increase_pressed();

    void on_Wrist1_Increase_released();

    void on_Wrist1_Decrease_pressed();

    void on_Wrist1_Decrease_released();

    void on_Wrist2_Increase_pressed();

    void on_Wrist2_Increase_released();

    void on_Wrist2_Decrease_pressed();

    void on_Wrist2_Decrease_released();

    void on_Wrist3_Increase_pressed();

    void on_Wrist3_Increase_released();

    void on_Wrist3_Decrease_pressed();

    void on_Wrist3_Decrease_released();

    void on_techmode_clicked();

    void on_Debug_TCP_clicked();

    void on_Shut_Down_Robot_clicked();

    void on_Speed_Slider_sliderReleased();

    void on_UR_Stop_clicked();

    void on_pushButton_zero_released();

    void on_pushButton_setTCP_clicked();

    void on_pushButton_resetTCP_clicked();

    void on_pushButton_Connect_clicked();


    void on_Debug_Joint_clicked();


private:
	Ui::UR_class_testClass ui;
};

#endif // UR_CLASS_TEST_H
