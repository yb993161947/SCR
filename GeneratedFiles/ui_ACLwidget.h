/********************************************************************************
** Form generated from reading UI file 'ACLwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACLWIDGET_H
#define UI_ACLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <navilabel.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_Exit;
    QTabWidget *tabWidget_manipulate;
    QWidget *tab_Femur;
    QGroupBox *groupBox_Lab_Femur;
    QRadioButton *radioButton_P1;
    QRadioButton *radioButton_P4;
    QCheckBox *checkBox_Lat_Femur;
    QRadioButton *radioButton_P2;
    QRadioButton *radioButton_P5;
    QLabel *label_Lat_Picture_2;
    QRadioButton *radioButton_P3;
    QGroupBox *groupBox_AP_Femur;
    QLabel *label_AP_picture_2;
    QRadioButton *radioButton_A1;
    QRadioButton *radioButton_A2;
    QRadioButton *radioButton_A3;
    QRadioButton *radioButton_A4;
    QRadioButton *radioButton_A5;
    QCheckBox *checkBox_AP_Femur;
    QPushButton *pushButton_Femur_finished;
    QPushButton *pushButton_guide_Femur;
    QLabel *labelResult_Femur;
    QPushButton *pushButton_Femur_finished_2;
    QPushButton *pushButton_Femur_finished_3;
    QWidget *tab_Tibia;
    QGroupBox *groupBox_Lat_Tibia;
    QRadioButton *radioButton_T1;
    QRadioButton *radioButton_T4;
    QRadioButton *radioButton_T6;
    QLabel *label_Lat_Picture_3;
    QRadioButton *radioButton_T2;
    QRadioButton *radioButton_T3;
    QRadioButton *radioButton_T5;
    QCheckBox *checkBox_Lat_Tibia;
    QGroupBox *groupBox_AP_Tibia;
    QLabel *label_AP_picture;
    QRadioButton *radioButton_B1;
    QRadioButton *radioButton_B3;
    QRadioButton *radioButton_B2;
    QRadioButton *radioButton_B4;
    QCheckBox *checkBox_AP_Tibia;
    QPushButton *pushButton_Tibia_finished;
    QPushButton *pushButton_guide_Tibia;
    QLabel *labelResult_Tibia;
    QWidget *tab_simulate;
    QGroupBox *groupBox_ExchangeShowGuide;
    QRadioButton *radioButton_Femur;
    QRadioButton *radioButton_Tibia;
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_moveRobotin;
    QLabel *label_3;
    QPushButton *pushButton_moveRobotin_2;
    QLabel *label_4;
    QPushButton *pushButton_moveRobotin_3;
    QLabel *label_5;
    QPushButton *pushButton_moveRobot;
    QPushButton *pushButton_moveRobotin_4;
    QComboBox *comboBox_CameraIndex;
    QPushButton *pushButton_InitRobot;
    QPushButton *pushButton_SetRobot;
    NaviLabel *label_Navi;
    QWidget *tab_robot;
    QGroupBox *groupBox;
    QPushButton *pushButton_AP_OpenPicture;
    QPushButton *pushButton_AP_CapturePicture;
    QPushButton *pushButton_getXspottransform_AP;
    QPushButton *pushButton_ShowTiptool_AP;
    QPushButton *pushButton_Save_AP;
    QPushButton *pushButton_matching_AP;
    QCheckBox *checkBox_showAP;
    QSlider *horizontalSlider_Femur_AP;
    QSlider *horizontalSlider_Tibia_AP;
    QPushButton *pushButton_mirror_AP;
    QLabel *label;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_Lat_OpenPicture;
    QPushButton *pushButton_Lat_CapturePicture;
    QPushButton *pushButton_getXspottransform_Lat;
    QPushButton *pushButton_ShowTiptool_Lat;
    QPushButton *pushButton_Save_Lat;
    QPushButton *pushButton_matching_Lat;
    QCheckBox *checkBox_showLat;
    QSlider *horizontalSlider_Femur_Lat;
    QSlider *horizontalSlider_Tibia_Lat;
    QLabel *label_2;
    QPushButton *pushButton_mirror_Lat;
    QGraphicsView *graphicsView_AP;
    QGraphicsView *graphicsView_Lat;
    QFrame *frame;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_InitRobot_2;
    QPushButton *pushButton_InitRobot_3;
    QLabel *label_APdata;
    QLabel *label_Latdata;
    QPushButton *pushButtonSetting;
    QGraphicsView *graphicsView_Main;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1920, 1080);
        Widget->setStyleSheet(QLatin1String("QPushButton{\n"
"    color: white;\n"
"	background-color: rgb(53, 63, 75);\n"
"}\n"
"QGroupBox{\n"
"	color: white;\n"
"}\n"
"QLabel{\n"
"	color: white;	\n"
"}"));
        pushButton_Exit = new QPushButton(Widget);
        pushButton_Exit->setObjectName(QStringLiteral("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(1813, 25, 91, 29));
        pushButton_Exit->setStyleSheet(QStringLiteral(""));
        tabWidget_manipulate = new QTabWidget(Widget);
        tabWidget_manipulate->setObjectName(QStringLiteral("tabWidget_manipulate"));
        tabWidget_manipulate->setGeometry(QRect(1600, 99, 311, 851));
        QPalette palette;
        QBrush brush(QColor(40, 70, 90, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        tabWidget_manipulate->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(11);
        tabWidget_manipulate->setFont(font);
        tabWidget_manipulate->setStyleSheet(QString::fromUtf8("QWidget#tab_Femur{\n"
"	border-image: url(:/images/bkg6.png);\n"
"}\n"
"QWidget#tab_Tibia{\n"
"	border-image: url(:/images/bkg6.png);\n"
"}\n"
"QWidget#tab_simulate{\n"
"	border-image: url(:/images/bkg6.png);\n"
"}\n"
"QWidget#tab_robot{\n"
"	border-image: url(:/images/bkg6.png);\n"
"}\n"
"QWidget#tab{\n"
"	font: 22pt \"\346\245\267\344\275\223\";\n"
"}"));
        tabWidget_manipulate->setTabShape(QTabWidget::Triangular);
        tab_Femur = new QWidget();
        tab_Femur->setObjectName(QStringLiteral("tab_Femur"));
        groupBox_Lab_Femur = new QGroupBox(tab_Femur);
        groupBox_Lab_Femur->setObjectName(QStringLiteral("groupBox_Lab_Femur"));
        groupBox_Lab_Femur->setGeometry(QRect(13, 240, 281, 222));
        radioButton_P1 = new QRadioButton(groupBox_Lab_Femur);
        radioButton_P1->setObjectName(QStringLiteral("radioButton_P1"));
        radioButton_P1->setGeometry(QRect(130, 70, 51, 17));
        QPalette palette1;
        QBrush brush2(QColor(0, 170, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_P1->setPalette(palette1);
        radioButton_P1->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_P4 = new QRadioButton(groupBox_Lab_Femur);
        radioButton_P4->setObjectName(QStringLiteral("radioButton_P4"));
        radioButton_P4->setGeometry(QRect(112, 122, 41, 17));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_P4->setPalette(palette2);
        radioButton_P4->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        checkBox_Lat_Femur = new QCheckBox(groupBox_Lab_Femur);
        checkBox_Lat_Femur->setObjectName(QStringLiteral("checkBox_Lat_Femur"));
        checkBox_Lat_Femur->setGeometry(QRect(20, 190, 111, 17));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        checkBox_Lat_Femur->setPalette(palette3);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font1.setPointSize(10);
        checkBox_Lat_Femur->setFont(font1);
        checkBox_Lat_Femur->setChecked(true);
        radioButton_P2 = new QRadioButton(groupBox_Lab_Femur);
        radioButton_P2->setObjectName(QStringLiteral("radioButton_P2"));
        radioButton_P2->setGeometry(QRect(100, 150, 41, 17));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_P2->setPalette(palette4);
        radioButton_P2->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_P5 = new QRadioButton(groupBox_Lab_Femur);
        radioButton_P5->setObjectName(QStringLiteral("radioButton_P5"));
        radioButton_P5->setGeometry(QRect(80, 60, 41, 17));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_P5->setPalette(palette5);
        radioButton_P5->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        label_Lat_Picture_2 = new QLabel(groupBox_Lab_Femur);
        label_Lat_Picture_2->setObjectName(QStringLiteral("label_Lat_Picture_2"));
        label_Lat_Picture_2->setGeometry(QRect(0, 0, 282, 222));
        label_Lat_Picture_2->setStyleSheet(QStringLiteral("border-image: url(:/images/ceweiB.png);"));
        radioButton_P3 = new QRadioButton(groupBox_Lab_Femur);
        radioButton_P3->setObjectName(QStringLiteral("radioButton_P3"));
        radioButton_P3->setGeometry(QRect(160, 120, 41, 17));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_P3->setPalette(palette6);
        radioButton_P3->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        label_Lat_Picture_2->raise();
        radioButton_P1->raise();
        radioButton_P4->raise();
        checkBox_Lat_Femur->raise();
        radioButton_P2->raise();
        radioButton_P5->raise();
        radioButton_P3->raise();
        groupBox_AP_Femur = new QGroupBox(tab_Femur);
        groupBox_AP_Femur->setObjectName(QStringLiteral("groupBox_AP_Femur"));
        groupBox_AP_Femur->setGeometry(QRect(13, 10, 282, 222));
        label_AP_picture_2 = new QLabel(groupBox_AP_Femur);
        label_AP_picture_2->setObjectName(QStringLiteral("label_AP_picture_2"));
        label_AP_picture_2->setGeometry(QRect(0, 0, 291, 222));
        label_AP_picture_2->setStyleSheet(QStringLiteral("border-image: url(:/images/zhengweiA.png);"));
        radioButton_A1 = new QRadioButton(groupBox_AP_Femur);
        radioButton_A1->setObjectName(QStringLiteral("radioButton_A1"));
        radioButton_A1->setGeometry(QRect(60, 110, 41, 17));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_A1->setPalette(palette7);
        radioButton_A1->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_A2 = new QRadioButton(groupBox_AP_Femur);
        radioButton_A2->setObjectName(QStringLiteral("radioButton_A2"));
        radioButton_A2->setGeometry(QRect(180, 110, 51, 17));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_A2->setPalette(palette8);
        radioButton_A2->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_A3 = new QRadioButton(groupBox_AP_Femur);
        radioButton_A3->setObjectName(QStringLiteral("radioButton_A3"));
        radioButton_A3->setGeometry(QRect(113, 93, 41, 17));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_A3->setPalette(palette9);
        radioButton_A3->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_A4 = new QRadioButton(groupBox_AP_Femur);
        radioButton_A4->setObjectName(QStringLiteral("radioButton_A4"));
        radioButton_A4->setGeometry(QRect(130, 110, 51, 17));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_A4->setPalette(palette10);
        radioButton_A4->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_A5 = new QRadioButton(groupBox_AP_Femur);
        radioButton_A5->setObjectName(QStringLiteral("radioButton_A5"));
        radioButton_A5->setGeometry(QRect(170, 50, 51, 17));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_A5->setPalette(palette11);
        radioButton_A5->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        checkBox_AP_Femur = new QCheckBox(groupBox_AP_Femur);
        checkBox_AP_Femur->setObjectName(QStringLiteral("checkBox_AP_Femur"));
        checkBox_AP_Femur->setGeometry(QRect(20, 190, 111, 17));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        checkBox_AP_Femur->setPalette(palette12);
        checkBox_AP_Femur->setFont(font1);
        checkBox_AP_Femur->setChecked(true);
        pushButton_Femur_finished = new QPushButton(tab_Femur);
        pushButton_Femur_finished->setObjectName(QStringLiteral("pushButton_Femur_finished"));
        pushButton_Femur_finished->setGeometry(QRect(160, 760, 111, 41));
        pushButton_Femur_finished->setStyleSheet(QStringLiteral(""));
        pushButton_guide_Femur = new QPushButton(tab_Femur);
        pushButton_guide_Femur->setObjectName(QStringLiteral("pushButton_guide_Femur"));
        pushButton_guide_Femur->setGeometry(QRect(20, 760, 101, 41));
        pushButton_guide_Femur->setStyleSheet(QStringLiteral(""));
        labelResult_Femur = new QLabel(tab_Femur);
        labelResult_Femur->setObjectName(QStringLiteral("labelResult_Femur"));
        labelResult_Femur->setGeometry(QRect(30, 500, 250, 221));
        labelResult_Femur->setStyleSheet(QLatin1String("border-image: url(:/images/bkg41.png);\n"
"color: rgb(255, 255, 255);"));
        labelResult_Femur->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelResult_Femur->setWordWrap(true);
        pushButton_Femur_finished_2 = new QPushButton(tab_Femur);
        pushButton_Femur_finished_2->setObjectName(QStringLiteral("pushButton_Femur_finished_2"));
        pushButton_Femur_finished_2->setGeometry(QRect(160, 720, 111, 41));
        pushButton_Femur_finished_2->setStyleSheet(QStringLiteral(""));
        pushButton_Femur_finished_3 = new QPushButton(tab_Femur);
        pushButton_Femur_finished_3->setObjectName(QStringLiteral("pushButton_Femur_finished_3"));
        pushButton_Femur_finished_3->setGeometry(QRect(20, 720, 101, 41));
        pushButton_Femur_finished_3->setStyleSheet(QStringLiteral(""));
        tabWidget_manipulate->addTab(tab_Femur, QString());
        tab_Tibia = new QWidget();
        tab_Tibia->setObjectName(QStringLiteral("tab_Tibia"));
        groupBox_Lat_Tibia = new QGroupBox(tab_Tibia);
        groupBox_Lat_Tibia->setObjectName(QStringLiteral("groupBox_Lat_Tibia"));
        groupBox_Lat_Tibia->setGeometry(QRect(13, 240, 282, 222));
        radioButton_T1 = new QRadioButton(groupBox_Lat_Tibia);
        radioButton_T1->setObjectName(QStringLiteral("radioButton_T1"));
        radioButton_T1->setGeometry(QRect(140, 170, 82, 17));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_T1->setPalette(palette13);
        radioButton_T1->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_T4 = new QRadioButton(groupBox_Lat_Tibia);
        radioButton_T4->setObjectName(QStringLiteral("radioButton_T4"));
        radioButton_T4->setGeometry(QRect(180, 180, 82, 17));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_T4->setPalette(palette14);
        radioButton_T4->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_T6 = new QRadioButton(groupBox_Lat_Tibia);
        radioButton_T6->setObjectName(QStringLiteral("radioButton_T6"));
        radioButton_T6->setGeometry(QRect(240, 120, 71, 20));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_T6->setPalette(palette15);
        radioButton_T6->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        label_Lat_Picture_3 = new QLabel(groupBox_Lat_Tibia);
        label_Lat_Picture_3->setObjectName(QStringLiteral("label_Lat_Picture_3"));
        label_Lat_Picture_3->setGeometry(QRect(0, 0, 281, 222));
        label_Lat_Picture_3->setStyleSheet(QStringLiteral("border-image: url(:/images/ceweiB.png);"));
        radioButton_T2 = new QRadioButton(groupBox_Lat_Tibia);
        radioButton_T2->setObjectName(QStringLiteral("radioButton_T2"));
        radioButton_T2->setGeometry(QRect(160, 90, 82, 17));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_T2->setPalette(palette16);
        radioButton_T2->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_T3 = new QRadioButton(groupBox_Lat_Tibia);
        radioButton_T3->setObjectName(QStringLiteral("radioButton_T3"));
        radioButton_T3->setGeometry(QRect(210, 100, 82, 17));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_T3->setPalette(palette17);
        radioButton_T3->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_T5 = new QRadioButton(groupBox_Lat_Tibia);
        radioButton_T5->setObjectName(QStringLiteral("radioButton_T5"));
        radioButton_T5->setGeometry(QRect(150, 120, 82, 17));
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette18.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette18.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_T5->setPalette(palette18);
        radioButton_T5->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        checkBox_Lat_Tibia = new QCheckBox(groupBox_Lat_Tibia);
        checkBox_Lat_Tibia->setObjectName(QStringLiteral("checkBox_Lat_Tibia"));
        checkBox_Lat_Tibia->setGeometry(QRect(20, 190, 111, 17));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette19.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        checkBox_Lat_Tibia->setPalette(palette19);
        checkBox_Lat_Tibia->setFont(font1);
        checkBox_Lat_Tibia->setChecked(true);
        label_Lat_Picture_3->raise();
        radioButton_T1->raise();
        radioButton_T4->raise();
        radioButton_T6->raise();
        radioButton_T2->raise();
        radioButton_T3->raise();
        radioButton_T5->raise();
        checkBox_Lat_Tibia->raise();
        groupBox_AP_Tibia = new QGroupBox(tab_Tibia);
        groupBox_AP_Tibia->setObjectName(QStringLiteral("groupBox_AP_Tibia"));
        groupBox_AP_Tibia->setGeometry(QRect(13, 10, 282, 222));
        label_AP_picture = new QLabel(groupBox_AP_Tibia);
        label_AP_picture->setObjectName(QStringLiteral("label_AP_picture"));
        label_AP_picture->setGeometry(QRect(0, 0, 291, 222));
        label_AP_picture->setStyleSheet(QStringLiteral("border-image: url(:/images/zhengweiA.png);"));
        radioButton_B1 = new QRadioButton(groupBox_AP_Tibia);
        radioButton_B1->setObjectName(QStringLiteral("radioButton_B1"));
        radioButton_B1->setGeometry(QRect(10, 110, 82, 17));
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette20.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette20.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_B1->setPalette(palette20);
        radioButton_B1->setLayoutDirection(Qt::RightToLeft);
        radioButton_B1->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_B3 = new QRadioButton(groupBox_AP_Tibia);
        radioButton_B3->setObjectName(QStringLiteral("radioButton_B3"));
        radioButton_B3->setGeometry(QRect(130, 110, 82, 17));
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette21.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette21.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_B3->setPalette(palette21);
        radioButton_B3->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_B2 = new QRadioButton(groupBox_AP_Tibia);
        radioButton_B2->setObjectName(QStringLiteral("radioButton_B2"));
        radioButton_B2->setGeometry(QRect(190, 110, 82, 17));
        QPalette palette22;
        palette22.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette22.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette22.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_B2->setPalette(palette22);
        radioButton_B2->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        radioButton_B4 = new QRadioButton(groupBox_AP_Tibia);
        radioButton_B4->setObjectName(QStringLiteral("radioButton_B4"));
        radioButton_B4->setGeometry(QRect(100, 180, 82, 17));
        QPalette palette23;
        palette23.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette23.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette23.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        radioButton_B4->setPalette(palette23);
        radioButton_B4->setStyleSheet(QStringLiteral("font: 14pt \"Adobe Arabic\";"));
        checkBox_AP_Tibia = new QCheckBox(groupBox_AP_Tibia);
        checkBox_AP_Tibia->setObjectName(QStringLiteral("checkBox_AP_Tibia"));
        checkBox_AP_Tibia->setGeometry(QRect(20, 190, 111, 17));
        QPalette palette24;
        palette24.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette24.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette24.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        checkBox_AP_Tibia->setPalette(palette24);
        checkBox_AP_Tibia->setFont(font1);
        checkBox_AP_Tibia->setChecked(true);
        pushButton_Tibia_finished = new QPushButton(tab_Tibia);
        pushButton_Tibia_finished->setObjectName(QStringLiteral("pushButton_Tibia_finished"));
        pushButton_Tibia_finished->setGeometry(QRect(170, 760, 111, 41));
        pushButton_Tibia_finished->setStyleSheet(QStringLiteral(""));
        pushButton_guide_Tibia = new QPushButton(tab_Tibia);
        pushButton_guide_Tibia->setObjectName(QStringLiteral("pushButton_guide_Tibia"));
        pushButton_guide_Tibia->setGeometry(QRect(20, 760, 101, 41));
        pushButton_guide_Tibia->setStyleSheet(QStringLiteral(""));
        labelResult_Tibia = new QLabel(tab_Tibia);
        labelResult_Tibia->setObjectName(QStringLiteral("labelResult_Tibia"));
        labelResult_Tibia->setGeometry(QRect(30, 500, 250, 221));
        labelResult_Tibia->setStyleSheet(QLatin1String("border-image: url(:/images/bkg41.png);\n"
"color: rgb(255, 255, 255);"));
        labelResult_Tibia->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelResult_Tibia->setWordWrap(true);
        tabWidget_manipulate->addTab(tab_Tibia, QString());
        tab_simulate = new QWidget();
        tab_simulate->setObjectName(QStringLiteral("tab_simulate"));
        groupBox_ExchangeShowGuide = new QGroupBox(tab_simulate);
        groupBox_ExchangeShowGuide->setObjectName(QStringLiteral("groupBox_ExchangeShowGuide"));
        groupBox_ExchangeShowGuide->setGeometry(QRect(40, 70, 231, 91));
        radioButton_Femur = new QRadioButton(groupBox_ExchangeShowGuide);
        radioButton_Femur->setObjectName(QStringLiteral("radioButton_Femur"));
        radioButton_Femur->setGeometry(QRect(10, 40, 117, 21));
        radioButton_Tibia = new QRadioButton(groupBox_ExchangeShowGuide);
        radioButton_Tibia->setObjectName(QStringLiteral("radioButton_Tibia"));
        radioButton_Tibia->setGeometry(QRect(10, 60, 117, 21));
        pushButton = new QPushButton(tab_simulate);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 20, 121, 31));
        groupBox_3 = new QGroupBox(tab_simulate);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(40, 270, 231, 271));
        pushButton_moveRobotin = new QPushButton(groupBox_3);
        pushButton_moveRobotin->setObjectName(QStringLiteral("pushButton_moveRobotin"));
        pushButton_moveRobotin->setGeometry(QRect(10, 80, 101, 31));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 84, 101, 21));
        pushButton_moveRobotin_2 = new QPushButton(groupBox_3);
        pushButton_moveRobotin_2->setObjectName(QStringLiteral("pushButton_moveRobotin_2"));
        pushButton_moveRobotin_2->setGeometry(QRect(10, 120, 101, 31));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(120, 130, 101, 21));
        pushButton_moveRobotin_3 = new QPushButton(groupBox_3);
        pushButton_moveRobotin_3->setObjectName(QStringLiteral("pushButton_moveRobotin_3"));
        pushButton_moveRobotin_3->setGeometry(QRect(10, 170, 101, 31));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(120, 160, 111, 61));
        pushButton_moveRobot = new QPushButton(groupBox_3);
        pushButton_moveRobot->setObjectName(QStringLiteral("pushButton_moveRobot"));
        pushButton_moveRobot->setGeometry(QRect(10, 40, 101, 31));
        pushButton_moveRobotin_4 = new QPushButton(groupBox_3);
        pushButton_moveRobotin_4->setObjectName(QStringLiteral("pushButton_moveRobotin_4"));
        pushButton_moveRobotin_4->setGeometry(QRect(10, 220, 101, 31));
        comboBox_CameraIndex = new QComboBox(tab_simulate);
        comboBox_CameraIndex->setObjectName(QStringLiteral("comboBox_CameraIndex"));
        comboBox_CameraIndex->setGeometry(QRect(190, 20, 81, 31));
        comboBox_CameraIndex->setStyleSheet(QStringLiteral("border-image: url(:/images/bkg_text.png);"));
        pushButton_InitRobot = new QPushButton(tab_simulate);
        pushButton_InitRobot->setObjectName(QStringLiteral("pushButton_InitRobot"));
        pushButton_InitRobot->setGeometry(QRect(170, 180, 101, 31));
        pushButton_SetRobot = new QPushButton(tab_simulate);
        pushButton_SetRobot->setObjectName(QStringLiteral("pushButton_SetRobot"));
        pushButton_SetRobot->setGeometry(QRect(50, 180, 101, 31));
        label_Navi = new NaviLabel(tab_simulate);
        label_Navi->setObjectName(QStringLiteral("label_Navi"));
        label_Navi->setGeometry(QRect(30, 560, 250, 250));
        label_Navi->setStyleSheet(QStringLiteral("border-image: url(:/Resources/rr.png);"));
        label_Navi->setFrameShape(QFrame::StyledPanel);
        tabWidget_manipulate->addTab(tab_simulate, QString());
        tab_robot = new QWidget();
        tab_robot->setObjectName(QStringLiteral("tab_robot"));
        tabWidget_manipulate->addTab(tab_robot, QString());
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 870, 731, 111));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\344\270\255\345\256\213"));
        font2.setPointSize(12);
        groupBox->setFont(font2);
        pushButton_AP_OpenPicture = new QPushButton(groupBox);
        pushButton_AP_OpenPicture->setObjectName(QStringLiteral("pushButton_AP_OpenPicture"));
        pushButton_AP_OpenPicture->setGeometry(QRect(10, 30, 71, 30));
        pushButton_AP_OpenPicture->setStyleSheet(QStringLiteral(""));
        pushButton_AP_CapturePicture = new QPushButton(groupBox);
        pushButton_AP_CapturePicture->setObjectName(QStringLiteral("pushButton_AP_CapturePicture"));
        pushButton_AP_CapturePicture->setGeometry(QRect(10, 70, 71, 30));
        pushButton_AP_CapturePicture->setStyleSheet(QStringLiteral(""));
        pushButton_getXspottransform_AP = new QPushButton(groupBox);
        pushButton_getXspottransform_AP->setObjectName(QStringLiteral("pushButton_getXspottransform_AP"));
        pushButton_getXspottransform_AP->setGeometry(QRect(160, 30, 71, 31));
        pushButton_getXspottransform_AP->setStyleSheet(QStringLiteral(""));
        pushButton_ShowTiptool_AP = new QPushButton(groupBox);
        pushButton_ShowTiptool_AP->setObjectName(QStringLiteral("pushButton_ShowTiptool_AP"));
        pushButton_ShowTiptool_AP->setGeometry(QRect(160, 70, 71, 31));
        pushButton_ShowTiptool_AP->setStyleSheet(QStringLiteral(""));
        pushButton_Save_AP = new QPushButton(groupBox);
        pushButton_Save_AP->setObjectName(QStringLiteral("pushButton_Save_AP"));
        pushButton_Save_AP->setGeometry(QRect(250, 30, 71, 31));
        pushButton_Save_AP->setStyleSheet(QStringLiteral(""));
        pushButton_matching_AP = new QPushButton(groupBox);
        pushButton_matching_AP->setObjectName(QStringLiteral("pushButton_matching_AP"));
        pushButton_matching_AP->setGeometry(QRect(470, 30, 71, 31));
        checkBox_showAP = new QCheckBox(groupBox);
        checkBox_showAP->setObjectName(QStringLiteral("checkBox_showAP"));
        checkBox_showAP->setEnabled(false);
        checkBox_showAP->setGeometry(QRect(650, 40, 61, 21));
        checkBox_showAP->setMouseTracking(true);
        checkBox_showAP->setChecked(true);
        horizontalSlider_Femur_AP = new QSlider(groupBox);
        horizontalSlider_Femur_AP->setObjectName(QStringLiteral("horizontalSlider_Femur_AP"));
        horizontalSlider_Femur_AP->setGeometry(QRect(470, 70, 171, 20));
        horizontalSlider_Femur_AP->setStyleSheet(QLatin1String("\n"
"         QSlider::add-page:Horizontal\n"
"         {    \n"
"            background-color: rgb(87, 97, 106);\n"
"            height:4px;\n"
"         }\n"
"         QSlider::sub-page:Horizontal \n"
"        {\n"
"            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\n"
"            height:4px;\n"
"         }\n"
"        QSlider::groove:Horizontal\n"
"        {\n"
"            background:transparent;\n"
"            height:6px;\n"
"        }\n"
"        QSlider::handle:Horizontal \n"
"        {\n"
"            height: 20px;\n"
"            width:20px;\n"
"            border-image: url(:/images/whitecircle.png);\n"
"            margin: -8 0px; \n"
"        }"));
        horizontalSlider_Femur_AP->setOrientation(Qt::Horizontal);
        horizontalSlider_Tibia_AP = new QSlider(groupBox);
        horizontalSlider_Tibia_AP->setObjectName(QStringLiteral("horizontalSlider_Tibia_AP"));
        horizontalSlider_Tibia_AP->setGeometry(QRect(470, 90, 171, 20));
        horizontalSlider_Tibia_AP->setStyleSheet(QLatin1String("\n"
"         QSlider::add-page:Horizontal\n"
"         {    \n"
"            background-color: rgb(87, 97, 106);\n"
"            height:4px;\n"
"         }\n"
"         QSlider::sub-page:Horizontal \n"
"        {\n"
"            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\n"
"            height:4px;\n"
"         }\n"
"        QSlider::groove:Horizontal\n"
"        {\n"
"            background:transparent;\n"
"            height:6px;\n"
"        }\n"
"        QSlider::handle:Horizontal \n"
"        {\n"
"            height: 20px;\n"
"            width:20px;\n"
"            border-image: url(:/images/whitecircle.png);\n"
"            margin: -8 0px; \n"
"        }"));
        horizontalSlider_Tibia_AP->setOrientation(Qt::Horizontal);
        pushButton_mirror_AP = new QPushButton(groupBox);
        pushButton_mirror_AP->setObjectName(QStringLiteral("pushButton_mirror_AP"));
        pushButton_mirror_AP->setGeometry(QRect(560, 30, 71, 31));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(650, 70, 71, 21));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(810, 870, 731, 111));
        groupBox_2->setFont(font2);
        pushButton_Lat_OpenPicture = new QPushButton(groupBox_2);
        pushButton_Lat_OpenPicture->setObjectName(QStringLiteral("pushButton_Lat_OpenPicture"));
        pushButton_Lat_OpenPicture->setGeometry(QRect(20, 30, 71, 30));
        pushButton_Lat_OpenPicture->setStyleSheet(QStringLiteral(""));
        pushButton_Lat_CapturePicture = new QPushButton(groupBox_2);
        pushButton_Lat_CapturePicture->setObjectName(QStringLiteral("pushButton_Lat_CapturePicture"));
        pushButton_Lat_CapturePicture->setGeometry(QRect(20, 70, 71, 30));
        pushButton_Lat_CapturePicture->setStyleSheet(QStringLiteral(""));
        pushButton_getXspottransform_Lat = new QPushButton(groupBox_2);
        pushButton_getXspottransform_Lat->setObjectName(QStringLiteral("pushButton_getXspottransform_Lat"));
        pushButton_getXspottransform_Lat->setGeometry(QRect(170, 30, 71, 31));
        pushButton_getXspottransform_Lat->setStyleSheet(QStringLiteral(""));
        pushButton_ShowTiptool_Lat = new QPushButton(groupBox_2);
        pushButton_ShowTiptool_Lat->setObjectName(QStringLiteral("pushButton_ShowTiptool_Lat"));
        pushButton_ShowTiptool_Lat->setGeometry(QRect(170, 70, 71, 31));
        pushButton_ShowTiptool_Lat->setStyleSheet(QStringLiteral(""));
        pushButton_Save_Lat = new QPushButton(groupBox_2);
        pushButton_Save_Lat->setObjectName(QStringLiteral("pushButton_Save_Lat"));
        pushButton_Save_Lat->setGeometry(QRect(250, 30, 71, 31));
        pushButton_Save_Lat->setStyleSheet(QStringLiteral(""));
        pushButton_matching_Lat = new QPushButton(groupBox_2);
        pushButton_matching_Lat->setObjectName(QStringLiteral("pushButton_matching_Lat"));
        pushButton_matching_Lat->setGeometry(QRect(470, 30, 71, 31));
        checkBox_showLat = new QCheckBox(groupBox_2);
        checkBox_showLat->setObjectName(QStringLiteral("checkBox_showLat"));
        checkBox_showLat->setEnabled(false);
        checkBox_showLat->setGeometry(QRect(650, 40, 93, 21));
        checkBox_showLat->setChecked(true);
        horizontalSlider_Femur_Lat = new QSlider(groupBox_2);
        horizontalSlider_Femur_Lat->setObjectName(QStringLiteral("horizontalSlider_Femur_Lat"));
        horizontalSlider_Femur_Lat->setGeometry(QRect(470, 70, 171, 20));
        horizontalSlider_Femur_Lat->setStyleSheet(QLatin1String("\n"
"         QSlider::add-page:Horizontal\n"
"         {    \n"
"            background-color: rgb(87, 97, 106);\n"
"            height:4px;\n"
"         }\n"
"         QSlider::sub-page:Horizontal \n"
"        {\n"
"            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\n"
"            height:4px;\n"
"         }\n"
"        QSlider::groove:Horizontal\n"
"        {\n"
"            background:transparent;\n"
"            height:6px;\n"
"        }\n"
"        QSlider::handle:Horizontal \n"
"        {\n"
"            height: 20px;\n"
"            width:20px;\n"
"            border-image: url(:/images/whitecircle.png);\n"
"            margin: -8 0px; \n"
"        }"));
        horizontalSlider_Femur_Lat->setOrientation(Qt::Horizontal);
        horizontalSlider_Tibia_Lat = new QSlider(groupBox_2);
        horizontalSlider_Tibia_Lat->setObjectName(QStringLiteral("horizontalSlider_Tibia_Lat"));
        horizontalSlider_Tibia_Lat->setGeometry(QRect(470, 90, 171, 20));
        horizontalSlider_Tibia_Lat->setStyleSheet(QLatin1String("\n"
"         QSlider::add-page:Horizontal\n"
"         {    \n"
"            background-color: rgb(87, 97, 106);\n"
"            height:4px;\n"
"         }\n"
"         QSlider::sub-page:Horizontal \n"
"        {\n"
"            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\n"
"            height:4px;\n"
"         }\n"
"        QSlider::groove:Horizontal\n"
"        {\n"
"            background:transparent;\n"
"            height:6px;\n"
"        }\n"
"        QSlider::handle:Horizontal \n"
"        {\n"
"            height: 20px;\n"
"            width:20px;\n"
"            border-image: url(:/images/whitecircle.png);\n"
"            margin: -8 0px; \n"
"        }"));
        horizontalSlider_Tibia_Lat->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(650, 70, 71, 21));
        pushButton_mirror_Lat = new QPushButton(groupBox_2);
        pushButton_mirror_Lat->setObjectName(QStringLiteral("pushButton_mirror_Lat"));
        pushButton_mirror_Lat->setGeometry(QRect(560, 30, 71, 31));
        graphicsView_AP = new QGraphicsView(Widget);
        graphicsView_AP->setObjectName(QStringLiteral("graphicsView_AP"));
        graphicsView_AP->setGeometry(QRect(30, 110, 750, 750));
        graphicsView_AP->setStyleSheet(QStringLiteral("border-image: url(:/images/bkg41.png);"));
        graphicsView_Lat = new QGraphicsView(Widget);
        graphicsView_Lat->setObjectName(QStringLiteral("graphicsView_Lat"));
        graphicsView_Lat->setGeometry(QRect(810, 110, 750, 750));
        graphicsView_Lat->setStyleSheet(QStringLiteral("border-image: url(:/images/bkg41.png);"));
        frame = new QFrame(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 1920, 1080));
        frame->setStyleSheet(QString::fromUtf8("QFrame#frame{\n"
"	\n"
"	border-image: url(:/images/bkg - \345\211\257\346\234\254.png);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1740, 990, 101, 51));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(1620, 990, 101, 51));
        pushButton_InitRobot_2 = new QPushButton(frame);
        pushButton_InitRobot_2->setObjectName(QStringLiteral("pushButton_InitRobot_2"));
        pushButton_InitRobot_2->setGeometry(QRect(1620, 960, 101, 31));
        pushButton_InitRobot_3 = new QPushButton(frame);
        pushButton_InitRobot_3->setObjectName(QStringLiteral("pushButton_InitRobot_3"));
        pushButton_InitRobot_3->setGeometry(QRect(1740, 960, 101, 31));
        pushButton_2->raise();
        pushButton_3->raise();
        tabWidget_manipulate->raise();
        pushButton_InitRobot_2->raise();
        pushButton_InitRobot_3->raise();
        label_APdata = new QLabel(Widget);
        label_APdata->setObjectName(QStringLiteral("label_APdata"));
        label_APdata->setGeometry(QRect(470, 760, 300, 100));
        label_APdata->setStyleSheet(QLatin1String("background:transparent;\n"
"color: rgb(255, 255, 255);"));
        label_APdata->setAlignment(Qt::AlignJustify|Qt::AlignTop);
        label_Latdata = new QLabel(Widget);
        label_Latdata->setObjectName(QStringLiteral("label_Latdata"));
        label_Latdata->setGeometry(QRect(1260, 760, 300, 100));
        label_Latdata->setStyleSheet(QLatin1String("background:transparent;\n"
"color: rgb(255, 255, 255);"));
        label_Latdata->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        pushButtonSetting = new QPushButton(Widget);
        pushButtonSetting->setObjectName(QStringLiteral("pushButtonSetting"));
        pushButtonSetting->setGeometry(QRect(1850, 990, 61, 51));
        pushButtonSetting->setStyleSheet(QStringLiteral(""));
        graphicsView_Main = new QGraphicsView(Widget);
        graphicsView_Main->setObjectName(QStringLiteral("graphicsView_Main"));
        graphicsView_Main->setGeometry(QRect(110, 110, 900, 900));
        graphicsView_Main->setStyleSheet(QStringLiteral("border-image: url(:/images/bkg41.png);"));
        frame->raise();
        graphicsView_Main->raise();
        pushButton_Exit->raise();
        tabWidget_manipulate->raise();
        groupBox_2->raise();
        graphicsView_Lat->raise();
        graphicsView_AP->raise();
        groupBox->raise();
        label_APdata->raise();
        label_Latdata->raise();
        pushButtonSetting->raise();

        retranslateUi(Widget);

        tabWidget_manipulate->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        pushButton_Exit->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", 0));
        groupBox_Lab_Femur->setTitle(QApplication::translate("Widget", "GroupBox", 0));
        radioButton_P1->setText(QApplication::translate("Widget", "P1", 0));
        radioButton_P4->setText(QApplication::translate("Widget", "P4", 0));
        checkBox_Lat_Femur->setText(QApplication::translate("Widget", "\344\276\247\344\275\215\350\247\204\345\210\222\350\267\257\347\273\217", 0));
        radioButton_P2->setText(QApplication::translate("Widget", "P2", 0));
        radioButton_P5->setText(QApplication::translate("Widget", "P5", 0));
        label_Lat_Picture_2->setText(QString());
        radioButton_P3->setText(QApplication::translate("Widget", "P3", 0));
        groupBox_AP_Femur->setTitle(QApplication::translate("Widget", "GroupBox", 0));
        label_AP_picture_2->setText(QString());
        radioButton_A1->setText(QApplication::translate("Widget", "A1", 0));
        radioButton_A2->setText(QApplication::translate("Widget", "A2", 0));
        radioButton_A3->setText(QApplication::translate("Widget", "A3", 0));
        radioButton_A4->setText(QApplication::translate("Widget", "A4", 0));
        radioButton_A5->setText(QApplication::translate("Widget", "A5", 0));
        checkBox_AP_Femur->setText(QApplication::translate("Widget", "\346\255\243\344\275\215\350\247\204\345\210\222\350\267\257\347\273\217", 0));
        pushButton_Femur_finished->setText(QApplication::translate("Widget", "\350\247\204\345\210\222\345\256\214\346\210\220", 0));
        pushButton_guide_Femur->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\345\257\274\350\210\252", 0));
        labelResult_Femur->setText(QString());
        pushButton_Femur_finished_2->setText(QApplication::translate("Widget", "\351\222\210\345\255\224\347\233\264\347\272\277\346\265\213\350\257\225", 0));
        pushButton_Femur_finished_3->setText(QApplication::translate("Widget", "\351\222\210\345\255\224\346\225\260\346\215\256\351\207\207\351\233\206", 0));
        tabWidget_manipulate->setTabText(tabWidget_manipulate->indexOf(tab_Femur), QApplication::translate("Widget", "\350\202\241\351\252\250", 0));
        groupBox_Lat_Tibia->setTitle(QApplication::translate("Widget", "GroupBox", 0));
        radioButton_T1->setText(QApplication::translate("Widget", "T1", 0));
        radioButton_T4->setText(QApplication::translate("Widget", "T4", 0));
        radioButton_T6->setText(QApplication::translate("Widget", "T6", 0));
        label_Lat_Picture_3->setText(QString());
        radioButton_T2->setText(QApplication::translate("Widget", "T2", 0));
        radioButton_T3->setText(QApplication::translate("Widget", "T3", 0));
        radioButton_T5->setText(QApplication::translate("Widget", "T5", 0));
        checkBox_Lat_Tibia->setText(QApplication::translate("Widget", "\344\276\247\344\275\215\350\247\204\345\210\222\350\267\257\347\273\217", 0));
        groupBox_AP_Tibia->setTitle(QApplication::translate("Widget", "GroupBox", 0));
        label_AP_picture->setText(QString());
        radioButton_B1->setText(QApplication::translate("Widget", "B1", 0));
        radioButton_B3->setText(QApplication::translate("Widget", "B3", 0));
        radioButton_B2->setText(QApplication::translate("Widget", "B2", 0));
        radioButton_B4->setText(QApplication::translate("Widget", "B4", 0));
        checkBox_AP_Tibia->setText(QApplication::translate("Widget", "\346\255\243\344\275\215\350\247\204\345\210\222\350\267\257\347\273\217", 0));
        pushButton_Tibia_finished->setText(QApplication::translate("Widget", "\350\247\204\345\210\222\345\256\214\346\210\220", 0));
        pushButton_guide_Tibia->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\345\257\274\350\210\252", 0));
        labelResult_Tibia->setText(QString());
        tabWidget_manipulate->setTabText(tabWidget_manipulate->indexOf(tab_Tibia), QApplication::translate("Widget", "\350\203\253\351\252\250", 0));
        groupBox_ExchangeShowGuide->setTitle(QApplication::translate("Widget", "\345\210\207\346\215\242\345\257\274\350\210\252\345\257\271\350\261\241", 0));
        radioButton_Femur->setText(QApplication::translate("Widget", "   \350\202\241\351\252\250", 0));
        radioButton_Tibia->setText(QApplication::translate("Widget", "   \350\203\253\351\252\250", 0));
        pushButton->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\345\205\263\350\212\202\351\225\234", 0));
        groupBox_3->setTitle(QApplication::translate("Widget", "\346\234\272\345\231\250\344\272\272\350\277\220\345\212\250", 0));
        pushButton_moveRobotin->setText(QApplication::translate("Widget", "\347\247\273\345\212\250\350\207\263\350\267\257\345\276\204", 0));
        label_3->setText(QApplication::translate("Widget", "\357\274\210\351\225\277\346\214\211\350\207\263\345\201\234\346\255\242\357\274\211", 0));
        pushButton_moveRobotin_2->setText(QApplication::translate("Widget", "\345\205\245\351\222\211", 0));
        label_4->setText(QApplication::translate("Widget", "\357\274\210\351\225\277\346\214\211\350\207\263\345\201\234\346\255\242\357\274\211", 0));
        pushButton_moveRobotin_3->setText(QApplication::translate("Widget", "\345\207\272\351\222\211", 0));
        label_5->setText(QApplication::translate("Widget", "\357\274\210\351\225\277\346\214\211\350\207\263\345\201\234\346\255\242\357\274\211\n"
"\345\217\257\345\244\232\346\254\241\347\202\271\345\207\273\345\220\216\351\200\200", 0));
        pushButton_moveRobot->setText(QApplication::translate("Widget", "\347\247\273\345\212\250\346\234\272\345\231\250\344\272\272", 0));
        pushButton_moveRobotin_4->setText(QApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\344\275\215\345\247\277", 0));
        pushButton_InitRobot->setText(QApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\346\234\272\345\231\250\344\272\272", 0));
        pushButton_SetRobot->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\346\234\272\345\231\250\344\272\272", 0));
        label_Navi->setText(QString());
        tabWidget_manipulate->setTabText(tabWidget_manipulate->indexOf(tab_simulate), QApplication::translate("Widget", "\344\273\277\347\234\237", 0));
        tabWidget_manipulate->setTabText(tabWidget_manipulate->indexOf(tab_robot), QApplication::translate("Widget", "\346\234\272\345\231\250\344\272\272", 0));
        groupBox->setTitle(QApplication::translate("Widget", "\346\255\243\344\275\215\346\223\215\344\275\234", 0));
        pushButton_AP_OpenPicture->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        pushButton_AP_CapturePicture->setText(QApplication::translate("Widget", "\351\207\207\351\233\206\345\233\276\347\211\207", 0));
        pushButton_getXspottransform_AP->setText(QApplication::translate("Widget", "\351\207\207\351\233\206NDI", 0));
        pushButton_ShowTiptool_AP->setText(QApplication::translate("Widget", "\346\230\276\347\244\272\346\216\242\351\222\210", 0));
        pushButton_Save_AP->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        pushButton_matching_AP->setText(QApplication::translate("Widget", "\351\205\215\345\207\206", 0));
        checkBox_showAP->setText(QApplication::translate("Widget", "\346\230\276\347\244\272", 0));
        pushButton_mirror_AP->setText(QApplication::translate("Widget", "\347\277\273\350\275\254", 0));
        label->setText(QApplication::translate("Widget", "\351\200\217\346\230\216\345\272\246", 0));
        groupBox_2->setTitle(QApplication::translate("Widget", "\344\276\247\344\275\215\346\223\215\344\275\234", 0));
        pushButton_Lat_OpenPicture->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        pushButton_Lat_CapturePicture->setText(QApplication::translate("Widget", "\351\207\207\351\233\206\345\233\276\347\211\207", 0));
        pushButton_getXspottransform_Lat->setText(QApplication::translate("Widget", "\351\207\207\351\233\206NDI", 0));
        pushButton_ShowTiptool_Lat->setText(QApplication::translate("Widget", "\346\230\276\347\244\272\346\216\242\351\222\210", 0));
        pushButton_Save_Lat->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        pushButton_matching_Lat->setText(QApplication::translate("Widget", "\351\205\215\345\207\206", 0));
        checkBox_showLat->setText(QApplication::translate("Widget", "\346\230\276\347\244\272", 0));
        label_2->setText(QApplication::translate("Widget", "\351\200\217\346\230\216\345\272\246", 0));
        pushButton_mirror_Lat->setText(QApplication::translate("Widget", "\347\277\273\350\275\254", 0));
        pushButton_2->setText(QApplication::translate("Widget", "\346\255\243\344\276\247\344\275\215\351\207\207\351\233\206", 0));
        pushButton_3->setText(QApplication::translate("Widget", "\345\257\274\345\205\245\346\225\260\346\215\256", 0));
        pushButton_InitRobot_2->setText(QApplication::translate("Widget", "\346\234\253\347\253\257\346\255\243\344\275\215\345\257\274\350\210\252", 0));
        pushButton_InitRobot_3->setText(QApplication::translate("Widget", "\346\234\253\347\253\257\344\276\247\344\275\215\345\257\274\350\210\252", 0));
        label_APdata->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\357\274\232", 0));
        label_Latdata->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\357\274\232", 0));
        pushButtonSetting->setText(QApplication::translate("Widget", "\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACLWIDGET_H
