/********************************************************************************
** Form generated from reading UI file 'capturevideowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTUREVIDEOWIDGET_H
#define UI_CAPTUREVIDEOWIDGET_H

#include <./captureVideo/lassowidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CaptureVideoWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frameBase;
    QPushButton *pushButton_Exit;
    QPushButton *pushButton_Process;
    QLabel *label_Picture;
    LassoWidget *widget_lasso;
    QGroupBox *groupBox_Xspot;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_10;
    QRadioButton *radioButton_11;
    QPushButton *pushButtonCalculate;
    QRadioButton *radioButton_findPt;
    QFrame *frame;
    QCheckBox *checkBox_removeCircle;
    QRadioButton *radioButton_source;
    QRadioButton *radioButton_refined;
    QPushButton *pushButton_OpenImage;
    QPushButton *pushButton_OpenVideo;
    QPushButton *pushButton_Capture;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *CaptureVideoWidget)
    {
        if (CaptureVideoWidget->objectName().isEmpty())
            CaptureVideoWidget->setObjectName(QStringLiteral("CaptureVideoWidget"));
        CaptureVideoWidget->setEnabled(true);
        CaptureVideoWidget->resize(1080, 722);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon-capture.png"), QSize(), QIcon::Normal, QIcon::Off);
        CaptureVideoWidget->setWindowIcon(icon);
        CaptureVideoWidget->setStyleSheet(QString::fromUtf8("QCheckBox,QRadioButton{\n"
"color:white;\n"
"	font: 11pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#frameBase{\n"
"	border-image: url(:/Resources/resource/bkgNull.png) 0 0 0 0 stretch stretch;\n"
"\n"
"    position: relative;\n"
"\n"
"}\n"
"QPushButton{\n"
"    color: white;\n"
"	background-color: rgb(53, 63, 75);\n"
"}\n"
"#label_Picture{\n"
"   	background: black;\n"
"    border: 2px solid gray;\n"
"position:relative;\n"
"    top: 100px;\n"
"}\n"
"QGroupBox{border-image: url(:/Resources/resource/xspot_yu1.PNG);}\n"
"\n"
""));
        horizontalLayout = new QHBoxLayout(CaptureVideoWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frameBase = new QFrame(CaptureVideoWidget);
        frameBase->setObjectName(QStringLiteral("frameBase"));
        frameBase->setFrameShape(QFrame::StyledPanel);
        frameBase->setFrameShadow(QFrame::Raised);
        pushButton_Exit = new QPushButton(frameBase);
        pushButton_Exit->setObjectName(QStringLiteral("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(30, 560, 80, 30));
        pushButton_Process = new QPushButton(frameBase);
        pushButton_Process->setObjectName(QStringLiteral("pushButton_Process"));
        pushButton_Process->setGeometry(QRect(850, 270, 80, 30));
        label_Picture = new QLabel(frameBase);
        label_Picture->setObjectName(QStringLiteral("label_Picture"));
        label_Picture->setGeometry(QRect(140, 80, 600, 600));
        label_Picture->setScaledContents(true);
        widget_lasso = new LassoWidget(frameBase);
        widget_lasso->setObjectName(QStringLiteral("widget_lasso"));
        widget_lasso->setGeometry(QRect(140, 80, 600, 600));
        groupBox_Xspot = new QGroupBox(frameBase);
        groupBox_Xspot->setObjectName(QStringLiteral("groupBox_Xspot"));
        groupBox_Xspot->setGeometry(QRect(750, 400, 321, 241));
        groupBox_Xspot->setStyleSheet(QString::fromUtf8("font: 75 9pt \"\345\256\213\344\275\223\";"));
        radioButton_9 = new QRadioButton(groupBox_Xspot);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));
        radioButton_9->setGeometry(QRect(240, 140, 41, 19));
        radioButton_1 = new QRadioButton(groupBox_Xspot);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(170, 100, 41, 19));
        radioButton_2 = new QRadioButton(groupBox_Xspot);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(140, 70, 41, 19));
        radioButton_2->setLayoutDirection(Qt::RightToLeft);
        radioButton_3 = new QRadioButton(groupBox_Xspot);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(140, 50, 41, 19));
        radioButton_3->setLayoutDirection(Qt::RightToLeft);
        radioButton_4 = new QRadioButton(groupBox_Xspot);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(160, 30, 41, 19));
        radioButton_5 = new QRadioButton(groupBox_Xspot);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(100, 70, 41, 19));
        radioButton_6 = new QRadioButton(groupBox_Xspot);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(80, 80, 41, 19));
        radioButton_7 = new QRadioButton(groupBox_Xspot);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(60, 90, 41, 20));
        radioButton_7->setLayoutDirection(Qt::LeftToRight);
        radioButton_8 = new QRadioButton(groupBox_Xspot);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(40, 100, 21, 20));
        radioButton_8->setLayoutDirection(Qt::LeftToRight);
        radioButton_10 = new QRadioButton(groupBox_Xspot);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
        radioButton_10->setGeometry(QRect(260, 160, 41, 19));
        radioButton_11 = new QRadioButton(groupBox_Xspot);
        radioButton_11->setObjectName(QStringLiteral("radioButton_11"));
        radioButton_11->setGeometry(QRect(280, 220, 41, 19));
        pushButtonCalculate = new QPushButton(frameBase);
        pushButtonCalculate->setObjectName(QStringLiteral("pushButtonCalculate"));
        pushButtonCalculate->setGeometry(QRect(940, 270, 81, 31));
        radioButton_findPt = new QRadioButton(frameBase);
        radioButton_findPt->setObjectName(QStringLiteral("radioButton_findPt"));
        radioButton_findPt->setGeometry(QRect(960, 680, 91, 20));
        radioButton_findPt->setChecked(true);
        frame = new QFrame(frameBase);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(840, 80, 191, 181));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        checkBox_removeCircle = new QCheckBox(frame);
        checkBox_removeCircle->setObjectName(QStringLiteral("checkBox_removeCircle"));
        checkBox_removeCircle->setGeometry(QRect(20, 60, 71, 16));
        radioButton_source = new QRadioButton(frame);
        radioButton_source->setObjectName(QStringLiteral("radioButton_source"));
        radioButton_source->setGeometry(QRect(20, 10, 89, 21));
        radioButton_refined = new QRadioButton(frame);
        radioButton_refined->setObjectName(QStringLiteral("radioButton_refined"));
        radioButton_refined->setGeometry(QRect(20, 35, 101, 21));
        pushButton_OpenImage = new QPushButton(frame);
        pushButton_OpenImage->setObjectName(QStringLiteral("pushButton_OpenImage"));
        pushButton_OpenImage->setGeometry(QRect(100, 100, 80, 30));
        pushButton_OpenImage->setStyleSheet(QStringLiteral(""));
        pushButton_OpenVideo = new QPushButton(frame);
        pushButton_OpenVideo->setObjectName(QStringLiteral("pushButton_OpenVideo"));
        pushButton_OpenVideo->setGeometry(QRect(10, 100, 80, 30));
        pushButton_Capture = new QPushButton(frame);
        pushButton_Capture->setObjectName(QStringLiteral("pushButton_Capture"));
        pushButton_Capture->setGeometry(QRect(10, 140, 80, 30));
        pushButton = new QPushButton(frameBase);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(940, 323, 81, 31));
        pushButton_2 = new QPushButton(frameBase);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(850, 323, 81, 31));
        widget_lasso->raise();
        pushButton_Exit->raise();
        pushButton_Process->raise();
        label_Picture->raise();
        groupBox_Xspot->raise();
        pushButtonCalculate->raise();
        radioButton_findPt->raise();
        frame->raise();
        pushButton->raise();
        pushButton_2->raise();

        horizontalLayout->addWidget(frameBase);


        retranslateUi(CaptureVideoWidget);

        QMetaObject::connectSlotsByName(CaptureVideoWidget);
    } // setupUi

    void retranslateUi(QWidget *CaptureVideoWidget)
    {
        CaptureVideoWidget->setWindowTitle(QApplication::translate("CaptureVideoWidget", "CaptureVideoWidget", 0));
        pushButton_Exit->setText(QApplication::translate("CaptureVideoWidget", "\351\200\200\345\207\272\347\250\213\345\272\217", 0));
        pushButton_Process->setText(QApplication::translate("CaptureVideoWidget", "\345\244\204\347\220\206\345\233\276\345\203\217", 0));
        label_Picture->setText(QString());
        groupBox_Xspot->setTitle(QString());
        radioButton_9->setText(QString());
        radioButton_1->setText(QString());
        radioButton_2->setText(QString());
        radioButton_3->setText(QString());
        radioButton_4->setText(QString());
        radioButton_5->setText(QString());
        radioButton_6->setText(QString());
        radioButton_7->setText(QString());
        radioButton_8->setText(QString());
        radioButton_10->setText(QString());
        radioButton_11->setText(QString());
        pushButtonCalculate->setText(QApplication::translate("CaptureVideoWidget", "\350\256\241\347\256\227\345\217\202\346\225\260", 0));
        radioButton_findPt->setText(QApplication::translate("CaptureVideoWidget", "\347\202\271\346\215\225\346\215\211", 0));
        checkBox_removeCircle->setText(QApplication::translate("CaptureVideoWidget", "\346\266\210\351\232\220", 0));
        radioButton_source->setText(QApplication::translate("CaptureVideoWidget", "\345\216\237\345\233\276\345\203\217", 0));
        radioButton_refined->setText(QApplication::translate("CaptureVideoWidget", "\346\240\241\346\255\243\345\233\276\345\203\217", 0));
        pushButton_OpenImage->setText(QApplication::translate("CaptureVideoWidget", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        pushButton_OpenVideo->setText(QApplication::translate("CaptureVideoWidget", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        pushButton_Capture->setText(QApplication::translate("CaptureVideoWidget", "\346\210\252\345\217\226\345\233\276\347\211\207", 0));
        pushButton->setText(QApplication::translate("CaptureVideoWidget", "\346\222\244\351\224\200\347\202\271", 0));
        pushButton_2->setText(QApplication::translate("CaptureVideoWidget", "\344\277\235\345\255\230\345\233\276\347\211\207", 0));
    } // retranslateUi

};

namespace Ui {
    class CaptureVideoWidget: public Ui_CaptureVideoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTUREVIDEOWIDGET_H
