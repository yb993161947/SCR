  /////////////////////////////////////////////////////
/*
程序名称：前交叉韧带重建2D导航系统
程序功能：
    1、读入3D规划路经数据和标定关节镜图片；
    2、采集并纠正标准正侧位膝关节X光图片，
    3、在X图片上规划手术路径
    4、利用关节镜图片和NDI数据，辅助医生手术
软件编写：北航医疗机器人实验室胡磊
版本信息：V1.0  2017年2月4
 */


#include "ACLwidget.h"
#include "ui_ACLwidget.h"
#include "ui_dialog_setting.h"
/////////////
//继承功能类
#include <QMessageBox>//退出对话框
#include "QFileDialog.h"
///////////////////////
//针孔模型
#include <opencv2/opencv.hpp>
#include <dcmtk/dcmimgle/dcmimage.h>
#include "./carm/ImageRectify.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include "captureVideo/capturevideowidget.h"
#include "imagescene_femur_lat.h"
#include "imagescene_femur_ap.h"
#include "imagescene_Tibia_ap.h"
#include "imagescene_Tibia_lat.h"
#include "Eigen/Eigen"
#include "Eigen/SVD"
#include "Eigen/LU"
#include "QImage"
#include <string>
using namespace cv;
using namespace std;
using namespace Eigen;


const QString Path_Planning_Param_init="Path_Planning_Parameters_init.txt";//../ApplicationDocument/Path_Planning_Parameters_init.txt

const QString Path_Planning_Param="../ApplicationDocument/Path_Planning_Parameters.txt";///ApplicationDocument/Path_Planning_Parameters.txt

//TabWidget Index
#define INDEX_FEMUR 0
#define INDEX_TIBIA 1
#define INDEX_SIMULATE 2
#define INDEX_ROBOT 3

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);//不显示对话框

    //初始化函数，包括读入参数、设备初始化

    InitializationParameter();//初始化参数

    //NDI初始化
	thread_NDI = new thread_get_NDI_marker();
    thread_NDI->start();
    connect(thread_NDI, SIGNAL(threadSignal(QList<Info_NDI>))
        , this, SLOT(rev_NDI(QList<Info_NDI>)), Qt::DirectConnection);
//    connect(thread_NDI, SIGNAL(threadSignal(QList<Info_NDI>))
//        , this, SLOT(rev_NDI(QList<Info_NDI>))) ;

    // xspot上点相对于marker的坐标，如果用其它参考系作为基准，需要乘变换矩阵
        Eigen::MatrixXd XSpotPts3DMatrix;
        XSpotPts3DMatrix.resize(12, 3);
        XSpotPts3DMatrix << 353.5917295, -28.94508077, -58.35207327,
           350.457801, -33.334644, -88.32555342,
           347.1837796, -37.57368775, -118.639914,
           295.8181762, -34.59162595, -31.80863198,
           282.4332982, -40.8479307, -63.78963793,
           267.7006404, -47.70638125, -98.62438413,
           296.9313793, 37.83713989, -48.21922192,
           286.5644333, 42.54051603, -74.75168674,
           276.5781768, 47.58420394, -101.5227552,
           343.6148427, 33.11330516, -67.86624091,
           339.9296347, 36.50701665, -92.54845644,
           336.1567828, 39.58543792, -116.878661;

       for(int i = 0; i < 12; i++)
       {
           XSpotPtsinput << XSpotPts3DMatrix.row(i).transpose();
       }

      //NDI 矩阵初始化
       Xspot_matrix4d_AP_Femur = MatrixXd::Zero(4,4);
       Xspot_matrix4d_Lat_Femur = MatrixXd::Zero(4,4);
       Xspot_matrix4d_AP_Tibia = MatrixXd::Zero(4,4);
       Xspot_matrix4d_Lat_Tibia = MatrixXd::Zero(4,4);

       tiptopatXspot_AP_Femur =  MatrixXd::Zero(4,4);
       tiptopatXspot_Lat_Femur =  MatrixXd::Zero(4,4);
       tiptopatXspot_AP_Tibia =  MatrixXd::Zero(4,4);
       tiptopatXspot_Lat_Tibia =  MatrixXd::Zero(4,4);

       disofPixel_A4atA12 = 0;
       disofPixel_A5atA12 = 0;
       disofPixel_P4atP12 = 0;
       disofPixel_P4atP23 = 0;
       disofPixel_P5atP12 = 0;
       disofPixel_P5atP23 = 0;
       disofPixel_B3atB12 = 0;
       disofPixel_B4atB12 = 0;
       disofPixel_T5atT12 = 0;
       disofPixel_T5atT14 = 0;
       disofPixel_T6atT12 = 0;
       disofPixel_T6atT14 = 0;

       IsopenGuide_AP_Femur = 0;
       IsopenGuide_Lat_Femur = 0;
       IsopenGuide_AP_Tibia = 0;
       IsopenGuide_Lat_Tibia = 0;

       //需要标定呀
       RobotTCP = TofMarkeronRobot2robot.inverse() * TofTCP2MarkeronRobot;


//       //UI注册修改
//       ui->pushButton_AP_CapturePicture->hide();
//       ui->pushButton_getXspottransform_AP->hide();
//       ui->pushButton_ShowTiptool_AP->hide();
//       ui->pushButton_Save_AP->hide();
//       ui->pushButton_matching_AP->hide();
//       ui->pushButton_mirror_AP->hide();
//       ui->checkBox_showAP->hide();
//       ui->horizontalSlider_Femur_AP->hide();
//       ui->horizontalSlider_Tibia_AP->hide();
//       ui->label->hide();

//       ui->pushButton_Lat_CapturePicture->hide();
//       ui->pushButton_getXspottransform_Lat->hide();
//       ui->pushButton_ShowTiptool_Lat->hide();
//       ui->pushButton_Save_Lat->hide();
//       ui->pushButton_matching_Lat->hide();
//       ui->pushButton_mirror_Lat->hide();
//       ui->checkBox_showLat->hide();
//       ui->horizontalSlider_Femur_Lat->hide();
//       ui->horizontalSlider_Tibia_Lat->hide();
//       ui->label_2->hide();

//       ui->tabWidget_manipulate->removeTab(3);
//       ui->tabWidget_manipulate->removeTab(2);

//       ui->pushButton_guide_Tibia->hide();
//       ui->pushButton_Tibia_finished->hide();

//       ui->pushButton_guide_Femur->hide();
//       ui->pushButton_Femur_finished->hide();
//       ui->pushButtonSetting->hide();

//       carmwidget.hide();


}

//初始化参数
void Widget::InitializationParameter()
{

    //初始化设置窗口
    DialogSetting = new Dialog_Setting(this);

    imageScene_AP_Femur = new imageScene_Femur_AP(this);  //初始化股骨胫骨正侧位Scene
    imageScene_Lat_Femur = new imageScene_Femur_Lat(this);
    imageScene_AP_Tibia = new imageScene_Tibia_ap(this);
    imageScene_Lat_Tibia = new imageScene_Tibia_lat(this);



    //Ur
    Ur = new UR_class_test(this);
    Ur->setGeometry(110,110,1200,1200);

    //初始化捕捉图像窗口
    captureVideoWidget = new CaptureVideoWidget();

    connect(DialogSetting,SIGNAL(setPort(int)),this,SLOT(setPort(int)));

    connect(DialogSetting,SIGNAL(loadData_Femur_AP()),this,SLOT(loadData_Femur_AP()));

    connect(DialogSetting,SIGNAL(loadData_Femur_Lat()),this,SLOT(loadData_Femur_Lat()));

    connect(DialogSetting,SIGNAL(loadData_Tibia_AP()),this,SLOT(loadData_Tibia_AP()));

    connect(DialogSetting,SIGNAL(loadData_Tibia_Lat()),this,SLOT(loadData_Tibia_Lat()));

    connect(DialogSetting,SIGNAL(InitMarkerName(QList<QString>)),this,SLOT(InitMarkerName(QList<QString>)));

    connect(DialogSetting,SIGNAL(setTypeofDevice(TypeofDevice)),this,SLOT(setTypeofDevice(TypeofDevice)));

    current_operation = AP_FEMUR;//初始化当前操作类型
    //read3D_Planning();//读取3D规划路径

    //初始化特征点选择
    ui->radioButton_P1->setChecked(true);
    ui->radioButton_A1->setChecked(true);
    ui->radioButton_B1->setChecked(true);
    ui->radioButton_T1->setChecked(true);

    ui->graphicsView_AP->setScene(imageScene_AP_Femur);
    ui->graphicsView_Lat->setScene(imageScene_Lat_Femur);

    ui->radioButton_Femur->setEnabled(false);
    ui->radioButton_Tibia->setEnabled(false);

    connect(imageScene_Lat_Femur,SIGNAL(dotsHasSelected1(float)),
            imageScene_AP_Femur,SLOT(showsubline1(float)));

    connect(imageScene_Lat_Femur,SIGNAL(dotsHasSelected2(float)),
            imageScene_AP_Femur,SLOT(showsubline2(float)));

    connect(imageScene_Lat_Tibia,SIGNAL(dotsHasSelected1(float)),
            imageScene_AP_Tibia,SLOT(showsubline1(float)));

    connect(imageScene_AP_Femur,SIGNAL(pointChanged()),
            this,SLOT(Process_AP_Femur()));

    connect(imageScene_AP_Tibia,SIGNAL(pointChanged()),
            this,SLOT(Process_AP_Tibia()));

    connect(imageScene_Lat_Femur,SIGNAL(pointChanged()),
            this,SLOT(Process_Lat_Femur()));

    connect(imageScene_Lat_Tibia,SIGNAL(pointChanged()),
            this,SLOT(Process_Lat_Tibia()));
    //界面控制
    lastIndex = INDEX_FEMUR;
    on_tabWidget_manipulate_currentChanged(INDEX_FEMUR);
    ui->tabWidget_manipulate->setCurrentIndex(INDEX_FEMUR);
    ui->label_arthroscopy->hide();
    ui->radioButton_Femur->setChecked(true);

    lastIsShow[0] = 1;
    lastIsShow[1] = 1;
    lastIsShow[2] = 1;
    lastIsShow[3] = 1;

    MarkerName_Tiptool = "Marker_Tip";
    MarkerName_XSpot = "Marker_XSpot";
    MarkerName_Femur = "Marker_TreatedFar";
    MarkerName_Tibia = "Marker_TreatedFar";
    MarkerName_Tibia = "Marker_Robot";


    ui->horizontalSlider_Femur_AP->setMinimum(0);
    ui->horizontalSlider_Femur_AP->setMaximum(100);
    ui->horizontalSlider_Femur_AP->setValue(100);
    ui->horizontalSlider_Femur_AP->setGeometry(470,70,170,20);
    ui->horizontalSlider_Femur_AP->show();

    ui->horizontalSlider_Tibia_AP->setMinimum(0);
    ui->horizontalSlider_Tibia_AP->setMaximum(100);
    ui->horizontalSlider_Tibia_AP->setValue(100);
    ui->horizontalSlider_Tibia_AP->setGeometry(470,70,170,20);
    ui->horizontalSlider_Tibia_AP->hide();

    ui->horizontalSlider_Femur_Lat->setMinimum(0);
    ui->horizontalSlider_Femur_Lat->setMaximum(100);
    ui->horizontalSlider_Femur_Lat->setValue(100);
    ui->horizontalSlider_Femur_Lat->setGeometry(470,70,170,20);
    ui->horizontalSlider_Femur_Lat->show();

    ui->horizontalSlider_Tibia_Lat->setMinimum(0);
    ui->horizontalSlider_Tibia_Lat->setMaximum(100);
    ui->horizontalSlider_Tibia_Lat->setValue(100);
    ui->horizontalSlider_Tibia_Lat->setGeometry(470,70,170,20);
    ui->horizontalSlider_Tibia_Lat->hide();
}

Widget::~Widget()
{
    delete ui;
}


//画图事件
void Widget::paintEvent(QPaintEvent * )
{


}

void Widget::on_pushButton_Exit_clicked()//退出
{

    QMessageBox msgBox;
      msgBox.setText(QString::fromLocal8Bit("询问: 确定关闭程序吗？"));
      msgBox.setStandardButtons(QMessageBox::Yes |QMessageBox::No);
      msgBox.setDefaultButton(QMessageBox::Yes);
      int ret = msgBox.exec();

      switch (ret) {
        case QMessageBox::Yes:
            // Yes was clicked
            this->close();
        case QMessageBox::No:
            break;
        default:
            // should never be reached
            break;
      }

}


void Widget::on_tabWidget_manipulate_currentChanged(int index)//标签修改操作函数
{
      switch (index)
    {
        case INDEX_FEMUR:

            ui->graphicsView_AP->show();
            ui->graphicsView_Lat->show();
            ui->label_Latdata->show();
            ui->label_APdata->show();
            ui->groupBox->show();
            ui->groupBox_2->show();
            ui->label_arthroscopy->hide();
            ui->horizontalSlider_Femur_AP->show();
            ui->horizontalSlider_Tibia_AP->hide();
            ui->horizontalSlider_Femur_Lat->show();
            ui->horizontalSlider_Tibia_Lat->hide();


            if(lastIndex == INDEX_SIMULATE)
            {
                imageScene_AP_Femur->zoomIn(1.6667);
                imageScene_AP_Tibia->zoomIn(1.6667);
                imageScene_Lat_Femur->zoomIn(1.6667);
                imageScene_Lat_Tibia->zoomIn(1.6667);
            }
            lastIndex = INDEX_FEMUR;

            ui->graphicsView_AP->setGeometry(30,110,750,750);
            ui->graphicsView_Lat->setGeometry(810,110,750,750);
            ui->graphicsView_AP->setSceneRect(-250,-250,500,500);
            ui->graphicsView_Lat->setSceneRect(-250,-250,500,500);
            ui->graphicsView_AP->setScene(imageScene_AP_Femur);
            ui->graphicsView_Lat->setScene(imageScene_Lat_Femur);

//            ui->label_APdata->setText(QString::fromLocal8Bit
//                        ("股骨数据：\n disofPixel_A4atA12 = %1\n disofPixel_A5atA12 = %2")
//                               .arg(disofPixel_A4atA12).arg(disofPixel_A5atA12));
//            ui->label_Latdata->setText(QString::fromLocal8Bit
//                        ("股骨数据：\n disofPixel_P4atP12 = %1\n disofPixel_P4atP23 = %2\n disofPixel_P5atP12 = %3\n disofPixel_P5atP23 = %4")
//                          .arg(disofPixel_P4atP12).arg(disofPixel_P4atP23).arg(disofPixel_P5atP12).arg(disofPixel_P5atP23));
            ui->label_APdata->setText(QString::fromLocal8Bit
                        ("股骨数据：\n radio_A4atA12 = %1\n radio_A5atA12 = %2")
                               .arg(disofPixel_A4atA12 / disofA12).arg(disofPixel_A5atA12 / disofA12));
            ui->label_Latdata->setText(QString::fromLocal8Bit
                        ("股骨数据：\n radio_P4atP12 = %1\n radio_P4atP23 = %2\n radio_P5atP12 = %3\n radio_P5atP23 = %4")
                          .arg(disofPixel_P4atP12 / disofP12).arg(disofPixel_P4atP23 / disofP12_ver).arg(disofPixel_P5atP12 / disofP12).arg(disofPixel_P5atP23 / disofP12_ver));

            if(imageScene_AP_Femur->pixImage_matching.pixmap().isNull())
                ui->checkBox_showAP->setEnabled(false);
            else
                ui->checkBox_showAP->setEnabled(true);

            if(imageScene_AP_Femur->pixImage_matching.pixmap().isNull())
                ui->checkBox_showLat->setEnabled(false);
            else
                ui->checkBox_showLat->setEnabled(true);

            if(lastIsShow[0])
              ui->checkBox_showAP->setChecked(true);
            else
              ui->checkBox_showAP->setChecked(false);

            if(lastIsShow[1])
              ui->checkBox_showLat->setChecked(true);
            else
              ui->checkBox_showLat->setChecked(false);

            Ur->hide();
            break;
        case INDEX_TIBIA:
            ui->graphicsView_AP->show();
            ui->graphicsView_Lat->show();
            ui->label_Latdata->show();
            ui->label_APdata->show();
            ui->groupBox->show();
            ui->groupBox_2->show();
            ui->label_arthroscopy->hide();
            ui->horizontalSlider_Femur_AP->hide();
            ui->horizontalSlider_Tibia_AP->show();
            ui->horizontalSlider_Femur_Lat->hide();
            ui->horizontalSlider_Tibia_Lat->show();

            if(lastIndex == INDEX_SIMULATE)
            {
                imageScene_AP_Femur->zoomIn(1.6667);
                imageScene_AP_Tibia->zoomIn(1.6667);
                imageScene_Lat_Femur->zoomIn(1.6667);
                imageScene_Lat_Tibia->zoomIn(1.6667);
            }
            lastIndex = INDEX_TIBIA;

            ui->graphicsView_AP->setGeometry(30,110,750,750);
            ui->graphicsView_Lat->setGeometry(810,110,750,750);
            ui->graphicsView_AP->setSceneRect(-250,-250,500,500);
            ui->graphicsView_Lat->setSceneRect(-250,-250,500,500);


            ui->graphicsView_AP->setScene(imageScene_AP_Tibia);
            ui->graphicsView_Lat->setScene(imageScene_Lat_Tibia);

//            ui->label_APdata->setText(QString::fromLocal8Bit
//                        ("胫骨数据：\n disofPixel_B3atB12 = %1\n disofPixel_B4atB12 = %2\n")
//                               .arg(disofPixel_B3atB12).arg(disofPixel_B4atB12));
//            ui->label_Latdata->setText(QString::fromLocal8Bit
//                        ("胫骨数据：\n disofPixel_T5atT12 = %1\n disofPixel_T5atT14 = %2\n disofPixel_T6atT12 = %3\n disofPixel_T6atT14 = %4")
//                               .arg(disofPixel_T5atT12).arg(disofPixel_T5atT14).arg(disofPixel_T6atT12).arg(disofPixel_T6atT14));

            ui->label_APdata->setText(QString::fromLocal8Bit
                        ("胫骨数据：\n radio_B3atB12 = %1\n radio_B4atB12 = %2\n")
                               .arg(disofPixel_B3atB12 / disofB12).arg(disofPixel_B4atB12 / disofB12));
            ui->label_Latdata->setText(QString::fromLocal8Bit
                        ("胫骨数据：\n radio_T5atT12 = %1\n radio_T5atT14 = %2\n radio_T6atT12 = %3\n radio_T6atT14 = %4")
                               .arg(disofPixel_T5atT12 / disofT12).arg(disofPixel_T5atT14 / disofT14).arg(disofPixel_T6atT12 / disofT12).arg(disofPixel_T6atT14 / disofT14));

            if(imageScene_AP_Tibia->pixImage_matching.pixmap().isNull())
                ui->checkBox_showAP->setEnabled(false);
            else
                ui->checkBox_showAP->setEnabled(true);

            if(imageScene_AP_Tibia->pixImage_matching.pixmap().isNull())
                ui->checkBox_showLat->setEnabled(false);
            else
                ui->checkBox_showLat->setEnabled(true);

            if(lastIsShow[2])
              ui->checkBox_showAP->setChecked(true);
            else
              ui->checkBox_showAP->setChecked(false);

            if(lastIsShow[3])
              ui->checkBox_showLat->setChecked(true);
            else
              ui->checkBox_showLat->setChecked(false);

            Ur->hide();
            break;

        case INDEX_SIMULATE:
            ui->graphicsView_AP->show();
            ui->graphicsView_Lat->show();
            ui->label_Latdata->hide();
            ui->label_APdata->hide();
            ui->groupBox->hide();
            ui->groupBox_2->hide();
            ui->label_arthroscopy->show();

            ui->horizontalSlider_Femur_AP->hide();
            ui->horizontalSlider_Tibia_AP->hide();
            ui->horizontalSlider_Femur_Lat->hide();
            ui->horizontalSlider_Tibia_Lat->hide();

             if(lastIndex == INDEX_FEMUR || lastIndex == INDEX_TIBIA)
             {
                 imageScene_AP_Femur->zoomOut(1.6667);
                 imageScene_AP_Tibia->zoomOut(1.6667);
                 imageScene_Lat_Femur->zoomOut(1.6667);
                 imageScene_Lat_Tibia->zoomOut(1.6667);
             }
             lastIndex = INDEX_SIMULATE;


             ui->graphicsView_AP->setGeometry(1060,110,450,450);
             ui->graphicsView_Lat->setGeometry(1060,560,450,450);
             ui->graphicsView_AP->setSceneRect(-150,-150,300,300);
             ui->graphicsView_Lat->setSceneRect(-150,-150,300,300);

            //仿真操作补充
            Ur->hide();
            break;
        case INDEX_ROBOT:
            ui->label_arthroscopy->hide();
            ui->graphicsView_AP->hide();
            ui->graphicsView_Lat->hide();
            ui->label_Latdata->hide();
            ui->label_APdata->hide();
            ui->groupBox->hide();
            ui->groupBox_2->hide();

            ui->horizontalSlider_Femur_AP->hide();
            ui->horizontalSlider_Tibia_AP->hide();
            ui->horizontalSlider_Femur_Lat->hide();
            ui->horizontalSlider_Tibia_Lat->hide();
            //机器人操作补充
            Ur->show();
            break;

        default:
            break;
    }


}

//正位打开图片
void Widget::on_pushButton_AP_OpenPicture_clicked()
{

    qStr_AP_ImageFilePath = QFileDialog::getOpenFileName(nullptr, "加载图像",
        QApplication::applicationDirPath());

    //对图像进行处理并显示
    if(INDEX_FEMUR == ui->tabWidget_manipulate->currentIndex())
    {
        imageScene_AP_Femur->loadDCMImage(qStr_AP_ImageFilePath);

        ui->graphicsView_AP->setScene(imageScene_AP_Femur);
        current_operation = AP_FEMUR;

        for(int i = 0; i < 6;i++)
        {
            imageScene_AP_Tibia->Piximage_button[i].setScale(1);
            imageScene_AP_Tibia->Piximage_button_selected[i].setScale(1);
        }
    }
    else if(INDEX_TIBIA == ui->tabWidget_manipulate->currentIndex())
    {
        imageScene_AP_Tibia->loadDCMImage(qStr_AP_ImageFilePath);

        ui->graphicsView_AP->setScene(imageScene_AP_Tibia);
        current_operation = AP_TIBIA;

        for(int i = 0; i < 6;i++)
        {
            imageScene_AP_Tibia->Piximage_button[i].setScale(1);
            imageScene_AP_Tibia->Piximage_button_selected[i].setScale(1);
        }
    }
}

//侧位打开图片
void Widget::on_pushButton_Lat_OpenPicture_clicked()
{

    qStr_Lat_ImageFilePath = QFileDialog::getOpenFileName(nullptr, "加载图像",
        QApplication::applicationDirPath());

    //对图像进行处理并显示
    if (INDEX_FEMUR == ui->tabWidget_manipulate->currentIndex())
    {
        imageScene_Lat_Femur->loadDCMImage(qStr_Lat_ImageFilePath);

        ui->graphicsView_Lat->setScene(imageScene_Lat_Femur);
        current_operation = LAT_FEMUR;

    }
    else if (INDEX_TIBIA == ui->tabWidget_manipulate->currentIndex())
    {
        imageScene_Lat_Tibia->loadDCMImage(qStr_Lat_ImageFilePath);

        ui->graphicsView_Lat->setScene(imageScene_Lat_Tibia);
        current_operation = LAT_TIBIA;

    }

}

void Widget::on_radioButton_P1_clicked()
{
    imageScene_Lat_Femur->index_selected = 0;
}
void Widget::on_radioButton_P2_clicked()
{
    imageScene_Lat_Femur->index_selected = 1;
}
void Widget::on_radioButton_P3_clicked()
{
    imageScene_Lat_Femur->index_selected = 2;
}
void Widget::on_radioButton_P4_clicked()
{
    imageScene_Lat_Femur->index_selected = 3;
}
void Widget::on_radioButton_P5_clicked()
{
    imageScene_Lat_Femur->index_selected = 4;
}
void Widget::on_radioButton_A1_clicked()
{
    imageScene_AP_Femur->index_selected = 0;
}
void Widget::on_radioButton_A2_clicked()
{
    imageScene_AP_Femur->index_selected = 1;
}
void Widget::on_radioButton_A3_clicked()
{
    imageScene_AP_Femur->index_selected = 2;
}
void Widget::on_radioButton_A4_clicked()
{
    imageScene_AP_Femur->index_selected = 3;
}
void Widget::on_radioButton_A5_clicked()
{
    imageScene_AP_Femur->index_selected = 4;
}


//鼠标释放事件
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
//    switch (ui->tabWidget_manipulate->currentIndex)
//    {
//        case INDEX_FEMUR:

//            break;
//        case INDEX_TIBIA:

//            break;
//        case INDEX_SIMULATE:

//            break;
//        case INDEX_ROBOT:

//            break;

//        default:
//            break;
    //    }
}

Matrix4d Widget::caculateMovetoRoute(Vector3d End3DPt, Vector3d Start3DPt, Matrix4d Bone_Matrix, double dis)
{
    Vector3d N_dir = -End3DPt + Start3DPt;
    Vector3d N1 = (Bone_Matrix.inverse() * Robot_matrix4d * TofMarkeronRobot2robot).col(3).head(3);
    Vector3d N2 = (Bone_Matrix.inverse() * Robot_matrix4d * TofTCP2MarkeronRobot.inverse()).col(3).head(3);
    Vector3d Axis_Z = N2-N1;
    double theta = acosf(N_dir.dot(Axis_Z) / N_dir.norm());
    Vector3d AxisCross = Axis_Z.cross(N_dir);
    if (theta < 0)
        theta =  theta + PI;

    Matrix3d Rotate = rotateWithAxis(AxisCross , theta);
    Vector3d PosEnd=  ((End3DPt - N_dir/N_dir.norm() * dis) - N2.col(3).head(3))/1000 ;//延长距离200mm
    Matrix4d T;
    T.block(0,0,3,3) = Rotate;
    T.col(3).head(3) = PosEnd;
    T.row(3)<<0,0,0,1;
    return T;
}

void Widget::guide()
{

    guide_d(IsopenGuide_AP_Femur, imageScene_AP_Femur,
            Xspot_matrix4d_AP_Femur, Femur_matrix4d, transparams_Femur_AP);

    guide_d(IsopenGuide_Lat_Femur, imageScene_Lat_Femur,
            Xspot_matrix4d_Lat_Femur, Femur_matrix4d, transparams_Femur_Lat);

    guide_d(IsopenGuide_AP_Tibia, imageScene_AP_Tibia,
            Xspot_matrix4d_AP_Tibia, Tibia_matrix4d, transparams_Tibia_AP);

    guide_d(IsopenGuide_Lat_Tibia, imageScene_Lat_Tibia,
            Xspot_matrix4d_Lat_Tibia, Tibia_matrix4d, transparams_Tibia_Lat);

}

void Widget::guide_d(bool IsopenGuide, ImageScene *Imagescene, Matrix4d Xspot_matrix4d, Matrix4d tone, QList<double> transparams)
{
    if(IsopenGuide)//导航
    {
        if(tone(3,3) == 0)
        {
            Imagescene->Marker_Tip->hide();
            Imagescene->needle1->hide();
        }
        else if(Xspot_matrix4d(3,3) == 0)
        {
            Imagescene->Marker_Tip->hide();
            Imagescene->needle1->hide();

        }
        else
        {
            if(Tiptool_matrix4d(3,3) == 0)
            {
                Imagescene->Marker_Tip->hide();
            }
            else
            {
                Matrix4d tiptool2Xspot = Xspot_matrix4d * tone.inverse() * Tiptool_matrix4d;
                Vector4d Tiptop;
                Tiptop = tiptool2Xspot * tanzhen2tip;

                Vector2d Pt2D_TipTop,Pt2D_TipEnd;
                get2DPtfrom3D(Tiptop.head(3), transparams, Pt2D_TipTop);
                Vector4d tanzhen2end = tanzhen2tip;
                tanzhen2end(0) = 0;
                Vector4d Tipend = tiptool2Xspot * tanzhen2end;
                get2DPtfrom3D(Tipend.head(3), transparams, Pt2D_TipEnd);

                Imagescene->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
                Imagescene->Marker_Tip->show();
                Imagescene->update();
            }

            if(Robot_matrix4d(3,3) == 0)
            {
                Imagescene->needle1->hide();
            }
            else
            {
                Matrix4d Robot2Xspot = Xspot_matrix4d * tone.inverse() * Robot_matrix4d ;
                Matrix4d needle2Xspot = Robot2Xspot * RobotTCP;
                Vector4d Tiptop;
                Tiptop =needle2Xspot.col(3);

                Vector2d Pt2D_TipTop,Pt2D_TipEnd;
                get2DPtfrom3D(Tiptop.head(3), transparams, Pt2D_TipTop);
                Vector4d tanzhen2end = tanzhen2tip;
                tanzhen2end(0) = 0;
                Vector4d Tipend = Robot2Xspot.col(3);
                get2DPtfrom3D(Tipend.head(3), transparams, Pt2D_TipEnd);

                Vector2d dir = Pt2D_TipTop - Pt2D_TipEnd;
                double theta = atan2(dir(1),dir(0)) + PI / 2;


                Imagescene->needle1->setRotation(0);
                Imagescene->needle1->setPos(Pt2D_TipTop(0)-Imagescene->needle1->width / 2,Pt2D_TipTop(1));
                Imagescene->needle1->setRotation(theta);
                Imagescene->needle1->show();
                Imagescene->update();
            }
        }

     }
}

bool Widget::get2DPtfrom3D(Vector3d Pt_3D, QList<double> transparams, Vector2d &Pt_2D)
{
    if(transparams.size() != 11)
        return false;

    Pt_2D(0) = (transparams[0] * Pt_3D(0) + transparams[1] * Pt_3D(1) + transparams[2] * Pt_3D(2) + transparams[3])/
            (transparams[4] * Pt_3D(0) + transparams[5] * Pt_3D(1) + transparams[6] * Pt_3D(2) + 1 );
    Pt_2D(1) = (transparams[7] * Pt_3D(0) + transparams[8] * Pt_3D(1) + transparams[9]* Pt_3D(2) + transparams[10])/
            (transparams[4] * Pt_3D(0) + transparams[5] * Pt_3D(1) + transparams[6] * Pt_3D(2) + 1 );
    return true;
}

bool Widget::get3DLinefrom2D(Vector2d Pt_2D, QList<double> transparams, QList<Vector4d> &transparams_Line)
{
    if(transparams.size() != 11)
        return false;
    Vector4d param;
    param(0) = transparams[4] * Pt_2D(0) - transparams[0];
    param(1) = transparams[5] * Pt_2D(0) - transparams[1];
    param(2) = transparams[6] * Pt_2D(0) - transparams[2];
    param(3) = Pt_2D(0) - transparams[3];
    transparams_Line.push_back(param);

    param(0) = transparams[4] * Pt_2D(1) - transparams[7];
    param(1) = transparams[5] * Pt_2D(1) - transparams[8];
    param(2) = transparams[6] * Pt_2D(1) - transparams[9];
    param(3) = Pt_2D(1) - transparams[10];
    transparams_Line.push_back(param);
    return true;
}

bool Widget::get3DPtfrom2Ds(QList<Vector2d> Pt_2Ds, QList<QList<double> > ListOfTransparams, QList<Matrix4d> Xspot_matrix4d, Vector3d &Pt_3D)
{
    if(Pt_2Ds.size() != 2)
        return false;
    if(ListOfTransparams.size() != 2)
        return false;
    if(Pt_2Ds.size() != ListOfTransparams.size())
        return false;
    if(Xspot_matrix4d.size() < 2)
        return false;

    QList<Vector4d> transparams_Line;
    transparams_Line.clear();
    for(auto i = 0 ;i < Pt_2Ds.size();i++)
    {
      get3DLinefrom2D(Pt_2Ds[i], ListOfTransparams[i],transparams_Line);
    }
    //此处写法有bug，必须限制transparams_Line.size为4
    Matrix<double,4, 3> params;
    Vector4d B;
	Matrix4d params_Xspot;
	for (int i = 0; i < transparams_Line.size(); i++)
	{
		params_Xspot.row(i) = transparams_Line[i];
	}
	Matrix4d params_bone;
	 params_bone.block(0,0,2,4) = params_Xspot.block(0, 0, 2, 4) * Xspot_matrix4d[0];
	 params_bone.block(2, 0, 2, 4) = params_Xspot.block(2, 0 , 2, 4) * Xspot_matrix4d[1];

		params = params_bone.block(0, 0, 4, 3);
		B = -params_bone.col(3);

	JacobiSVD<MatrixXd> svd(params, ComputeThinU | ComputeThinV);
	svd.matrixU();
	svd.matrixV();
    Pt_3D = svd.solve(B);
    return true;
}

//判断鼠标位置是否在目标矩形里面
bool Widget::judgeMousePos(const QPoint &point, const QRect &rect)
{
    if((point.x()>=rect.x()) && (point.x()<=rect.x()+rect.width())
            && (point.y()>=rect.y()) && (point.y()<=rect.y()+rect.height()))
    {
        return true;
    }
    else
    {
        return false;
    }
}


//四方格



//垂足点计算
QPointF  Widget::VerticalPoint(QPointF StartPoint,QPointF EndPoint,QPointF XPoint)
{
    QPointF VerticalPoint;


    //        //计算垂直点。云鹏程序修改
    //        QPointF StartPoint;
    //        QPointF EndPoint;
    //        QPointF XPoint;


           // QPointF Pedalpoint;

            //侧位计算，计算第二条线中间线和第一条线之间的角度，该角度是侧位的规划角度
            double k;//k为中垂线 的斜率
            double k0;// 第一条直线的斜率
            double alpha;//两直线夹角
            if(EndPoint.x() - StartPoint.x() ==0 || EndPoint.y() - StartPoint.y() ==0)//计算中垂线的斜率
            {
                 k = (EndPoint.y() - StartPoint.y())/(EndPoint.x() - StartPoint.x()+0.00000000000000001);//中垂线的斜率
            }
            else
            {
                k = (EndPoint.y() - StartPoint.y())/(EndPoint.x() - StartPoint.x());//+0.00000000000000001);//中垂线的斜率

                //计算第三直线入端到中垂线垂足
                VerticalPoint.setX(( k * k * StartPoint.x() + k *(XPoint.y() - StartPoint.y()) + XPoint.x()) / (k * k + 1));//垂足点坐标
                VerticalPoint.setY(k * (VerticalPoint.x() - StartPoint.x()) + StartPoint.y());
            }


            return VerticalPoint;
}

QImage Widget::cvMat2QImage(const Mat &mat)
{

    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar* pSrc = mat.data;
        for(int row = 0; row < mat.rows; row++)
        {
            uchar* pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

//读入3D规划导向参数
void Widget::read3D_Planning() {
    qStr_Lat_ImageFilePath = "";//正侧位图片设为空
    qStr_AP_ImageFilePath = "";

    //3D规划预留接口,读入参数
    QFile myFile(Path_Planning_Param_init);//Path_Planning_Param_init

    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))//打开初始化的路径规划文件
    {
        return;
    }
    QTextStream iFPath_Planning_Param_init(&myFile);

    double dParam[16];

    for (int i = 0; i<16; i++)
    {
        if (iFPath_Planning_Param_init.atEnd())//如果参数不足就退出
        {
            break;
        }
        else
        {
            iFPath_Planning_Param_init >> dParam[i];
        }
    }
/**********************************
*3D规划数据操作
*之后补充具体内容，实为根据数据格式，修改ImageScence中的Piximage_point[]数据。
*
*
*
***********************************/
    qPoint_Tibia_AP_Start.setX(dParam[0]);//
    qPoint_Tibia_AP_Start.setY(dParam[1]);
    qPoint_Tibia_AP_End.setX(dParam[2]);//
    qPoint_Tibia_AP_End.setY(dParam[3]);//

    qPoint_Femur_AP_Start.setX(dParam[4]);//
    qPoint_Femur_AP_Start.setY(dParam[5]);//
    qPoint_Femur_AP_End.setX(dParam[6]);//
    qPoint_Femur_AP_End.setY(dParam[7]);//

    qPoint_Tibia_Lat_Start.setX(dParam[8]);//
    qPoint_Tibia_Lat_Start.setY(dParam[9]);//
    qPoint_Tibia_Lat_End.setX(dParam[10]);//
    qPoint_Tibia_Lat_End.setY(dParam[11]);//

    qPoint_Femur_Lat_Start.setX(dParam[12]);//
    qPoint_Femur_Lat_Start.setY(dParam[13]);//
    qPoint_Femur_Lat_End.setX(dParam[14]);//
    qPoint_Femur_Lat_End.setY(dParam[15]);//

}

float Widget::distance_DotToDot(QPointF linePoint1, QPointF linePoint2)
{
    return sqrtf((linePoint1.x() - linePoint2.x())*(linePoint1.x() - linePoint2.x()) +
                 (linePoint1.y() - linePoint2.y())*(linePoint1.y() - linePoint2.y()));
}

void Widget::caculate_Femur_AP()
{
   Matrix<float,2,1> A1;
   A1<< imageScene_AP_Femur->Piximage_point[0].x() ,imageScene_AP_Femur->Piximage_point[0].y();
   Matrix<float,2,1> A2;
   A2<< imageScene_AP_Femur->Piximage_point[1].x() ,imageScene_AP_Femur->Piximage_point[1].y();
   Matrix<float,2,1> A4;
   A4<< imageScene_AP_Femur->Piximage_point[3].x() ,imageScene_AP_Femur->Piximage_point[3].y();
   Matrix<float,2,1> A5;
   A5<< imageScene_AP_Femur->Piximage_point[4].x() ,imageScene_AP_Femur->Piximage_point[4].y();

   disofA12 = (A2-A1).norm();
   disofPixel_A4atA12 = (A2-A1).dot((A4-A1)) / disofA12;
   disofPixel_A5atA12 = (A2-A1).dot((A5-A1)) / disofA12;

}

void Widget::caculate_Femur_Lat()
{
    Matrix<float,2,1> P1;
    P1<< imageScene_Lat_Femur->Piximage_point[0].x() ,imageScene_Lat_Femur->Piximage_point[0].y();
    Matrix<float,2,1> P2;
    P2<< imageScene_Lat_Femur->Piximage_point[1].x() ,imageScene_Lat_Femur->Piximage_point[1].y();
    Matrix<float,2,1> P3;
    P3<< imageScene_Lat_Femur->Piximage_point[2].x() ,imageScene_Lat_Femur->Piximage_point[2].y();
    Matrix<float,2,1> P4;
    P4<< imageScene_Lat_Femur->Piximage_point[3].x() ,imageScene_Lat_Femur->Piximage_point[3].y();
    Matrix<float,2,1> P5;
    P5<< imageScene_Lat_Femur->Piximage_point[4].x() ,imageScene_Lat_Femur->Piximage_point[4].y();

    disofPixel_P4atP12 = (P1-P2).dot((P4-P2)) / (P1-P2).norm();
    Matrix<float,2,1> P12_ver ;
    Matrix<float,2,1> P12 = P1 - P2;

    disofP12 = (P1-P2).norm();
	float disP3toP12 =  imageScene_AP_Femur->distance_DotToLine(QPointF(P1(0), P1(1)), QPointF(P2(0), P2(1)), QPointF(P3(0), P3(1)));
	P12_ver << P12(1), -P12(0);
	P12_ver = P12_ver / disofP12 * qAbs(disP3toP12);
	disofP12_ver = P12_ver.norm();
    disofPixel_P4atP23 = P12_ver.dot(P4 - P2) / disofP12_ver;
    disofPixel_P5atP12 = (P1-P2).dot(P5 - P2) / disofP12;
    disofPixel_P5atP23 = P12_ver.dot(P5 - P2) / disofP12_ver;
}

void Widget::caculate_Tibia_AP()
{
    Matrix<float,2,1> B1;
    B1<< imageScene_AP_Tibia->Piximage_point[0].x() ,imageScene_AP_Tibia->Piximage_point[0].y();
    Matrix<float,2,1> B2;
    B2<< imageScene_AP_Tibia->Piximage_point[1].x() ,imageScene_AP_Tibia->Piximage_point[1].y();
    Matrix<float,2,1> B3;
    B3<< imageScene_AP_Tibia->Piximage_point[2].x() ,imageScene_AP_Tibia->Piximage_point[2].y();
    Matrix<float,2,1> B4;
    B4<< imageScene_AP_Tibia->Piximage_point[3].x() ,imageScene_AP_Tibia->Piximage_point[3].y();

    disofB12 =  (B2-B1).norm();
    disofPixel_B3atB12 = (B2-B1).dot((B3-B1)) / disofB12;
    disofPixel_B4atB12 = (B2-B1).dot((B4-B1)) / disofB12;

}

void Widget::caculate_Tibia_Lat()
{
    Matrix<float,2,1> T1;
    T1<< imageScene_Lat_Tibia->Piximage_point[0].x() ,imageScene_Lat_Tibia->Piximage_point[0].y();
    Matrix<float,2,1> T2;
    T2<< imageScene_Lat_Tibia->Piximage_point[1].x() ,imageScene_Lat_Tibia->Piximage_point[1].y();
    Matrix<float,2,1> T3;
    T3<< imageScene_Lat_Tibia->Piximage_point[2].x() ,imageScene_Lat_Tibia->Piximage_point[2].y();
    Matrix<float,2,1> T4;
    T4<< imageScene_Lat_Tibia->Piximage_point[3].x() ,imageScene_Lat_Tibia->Piximage_point[3].y();
    Matrix<float,2,1> T5;
    T5<< imageScene_Lat_Tibia->Piximage_point[4].x() ,imageScene_Lat_Tibia->Piximage_point[4].y();
    Matrix<float,2,1> T6;
    T6<< imageScene_Lat_Tibia->Piximage_point[5].x() ,imageScene_Lat_Tibia->Piximage_point[5].y();

    disofT12 =  (T1-T2).norm();
    disofPixel_T5atT12 = (T2-T1).dot(T5 - T1) / disofT12;
    disofPixel_T6atT12 = (T2-T1).dot(T6 - T1) / disofT12;
    disofT14 =  (T1-T4).norm();
    disofPixel_T5atT14 = (T4-T1).dot((T5-T1)) / disofT14;
    disofPixel_T6atT14 = (T4-T1).dot((T6-T1)) / disofT14;
//    Matrix<float,2,1> T12_ver;
//    T12_ver << (T2-T1)(1) , -(T2-T1)(0);
//    disofPixel_T5atT14 = T12_ver.dot(T5 - T1) / T12_ver.norm();
//    disofPixel_T6atT12 = (T1-T2).dot(T6 - T2) / disofT12;
//    disofPixel_T6atT14 = T12_ver.dot(T6 - T2) / T12_ver.norm();

}

bool Widget::OpenCamera()
{
    bool ret = camera->open(cam_index);
    if(ret)
    {
        camTimer->start(50);
    }
    return ret;
}

Mat Widget::enhancePic(Mat SRC)
{
    if(SRC.type() != CV_8UC3)
    {
        return SRC;
    }
    Mat SRC_gray;
    cvtColor(SRC,SRC_gray, CV_BGR2GRAY);

	Mat SRC_mask = cv::Mat::zeros(cv::Size(SRC.rows,SRC.cols), CV_8UC1);

    vector< vector< Point> > contours;   //定义一个轮廓容器
    findContours(SRC_gray,
        contours,                // 轮廓容器
        CV_RETR_EXTERNAL,        // 只检测外轮廓
        CV_CHAIN_APPROX_NONE);   // 存储所有的轮廓点
    for(int i = 0; i <contours.size(); i++ )
    {
        if( cv::contourArea(contours[i])>20000)
            drawContours(SRC, contours, i, Scalar(0,0,255),1);
    }
//	namedWindow("show1");
//	imshow("show1", SRC);
//	waitKey(0);
	for (int i = 0; i <contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		if (area > 20000)
			drawContours(SRC_mask, contours, i, Scalar(255), CV_FILLED);
	}
//	namedWindow("show2");
//	imshow("show2", SRC_mask);
//	waitKey(0);
	Mat png(SRC.size(), CV_8UC4);
	int w = SRC.cols;
	int h = SRC.rows;
	int src_channel = SRC.channels();
	int src_step = SRC.step;
	int dst_channel = png.channels();
	int dst_step = png.step;

	for (int j = 0; j<h; j++)
	{
		for (int i = 0; i<w; i++)
		{
			uchar *src = SRC.data + j*src_step + src_channel*i;
			uchar *dst = png.data + j*dst_step + dst_channel*i;
			uchar *msk = SRC_mask.data + j*SRC_mask.step ;
            dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];

			dst[3] = msk[i];
		} 
	}
//	namedWindow("show");
//	imshow("show", png);
//	waitKey(0);
	return png;



}

Matrix3d Widget::rotateWithAxis(Vector3d Axis, double theta)
{
    Axis = Axis / Axis.norm();
    Matrix3d R;
    R(0,0) = Axis(0) * Axis(0) * (1 - cosf(float(theta))) + cosf(float(theta));
    R(0,1) = Axis(1) * Axis(0) * (1 - cosf(float(theta))) - Axis(2) * sinf(float(theta));
    R(0,2) = Axis(2) * Axis(0) * (1 - cosf(float(theta))) + Axis(1) * sinf(float(theta));

    R(1,0) = Axis(0) * Axis(1) * (1 - cosf(float(theta))) + Axis(2) * sinf(float(theta));
    R(1,1) = Axis(1) * Axis(1) * (1 - cosf(float(theta))) + cosf(float(theta));
    R(1,2) = Axis(2) * Axis(1) * (1 - cosf(float(theta))) - Axis(0) * sinf(float(theta));

    R(2,0) = Axis(0) * Axis(2) * (1 - cosf(float(theta))) - Axis(1) * sinf(float(theta));
    R(2,1) = Axis(1) * Axis(2) * (1 - cosf(float(theta))) + Axis(0) * sinf(float(theta));
    R(2,2) = Axis(2) * Axis(2) * (1 - cosf(float(theta))) + cosf(float(theta));

    return R;
}

void Widget::timerSlot()
{
    camera->retrieve(camImage); //获取一帧图像
    if(!camImage.empty())
    {
        cv::cvtColor(camImage, camImage, cv::COLOR_BGR2GRAY);
        QImage disImage = cvMat2QImage(camImage);

        ui->label_arthroscopy->setPixmap(QPixmap::fromImage(disImage).scaled(ui->label_arthroscopy->width(),ui->label_arthroscopy->height()));
    }
    update();
}

void Widget::on_radioButton_T1_clicked()
{
    imageScene_Lat_Tibia->index_selected = 0;
}

void Widget::on_radioButton_T2_clicked()
{
    imageScene_Lat_Tibia->index_selected = 1;
}

void Widget::on_radioButton_T3_clicked()
{
    imageScene_Lat_Tibia->index_selected = 2;
}

void Widget::on_radioButton_T4_clicked()
{
    imageScene_Lat_Tibia->index_selected = 3;
}

void Widget::on_radioButton_T5_clicked()
{
    imageScene_Lat_Tibia->index_selected = 4;
}

void Widget::on_radioButton_T6_clicked()
{
    imageScene_Lat_Tibia->index_selected = 5;
}

void Widget::on_radioButton_B1_clicked()
{
    imageScene_AP_Tibia->index_selected = 0;
}

void Widget::on_radioButton_B2_clicked()
{
    imageScene_AP_Tibia->index_selected = 1;
}

void Widget::on_radioButton_B3_clicked()
{
    imageScene_AP_Tibia->index_selected = 2;
}

void Widget::on_radioButton_B4_clicked()
{
    imageScene_AP_Tibia->index_selected = 3;
}

void Widget::on_pushButton_getXspottransform_AP()
{
    if (ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        //需要修改。。。。。。。。
        ///////////////////////////////////
        imageScene_AP_Femur->MatrixTipTool = Tiptool_matrix4d;
        imageScene_AP_Femur->MatrixXSpot =  Xspot_matrix4d;

    }
    if (ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        //需要修改。。。。。。。。
        ///////////////////////////////////
        imageScene_AP_Tibia->MatrixTipTool = Tiptool_matrix4d;
        imageScene_AP_Tibia->MatrixXSpot = Xspot_matrix4d;

    }
}

void Widget::on_pushButton_getXspottransform_Lat()
{
    if (ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        //需要修改。。。。。。。。
        ///////////////////////////////////
        imageScene_Lat_Femur->MatrixTipTool = Tiptool_matrix4d;
        imageScene_Lat_Femur->MatrixXSpot = Xspot_matrix4d;

    }
    if (ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        //需要修改。。。。。。。。
        ///////////////////////////////////
        imageScene_Lat_Tibia->MatrixTipTool = Tiptool_matrix4d;
        imageScene_Lat_Tibia->MatrixXSpot = Xspot_matrix4d;

    }
}

void Widget::rev_NDI(QList<Info_NDI> ListInfo_NDI)
{
    Tiptool_matrix4d(3, 3) = 0;
    Xspot_matrix4d(3, 3) = 0;
    Femur_matrix4d(3, 3) = 0;
    Tibia_matrix4d(3, 3) = 0;
    Robot_matrix4d(3,3) = 0;
    DialogSetting->ui->label_Tip->setStyleSheet("border-image: url(:/Resources/tip_disable.png);");
    DialogSetting->ui->label_Xspot->setStyleSheet("border-image: url(:/Resources/XSpot_disable.png);");
    DialogSetting->ui->label_Robot->setStyleSheet("border-image: url(:/Resources/ur_robot_disable.png);");
    DialogSetting->ui->label_Femur->setStyleSheet("border-image: url(:/Resources/resource/Femur_disable.png);");
    DialogSetting->ui->label_Tibia->setStyleSheet("border-image: url(:/Resources/resource/Tibia_disable.png);");
    for(auto i = ListInfo_NDI.begin() ; i < ListInfo_NDI.end() ; i++)
    {
        //改名字。。。。。。。。。。。。。。。。
        //qDebug()<<(*i).name;
        if ((*i).name == MarkerName_Tiptool)
        {
            Tiptool_matrix4d = (*i).Pos;
            DialogSetting->ui->label_Tip->setStyleSheet("border-image: url(:/Resources/tip_enable.png);");
        }
        else if ((*i).name == MarkerName_XSpot)
        {
            Xspot_matrix4d = (*i).Pos;
            DialogSetting->ui->label_Xspot->setStyleSheet("border-image: url(:/Resources/XSpot_enable.png);");
        }
        else if ((*i).name == MarkerName_Femur)
        {
            Femur_matrix4d = (*i).Pos;
            DialogSetting->ui->label_Femur->setStyleSheet("border-image: url(:/Resources/resource/Femur_enable.png);");
        }
        else if ((*i).name == MarkerName_Tibia)
 //        else if ((*i).name == MarkerName_Tibia)
        {
            Tibia_matrix4d = (*i).Pos;
            DialogSetting->ui->label_Tibia->setStyleSheet("border-image: url(:/Resources/resource/Tibia_enable.png);");
        }
        else if((*i).name == MarkerName_Robot)
        {
            Robot_matrix4d = (*i).Pos;
            DialogSetting->ui->label_Robot->setStyleSheet("border-image: url(:/Resources/ur_robot_enable.png);");
        }
    }
       guide();//导航


}

void Widget::on_pushButton_AP_CapturePicture_clicked()
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
       current_operation = AP_FEMUR;
       delete captureVideoWidget;
       captureVideoWidget = new CaptureVideoWidget;

       captureVideoWidget->pushXSpot3DCoordinates(XSpotPtsinput);
       captureVideoWidget->setWindowModality(Qt::ApplicationModal);
       connect(captureVideoWidget,SIGNAL(processFinished(bool))
               ,this,SLOT(imageHasLoad(bool)));
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
       current_operation = AP_TIBIA;
       delete captureVideoWidget;

       captureVideoWidget = new CaptureVideoWidget;
       captureVideoWidget->pushXSpot3DCoordinates(XSpotPtsinput);

       captureVideoWidget->setWindowModality(Qt::ApplicationModal);
       connect(captureVideoWidget,SIGNAL(processFinished(bool))
               ,this,SLOT(imageHasLoad(bool)));
    }
    captureVideoWidget->show();
}

void Widget::on_pushButton_Lat_CapturePicture_clicked()
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {

        current_operation = LAT_FEMUR;
        delete captureVideoWidget;
        captureVideoWidget = new CaptureVideoWidget;

        captureVideoWidget->pushXSpot3DCoordinates(XSpotPtsinput);
        captureVideoWidget->setWindowModality(Qt::ApplicationModal);
        connect(captureVideoWidget,SIGNAL(processFinished(bool))
                ,this,SLOT(imageHasLoad(bool)));
    }

    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        current_operation = LAT_TIBIA;
        delete captureVideoWidget;
        captureVideoWidget = new CaptureVideoWidget;

        captureVideoWidget->pushXSpot3DCoordinates(XSpotPtsinput);

        captureVideoWidget->setWindowModality(Qt::ApplicationModal);
        connect(captureVideoWidget,SIGNAL(processFinished(bool))
                ,this,SLOT(imageHasLoad(bool)));
    }

    captureVideoWidget->show();
}
//当捕获图像窗口后读入图像
void Widget::imageHasLoad(bool issuccessfully)
{

    float  size11 = (captureVideoWidget->original_image.cols + captureVideoWidget->original_image.rows)/2;
    switch(current_operation)
    {
    case AP_FEMUR:
        if(!captureVideoWidget->refined_image_nopoints.empty())
           imageScene_AP_Femur->loadImage(captureVideoWidget->refined_image_nopoints);
        else
           imageScene_AP_Femur->loadImage(captureVideoWidget->original_image);
        if(!captureVideoWidget->original_image.empty())//调整按键大小
        for(int i = 0; i < 6;i++)
        {
            imageScene_AP_Femur->Piximage_button[i].setScale(size11/750);
            imageScene_AP_Femur->Piximage_button_selected[i].setScale(size11/750);
        }

        ui->graphicsView_AP->setScene(imageScene_AP_Femur);
        if(issuccessfully)
        transparams_Femur_AP = captureVideoWidget->getPinHoleParameters();

        break;

    case LAT_FEMUR:
        if(!captureVideoWidget->refined_image_nopoints.empty())
            imageScene_Lat_Femur->loadImage(captureVideoWidget->refined_image_nopoints);
        else
            imageScene_Lat_Femur->loadImage(captureVideoWidget->original_image);
        if(!captureVideoWidget->original_image.empty())//调整按键大小
        for(int i = 0; i < 6;i++)
        {
            imageScene_Lat_Femur->Piximage_button[i].setScale(size11/750);
            imageScene_Lat_Femur->Piximage_button_selected[i].setScale(size11/750);
        }

        ui->graphicsView_Lat->setScene(imageScene_Lat_Femur);
        if(issuccessfully)
        transparams_Femur_Lat = captureVideoWidget->getPinHoleParameters();


        break;

    case AP_TIBIA:
        if(!captureVideoWidget->refined_image_nopoints.empty())
            imageScene_AP_Tibia->loadImage(captureVideoWidget->refined_image_nopoints);
        else
            imageScene_AP_Tibia->loadImage(captureVideoWidget->original_image);
        if(!captureVideoWidget->original_image.empty())//调整按键大小
        for(int i = 0; i < 6;i++)
        {
            imageScene_AP_Tibia->Piximage_button[i].setScale(size11/750);
            imageScene_AP_Tibia->Piximage_button_selected[i].setScale(size11/750);
        }

        ui->graphicsView_AP->setScene(imageScene_AP_Tibia);
        if(issuccessfully)
        transparams_Tibia_AP = captureVideoWidget->getPinHoleParameters();


        break;
    case LAT_TIBIA:
        if(!captureVideoWidget->refined_image_nopoints.empty())
            imageScene_Lat_Tibia->loadImage(captureVideoWidget->refined_image_nopoints);
        else
            imageScene_Lat_Tibia->loadImage(captureVideoWidget->original_image);
        if(!captureVideoWidget->original_image.empty())//调整按键大小
        for(int i = 0; i < 6;i++)
        {
            imageScene_Lat_Tibia->Piximage_button[i].setScale(size11/750);
            imageScene_Lat_Tibia->Piximage_button_selected[i].setScale(size11/750);
        }

        ui->graphicsView_Lat->setScene(imageScene_Lat_Tibia);
        if(issuccessfully)
        transparams_Tibia_Lat = captureVideoWidget->getPinHoleParameters();

        break;
    }

    captureVideoWidget->close();
    update();
}


void Widget::Process_AP_Femur()
{
    int  i ;
    for(i = 0; i<5 ; i++)
    {
        if(imageScene_AP_Femur->Piximage_point[i] == QPoint(-1,-1))
            break;
    }
    if(i == 5)
    {
       caculate_Femur_AP();
       ui->label_APdata->setText(QString::fromLocal8Bit
                   ("股骨数据：\n disofPixel_A4atA12 = %1\n disofPixel_A5atA12 = %2")
                          .arg(disofPixel_A4atA12 / disofA12).arg(disofPixel_A5atA12 / disofA12));

    }
    imageScene_AP_Femur->update();
}

void Widget::Process_AP_Tibia()
{
    int  i ;
    for(i = 0; i<4 ; i++)
    {
        if(imageScene_AP_Tibia->Piximage_point[i] == QPoint(-1,-1))
            break;
    }
    if(i == 4)
    {
       caculate_Tibia_AP();
       ui->label_APdata->setText(QString::fromLocal8Bit
                   ("胫骨数据：\n raido_B3atB12 = %1\n radio_B4atB12 = %2\n")
                          .arg(disofPixel_B3atB12 / disofB12).arg(disofPixel_B4atB12 / disofB12));

    }
    imageScene_AP_Tibia->update();
}

void Widget::Process_Lat_Femur()
{
    int  i ;
    for(i = 0; i<5 ; i++)
    {
        if(imageScene_Lat_Femur->Piximage_point[i] == QPoint(-1,-1))
            break;
    }
    if(i == 5)
    {
       caculate_Femur_Lat();
       ui->label_Latdata->setText(QString::fromLocal8Bit
                   ("股骨数据：\n radio_P4atP12 = %1\n radio_P4atP23 = %2\n radio_P5atP12 = %3\n radio_P5atP23 = %4")
                          .arg(disofPixel_P4atP12 / disofP12).arg(disofPixel_P4atP23 / disofP12_ver).arg(disofPixel_P5atP12 / disofP12).arg(disofPixel_P5atP23 / disofP12_ver));
    qDebug()<< "(" << disofPixel_P4atP12 / disofP12 <<","<< disofPixel_P4atP23 / disofP12_ver <<") , (";

    }
    imageScene_Lat_Femur->update();
}

void Widget::Process_Lat_Tibia()
{
    int  i ;
    for(i = 0; i<6 ; i++)
    {
        if(imageScene_Lat_Tibia->Piximage_point[i] == QPoint(-1,-1))
            break;
    }
    if(i == 6)
    {
       caculate_Tibia_Lat();
       ui->label_Latdata->setText(QString::fromLocal8Bit
                   ("胫骨数据：\n radio_T5atT12 = %1\n radio_T5atT14 = %2\n radio_T6atT12 = %3\n radio_T6atT14 = %4")
                          .arg(disofPixel_T5atT12 / disofT12).arg(disofPixel_T5atT14 / disofT14).arg(disofPixel_T6atT12 / disofT12).arg(disofPixel_T6atT14 / disofT14));
    }
    imageScene_Lat_Tibia->update();
}

void Widget::on_checkBox_AP_Femur_clicked(bool checked)
{
    if(checked)
    {
        for(int i = 0 ;i < 5;i++)
        {
            if(imageScene_AP_Femur->Piximage_point[i] != QPointF(-1,-1))
                imageScene_AP_Femur->Piximage_button[i].show();
        }
        imageScene_AP_Femur->Line1_2->show();
        imageScene_AP_Femur->subline1->show();
        imageScene_AP_Femur->subline2->show();
    }
    else
    {
        for(int i = 0 ;i < 5;i++)
        {
           imageScene_AP_Femur->Piximage_button[i].hide();
           imageScene_AP_Femur->Piximage_button_selected[i].hide();
        }
        imageScene_AP_Femur->Line1_2->hide();
        imageScene_AP_Femur->subline1->hide();
        imageScene_AP_Femur->subline2->hide();
    }
}


void Widget::on_checkBox_Lat_Femur_clicked(bool checked)
{
    if(checked)
    {
        for(int i = 0 ;i < 5;i++)
        {
           imageScene_Lat_Femur->Piximage_button[i].show();
        }
        imageScene_Lat_Femur->Line1_2->show();
        imageScene_Lat_Femur->tablesketch->show();

    }
    else
    {
        for(int i = 0 ;i < 5;i++)
        {
           imageScene_Lat_Femur->Piximage_button[i].hide();
           imageScene_Lat_Femur->Piximage_button_selected[i].hide();
        }
        imageScene_Lat_Femur->Line1_2->hide();
        imageScene_Lat_Femur->tablesketch->hide();
    }
}

void Widget::on_checkBox_AP_Tibia_clicked(bool checked)
{
    if(checked)
    {
        for(int i = 0 ;i < 4;i++)
        {
           imageScene_AP_Tibia->Piximage_button[i].show();

        }
       imageScene_AP_Tibia->Line1_2->show();
       imageScene_AP_Tibia->subline1->show();//等比例辅助线直线
    }
    else
    {
        for(int i = 0 ;i < 4;i++)
        {
           imageScene_AP_Tibia->Piximage_button[i].hide();
           imageScene_Lat_Tibia->Piximage_button_selected[i].hide();
        }
       imageScene_AP_Tibia->Line1_2->hide();
       imageScene_AP_Tibia->subline1->hide();//等比例辅助线直线
    }
}

void Widget::on_checkBox_Lat_Tibia_clicked(bool checked)
{
    if(checked)
    {
        for(int i = 0 ;i < 6;i++)
        {
           imageScene_Lat_Tibia->Piximage_button[i].show();
        }
       imageScene_Lat_Tibia->Line1_2->show();
       imageScene_Lat_Tibia->Line1_2cross->show();
       imageScene_Lat_Tibia->Line1_4->show();
       imageScene_Lat_Tibia->Line2_3->show();
    }
    else
    {
        for(int i = 0 ;i < 6;i++)
        {
           imageScene_Lat_Tibia->Piximage_button[i].hide();
                 imageScene_Lat_Tibia->Piximage_button_selected[i].hide();
        }
        imageScene_Lat_Tibia->Line1_2->hide();
        imageScene_Lat_Tibia->Line1_2cross->hide();
        imageScene_Lat_Tibia->Line1_4->hide();
        imageScene_Lat_Tibia->Line2_3->hide();
    }
}

void Widget::on_pushButton_getXspottransform_AP_clicked()
{
//    disconnect(thread_NDI, SIGNAL(threadSignal(QList<Info_NDI>))//线程冲突？？
//                   , this, SLOT(rev_NDI(QList<Info_NDI>)));
    if(Xspot_matrix4d(3,3) == 0)
    {
        QMessageBox::warning(this,u8"操作失败",u8"未发现Xpot");
        return;
    }
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR )
    {
        if(Femur_matrix4d(3,3) == 0)
        {
            QMessageBox::warning(this,u8"操作失败",u8"未发现股骨");
            return;
        }

        Xspot_matrix4d_AP_Femur = Xspot_matrix4d.inverse() * Femur_matrix4d;
        if(Tiptool_matrix4d(3,3) != 0)
            tiptopatXspot_AP_Femur = Xspot_matrix4d.inverse() * Tiptool_matrix4d;
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA )
    {
        if(Tibia_matrix4d(3,3) == 0)
        {
            QMessageBox::warning(this,u8"操作失败",u8"未发现胫骨");
            return;
        }

        Xspot_matrix4d_AP_Tibia = Xspot_matrix4d.inverse() * Tibia_matrix4d;
        if(Tiptool_matrix4d(3,3) != 0)
            tiptopatXspot_AP_Tibia =Xspot_matrix4d.inverse() * Tiptool_matrix4d;
    }
//    connect(thread_NDI, SIGNAL(threadSignal(QList<Info_NDI>))//线程冲突？？
//       , this, SLOT(rev_NDI(QList<Info_NDI>)));
}

void Widget::on_pushButton_getXspottransform_Lat_clicked()
{
//    disconnect(thread_NDI, SIGNAL(threadSignal(QList<Info_NDI>))//线程冲突？？
//        , this, SLOT(rev_NDI(QList<Info_NDI>)));
    if(Xspot_matrix4d(3,3) == 0)
    {
        QMessageBox::warning(this,u8"操作失败",u8"未发现Xpot");
        return;
    }
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR )
    {
        if(Femur_matrix4d(3,3) == 0)
        {
            QMessageBox::warning(this,u8"操作失败",u8"未发现股骨");
            return;
        }
        Xspot_matrix4d_Lat_Femur =  Xspot_matrix4d.inverse() * Femur_matrix4d ;
        if(Tiptool_matrix4d(3,3) != 0)
                 tiptopatXspot_Lat_Femur = Xspot_matrix4d.inverse() * Tiptool_matrix4d;
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA )
    {
        if(Tibia_matrix4d(3,3) == 0)
        {
            QMessageBox::warning(this,u8"操作失败",u8"未发现胫骨");
            return;
        }

        Xspot_matrix4d_Lat_Tibia = Xspot_matrix4d.inverse()* Tibia_matrix4d;
        if(Tiptool_matrix4d(3,3) != 0)
                tiptopatXspot_Lat_Tibia = Xspot_matrix4d.inverse() * Tiptool_matrix4d;
    }
//    connect(thread_NDI, SIGNAL(threadSignal(QList<Info_NDI>))//线程冲突？？
//       , this, SLOT(rev_NDI(QList<Info_NDI>)));
}

void Widget::on_pushButton_Femur_finished_clicked()
{
    if(  Xspot_matrix4d_AP_Femur(3,3) == 0 )
    {
        QMessageBox::warning(this,u8"操作失败",u8"未记录股骨正位Xpot");
        return;
    }
    if(  Xspot_matrix4d_Lat_Femur(3,3) == 0 )
    {
        QMessageBox::warning(this,u8"操作失败",u8"未记录股骨侧位Xpot");
        return;
    }
    if(imageScene_AP_Femur->Piximage_point[3] == QPointF(-1,-1) ||
          imageScene_AP_Femur->Piximage_point[4] == QPointF(-1,-1))
    {
        QMessageBox::warning(this,u8"操作失败",u8"未规划股骨正位手术路径");
        return;
    }
    if( imageScene_Lat_Femur->Piximage_point[4] == QPointF(-1,-1) ||
               imageScene_Lat_Femur->Piximage_point[3] == QPointF(-1,-1))
    {
        QMessageBox::warning(this,u8"操作失败",u8"未规划股骨侧位手术路径");
        return;
    }
    if( transparams_Femur_AP.size() != 11 )

    {
        QMessageBox::warning(this,u8"操作失败",u8"无法识别股骨正位Xpot点");
        return;
    }
    if( transparams_Femur_Lat.size() != 11 )
    {
        QMessageBox::warning(this,u8"操作失败",u8"无法识别股骨侧位Xpot点");
        return;
    }

    ui->radioButton_Femur->setEnabled(true);
    on_radioButton_Femur_clicked();

    StartPt_Femur_AP(0) = double(imageScene_AP_Femur->Piximage_point[4].x());
    StartPt_Femur_AP(1) = double(imageScene_AP_Femur->Piximage_point[4].y());
    EndPt_Femur_AP(0) = double(imageScene_AP_Femur->Piximage_point[3].x());
    EndPt_Femur_AP(1) = double(imageScene_AP_Femur->Piximage_point[3].y());

    StartPt_Femur_Lat(0) = double(imageScene_Lat_Femur->Piximage_point[4].x());
    StartPt_Femur_Lat(1) = double(imageScene_Lat_Femur->Piximage_point[4].y());
    EndPt_Femur_Lat(0) = double(imageScene_Lat_Femur->Piximage_point[3].x());
    EndPt_Femur_Lat(1) = double(imageScene_Lat_Femur->Piximage_point[3].y());

    QList<Vector2d> Pt_2Ds;
    Pt_2Ds.clear();
    Pt_2Ds.push_back(StartPt_Femur_AP);
    Pt_2Ds.push_back(StartPt_Femur_Lat);

    QList<QList<double> > ListOfTransparams;
    ListOfTransparams.clear();
    ListOfTransparams.push_back(transparams_Femur_AP);
    ListOfTransparams.push_back(transparams_Femur_Lat);

    QList<Matrix4d>  Xspot_matrix4d;
    Xspot_matrix4d.clear();
    Xspot_matrix4d.push_back(Xspot_matrix4d_AP_Femur);
    Xspot_matrix4d.push_back(Xspot_matrix4d_Lat_Femur);

    get3DPtfrom2Ds(Pt_2Ds,ListOfTransparams,Xspot_matrix4d,Start3DPt_Femur);

    Pt_2Ds.clear();
    Pt_2Ds.push_back(EndPt_Femur_AP);
    Pt_2Ds.push_back(EndPt_Femur_Lat);

    get3DPtfrom2Ds(Pt_2Ds,ListOfTransparams,Xspot_matrix4d,End3DPt_Femur);

    QString str;
    str = QString("Start3DPt_Femur:%1,\n%2,\n%3\nEnd3DPt_Femur:%4,\n%5,\n%6\n")
            .arg(Start3DPt_Femur(0)).arg(Start3DPt_Femur(1)).arg(Start3DPt_Femur(2))
            .arg(End3DPt_Femur(0)).arg(End3DPt_Femur(1)).arg(End3DPt_Femur(2));
    ui->labelResult_Femur->setText(str);
}

void Widget::on_pushButton_Tibia_finished_clicked()
{
    if(  Xspot_matrix4d_AP_Tibia(3,3) == 0 )
    {
        QMessageBox::warning(this,u8"操作失败",u8"未记录胫骨正位Xpot");
        return;
    }
    if(  Xspot_matrix4d_Lat_Tibia(3,3) == 0 )
    {
        QMessageBox::warning(this,u8"操作失败",u8"未记录胫骨侧位Xpot");
        return;
    }
    if(imageScene_AP_Tibia->Piximage_point[2] == QPointF(-1,-1) ||
          imageScene_AP_Tibia->Piximage_point[3] == QPointF(-1,-1))
    {
        QMessageBox::warning(this,u8"操作失败",u8"未规划胫骨正位手术路径");
        return;
    }
    if( imageScene_Lat_Tibia->Piximage_point[4] == QPointF(-1,-1) ||
               imageScene_Lat_Tibia->Piximage_point[5] == QPointF(-1,-1))
    {
        QMessageBox::warning(this,u8"操作失败",u8"未规划胫骨侧位手术路径");
        return;
    }
    if( transparams_Tibia_AP.size() != 11 )

    {
        QMessageBox::warning(this,u8"操作失败",u8"无法识别胫骨正位Xpot点");
        return;
    }
    if( transparams_Tibia_Lat.size() != 11 )
    {
        QMessageBox::warning(this,u8"操作失败",u8"无法识别胫骨侧位Xpot点");
        return;
    }
    ui->radioButton_Tibia->setEnabled(true);
    on_radioButton_Tibia_clicked();


    StartPt_Tibia_AP(0) = double(imageScene_AP_Tibia->Piximage_point[3].x());
    StartPt_Tibia_AP(1) = double(imageScene_AP_Tibia->Piximage_point[3].y());
    EndPt_Tibia_AP(0) = double(imageScene_AP_Tibia->Piximage_point[2].x());
    EndPt_Tibia_AP(1) = double(imageScene_AP_Tibia->Piximage_point[2].y());

    StartPt_Tibia_Lat(0) = double(imageScene_Lat_Tibia->Piximage_point[5].x());
    StartPt_Tibia_Lat(1) = double(imageScene_Lat_Tibia->Piximage_point[5].y());
    EndPt_Tibia_Lat(0) = double(imageScene_Lat_Tibia->Piximage_point[4].x());
    EndPt_Tibia_Lat(1) = double(imageScene_Lat_Tibia->Piximage_point[4].y());

    QList<Vector2d> Pt_2Ds;
    Pt_2Ds.clear();
    Pt_2Ds.push_back(StartPt_Tibia_AP);
    Pt_2Ds.push_back(StartPt_Tibia_Lat);

    QList<QList<double> > ListOfTransparams;
    ListOfTransparams.clear();
    ListOfTransparams.push_back(transparams_Tibia_AP);
    ListOfTransparams.push_back(transparams_Tibia_Lat);

    QList<Matrix4d> Xspot_matrix4d;
    Xspot_matrix4d.clear();
    Xspot_matrix4d.push_back(Xspot_matrix4d_AP_Tibia);
    Xspot_matrix4d.push_back(Xspot_matrix4d_Lat_Tibia);

    get3DPtfrom2Ds(Pt_2Ds,ListOfTransparams,Xspot_matrix4d,Start3DPt_Tibia);

    Pt_2Ds.clear();
    Pt_2Ds.push_back(EndPt_Tibia_AP);
    Pt_2Ds.push_back(EndPt_Tibia_Lat);

    get3DPtfrom2Ds(Pt_2Ds,ListOfTransparams,Xspot_matrix4d,End3DPt_Tibia);

    QString str;
    str = QString("Start3DPt_Tibia:%1,\n%2,\n%3\nEnd3DPt_Tibia:%4,\n%5,\n%6\n")
            .arg(Start3DPt_Tibia(0)).arg(Start3DPt_Tibia(1)).arg(Start3DPt_Tibia(2))
            .arg(End3DPt_Tibia(0)).arg(End3DPt_Tibia(1)).arg(End3DPt_Tibia(2));
    ui->labelResult_Tibia->setText(str);
}


void Widget::on_pushButton_ShowTiptool_Lat_clicked()
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        if(tiptopatXspot_Lat_Femur(3,3)  = 0)
        {
            return;
        }
        Vector4d Tiptop;
        Tiptop = tiptopatXspot_Lat_Femur * tanzhen2tip;
        Vector2d Pt2D_TipTop,Pt2D_TipEnd;
        get2DPtfrom3D(Tiptop.head(3), transparams_Femur_Lat, Pt2D_TipTop);

		Vector4d tanzhen2end = tanzhen2tip;
		tanzhen2end(0) = 0;
		Vector4d Tipend = tiptopatXspot_Lat_Femur * tanzhen2end;
        get2DPtfrom3D(Tipend.head(3), transparams_Femur_Lat, Pt2D_TipEnd);

        imageScene_Lat_Femur->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
        imageScene_Lat_Femur->Marker_Tip->show();
        imageScene_Lat_Femur->update();
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        if(tiptopatXspot_Lat_Tibia(3,3)  == 0)
        {
            return;
        }
        Vector4d Tiptop;

        Tiptop = tiptopatXspot_Lat_Tibia * tanzhen2tip;

        Vector2d Pt2D_TipTop,Pt2D_TipEnd;
        get2DPtfrom3D(Tiptop.head(3), transparams_Tibia_Lat, Pt2D_TipTop);
		Vector4d tanzhen2end = tanzhen2tip;
		tanzhen2end(0) = 0;
        Vector4d Tipend = tiptopatXspot_Lat_Tibia * tanzhen2end;

        get2DPtfrom3D(Tipend.head(3), transparams_Tibia_Lat, Pt2D_TipEnd);
        imageScene_Lat_Tibia->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
        imageScene_Lat_Tibia->Marker_Tip->show();
        imageScene_Lat_Tibia->update();
    }
}

void Widget::on_pushButton_ShowTiptool_AP_clicked()
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        if(tiptopatXspot_AP_Femur(3,3)  == 0)
        {
            return;
        }
        Vector4d Tiptop;
        Tiptop = tiptopatXspot_AP_Femur * tanzhen2tip;
        Vector2d Pt2D_TipTop,Pt2D_TipEnd;
        get2DPtfrom3D(Tiptop.head(3), transparams_Femur_AP, Pt2D_TipTop);

		Vector4d tanzhen2end = tanzhen2tip;
		tanzhen2end(0) = 0;
        Vector4d Tipend = tiptopatXspot_AP_Femur * tanzhen2end;
        get2DPtfrom3D(Tipend.head(3), transparams_Femur_AP, Pt2D_TipEnd);

        imageScene_AP_Femur->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
        imageScene_AP_Femur->Marker_Tip->show();
        imageScene_AP_Femur->update();
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        if(tiptopatXspot_AP_Tibia(3,3)  == 0 )
        {
            return;
        }
        Vector4d Tiptop;

        Tiptop = tiptopatXspot_AP_Tibia * tanzhen2tip;

        Vector2d Pt2D_TipTop,Pt2D_TipEnd;
        get2DPtfrom3D(Tiptop.head(3), transparams_Tibia_AP, Pt2D_TipTop);

		Vector4d tanzhen2end = tanzhen2tip;
		tanzhen2end(0) = 0;
        Vector4d Tipend = tiptopatXspot_Lat_Tibia* tanzhen2end;
        get2DPtfrom3D(Tipend.head(3), transparams_Tibia_Lat, Pt2D_TipEnd);

        imageScene_AP_Tibia->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
        imageScene_AP_Tibia->Marker_Tip->show();
        imageScene_AP_Tibia->update();
    }
}



void Widget::on_pushButton_Save_AP_clicked()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);

	if (ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
	{
		path += "/Data_Femur_AP.txt";
		file.setFileName(path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
		{
			out_file.setDevice(&file);
			out_file << "Piximage_point" << endl;
			for (int i = 0; i < 5; i++)
				out_file << imageScene_AP_Femur->Piximage_point[i].x() << ' ' << imageScene_AP_Femur->Piximage_point[i].y() << endl;
			out_file << "Xspot_matrix4d_AP_Femur" << endl;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file << Xspot_matrix4d_AP_Femur(i, j) << ' ';
				out_file << endl;
			}
			out_file << "tiptopatXspot_AP_Femur" << endl;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file << tiptopatXspot_AP_Femur(i, j) << ' ';
				out_file << endl;
			}
			out_file << "transparams_Femur_AP" << endl;
			for (auto i = transparams_Femur_AP.begin(); i < transparams_Femur_AP.end(); i++)
			{
				out_file << *i << ' ';
			}
			file.close();
		}
	}
       if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
       {
          path += "/Data_Tibia_AP.txt";
          file.setFileName(path);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
          {
              out_file.setDevice(&file);
              out_file<< "Piximage_point" <<endl;
              for(int i = 0; i < 4 ;i++)
              out_file<<imageScene_AP_Tibia->Piximage_point[i].x() <<' '<< imageScene_AP_Tibia->Piximage_point[i].y() << endl;
               out_file<< "Xspot_matrix4d_AP_Tibia" <<endl;
              for(int i =0; i < 4;i++)
              {
                  for(int j =0; j < 4;j++)
                   out_file<<Xspot_matrix4d_AP_Tibia(i,j)<<' ';
                   out_file<< endl;
              }
               out_file<< "tiptopatXspot_AP_Tibia" <<endl;
              for(int i =0; i < 4;i++)
              {
                  for(int j =0; j < 4;j++)
                   out_file<<tiptopatXspot_AP_Tibia(i,j)<<' ';
                   out_file<< endl;
              }
			  out_file << "transparams_Tibia_AP" << endl;
              for(auto i = transparams_Tibia_AP.begin(); i < transparams_Tibia_AP.end(); i++)
              {
                   out_file<<*i << ' ';
              }
               file.close();
          }
       }

   
}

void Widget::on_pushButton_Save_Lat_clicked()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);

	if (ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
	{
		path += "/Data_Femur_Lat.txt";
		file.setFileName(path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
		{
			out_file.setDevice(&file);
			out_file << "Piximage_point" << endl;
			for (int i = 0; i < 5; i++)
				out_file << imageScene_Lat_Femur->Piximage_point[i].x() << ' ' << imageScene_Lat_Femur->Piximage_point[i].y() << endl;
			out_file << "Xspot_matrix4d_Lat_Femur" << endl;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file << Xspot_matrix4d_Lat_Femur(i, j) << ' ';
				out_file << endl;
			}
			out_file << "tiptopatXspot_Lat_Femur" << endl;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file << tiptopatXspot_Lat_Femur(i, j) << ' ';
				out_file << endl;
			}
			out_file << "transparams_Femur_Lat" << endl;
			for (auto i = transparams_Femur_Lat.begin(); i < transparams_Femur_Lat.end(); i++)
			{
				out_file << *i << ' ';
			}
			file.close();
		}
	}
        if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        {
            path += "/Data_Tibia_Lat.txt";
            file.setFileName(path);
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
            {
                out_file.setDevice(&file);
                out_file<< "Piximage_point" <<endl;
                for(int i = 0; i < 6 ;i++)
                    out_file<<imageScene_Lat_Tibia->Piximage_point[i].x() <<' '<< imageScene_Lat_Tibia->Piximage_point[i].y() << endl;

                out_file<< "Xspot_matrix4d_Lat_Tibia" <<endl;
                for(int i =0; i < 4;i++)
                {
                    for(int j =0; j < 4;j++)
                        out_file<<Xspot_matrix4d_Lat_Tibia(i,j)<<' ';
                    out_file<< endl;
                }

                out_file<< "tiptopatXspot_Lat_Tibia" <<endl;
                for(int i =0; i < 4;i++)
                {
                    for(int j =0; j < 4;j++)
                        out_file<<tiptopatXspot_Lat_Tibia(i,j)<<' ';
                    out_file<< endl;
                }
				out_file << "transparams_Tibia_Lat" << endl;
                for(auto i = transparams_Tibia_Lat.begin(); i < transparams_Tibia_Lat.end(); i++)
                {
                     out_file<<*i << ' ';
                }

                file.close();
            }
        
    }
}

void Widget::on_pushButton_Read_Lat_clicked()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);


	if (ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
	{
		path += "/Data_Femur_Lat.txt";
		file.setFileName(path);
		QString str;
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
		{
			out_file.setDevice(&file);

			out_file >> str;
			if (str != "Piximage_point")
				return;
			for (int i = 0; i < 5; i++)
			{
				float ftemp;
				out_file >> ftemp;
				imageScene_Lat_Femur->Piximage_point[i].setX(ftemp);
				out_file >> ftemp;
				imageScene_Lat_Femur->Piximage_point[i].setY(ftemp);
			}

			out_file >> str;
			if (str != "Xspot_matrix4d_Lat_Femur")
				return;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file >> Xspot_matrix4d_Lat_Femur(i, j);
			}

			out_file >> str;
			if (str != "tiptopatXspot_Lat_Femur")
				return;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file >> tiptopatXspot_Lat_Femur(i, j);
			}

			out_file >> str;
			if (str != "transparams_Femur_Lat")
				return;
			transparams_Femur_Lat.clear();

			double dtemp;
			while (1)
			{
				out_file >> dtemp;
				if (out_file.atEnd()) break;
				transparams_Femur_Lat.append(dtemp);
			}
			imageScene_Lat_Femur->selected_hide();
			imageScene_Lat_Femur->selected_show();
			imageScene_Lat_Femur->Marker_Tip->show();
			for (int i = 0; i < 6; i++)
			{
				if (imageScene_Lat_Femur->Piximage_point[i] != QPointF(-1, -1))
				{
					imageScene_Lat_Femur->Piximage_button_selected[i].setPos(imageScene_Lat_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Femur->Piximage_button->scale());//按钮图片像素/2*倍率
					imageScene_Lat_Femur->Piximage_button[i].setPos(imageScene_Lat_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Femur->Piximage_button->scale());
					imageScene_Lat_Femur->Piximage_button[i].show();
				}
			}

			file.close();
		}

	}
	
        if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        {
            path += "/Data_TIBIA_Lat.txt";
            file.setFileName(path);
            QString str;
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
            {
                out_file.setDevice(&file);

                out_file >> str;
                if(str != "Piximage_point")
                    return;
                for(int i = 0; i < 6 ;i++)
                {
                    float ftemp;
                    out_file>>ftemp;
                            imageScene_Lat_Tibia->Piximage_point[i].setX(ftemp);
                    out_file>>ftemp;
                            imageScene_Lat_Tibia->Piximage_point[i].setY(ftemp);

                }

                out_file >> str;
                if(str != "Xspot_matrix4d_Lat_Tibia")
                    return;
                for(int i =0; i < 4;i++)
                {
                    for(int j =0; j < 4;j++)
                        out_file >> Xspot_matrix4d_Lat_Tibia(i,j);
                }

                out_file >> str;
                if(str != "tiptopatXspot_Lat_Tibia")
                    return;
                for(int i =0; i < 4;i++)
                {
                    for(int j =0; j < 4;j++)
                        out_file >> tiptopatXspot_Lat_Tibia(i,j);
                }

				out_file >> str;
				if (str != "transparams_Tibia_Lat")
					return;
				transparams_Tibia_Lat.clear();
                double dtemp;
				while (1)
				{
					out_file >> dtemp;
					if (out_file.atEnd()) break;
                    transparams_Tibia_Lat.append(dtemp);
                }
				imageScene_Lat_Tibia->selected_hide();
				imageScene_Lat_Tibia->selected_show();

				imageScene_Lat_Tibia->Marker_Tip->show();
				for (int i = 0; i < 6; i++)
				{
					if (imageScene_Lat_Tibia->Piximage_point[i] != QPointF(-1, -1))
					{
						imageScene_Lat_Tibia->Piximage_button_selected[i].setPos(imageScene_Lat_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Tibia->Piximage_button->scale());//按钮图片像素/2*倍率
						imageScene_Lat_Tibia->Piximage_button[i].setPos(imageScene_Lat_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Tibia->Piximage_button->scale());
						imageScene_Lat_Tibia->Piximage_button[i].show();
					}

				}


                file.close();
            }
        }
}

void Widget::on_pushButton_Read_AP_clicked()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);

	if (ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
	{
		path += "/Data_Femur_AP.txt";
		file.setFileName(path);
		QString str;
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
		{
			out_file.setDevice(&file);

			out_file >> str;
			if (str != "Piximage_point")
				return;
			for (int i = 0; i < 5; i++)
			{
				float ftemp;
				out_file >> ftemp;
				imageScene_AP_Femur->Piximage_point[i].setX(ftemp);
				out_file >> ftemp;
				imageScene_AP_Femur->Piximage_point[i].setY(ftemp);
			}


			out_file >> str;
			if (str != "Xspot_matrix4d_AP_Femur")
				return;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file >> Xspot_matrix4d_AP_Femur(i, j);
			}

			out_file >> str;
			if (str != "tiptopatXspot_AP_Femur")
				return;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					out_file >> tiptopatXspot_AP_Femur(i, j);
			}
			out_file >> str;
			if (str != "transparams_Femur_AP")
				return;
			double dtemp;
			transparams_Femur_AP.clear();
			while (1)
			{
				out_file >> dtemp;
				if (out_file.atEnd()) break;
				transparams_Femur_AP.append(dtemp);
			}
			imageScene_AP_Femur->selected_hide();
			imageScene_AP_Femur->selected_show();
            qDebug()<<1;
			imageScene_AP_Femur->Marker_Tip->show();
			for (int i = 0; i < 5; i++)
			{
				if (imageScene_AP_Femur->Piximage_point[i] != QPointF(-1, -1))
				{
					imageScene_AP_Femur->Piximage_button_selected[i].setPos(imageScene_AP_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Femur->Piximage_button->scale());//按钮图片像素/2*倍率
					imageScene_AP_Femur->Piximage_button[i].setPos(imageScene_AP_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Femur->Piximage_button->scale());
					imageScene_AP_Femur->Piximage_button[i].show();
				}
					
			}


			file.close();
		}
	}

        if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        {
            path += "/Data_Tibia_AP.txt";
            file.setFileName(path);
            QString str;
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
            {
                out_file.setDevice(&file);

                out_file >> str;
                if(str != "Piximage_point")
                    return;
                for(int i = 0; i < 4 ;i++)
                {
                    float ftemp;
                    out_file>>ftemp;
                            imageScene_AP_Tibia->Piximage_point[i].setX(ftemp);
                    out_file>>ftemp;
                            imageScene_AP_Tibia->Piximage_point[i].setY(ftemp);
                }


                out_file >> str;
                if(str != "Xspot_matrix4d_AP_Tibia")
                    return;
                for(int i =0; i < 4;i++)
                {
                    for(int j =0; j < 4;j++)
                        out_file >> Xspot_matrix4d_AP_Tibia(i,j);
                }

                out_file >> str;
                if(str != "tiptopatXspot_AP_Tibia")
                    return;
                for(int i =0; i < 4;i++)
                {
                    for(int j =0; j < 4;j++)
                        out_file >> tiptopatXspot_AP_Tibia(i,j);
                }
				out_file >> str;
				if (str != "transparams_Tibia_AP")
					return;
                double dtemp;
				transparams_Tibia_AP.clear();
                while(1)
                {
                    out_file >> dtemp;
					if (out_file.atEnd()) break;
					transparams_Tibia_AP.append(dtemp);
                }
				imageScene_AP_Tibia->selected_hide();
				imageScene_AP_Tibia->selected_show();
				imageScene_AP_Tibia->Marker_Tip->show();
				for (int i = 0; i < 4; i++)
				{
					if (imageScene_AP_Tibia->Piximage_point[i] != QPointF(-1, -1))
					{
						imageScene_AP_Tibia->Piximage_button_selected[i].setPos(imageScene_AP_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Tibia->Piximage_button->scale());//按钮图片像素/2*倍率
						imageScene_AP_Tibia->Piximage_button[i].setPos(imageScene_AP_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Tibia->Piximage_button->scale());
						imageScene_AP_Tibia->Piximage_button[i].show();	
					}
					
				}

                file.close();
            }
        }

}

void Widget::setPort(int Port)
{
    thread_NDI->init_udp(Port);
}

void Widget::loadData_Femur_AP()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);
    path += "/Data_Femur_AP.txt";
    file.setFileName(path);
    QString str;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
    {
        out_file.setDevice(&file);

        out_file >> str;
        if (str != "Piximage_point")
            return;
        for (int i = 0; i < 5; i++)
        {
            float ftemp;
            out_file >> ftemp;
            imageScene_AP_Femur->Piximage_point[i].setX(ftemp);
            out_file >> ftemp;
            imageScene_AP_Femur->Piximage_point[i].setY(ftemp);
        }


        out_file >> str;
        if (str != "Xspot_matrix4d_AP_Femur")
            return;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                out_file >> Xspot_matrix4d_AP_Femur(i, j);
        }

        out_file >> str;
        if (str != "tiptopatXspot_AP_Femur")
            return;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                out_file >> tiptopatXspot_AP_Femur(i, j);
        }
        out_file >> str;
        if (str != "transparams_Femur_AP")
            return;
        double dtemp;
        transparams_Femur_AP.clear();
        while (1)
        {
            out_file >> dtemp;
            if (out_file.atEnd()) break;
            transparams_Femur_AP.append(dtemp);
        }
        imageScene_AP_Femur->selected_hide();
        imageScene_AP_Femur->selected_show();
        qDebug()<<1;

        Vector4d Tiptop;
        Tiptop = tiptopatXspot_AP_Femur * tanzhen2tip;
        Vector2d Pt2D_TipTop,Pt2D_TipEnd;
        get2DPtfrom3D(Tiptop.head(3), transparams_Femur_AP, Pt2D_TipTop);

		Vector4d tanzhen2end = tanzhen2tip;
		tanzhen2end(0) = 0;
		Vector4d Tipend = tiptopatXspot_AP_Femur * tanzhen2end;
		get2DPtfrom3D(Tipend.head(3), transparams_Femur_AP, Pt2D_TipEnd);


        imageScene_AP_Femur->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
        imageScene_AP_Femur->Marker_Tip->show();
        imageScene_AP_Femur->update();

        for (int i = 0; i < 5; i++)
        {
            if (imageScene_AP_Femur->Piximage_point[i] != QPointF(-1, -1))
            {
                imageScene_AP_Femur->Piximage_button_selected[i].setPos(imageScene_AP_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Femur->Piximage_button->scale());//按钮图片像素/2*倍率
                imageScene_AP_Femur->Piximage_button[i].setPos(imageScene_AP_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Femur->Piximage_button->scale());
                imageScene_AP_Femur->Piximage_button[i].show();
            }

        }


        file.close();
    }
}

void Widget::loadData_Femur_Lat()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);

        path += "/Data_Femur_Lat.txt";
        file.setFileName(path);
        QString str;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
        {
            out_file.setDevice(&file);

            out_file >> str;
            if (str != "Piximage_point")
                return;
            for (int i = 0; i < 5; i++)
            {
                float ftemp;
                out_file >> ftemp;
                imageScene_Lat_Femur->Piximage_point[i].setX(ftemp);
                out_file >> ftemp;
                imageScene_Lat_Femur->Piximage_point[i].setY(ftemp);
            }

            out_file >> str;
            if (str != "Xspot_matrix4d_Lat_Femur")
                return;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                    out_file >> Xspot_matrix4d_Lat_Femur(i, j);
            }

            out_file >> str;
            if (str != "tiptopatXspot_Lat_Femur")
                return;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                    out_file >> tiptopatXspot_Lat_Femur(i, j);
            }

            out_file >> str;
            if (str != "transparams_Femur_Lat")
                return;
            transparams_Femur_Lat.clear();

            double dtemp;
            while (1)
            {
                out_file >> dtemp;
                if (out_file.atEnd()) break;
                transparams_Femur_Lat.append(dtemp);
            }
            imageScene_Lat_Femur->selected_hide();
            imageScene_Lat_Femur->selected_show();

            Vector4d Tiptop;
            Tiptop = tiptopatXspot_Lat_Femur * tanzhen2tip;

            Vector2d Pt2D_TipTop,Pt2D_TipEnd;
            get2DPtfrom3D(Tiptop.head(3), transparams_Femur_Lat, Pt2D_TipTop);

			Vector4d tanzhen2end = tanzhen2tip;
			tanzhen2end(0) = 0;
			Vector4d Tipend = tiptopatXspot_Lat_Femur * tanzhen2end;
			get2DPtfrom3D(Tipend.head(3), transparams_Femur_Lat, Pt2D_TipEnd);

            imageScene_Lat_Femur->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
            imageScene_Lat_Femur->Marker_Tip->show();
            imageScene_Lat_Femur->update();

            for (int i = 0; i < 6; i++)
            {
                if (imageScene_Lat_Femur->Piximage_point[i] != QPointF(-1, -1))
                {
                    imageScene_Lat_Femur->Piximage_button_selected[i].setPos(imageScene_Lat_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Femur->Piximage_button->scale());//按钮图片像素/2*倍率
                    imageScene_Lat_Femur->Piximage_button[i].setPos(imageScene_Lat_Femur->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Femur->Piximage_button->scale());
                    imageScene_Lat_Femur->Piximage_button[i].show();
                }
            }

            file.close();
        }

}

void Widget::loadData_Tibia_AP()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);


        path += "/Data_Tibia_AP.txt";
        file.setFileName(path);
        QString str;
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
        {
            out_file.setDevice(&file);

            out_file >> str;
            if(str != "Piximage_point")
                return;
            for(int i = 0; i < 4 ;i++)
            {
                float ftemp;
                out_file>>ftemp;
                        imageScene_AP_Tibia->Piximage_point[i].setX(ftemp);
                out_file>>ftemp;
                        imageScene_AP_Tibia->Piximage_point[i].setY(ftemp);
            }


            out_file >> str;
            if(str != "Xspot_matrix4d_AP_Tibia")
                return;
            for(int i =0; i < 4;i++)
            {
                for(int j =0; j < 4;j++)
                    out_file >> Xspot_matrix4d_AP_Tibia(i,j);
            }

            out_file >> str;
            if(str != "tiptopatXspot_AP_Tibia")
                return;
            for(int i =0; i < 4;i++)
            {
                for(int j =0; j < 4;j++)
                    out_file >> tiptopatXspot_AP_Tibia(i,j);
            }
            out_file >> str;
            if (str != "transparams_Tibia_AP")
                return;
            double dtemp;
            transparams_Tibia_AP.clear();
            while(1)
            {
                out_file >> dtemp;
                if (out_file.atEnd()) break;
                transparams_Tibia_AP.append(dtemp);
            }
            imageScene_AP_Tibia->selected_hide();
            imageScene_AP_Tibia->selected_show();

            Vector4d Tiptop;

            Tiptop = tiptopatXspot_AP_Tibia * tanzhen2tip;

            Vector2d Pt2D_TipTop,Pt2D_TipEnd;
            get2DPtfrom3D(Tiptop.head(3), transparams_Tibia_AP, Pt2D_TipTop);

			Vector4d tanzhen2end = tanzhen2tip;
			tanzhen2end(0) = 0;
			Vector4d Tipend = tiptopatXspot_AP_Tibia * tanzhen2end;
			get2DPtfrom3D(Tipend.head(3), transparams_Tibia_AP, Pt2D_TipEnd);

            imageScene_AP_Tibia->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
            imageScene_AP_Tibia->Marker_Tip->show();
            imageScene_AP_Tibia->update();

            for (int i = 0; i < 4; i++)
            {
                if (imageScene_AP_Tibia->Piximage_point[i] != QPointF(-1, -1))
                {
                    imageScene_AP_Tibia->Piximage_button_selected[i].setPos(imageScene_AP_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Tibia->Piximage_button->scale());//按钮图片像素/2*倍率
                    imageScene_AP_Tibia->Piximage_button[i].setPos(imageScene_AP_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_AP_Tibia->Piximage_button->scale());
                    imageScene_AP_Tibia->Piximage_button[i].show();
                }

            }

            file.close();
        }

}

void Widget::loadData_Tibia_Lat()
{
    QString path = QApplication::applicationDirPath();
    path =path +  "/DataDocument" ;
    QDir dir;
    dir.mkpath(path);

    path += "/Data_TIBIA_Lat.txt";
    file.setFileName(path);
    QString str;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本文式写入
    {
        out_file.setDevice(&file);

        out_file >> str;
        if(str != "Piximage_point")
            return;
        for(int i = 0; i < 6 ;i++)
        {
            float ftemp;
            out_file>>ftemp;
                    imageScene_Lat_Tibia->Piximage_point[i].setX(ftemp);
            out_file>>ftemp;
                    imageScene_Lat_Tibia->Piximage_point[i].setY(ftemp);

        }

        out_file >> str;
        if(str != "Xspot_matrix4d_Lat_Tibia")
            return;
        for(int i =0; i < 4;i++)
        {
            for(int j =0; j < 4;j++)
                out_file >> Xspot_matrix4d_Lat_Tibia(i,j);
        }

        out_file >> str;
        if(str != "tiptopatXspot_Lat_Tibia")
            return;
        for(int i =0; i < 4;i++)
        {
            for(int j =0; j < 4;j++)
                out_file >> tiptopatXspot_Lat_Tibia(i,j);
        }

        out_file >> str;
        if (str != "transparams_Tibia_Lat")
            return;
        transparams_Tibia_Lat.clear();
        double dtemp;
        while (1)
        {
            out_file >> dtemp;
            if (out_file.atEnd()) break;
            transparams_Tibia_Lat.append(dtemp);
        }
        imageScene_Lat_Tibia->selected_hide();
        imageScene_Lat_Tibia->selected_show();


        Vector4d Tiptop;
        Tiptop = tiptopatXspot_Lat_Tibia * tanzhen2tip;

        Vector2d Pt2D_TipTop,Pt2D_TipEnd;
        get2DPtfrom3D(Tiptop.head(3), transparams_Tibia_Lat, Pt2D_TipTop);

		Vector4d tanzhen2end = tanzhen2tip;
		tanzhen2end(0) = 0;
		Vector4d Tipend = tiptopatXspot_Lat_Tibia * tanzhen2end;
		get2DPtfrom3D(Tipend.head(3), transparams_Tibia_Lat, Pt2D_TipEnd);

        imageScene_Lat_Tibia->Marker_Tip->setLine(Pt2D_TipEnd(0),Pt2D_TipEnd(1),Pt2D_TipTop(0),Pt2D_TipTop(1));
        imageScene_Lat_Tibia->Marker_Tip->show();
        imageScene_Lat_Tibia->update();

        for (int i = 0; i < 6; i++)
        {
            if (imageScene_Lat_Tibia->Piximage_point[i] != QPointF(-1, -1))
            {
                imageScene_Lat_Tibia->Piximage_button_selected[i].setPos(imageScene_Lat_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Tibia->Piximage_button->scale());//按钮图片像素/2*倍率
                imageScene_Lat_Tibia->Piximage_button[i].setPos(imageScene_Lat_Tibia->Piximage_point[i] - QPoint(10, 10)*imageScene_Lat_Tibia->Piximage_button->scale());
                imageScene_Lat_Tibia->Piximage_button[i].show();
            }

        }


        file.close();
    }
}

void Widget::on_pushButtonSetting_clicked()
{
    DialogSetting->show();
}

void Widget::on_pushButton_guide_Tibia_clicked()
{
	if (ui->pushButton_guide_Tibia->text() == u8"开始导航")
	{
	    IsopenGuide_AP_Tibia = true;
		IsopenGuide_Lat_Tibia = true;
		ui->pushButton_guide_Tibia->setText(u8"结束导航");
	}
	else
	{
		IsopenGuide_AP_Tibia = false;
		IsopenGuide_Lat_Tibia = false;
		ui->pushButton_guide_Tibia->setText(u8"开始导航");
	}

}

void Widget::on_pushButton_guide_Femur_clicked()
{
	if (ui->pushButton_guide_Femur->text() == u8"开始导航")
	{
		IsopenGuide_AP_Femur = true;
		IsopenGuide_Lat_Femur = true;
		ui->pushButton_guide_Femur->setText(u8"结束导航");
	}
	else
	{
		IsopenGuide_AP_Femur = false;
		IsopenGuide_Lat_Femur = false;
		ui->pushButton_guide_Femur->setText(u8"开始导航");
	}
}

void Widget::on_radioButton_Femur_clicked()
{
    ui->graphicsView_AP->setScene(imageScene_AP_Femur);
    ui->graphicsView_Lat->setScene(imageScene_Lat_Femur);
}

void Widget::on_radioButton_Tibia_clicked()
{
    ui->graphicsView_AP->setScene(imageScene_AP_Tibia);
    ui->graphicsView_Lat->setScene(imageScene_Lat_Tibia);
}

void Widget::InitMarkerName(QList<QString> name)
{
	MarkerName_Femur = name[0];
	MarkerName_Tibia = name[1];
	MarkerName_XSpot = name[2];
	MarkerName_Tiptool = name[3];
    MarkerName_Robot = name[4];
}



void Widget::on_pushButton_matching_Lat_clicked()
{
    char* filename;

    QString FilePath = QFileDialog::getOpenFileName(nullptr, u8"打开图片");

    QByteArray ba = FilePath.toLatin1(); // QString转为char*
    filename = ba.data();
    cv::Mat original_image;

    QPixmap pixmap;
    char* prefix;
    size_t filename_length = strlen(filename); // length ()
    // int filename_length=filename.length();//
    prefix = filename + filename_length - 3; //获得后三位字符
    if(strcmp(prefix, "BMP") == 0 || strcmp(prefix, "bmp") == 0 ||
            strcmp(prefix, "JPG") == 0 || strcmp(prefix, "jpg") == 0)
    {
        Mat SRC;
        SRC = imread(FilePath.toLocal8Bit().data());
        Mat DIST =enhancePic(SRC);
        QImage qimg = cvMat2QImage(DIST);
        pixmap=QPixmap::fromImage(qimg);
    }
    else
    {
        // cout<<"unrecognized format";
        return;
    }

    if(!pixmap.isNull())
    {
        if(ui->tabWidget_manipulate->currentIndex() ==INDEX_FEMUR)
        {
            imageScene_Lat_Femur->setMoveObj(1);
            imageScene_Lat_Femur->loadMatchingImage(pixmap);
            imageScene_Lat_Femur->pixImage_matching.setPos(-375,-375);

            imageScene_Lat_Femur->pixImage_matching.show();
            ui->checkBox_showLat->setCheckable(true);
            ui->checkBox_showLat->setEnabled(true);
        }
        else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        {
            imageScene_Lat_Tibia->setMoveObj(1);
            imageScene_Lat_Tibia->loadMatchingImage(pixmap);
            imageScene_Lat_Tibia->pixImage_matching.setPos(-375,-375);

            imageScene_Lat_Tibia->pixImage_matching.show();
            ui->checkBox_showLat->setCheckable(true);
            ui->checkBox_showLat->setEnabled(true);
        }

    }
}

void Widget::on_pushButton_matching_AP_clicked()
{
    char* filename;

    QString FilePath = QFileDialog::getOpenFileName(nullptr, u8"打开图片");

    QByteArray ba = FilePath.toLatin1(); // QString转为char*
    filename = ba.data();

    QPixmap pixmap;
    char* prefix;
    size_t filename_length = strlen(filename); // length ()
    // int filename_length=filename.length();//
    prefix = filename + filename_length - 3; //获得后三位字符

    if(strcmp(prefix, "BMP") == 0 || strcmp(prefix, "bmp") == 0 ||
            strcmp(prefix, "JPG") == 0 || strcmp(prefix, "jpg") == 0)
    {
        Mat SRC;
        SRC = imread(FilePath.toLocal8Bit().data());
        Mat DIST =enhancePic(SRC);
        QImage qimg = cvMat2QImage(DIST);
        pixmap=QPixmap::fromImage(qimg);

    }
    else
    {
        return;
    }

    if(!pixmap.isNull())
    {

        if(ui->tabWidget_manipulate->currentIndex() ==INDEX_FEMUR)
        {
            imageScene_AP_Femur->setMoveObj(1);
            imageScene_AP_Femur->loadMatchingImage(pixmap);

            imageScene_AP_Femur->pixImage_matching.show();
            ui->checkBox_showAP->setCheckable(true);
            ui->checkBox_showAP->setEnabled(true);
        }
        else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        {
            imageScene_AP_Tibia->setMoveObj(1);
            imageScene_AP_Tibia->loadMatchingImage(pixmap);

            imageScene_AP_Tibia->pixImage_matching.show();
            ui->checkBox_showAP->setCheckable(true);
            ui->checkBox_showAP->setEnabled(true);
        }

    }

}

void Widget::on_checkBox_showAP_clicked(bool checked)
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        if(checked)
        {
            imageScene_AP_Femur->pixImage_matching.show();
            imageScene_AP_Femur->setMoveObj(1);
            lastIsShow[0] = 1;
        }
        else
        {
            imageScene_AP_Femur->pixImage_matching.hide();
            imageScene_AP_Femur->setMoveObj(0);
            lastIsShow[0] = 0;
        }
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        if(checked)
        {
            imageScene_AP_Tibia->pixImage_matching.show();
            imageScene_AP_Tibia->setMoveObj(1);
            lastIsShow[2] = 1;
        }
        else
        {
            imageScene_AP_Tibia->pixImage_matching.hide();
            imageScene_AP_Tibia->setMoveObj(0);
            lastIsShow[2] = 0;
        }
    }
}

void Widget::on_checkBox_showLat_clicked(bool checked)
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        if(checked)
        {
            imageScene_Lat_Femur->pixImage_matching.show();
            imageScene_Lat_Femur->setMoveObj(1);
            lastIsShow[1] = 1;
        }
        else
        {
            imageScene_Lat_Femur->pixImage_matching.hide();
            imageScene_Lat_Femur->setMoveObj(0);
            lastIsShow[1] = 0;
        }
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        if(checked)
        {
            imageScene_Lat_Tibia->pixImage_matching.show();
            imageScene_Lat_Tibia->setMoveObj(1);
            lastIsShow[3] = 1;
        }
        else
        {
            imageScene_Lat_Tibia->pixImage_matching.hide();
            imageScene_Lat_Tibia->setMoveObj(0);
            lastIsShow[3] = 0;
        }
    }
}


void Widget::on_pushButton_clicked()
{
    //摄像头
           cam_index = 0;
           camera = new cv::VideoCapture;
           camTimer = new QTimer();
           connect(camTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
           OpenCamera();
}


void Widget::on_horizontalSlider_Tibia_AP_valueChanged(int value)
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        imageScene_AP_Tibia->pixImage_matching.setOpacity(((float)value)/ui->horizontalSlider_Tibia_AP->maximum());

        update();
}

void Widget::on_horizontalSlider_Femur_Lat_valueChanged(int value)
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
        imageScene_Lat_Femur->pixImage_matching.setOpacity(((float)value)/ui->horizontalSlider_Femur_Lat->maximum());

    update();
}

void Widget::on_horizontalSlider_Tibia_Lat_valueChanged(int value)
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
        imageScene_Lat_Tibia->pixImage_matching.setOpacity(((float)value)/ui->horizontalSlider_Tibia_Lat->maximum());

    update();
}

void Widget::on_horizontalSlider_Femur_AP_valueChanged(int value)
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
        imageScene_AP_Femur->pixImage_matching.setOpacity(((float)value)/ui->horizontalSlider_Femur_AP->maximum());

    update();
}



void Widget::on_pushButton_mirror_AP_clicked()
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        QImage image_mirror;
        image_mirror = imageScene_AP_Femur->pixImage_matching.pixmap().toImage().mirrored();
        imageScene_AP_Femur->pixImage_matching.setPixmap(QPixmap::fromImage(image_mirror));
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        QImage image_mirror;
        image_mirror = imageScene_AP_Tibia->pixImage_matching.pixmap().toImage().mirrored();
        imageScene_AP_Tibia->pixImage_matching.setPixmap(QPixmap::fromImage(image_mirror));
    }
}

void Widget::on_pushButton_mirror_Lat_clicked()
{
    if(ui->tabWidget_manipulate->currentIndex() == INDEX_FEMUR)
    {
        QImage image_mirror;
        image_mirror = imageScene_Lat_Femur->pixImage_matching.pixmap().toImage().mirrored();
        imageScene_Lat_Femur->pixImage_matching.setPixmap(QPixmap::fromImage(image_mirror));
    }
    else if(ui->tabWidget_manipulate->currentIndex() == INDEX_TIBIA)
    {
        QImage image_mirror;
        image_mirror = imageScene_Lat_Tibia->pixImage_matching.pixmap().toImage().mirrored();
        imageScene_Lat_Tibia->pixImage_matching.setPixmap(QPixmap::fromImage(image_mirror));
    }
}


void Widget::on_pushButton_moveRobot_clicked()
{
    //开始点和止点反了，所以N_DIr = start - end
    if(ui->radioButton_Femur->isChecked())
    {
        T_End = caculateMovetoRoute(End3DPt_Femur,Start3DPt_Femur,Femur_matrix4d,100);
        double pos[6];
        Ur->pUR5->matrix_2_UR6params(T_End,pos);
        Ur->pUR5->yb_movep_TCP(pos);
        return;
    }
    if(ui->radioButton_Tibia->isChecked())
    {
        T_End = caculateMovetoRoute(End3DPt_Tibia,Start3DPt_Tibia,Tibia_matrix4d,100);
        double pos[6];
        Ur->pUR5->matrix_2_UR6params(T_End,pos);
        Ur->pUR5->yb_movep_TCP(pos);
        return;
    }
}

void Widget::on_pushButton_moveRobotin_pressed()
{
   //开始点和止点反了，所以N_DIr = start - end
    if(ui->radioButton_Femur->isChecked())
    {
        T_End = caculateMovetoRoute(End3DPt_Femur,Start3DPt_Femur,Femur_matrix4d,10);
        double pos[6];
        Ur->pUR5->matrix_2_UR6params(T_End,pos);
        Ur->pUR5->yb_movep_TCP(pos);
        return;
    }
    if(ui->radioButton_Tibia->isChecked())
    {
        T_End = caculateMovetoRoute(End3DPt_Tibia,Start3DPt_Tibia,Tibia_matrix4d,10);
        double pos[6];
        Ur->pUR5->matrix_2_UR6params(T_End,pos);
        Ur->pUR5->yb_movep_TCP(pos);
        return;
    }
}

void Widget::on_pushButton_moveRobotin_released()
{
    Ur->pUR5->stopl();
}

void Widget::on_pushButton_moveRobotin_2_pressed()
{

}

void Widget::on_pushButton_moveRobotin_2_released()
{
        Ur->pUR5->stopl();
}

void Widget::on_pushButton_moveRobotin_3_pressed()
{

}

void Widget::on_pushButton_moveRobotin_3_released()
{
    Ur->pUR5->stopl();
}

void Widget::on_pushButton_2_clicked()
{
    carmwidget.show();
}

void Widget::setTypeofDevice(TypeofDevice type)
{
    thread_NDI->setTypeofDevice(type);
}
