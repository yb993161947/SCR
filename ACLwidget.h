#ifndef ACLWIDGET_H
#define ACLWIDGET_H

#include <QWidget>
//hulei
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QCheckBox>
#include <QPen>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QString>
#include <QTextStream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "ImageScene.h"
#include "imagescene_femur_lat.h"
#include "imagescene_femur_ap.h"
#include "imagescene_Tibia_ap.h"
#include "imagescene_Tibia_lat.h"
#include "thread_get_ndi_marker.h"
#include "captureVideo/capturevideowidget.h"
#include "Eigen/SVD"
#include "dialog_setting.h"
#include <QTimer>
#include "./core.hpp"
#include "highgui.h"
#include "UrAPI/ur_class_test.h"
#include "CArmAngleCalCuLate/widget.h"
#include "imagescene_camera.h"

//Xspot上有两个Marker标记，Marker1相对于模型中心点1的坐标，Marker2相对于模型中心点2的坐标


using namespace cv;
//NDI
//const Vector4d tanzhen2tip(159, -0.24, -18.22, 1.0000);
//tracker,MARKERTIP_LONG
//const Vector4d tanzhen2tip(-196.4532 ,- 1.7583, - 0.1103,	1);

//const Vector4d tanzhen2tip(148.0390, 4.9085, -11.9415, 1.0000);
namespace Ui {
class Widget;
}
#define CAMERAINDEX 0
#define APINDEX 1
#define LATINDEX 2

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //参数定义
    //定义输入参数

    QString qStr_AP_ImageFilePath ;//打开正位图片的路径名
    QString qStr_Lat_ImageFilePath ;//打开侧位图片的路径名

    //定义current_operation当前操作
    enum{AP_FEMUR,
         LAT_FEMUR,
         AP_TIBIA,
         LAT_TIBIA}current_operation;//当前操作类型，分为AP_FEMUR,LAT_TEMUR,AP_TIBIA,LAT_TIBIA四种
 
    //自定义函数
    void InitializationParameter();//初始化参数
    bool judgeMousePos(const QPoint &point, const QRect &rect);//判断鼠标的位置是否在指定区域
	QPointF VerticalPoint(QPointF StartPoint, QPointF EndPoint, QPointF XPoint);//求2垂足点坐标
    QImage cvMat2QImage(const cv::Mat& mat);
    //设置窗口
    Dialog_Setting *DialogSetting;

    //虚拟函数
    void paintEvent(QPaintEvent *e);//重写绘图函数内容
    void mouseReleaseEvent(QMouseEvent *e);	//鼠标事件
    void mouseDoubleClickEvent ( QMouseEvent * e );
    //日志文件
    QFile file;
    QTextStream out_file;


    //sceneview
    imageScene_Femur_AP *imageScene_AP_Femur;//股骨正位窗口图像
	imageScene_Femur_Lat *imageScene_Lat_Femur;//股骨侧位窗口图像
    imageScene_Tibia_ap *imageScene_AP_Tibia;//胫骨正位窗口图像
    imageScene_Tibia_lat *imageScene_Lat_Tibia;//胫骨正位窗

									 
	//Ndi								
    Matrix4d Tiptool_matrix4d;//探针坐标
    Matrix4d Xspot_matrix4d;//Xspot坐标
	Matrix4d Femur_matrix4d;//股骨坐标
	Matrix4d Tibia_matrix4d;//胫骨坐标
    Matrix4d Robot_matrix4d;//胫骨坐标

    QList<Matrix4d> Tiptool_matrix4d_ver;//探针坐标
    QList<Matrix4d> Xspot_matrix4d_ver;//Xspot坐标
    QList<Matrix4d> Femur_matrix4d_ver;//股骨坐标
    QList<Matrix4d> Tibia_matrix4d_ver;//胫骨坐标
    QList<Matrix4d> Robot_matrix4d_ver;//胫骨坐标

    Matrix4d Xspot_matrix4d_AP_Femur;//采集图像时骨头Marker在Xspot下的坐标，后续用于探针导航；
    Matrix4d Xspot_matrix4d_Lat_Femur;//采集图像时骨头Marker在Xspot下的坐标，后续用于探针导航；
    Matrix4d Xspot_matrix4d_AP_Tibia;//采集图像时骨头Marker在Xspot下的坐标，后续用于探针导航；
    Matrix4d Xspot_matrix4d_Lat_Tibia;//采集图像时骨头Marker在Xspot下的坐标，后续用于探针导航；

    Matrix4d tiptopatXspot_AP_Femur;//采集图像时记录下探针相对于XSpot的坐标
    Matrix4d tiptopatXspot_Lat_Femur;
    Matrix4d tiptopatXspot_AP_Tibia;
    Matrix4d tiptopatXspot_Lat_Tibia;

    //标定数据
    Vector4d TofTCP_Up2MarkeronRobot;
    Vector4d TofTCP_Down2MarkeronRobot;
    Matrix4d TofMarkerTip1toMarkerTip2;
    Matrix4d TofMarkeronRobot2Robot;
    Matrix4d XSpotMarker1toMarker2;
    Matrix4d XSpotMarker1toMarkerUp;
    Matrix4d TCPMarker1toTCPMarker2;
	Matrix4d TCPMarker1toTCPMarker3;
    Matrix4d TCPMarker1toTCPMarkerUp;
    Matrix4d TofMarker1ToTip1;
    Vector4d tanzhen2tip;
    Vector4d tanzhen2tipend;
	void caculateMovetoRoute(Vector3d End3DPt, Vector3d Start3DPt, Matrix4d &Bone_Matrix, double pos[]);//单位mm
    void caculateMoveAngle(Vector3d End3DPt,Vector3d Start3DPt,Matrix4d &Bone_Matrix ,double pos[]);//单位mm

    QString MarkerName_Femur;
    QString MarkerName_Tibia;
    QString MarkerName_XSpot;
    QString MarkerName_XSpot2;
    QString MarkerName_XSpot3;
    QString MarkerName_Tiptool1;
    QString MarkerName_Tiptool2;
    QString MarkerName_Robot;
    QString MarkerName_Robot2;
    QString MarkerName_Robot3;
    //导航标志
    bool IsopenGuide_AP_Femur;
    bool IsopenGuide_Lat_Femur;
    bool IsopenGuide_AP_Tibia;
    bool IsopenGuide_Lat_Tibia;
    bool IsopenGuide_AP_Femur_last = false;
    bool IsopenGuide_Lat_Femur_last = false;
    bool IsopenGuide_AP_Tibia_last = false;
    bool IsopenGuide_Lat_Tibia_last = false;
    void guide();
    void guide_d(bool IsopenGuide,ImageScene *Imagescene,Matrix4d &Xspot_matrix4d,Matrix4d &tone, QList<double> transparams,Matrix4d &Mark_Adjust);


	thread_get_NDI_marker *thread_NDI;

    //Xspot
    QList<Eigen::Vector3d> XSpotPtsinput;
    QList<double> transparams_Femur_AP;//11个参数
    QList<double> transparams_Femur_Lat;
    QList<double> transparams_Tibia_AP;
    QList<double> transparams_Tibia_Lat;
    bool get2DPtfrom3D(Vector3d Pt_3D, QList<double> transparams, Vector2d &Pt_2D);
    bool get3DLinefrom2D(Vector2d &Pt_2D, QList<double> transparams,QList<Vector4d> &transparams_Line);

	bool Widget::Shift2DPtfrom2D(Vector2d &Pt_Scr,
		QList<double> transparams_Scr,
		QList<Vector2d> &Line_Dist,
		QList<double> transparams_Dist,
		Matrix4d &MarkerOnXspot_scr,
		Matrix4d &MarkerOnXspot_dist);

    bool get3DPtfrom2Ds(QList<Vector2d > Pt_2Ds, QList<QList<double> > ListOfTransparams,QList<Matrix4d> Xspot_matrix4d,Vector3d &Pt_3D);
	//3D规划文件处理
	void read3D_Planning();//读入3D规划导向参数
	QPoint qPoint_Tibia_AP_Start,//股骨、胫骨正侧位进出点，共8个
            qPoint_Tibia_AP_End,
            qPoint_Tibia_Lat_Start,
            qPoint_Tibia_Lat_End,
            qPoint_Femur_AP_Start,
            qPoint_Femur_AP_End,
            qPoint_Femur_Lat_Start,
            qPoint_Femur_Lat_End;

    //采集图像窗口
    CaptureVideoWidget *captureVideoWidget;

    //计算坐标
    float distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot);
    float distance_DotToDot(QPointF linePoint1, QPointF linePoint2);

    void caculate_Femur_AP();
    float disofPixel_A4atA12;//A4在line12上的投影长度
    float disofPixel_A5atA12;//A5在line12上的投影长度
    float disofA12;//Line12的长度
    void caculate_Femur_Lat();
    float disofPixel_P4atP12;//P4在P12上的投影长度
    float disofPixel_P4atP23;//P4在P12垂直方向的投影长度
    float disofPixel_P5atP12;//P5在P12上的投影长度
    float disofPixel_P5atP23;//P5在P12垂直方向上的投影长度
    float disofP12;//P12的距离
    float disofP12_ver;//垂直于P12到P3点的距离
    void caculate_Tibia_AP();
    float disofPixel_B3atB12;//B3在B12上的投影长度
    float disofPixel_B4atB12;//B4在B12上的投影长度
    float disofB12;//B12的距离
    void caculate_Tibia_Lat();
    float disofPixel_T5atT12;//T5在T14上的投影长度
    float disofPixel_T5atT14;//T5在T14垂直方向的投影长度
    float disofPixel_T6atT12;//T6在T12上的投影长度
    float disofPixel_T6atT14;//T6在T14垂直方向上的投影长度
    float disofT12;//T12长度
    float disofT14;//T14长度

    Vector2d StartPt_Femur_AP,EndPt_Femur_AP;//2D图上规划的坐标
    Vector2d StartPt_Femur_Lat,EndPt_Femur_Lat;
    Vector2d StartPt_Tibia_AP,EndPt_Tibia_AP;
    Vector2d StartPt_Tibia_Lat,EndPt_Tibia_Lat;

    Vector3d Start3DPt_Femur,End3DPt_Femur;//3D下的规划点坐标
    Vector3d Start3DPt_Tibia,End3DPt_Tibia;

    //文本框数据
    QString data_Femur_AP;
    QString data_Femur_Lat;
    QString data_Tibia_AP;
    QString data_Tibia_Lat;

    //小窗口切换
    int lastIndex;
    int lastIsShow[4];

    //摄像头
    imagescene_camera *cameraScene;


    //图像叠加
    cv::Mat enhancePic(cv::Mat SRC);

    //Ur控制
    UR_class_test *Ur;
    Matrix4d RobotTCP;
    Matrix3d rotateWithAxis(Vector3d Axis,double theta);//弧度
    Matrix4d T_End; //第一步，运动到路径上
    Matrix4d T_End1; //第一步，运动到路径上
    Matrix4d T_End2; //第一步，运动到路径上

    //CArm角度调整模块
    CArmWidget carmwidget;

    //配置文件
    void readSettingFile();

    //监视程序
    QProcess *pro_fileWatcher;

    //窗口切换
    QGraphicsScene *CameraScene;
    QGraphicsPixmapItem *CameraPix;

    QGraphicsView *CameraWidget, *APWidget, *LatWidget;
    int Index_widget[3] = {CAMERAINDEX,APINDEX,LATINDEX};

    //探针矫正
    Matrix4d Marker_Adjust[4];

private slots:


    void on_pushButton_Exit_clicked();

    void on_tabWidget_manipulate_currentChanged(int index);

    void on_pushButton_AP_OpenPicture_clicked();

    void on_pushButton_Lat_OpenPicture_clicked();

    void on_radioButton_P1_clicked();

    void on_radioButton_P2_clicked();

    void on_radioButton_P3_clicked();

    void on_radioButton_P4_clicked();

    void on_radioButton_P5_clicked();

    void on_radioButton_A1_clicked();

    void on_radioButton_A2_clicked();

    void on_radioButton_A3_clicked();

    void on_radioButton_A4_clicked();

    void on_radioButton_A5_clicked();

    void on_radioButton_T1_clicked();

    void on_radioButton_T2_clicked();

    void on_radioButton_T3_clicked();

    void on_radioButton_T4_clicked();

    void on_radioButton_T5_clicked();

    void on_radioButton_T6_clicked();

    void on_radioButton_B1_clicked();	

    void on_radioButton_B2_clicked();

    void on_radioButton_B3_clicked();

    void on_radioButton_B4_clicked();

    void on_pushButton_getXspottransform_AP();

    void on_pushButton_getXspottransform_Lat();

    void rev_NDI(QList<Info_NDI> ListInfo_NDI);//接收NDI

    void on_pushButton_AP_CapturePicture_clicked();//AP捕捉图像窗口

    void imageHasLoad(bool issuccessfully);//捕捉图像槽

    void on_pushButton_Lat_CapturePicture_clicked();

    void Process_AP_Femur(int index);//处理数据

    void Process_AP_Tibia(int index);

    void Process_Lat_Femur(int index);

    void Process_Lat_Tibia(int index);

    void on_checkBox_AP_Femur_clicked(bool checked);

    void on_checkBox_Lat_Femur_clicked(bool checked);

    void on_checkBox_AP_Tibia_clicked(bool checked);

    void on_checkBox_Lat_Tibia_clicked(bool checked);

    void on_pushButton_getXspottransform_AP_clicked();

    void on_pushButton_getXspottransform_Lat_clicked();

    void on_pushButton_Femur_finished_clicked();

    void on_pushButton_Tibia_finished_clicked();

    void on_pushButton_ShowTiptool_Lat_clicked();

    void on_pushButton_ShowTiptool_AP_clicked();

    void on_pushButton_Save_AP_clicked();

    void on_pushButton_Save_Lat_clicked();

    void on_pushButton_Read_Lat_clicked();

    void on_pushButton_Read_AP_clicked();

    void setPort(int Port);

    void loadData_Femur_AP();

    void loadData_Femur_Lat();

    void loadData_Tibia_AP();

    void loadData_Tibia_Lat();

    void on_pushButtonSetting_clicked();

    void on_pushButton_guide_Femur_clicked();

    void on_pushButton_guide_Tibia_clicked();

    void on_radioButton_Femur_clicked();

    void on_radioButton_Tibia_clicked();

    void InitMarkerName(QList<QString> name);

    void on_pushButton_matching_Lat_clicked();

    void on_pushButton_matching_AP_clicked();

    void on_checkBox_showAP_clicked(bool checked);

    void on_checkBox_showLat_clicked(bool checked);

    void on_pushButton_clicked();

    void on_horizontalSlider_Tibia_AP_valueChanged(int value);

    void on_horizontalSlider_Femur_Lat_valueChanged(int value);

    void on_horizontalSlider_Tibia_Lat_valueChanged(int value);

    void on_horizontalSlider_Femur_AP_valueChanged(int value);

    void on_pushButton_mirror_AP_clicked();

    void on_pushButton_mirror_Lat_clicked();

    void on_pushButton_moveRobot_clicked();

    void on_pushButton_moveRobotin_pressed();

    void on_pushButton_moveRobotin_released();

    void on_pushButton_moveRobotin_2_pressed();

    void on_pushButton_moveRobotin_2_released();

    void on_pushButton_moveRobotin_3_released();

    void on_pushButton_moveRobotin_3_pressed();

    void on_pushButton_2_clicked();

    void setTypeofDevice(TypeofDevice type);


    void Point_Change_Femur_AP(int index);
    void Point_Change_Tibia_AP(int index);
    void Point_Change_Femur_Lat(int index);
    void Point_Change_Tibia_Lat(int index);

    void on_pushButton_InitRobot_clicked();

    //视角切换



    void on_pushButton_SetRobot_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_Femur_finished_2_clicked();


    void on_pushButton_moveRobotin_4_clicked();

private:
    Ui::Widget *ui;
};

#endif // ACLWIDGET_H
