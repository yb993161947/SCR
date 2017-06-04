/********************************************************************************
** Form generated from reading UI file 'ur_class_test.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UR_CLASS_TEST_H
#define UI_UR_CLASS_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UR_class_testClass
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_UR_IP;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_GoHome;
    QPushButton *techmode;
    QPushButton *UR_Stop;
    QPushButton *Shut_Down_Robot;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_7;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *Base_Pose_X;
    QLineEdit *Base_Pose_Y;
    QLineEdit *Base_Pose_Z;
    QLineEdit *Base_Pose_RX;
    QLineEdit *Base_Pose_RY;
    QLineEdit *Base_Pose_RZ;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Base_Pose_X_Increase;
    QPushButton *Base_Pose_Y_Increase;
    QPushButton *Base_Pose_Z_Increase;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_4;
    QPushButton *Base_Pose_X_Decrease;
    QPushButton *Base_Pose_Y_Decrease;
    QPushButton *Base_Pose_Z_Decrease;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *Joint_Pose_Base;
    QLineEdit *Joint_Pose_Shoulder;
    QLineEdit *Joint_Pose_Elbow;
    QLineEdit *Joint_Pose_Wrist_1;
    QLineEdit *Joint_Pose_Wrist_2;
    QLineEdit *Joint_Pose_Wrist_3;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_7;
    QPushButton *Base_Increase;
    QPushButton *Shoulder_Increase;
    QPushButton *Elbow_Increase;
    QPushButton *Wrist1_Increase;
    QPushButton *Wrist2_Increase;
    QPushButton *Wrist3_Increase;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_8;
    QPushButton *Base_Decrease;
    QPushButton *Shoulder_Decrease;
    QPushButton *Elbow_Decrese;
    QPushButton *Wrist1_Decrease;
    QPushButton *Wrist2_Decrease;
    QPushButton *Wrist3_Decrease;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget8;
    QGridLayout *gridLayout;
    QLabel *label_14;
    QLineEdit *X_Or_Base;
    QLabel *label_16;
    QLineEdit *Y_Or_Shoulder;
    QLabel *label_18;
    QLineEdit *Z_Or_Elbow;
    QLabel *label_15;
    QLineEdit *Rx_Or_Wrist1;
    QLabel *label_17;
    QLineEdit *Ry_Or_Wrist2;
    QLabel *label_20;
    QLineEdit *Rz_Or_Wrist3;
    QWidget *layoutWidget9;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Debug_TCP;
    QPushButton *Debug_Joint;
    QPushButton *Debug_Tool;
    QPushButton *Debug_Direct;
    QPushButton *Debug_Test;
    QGroupBox *groupBox_5;
    QSlider *Speed_Slider;
    QLabel *label_19;
    QLineEdit *Speed_value;
    QPushButton *pushButton_zero;
    QPushButton *pushButton_setTCP;
    QLabel *label_UrState;
    QPushButton *pushButton_addPoint;
    QPushButton *pushButton_SaveAllPoint;
    QWidget *layoutWidget10;
    QFormLayout *formLayout;
    QPushButton *pushButton_savePoint_1;
    QPushButton *pushButton_move1;
    QPushButton *pushButton_savePoint_2;
    QPushButton *pushButton_move2;
    QPushButton *pushButton_savePoint_3;
    QPushButton *pushButton_move3;
    QPushButton *pushButton_savePoint_4;
    QPushButton *pushButton_move4;
    QPushButton *pushButton_savePoint_5;
    QPushButton *pushButton_move5;
    QPushButton *pushButton_savePoint_6;
    QPushButton *pushButton_move6;
    QPushButton *pushButton_savePoint_7;
    QPushButton *pushButton_move7;
    QPushButton *pushButton_savePoint_8;
    QPushButton *pushButton_move8;

    void setupUi(QWidget *UR_class_testClass)
    {
        if (UR_class_testClass->objectName().isEmpty())
            UR_class_testClass->setObjectName(QStringLiteral("UR_class_testClass"));
        UR_class_testClass->resize(979, 573);
        groupBox = new QGroupBox(UR_class_testClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 611, 81));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 30, 576, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_UR_IP = new QLineEdit(layoutWidget);
        lineEdit_UR_IP->setObjectName(QStringLiteral("lineEdit_UR_IP"));

        horizontalLayout->addWidget(lineEdit_UR_IP);

        pushButton_Connect = new QPushButton(layoutWidget);
        pushButton_Connect->setObjectName(QStringLiteral("pushButton_Connect"));

        horizontalLayout->addWidget(pushButton_Connect);

        pushButton_GoHome = new QPushButton(layoutWidget);
        pushButton_GoHome->setObjectName(QStringLiteral("pushButton_GoHome"));

        horizontalLayout->addWidget(pushButton_GoHome);

        techmode = new QPushButton(layoutWidget);
        techmode->setObjectName(QStringLiteral("techmode"));

        horizontalLayout->addWidget(techmode);

        UR_Stop = new QPushButton(layoutWidget);
        UR_Stop->setObjectName(QStringLiteral("UR_Stop"));

        horizontalLayout->addWidget(UR_Stop);

        Shut_Down_Robot = new QPushButton(layoutWidget);
        Shut_Down_Robot->setObjectName(QStringLiteral("Shut_Down_Robot"));

        horizontalLayout->addWidget(Shut_Down_Robot);

        groupBox_2 = new QGroupBox(UR_class_testClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 110, 261, 191));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 21, 151));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(32, 20, 71, 175));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Base_Pose_X = new QLineEdit(layoutWidget2);
        Base_Pose_X->setObjectName(QStringLiteral("Base_Pose_X"));

        verticalLayout_2->addWidget(Base_Pose_X);

        Base_Pose_Y = new QLineEdit(layoutWidget2);
        Base_Pose_Y->setObjectName(QStringLiteral("Base_Pose_Y"));

        verticalLayout_2->addWidget(Base_Pose_Y);

        Base_Pose_Z = new QLineEdit(layoutWidget2);
        Base_Pose_Z->setObjectName(QStringLiteral("Base_Pose_Z"));

        verticalLayout_2->addWidget(Base_Pose_Z);

        Base_Pose_RX = new QLineEdit(layoutWidget2);
        Base_Pose_RX->setObjectName(QStringLiteral("Base_Pose_RX"));

        verticalLayout_2->addWidget(Base_Pose_RX);

        Base_Pose_RY = new QLineEdit(layoutWidget2);
        Base_Pose_RY->setObjectName(QStringLiteral("Base_Pose_RY"));

        verticalLayout_2->addWidget(Base_Pose_RY);

        Base_Pose_RZ = new QLineEdit(layoutWidget2);
        Base_Pose_RZ->setObjectName(QStringLiteral("Base_Pose_RZ"));

        verticalLayout_2->addWidget(Base_Pose_RZ);

        layoutWidget3 = new QWidget(groupBox_2);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(100, 21, 82, 151));
        verticalLayout_3 = new QVBoxLayout(layoutWidget3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Base_Pose_X_Increase = new QPushButton(layoutWidget3);
        Base_Pose_X_Increase->setObjectName(QStringLiteral("Base_Pose_X_Increase"));

        verticalLayout_3->addWidget(Base_Pose_X_Increase);

        Base_Pose_Y_Increase = new QPushButton(layoutWidget3);
        Base_Pose_Y_Increase->setObjectName(QStringLiteral("Base_Pose_Y_Increase"));

        verticalLayout_3->addWidget(Base_Pose_Y_Increase);

        Base_Pose_Z_Increase = new QPushButton(layoutWidget3);
        Base_Pose_Z_Increase->setObjectName(QStringLiteral("Base_Pose_Z_Increase"));

        verticalLayout_3->addWidget(Base_Pose_Z_Increase);

        layoutWidget4 = new QWidget(groupBox_2);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(180, 20, 82, 151));
        verticalLayout_4 = new QVBoxLayout(layoutWidget4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        Base_Pose_X_Decrease = new QPushButton(layoutWidget4);
        Base_Pose_X_Decrease->setObjectName(QStringLiteral("Base_Pose_X_Decrease"));

        verticalLayout_4->addWidget(Base_Pose_X_Decrease);

        Base_Pose_Y_Decrease = new QPushButton(layoutWidget4);
        Base_Pose_Y_Decrease->setObjectName(QStringLiteral("Base_Pose_Y_Decrease"));

        verticalLayout_4->addWidget(Base_Pose_Y_Decrease);

        Base_Pose_Z_Decrease = new QPushButton(layoutWidget4);
        Base_Pose_Z_Decrease->setObjectName(QStringLiteral("Base_Pose_Z_Decrease"));

        verticalLayout_4->addWidget(Base_Pose_Z_Decrease);

        groupBox_3 = new QGroupBox(UR_class_testClass);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(350, 110, 321, 191));
        layoutWidget5 = new QWidget(groupBox_3);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(10, 20, 66, 151));
        verticalLayout_5 = new QVBoxLayout(layoutWidget5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget5);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_5->addWidget(label_6);

        label_9 = new QLabel(layoutWidget5);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_5->addWidget(label_9);

        label_10 = new QLabel(layoutWidget5);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_5->addWidget(label_10);

        label_11 = new QLabel(layoutWidget5);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_5->addWidget(label_11);

        label_12 = new QLabel(layoutWidget5);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_5->addWidget(label_12);

        label_13 = new QLabel(layoutWidget5);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_5->addWidget(label_13);

        layoutWidget_2 = new QWidget(groupBox_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(80, 20, 71, 175));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        Joint_Pose_Base = new QLineEdit(layoutWidget_2);
        Joint_Pose_Base->setObjectName(QStringLiteral("Joint_Pose_Base"));

        verticalLayout_6->addWidget(Joint_Pose_Base);

        Joint_Pose_Shoulder = new QLineEdit(layoutWidget_2);
        Joint_Pose_Shoulder->setObjectName(QStringLiteral("Joint_Pose_Shoulder"));

        verticalLayout_6->addWidget(Joint_Pose_Shoulder);

        Joint_Pose_Elbow = new QLineEdit(layoutWidget_2);
        Joint_Pose_Elbow->setObjectName(QStringLiteral("Joint_Pose_Elbow"));

        verticalLayout_6->addWidget(Joint_Pose_Elbow);

        Joint_Pose_Wrist_1 = new QLineEdit(layoutWidget_2);
        Joint_Pose_Wrist_1->setObjectName(QStringLiteral("Joint_Pose_Wrist_1"));

        verticalLayout_6->addWidget(Joint_Pose_Wrist_1);

        Joint_Pose_Wrist_2 = new QLineEdit(layoutWidget_2);
        Joint_Pose_Wrist_2->setObjectName(QStringLiteral("Joint_Pose_Wrist_2"));

        verticalLayout_6->addWidget(Joint_Pose_Wrist_2);

        Joint_Pose_Wrist_3 = new QLineEdit(layoutWidget_2);
        Joint_Pose_Wrist_3->setObjectName(QStringLiteral("Joint_Pose_Wrist_3"));

        verticalLayout_6->addWidget(Joint_Pose_Wrist_3);

        layoutWidget6 = new QWidget(groupBox_3);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(160, 20, 82, 181));
        verticalLayout_7 = new QVBoxLayout(layoutWidget6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        Base_Increase = new QPushButton(layoutWidget6);
        Base_Increase->setObjectName(QStringLiteral("Base_Increase"));

        verticalLayout_7->addWidget(Base_Increase);

        Shoulder_Increase = new QPushButton(layoutWidget6);
        Shoulder_Increase->setObjectName(QStringLiteral("Shoulder_Increase"));

        verticalLayout_7->addWidget(Shoulder_Increase);

        Elbow_Increase = new QPushButton(layoutWidget6);
        Elbow_Increase->setObjectName(QStringLiteral("Elbow_Increase"));

        verticalLayout_7->addWidget(Elbow_Increase);

        Wrist1_Increase = new QPushButton(layoutWidget6);
        Wrist1_Increase->setObjectName(QStringLiteral("Wrist1_Increase"));

        verticalLayout_7->addWidget(Wrist1_Increase);

        Wrist2_Increase = new QPushButton(layoutWidget6);
        Wrist2_Increase->setObjectName(QStringLiteral("Wrist2_Increase"));

        verticalLayout_7->addWidget(Wrist2_Increase);

        Wrist3_Increase = new QPushButton(layoutWidget6);
        Wrist3_Increase->setObjectName(QStringLiteral("Wrist3_Increase"));

        verticalLayout_7->addWidget(Wrist3_Increase);

        layoutWidget7 = new QWidget(groupBox_3);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(240, 20, 82, 181));
        verticalLayout_8 = new QVBoxLayout(layoutWidget7);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        Base_Decrease = new QPushButton(layoutWidget7);
        Base_Decrease->setObjectName(QStringLiteral("Base_Decrease"));

        verticalLayout_8->addWidget(Base_Decrease);

        Shoulder_Decrease = new QPushButton(layoutWidget7);
        Shoulder_Decrease->setObjectName(QStringLiteral("Shoulder_Decrease"));

        verticalLayout_8->addWidget(Shoulder_Decrease);

        Elbow_Decrese = new QPushButton(layoutWidget7);
        Elbow_Decrese->setObjectName(QStringLiteral("Elbow_Decrese"));

        verticalLayout_8->addWidget(Elbow_Decrese);

        Wrist1_Decrease = new QPushButton(layoutWidget7);
        Wrist1_Decrease->setObjectName(QStringLiteral("Wrist1_Decrease"));

        verticalLayout_8->addWidget(Wrist1_Decrease);

        Wrist2_Decrease = new QPushButton(layoutWidget7);
        Wrist2_Decrease->setObjectName(QStringLiteral("Wrist2_Decrease"));

        verticalLayout_8->addWidget(Wrist2_Decrease);

        Wrist3_Decrease = new QPushButton(layoutWidget7);
        Wrist3_Decrease->setObjectName(QStringLiteral("Wrist3_Decrease"));

        verticalLayout_8->addWidget(Wrist3_Decrease);

        groupBox_4 = new QGroupBox(UR_class_testClass);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 370, 621, 151));
        layoutWidget8 = new QWidget(groupBox_4);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(10, 20, 593, 71));
        gridLayout = new QGridLayout(layoutWidget8);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget8);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 0, 0, 1, 1);

        X_Or_Base = new QLineEdit(layoutWidget8);
        X_Or_Base->setObjectName(QStringLiteral("X_Or_Base"));

        gridLayout->addWidget(X_Or_Base, 0, 1, 1, 1);

        label_16 = new QLabel(layoutWidget8);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 0, 2, 1, 1);

        Y_Or_Shoulder = new QLineEdit(layoutWidget8);
        Y_Or_Shoulder->setObjectName(QStringLiteral("Y_Or_Shoulder"));

        gridLayout->addWidget(Y_Or_Shoulder, 0, 3, 1, 1);

        label_18 = new QLabel(layoutWidget8);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 0, 4, 1, 1);

        Z_Or_Elbow = new QLineEdit(layoutWidget8);
        Z_Or_Elbow->setObjectName(QStringLiteral("Z_Or_Elbow"));

        gridLayout->addWidget(Z_Or_Elbow, 0, 5, 1, 1);

        label_15 = new QLabel(layoutWidget8);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 1, 0, 1, 1);

        Rx_Or_Wrist1 = new QLineEdit(layoutWidget8);
        Rx_Or_Wrist1->setObjectName(QStringLiteral("Rx_Or_Wrist1"));

        gridLayout->addWidget(Rx_Or_Wrist1, 1, 1, 1, 1);

        label_17 = new QLabel(layoutWidget8);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 1, 2, 1, 1);

        Ry_Or_Wrist2 = new QLineEdit(layoutWidget8);
        Ry_Or_Wrist2->setObjectName(QStringLiteral("Ry_Or_Wrist2"));

        gridLayout->addWidget(Ry_Or_Wrist2, 1, 3, 1, 1);

        label_20 = new QLabel(layoutWidget8);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 1, 4, 1, 1);

        Rz_Or_Wrist3 = new QLineEdit(layoutWidget8);
        Rz_Or_Wrist3->setObjectName(QStringLiteral("Rz_Or_Wrist3"));

        gridLayout->addWidget(Rz_Or_Wrist3, 1, 5, 1, 1);

        layoutWidget9 = new QWidget(groupBox_4);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(10, 110, 591, 26));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget9);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Debug_TCP = new QPushButton(layoutWidget9);
        Debug_TCP->setObjectName(QStringLiteral("Debug_TCP"));

        horizontalLayout_2->addWidget(Debug_TCP);

        Debug_Joint = new QPushButton(layoutWidget9);
        Debug_Joint->setObjectName(QStringLiteral("Debug_Joint"));

        horizontalLayout_2->addWidget(Debug_Joint);

        Debug_Tool = new QPushButton(layoutWidget9);
        Debug_Tool->setObjectName(QStringLiteral("Debug_Tool"));

        horizontalLayout_2->addWidget(Debug_Tool);

        Debug_Direct = new QPushButton(layoutWidget9);
        Debug_Direct->setObjectName(QStringLiteral("Debug_Direct"));

        horizontalLayout_2->addWidget(Debug_Direct);

        Debug_Test = new QPushButton(layoutWidget9);
        Debug_Test->setObjectName(QStringLiteral("Debug_Test"));

        horizontalLayout_2->addWidget(Debug_Test);

        groupBox_5 = new QGroupBox(UR_class_testClass);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 310, 411, 51));
        Speed_Slider = new QSlider(groupBox_5);
        Speed_Slider->setObjectName(QStringLiteral("Speed_Slider"));
        Speed_Slider->setGeometry(QRect(110, 20, 161, 19));
        Speed_Slider->setMinimum(1);
        Speed_Slider->setMaximum(100);
        Speed_Slider->setValue(100);
        Speed_Slider->setOrientation(Qt::Horizontal);
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(40, 20, 30, 16));
        Speed_value = new QLineEdit(groupBox_5);
        Speed_value->setObjectName(QStringLiteral("Speed_value"));
        Speed_value->setGeometry(QRect(304, 21, 61, 20));
        pushButton_zero = new QPushButton(UR_class_testClass);
        pushButton_zero->setObjectName(QStringLiteral("pushButton_zero"));
        pushButton_zero->setGeometry(QRect(650, 400, 61, 31));
        pushButton_setTCP = new QPushButton(UR_class_testClass);
        pushButton_setTCP->setObjectName(QStringLiteral("pushButton_setTCP"));
        pushButton_setTCP->setGeometry(QRect(650, 450, 61, 31));
        label_UrState = new QLabel(UR_class_testClass);
        label_UrState->setObjectName(QStringLiteral("label_UrState"));
        label_UrState->setGeometry(QRect(640, 60, 131, 16));
        pushButton_addPoint = new QPushButton(UR_class_testClass);
        pushButton_addPoint->setObjectName(QStringLiteral("pushButton_addPoint"));
        pushButton_addPoint->setGeometry(QRect(730, 320, 89, 24));
        pushButton_SaveAllPoint = new QPushButton(UR_class_testClass);
        pushButton_SaveAllPoint->setObjectName(QStringLiteral("pushButton_SaveAllPoint"));
        pushButton_SaveAllPoint->setGeometry(QRect(840, 320, 89, 24));
        layoutWidget10 = new QWidget(UR_class_testClass);
        layoutWidget10->setObjectName(QStringLiteral("layoutWidget10"));
        layoutWidget10->setGeometry(QRect(741, 41, 221, 243));
        formLayout = new QFormLayout(layoutWidget10);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_savePoint_1 = new QPushButton(layoutWidget10);
        pushButton_savePoint_1->setObjectName(QStringLiteral("pushButton_savePoint_1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pushButton_savePoint_1);

        pushButton_move1 = new QPushButton(layoutWidget10);
        pushButton_move1->setObjectName(QStringLiteral("pushButton_move1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pushButton_move1);

        pushButton_savePoint_2 = new QPushButton(layoutWidget10);
        pushButton_savePoint_2->setObjectName(QStringLiteral("pushButton_savePoint_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, pushButton_savePoint_2);

        pushButton_move2 = new QPushButton(layoutWidget10);
        pushButton_move2->setObjectName(QStringLiteral("pushButton_move2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pushButton_move2);

        pushButton_savePoint_3 = new QPushButton(layoutWidget10);
        pushButton_savePoint_3->setObjectName(QStringLiteral("pushButton_savePoint_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton_savePoint_3);

        pushButton_move3 = new QPushButton(layoutWidget10);
        pushButton_move3->setObjectName(QStringLiteral("pushButton_move3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, pushButton_move3);

        pushButton_savePoint_4 = new QPushButton(layoutWidget10);
        pushButton_savePoint_4->setObjectName(QStringLiteral("pushButton_savePoint_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, pushButton_savePoint_4);

        pushButton_move4 = new QPushButton(layoutWidget10);
        pushButton_move4->setObjectName(QStringLiteral("pushButton_move4"));

        formLayout->setWidget(3, QFormLayout::FieldRole, pushButton_move4);

        pushButton_savePoint_5 = new QPushButton(layoutWidget10);
        pushButton_savePoint_5->setObjectName(QStringLiteral("pushButton_savePoint_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, pushButton_savePoint_5);

        pushButton_move5 = new QPushButton(layoutWidget10);
        pushButton_move5->setObjectName(QStringLiteral("pushButton_move5"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButton_move5);

        pushButton_savePoint_6 = new QPushButton(layoutWidget10);
        pushButton_savePoint_6->setObjectName(QStringLiteral("pushButton_savePoint_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, pushButton_savePoint_6);

        pushButton_move6 = new QPushButton(layoutWidget10);
        pushButton_move6->setObjectName(QStringLiteral("pushButton_move6"));

        formLayout->setWidget(5, QFormLayout::FieldRole, pushButton_move6);

        pushButton_savePoint_7 = new QPushButton(layoutWidget10);
        pushButton_savePoint_7->setObjectName(QStringLiteral("pushButton_savePoint_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, pushButton_savePoint_7);

        pushButton_move7 = new QPushButton(layoutWidget10);
        pushButton_move7->setObjectName(QStringLiteral("pushButton_move7"));

        formLayout->setWidget(6, QFormLayout::FieldRole, pushButton_move7);

        pushButton_savePoint_8 = new QPushButton(layoutWidget10);
        pushButton_savePoint_8->setObjectName(QStringLiteral("pushButton_savePoint_8"));

        formLayout->setWidget(7, QFormLayout::LabelRole, pushButton_savePoint_8);

        pushButton_move8 = new QPushButton(layoutWidget10);
        pushButton_move8->setObjectName(QStringLiteral("pushButton_move8"));

        formLayout->setWidget(7, QFormLayout::FieldRole, pushButton_move8);


        retranslateUi(UR_class_testClass);

        QMetaObject::connectSlotsByName(UR_class_testClass);
    } // setupUi

    void retranslateUi(QWidget *UR_class_testClass)
    {
        UR_class_testClass->setWindowTitle(QApplication::translate("UR_class_testClass", "UR_class_test", 0));
        groupBox->setTitle(QApplication::translate("UR_class_testClass", "UR_initialize", 0));
        label->setText(QApplication::translate("UR_class_testClass", "UR_IP", 0));
        lineEdit_UR_IP->setText(QApplication::translate("UR_class_testClass", "192.168.1.10", 0));
        pushButton_Connect->setText(QApplication::translate("UR_class_testClass", "Connect", 0));
        pushButton_GoHome->setText(QApplication::translate("UR_class_testClass", "\345\233\236\351\233\266", 0));
        techmode->setText(QApplication::translate("UR_class_testClass", "\347\244\272\346\225\231", 0));
        UR_Stop->setText(QApplication::translate("UR_class_testClass", "stop", 0));
        Shut_Down_Robot->setText(QApplication::translate("UR_class_testClass", "\345\205\263\351\227\255\346\234\272\345\231\250\344\272\272", 0));
        groupBox_2->setTitle(QApplication::translate("UR_class_testClass", "Base Pose", 0));
        label_2->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">x</p></body></html>", 0));
        label_3->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">y</p></body></html>", 0));
        label_4->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">z</p></body></html>", 0));
        label_5->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">rx</p></body></html>", 0));
        label_8->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">ry</p></body></html>", 0));
        label_7->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">rz</p></body></html>", 0));
        Base_Pose_X_Increase->setText(QApplication::translate("UR_class_testClass", "X+", 0));
        Base_Pose_Y_Increase->setText(QApplication::translate("UR_class_testClass", "Y+", 0));
        Base_Pose_Z_Increase->setText(QApplication::translate("UR_class_testClass", "Z+", 0));
        Base_Pose_X_Decrease->setText(QApplication::translate("UR_class_testClass", "X-", 0));
        Base_Pose_Y_Decrease->setText(QApplication::translate("UR_class_testClass", "Y-", 0));
        Base_Pose_Z_Decrease->setText(QApplication::translate("UR_class_testClass", "Z-", 0));
        groupBox_3->setTitle(QApplication::translate("UR_class_testClass", "Joint Pose", 0));
        label_6->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">Base</p></body></html>", 0));
        label_9->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">Shoulder</p></body></html>", 0));
        label_10->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">Elbow</p></body></html>", 0));
        label_11->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">Wrist1</p></body></html>", 0));
        label_12->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">Wrist2</p></body></html>", 0));
        label_13->setText(QApplication::translate("UR_class_testClass", "<html><head/><body><p align=\"center\">Wrist3</p></body></html>", 0));
        Base_Increase->setText(QApplication::translate("UR_class_testClass", "+", 0));
        Shoulder_Increase->setText(QApplication::translate("UR_class_testClass", "+", 0));
        Elbow_Increase->setText(QApplication::translate("UR_class_testClass", "+", 0));
        Wrist1_Increase->setText(QApplication::translate("UR_class_testClass", "+", 0));
        Wrist2_Increase->setText(QApplication::translate("UR_class_testClass", "+", 0));
        Wrist3_Increase->setText(QApplication::translate("UR_class_testClass", "+", 0));
        Base_Decrease->setText(QApplication::translate("UR_class_testClass", "-", 0));
        Shoulder_Decrease->setText(QApplication::translate("UR_class_testClass", "-", 0));
        Elbow_Decrese->setText(QApplication::translate("UR_class_testClass", "-", 0));
        Wrist1_Decrease->setText(QApplication::translate("UR_class_testClass", "-", 0));
        Wrist2_Decrease->setText(QApplication::translate("UR_class_testClass", "-", 0));
        Wrist3_Decrease->setText(QApplication::translate("UR_class_testClass", "-", 0));
        groupBox_4->setTitle(QApplication::translate("UR_class_testClass", "UR_control_precise  \345\215\225\344\275\215\357\274\210mm/\345\272\246\357\274\211", 0));
        label_14->setText(QApplication::translate("UR_class_testClass", "X/Base", 0));
        label_16->setText(QApplication::translate("UR_class_testClass", "Y/Shoulder", 0));
        label_18->setText(QApplication::translate("UR_class_testClass", "Z/Elbow", 0));
        label_15->setText(QApplication::translate("UR_class_testClass", "Rx/Wrist1", 0));
        label_17->setText(QApplication::translate("UR_class_testClass", "Ry/Wrist2", 0));
        label_20->setText(QApplication::translate("UR_class_testClass", "Rz/Wrist3", 0));
        Debug_TCP->setText(QApplication::translate("UR_class_testClass", "Debug TCP\357\274\210\350\277\220\345\212\250\351\224\231\350\257\257\357\274\211", 0));
        Debug_Joint->setText(QApplication::translate("UR_class_testClass", "Debug Joint", 0));
        Debug_Tool->setText(QApplication::translate("UR_class_testClass", "Debug Tool", 0));
        Debug_Direct->setText(QApplication::translate("UR_class_testClass", "Debug Direct", 0));
        Debug_Test->setText(QApplication::translate("UR_class_testClass", "Debug Test", 0));
        groupBox_5->setTitle(QApplication::translate("UR_class_testClass", "set speed", 0));
        label_19->setText(QApplication::translate("UR_class_testClass", "speed", 0));
        pushButton_zero->setText(QApplication::translate("UR_class_testClass", "zeroTCP", 0));
        pushButton_setTCP->setText(QApplication::translate("UR_class_testClass", "setTCP", 0));
        label_UrState->setText(QApplication::translate("UR_class_testClass", "TextLabel", 0));
        pushButton_addPoint->setText(QApplication::translate("UR_class_testClass", "\345\212\240\350\275\275\347\202\271", 0));
        pushButton_SaveAllPoint->setText(QApplication::translate("UR_class_testClass", "\345\255\230\345\202\250\347\202\271", 0));
        pushButton_savePoint_1->setText(QApplication::translate("UR_class_testClass", "\345\255\230L1\345\267\246", 0));
        pushButton_move1->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L1\345\267\246", 0));
        pushButton_savePoint_2->setText(QApplication::translate("UR_class_testClass", "\345\255\230L1\345\217\263", 0));
        pushButton_move2->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L1\345\217\263", 0));
        pushButton_savePoint_3->setText(QApplication::translate("UR_class_testClass", "\345\255\230L2\345\267\246", 0));
        pushButton_move3->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L2\345\267\246", 0));
        pushButton_savePoint_4->setText(QApplication::translate("UR_class_testClass", "\345\255\230L2\345\217\263", 0));
        pushButton_move4->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L2\345\217\263", 0));
        pushButton_savePoint_5->setText(QApplication::translate("UR_class_testClass", "\345\255\230L3\345\267\246", 0));
        pushButton_move5->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L3\345\267\246", 0));
        pushButton_savePoint_6->setText(QApplication::translate("UR_class_testClass", "\345\255\230L3\345\217\263", 0));
        pushButton_move6->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L3\345\217\263", 0));
        pushButton_savePoint_7->setText(QApplication::translate("UR_class_testClass", "\345\255\230L4\345\267\246", 0));
        pushButton_move7->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\260L4\345\267\246", 0));
        pushButton_savePoint_8->setText(QApplication::translate("UR_class_testClass", "\345\255\230L4\345\217\263", 0));
        pushButton_move8->setText(QApplication::translate("UR_class_testClass", "\350\277\220\345\212\250\345\210\2604\345\217\263", 0));
    } // retranslateUi

};

namespace Ui {
    class UR_class_testClass: public Ui_UR_class_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UR_CLASS_TEST_H
