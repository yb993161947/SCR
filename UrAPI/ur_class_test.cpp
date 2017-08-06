#include "ur_class_test.h"
#include "UR_interface.h"
#include <QDebug>

UR_class_test::UR_class_test(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	pUR5 = new UR_interface;
    GetRobotInfoThreadFlag = false;
    TechFlag = false;
    connect(ui.pushButton_GoHome,SIGNAL(clicked()),this,SLOT(UR_Home()));
    ui.groupBox_2->setEnabled(false);
    ui.groupBox_3->setEnabled(false);
    ui.groupBox_4->setEnabled(false);
    ui.groupBox_5->setEnabled(false);

}

UR_class_test::~UR_class_test()
{

}
void UR_class_test::Connect_UR()
{
	const std::string ip = ui.lineEdit_UR_IP->text().toStdString();
    if(!pUR5->connect_robot(ip))
    {
        qDebug()<<"failed in connecting robot";
        return;

    }
    GetRobotInfoThreadFlag = true;
    this->thread = new MyThread(this);  //将该类指针传递
    connect(this->thread, SIGNAL(threadSignal()), this, SLOT(getUR_PosData()));
    this->thread->start();

    ui.groupBox_2->setEnabled(true);
    ui.groupBox_3->setEnabled(true);
    ui.groupBox_4->setEnabled(true);
    ui.groupBox_5->setEnabled(true);
    //设置机器人初始速度
    ui.Speed_Slider->setValue(30);
    on_Speed_Slider_sliderReleased();
}
void UR_class_test::UR_Home()
{
	pUR5->go_home();
}
void UR_class_test::getUR_PosData()
{
    ui.Base_Pose_X->setText(QString("%1").arg(TcpPos[0]));
    ui.Base_Pose_Y->setText(QString("%1").arg(TcpPos[1]));
    ui.Base_Pose_Z->setText(QString("%1").arg(TcpPos[2]));
    ui.Base_Pose_RX->setText(QString("%1").arg(180 * TcpPos[3] / PI));
    ui.Base_Pose_RY->setText(QString("%1").arg(180 * TcpPos[4] / PI));
    ui.Base_Pose_RZ->setText(QString("%1").arg(180 * TcpPos[5] / PI));

    ui.Joint_Pose_Base->setText(QString("%1").arg(	 180 * Jointangle[0] / PI));
    ui.Joint_Pose_Shoulder->setText(QString("%1").arg(180 * Jointangle[1] / PI));
    ui.Joint_Pose_Elbow->setText(QString("%1").arg(	 180 * Jointangle[2] / PI));
    ui.Joint_Pose_Wrist_1->setText(QString("%1").arg(  180 * Jointangle[3] / PI));
    ui.Joint_Pose_Wrist_2->setText(QString("%1").arg(  180 * Jointangle[4] / PI));
    ui.Joint_Pose_Wrist_3->setText(QString("%1").arg(  180 * Jointangle[5] / PI));
}
void UR_class_test::on_Base_Pose_X_Increase_pressed()
{
    double tcp_speed[6]={0.03,0,0,0,0,0};
    pUR5->speedl(tcp_speed);
}

void UR_class_test::on_Base_Pose_Y_Increase_pressed()
{
    double tcp_speed[6]={0,0.03,0,0,0,0};
    pUR5->speedl(tcp_speed);
}


void UR_class_test::on_Base_Pose_X_Decrease_pressed()
{
    double tcp_speed[6]={-0.03,0,0,0,0,0};
    pUR5->speedl(tcp_speed);
}

void UR_class_test::on_Base_Pose_X_Increase_released()
{
    pUR5->stopl();
}

void UR_class_test::on_Base_Pose_X_Decrease_released()
{
    pUR5->stopl();
}

void UR_class_test::on_Base_Pose_Y_Increase_released()
{
    pUR5->stopl();
}

void UR_class_test::on_Base_Pose_Y_Decrease_pressed()
{
    double tcp_speed[6]={0,-0.03,0,0,0,0};
    pUR5->speedl(tcp_speed);
}

void UR_class_test::on_Base_Pose_Y_Decrease_released()
{
    pUR5->stopl();
}

void UR_class_test::on_Base_Pose_Z_Increase_pressed()
{
    double tcp_speed[6]={0,0,0.03,0,0,0};
    pUR5->speedl(tcp_speed);
}

void UR_class_test::on_Base_Pose_Z_Increase_released()
{
    pUR5->stopl();
}

void UR_class_test::on_Base_Pose_Z_Decrease_pressed()
{
    double tcp_speed[6]={0,0,-0.03,0,0,0};
    pUR5->speedl(tcp_speed);
}

void UR_class_test::on_Base_Pose_Z_Decrease_released()
{
    pUR5->stopl();
}

void UR_class_test::on_Base_Increase_pressed()
{
    double angle_speed[6]={0.1,0,0,0,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Base_Increase_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Base_Decrease_pressed()
{
    double angle_speed[6]={-0.1,0,0,0,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Base_Decrease_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Shoulder_Increase_pressed()
{
    double angle_speed[6]={0,0.1,0,0,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Shoulder_Increase_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Shoulder_Decrease_pressed()
{
    double angle_speed[6]={0,-0.1,0,0,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Shoulder_Decrease_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Elbow_Increase_pressed()
{
    double angle_speed[6]={0,0,0.1,0,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Elbow_Increase_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Elbow_Decrese_pressed()
{
    double angle_speed[6]={0,0,-0.1,0,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Elbow_Decrese_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Wrist1_Increase_pressed()
{
    double angle_speed[6]={0,0,0,0.1,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Wrist1_Increase_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Wrist1_Decrease_pressed()
{
    double angle_speed[6]={0,0,0,-0.1,0,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Wrist1_Decrease_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Wrist2_Increase_pressed()
{
    double angle_speed[6]={0,0,0,0,0.1,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}
void UR_class_test::on_Wrist2_Increase_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Wrist2_Decrease_pressed()
{
    double angle_speed[6]={0,0,0,0,-0.1,0}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Wrist2_Decrease_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Wrist3_Increase_pressed()
{
    double angle_speed[6]={0,0,0,0,0,0.1}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Wrist3_Increase_released()
{
    pUR5->stopj();
}

void UR_class_test::on_Wrist3_Decrease_pressed()
{
    double angle_speed[6]={0,0,0,0,0,-0.1}; //单位是rad/s
    pUR5->speedj(angle_speed);
}

void UR_class_test::on_Wrist3_Decrease_released()
{
    pUR5->stopj();
}

void UR_class_test::on_techmode_clicked()
{
    TechFlag = !TechFlag;
    if (TechFlag)
    {
        ui.techmode->setText("TechMode");
        pUR5->set_robot_mode(1);
    }
    else
    {
        ui.techmode->setText("Nomal");
        pUR5->set_robot_mode(0);
    }

}

void UR_class_test::on_Debug_TCP_clicked()
{
    QString str[6];
    double var[6];
    str[0] = ui.X_Or_Base->text();
    str[1] = ui.Y_Or_Shoulder->text();
    str[2] = ui.Z_Or_Elbow->text();
    str[3] = ui.Rx_Or_Wrist1->text();
    str[4] = ui.Ry_Or_Wrist2->text();
    str[5] = ui.Rz_Or_Wrist3->text();
    for (int i=0;i<3;i++)
    {
        var[i] = str[i].toDouble()/1000;  //转化为m
        var[i+3] = (str[i+3].toDouble())/180.0*PI; //转为弧度
    }
    pUR5->yb_movep_TCP(var);
}


void UR_class_test::on_Shut_Down_Robot_clicked()
{
    pUR5->power_off_robot();
}



void UR_class_test::on_Speed_Slider_sliderReleased()
{
    int pos = ui.Speed_Slider->value();
    ui.Speed_value->setText(QString("%1").arg(pos));
    double ratio = (double)pos/100;
    pUR5->set_speed(ratio);
}

void UR_class_test::on_UR_Stop_clicked()
{
    pUR5->stopj();
}


void UR_class_test::on_pushButton_zero_released()
{
    ui.X_Or_Base->setText("0");
    ui.Y_Or_Shoulder->setText("0");
    ui.Z_Or_Elbow->setText("0");
    ui.Rx_Or_Wrist1->setText("0");
    ui.Ry_Or_Wrist2->setText("0");
    ui.Rz_Or_Wrist3->setText("0");
}

void UR_class_test::on_pushButton_setTCP_clicked()
{

        QSettings *configIniRead = new QSettings("configure.ini", QSettings::IniFormat);
        QString TCP = configIniRead->value("/UR/TCP").toString();
        QStringList TCPList = TCP.split(',');
        delete configIniRead;
        double var[6];
        for(int i = 0; i < 6; i++)
        {
            var[i] = TCPList[i].toDouble();

        }
        for (int i=0;i<3;i++)
        {
            var[i] = var[i]/1000;
            var[i+3] =var[i+3]/180.0*PI;
        }
        pUR5->set_tcp_pos(var);
}

void UR_class_test::on_pushButton_resetTCP_clicked()
{
    double var[6] ={0,0,0,0,0,0};
    pUR5->set_tcp_pos(var);
}


void UR_class_test::on_pushButton_Connect_clicked()
{
    Connect_UR();
}


void UR_class_test::on_Debug_Joint_clicked()
{

    QString str[6];
      double var[6];
      str[0] = ui.X_Or_Base->text();
      str[1] = ui.Y_Or_Shoulder->text();
      str[2] = ui.Z_Or_Elbow->text();
      str[3] = ui.Rx_Or_Wrist1->text();
      str[4] = ui.Ry_Or_Wrist2->text();
      str[5] = ui.Rz_Or_Wrist3->text();
      for (int i=0;i<6;i++)
      {
          var[i] = (str[i].toDouble())/180.0*PI+Jointangle[i];
          if(var[i] > PI)
              var[i] -= 2*PI;
          if(var[i] < -PI)
              var[i] += 2*PI;
      }

      pUR5->movej_joint(var);
}

