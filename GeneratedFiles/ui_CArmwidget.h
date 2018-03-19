/********************************************************************************
** Form generated from reading UI file 'CArmwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARMWIDGET_H
#define UI_CARMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CArmWidget
{
public:
    QPushButton *pushButtonOpenPicture;
    QTextBrowser *textBrowserMeasureValue;
    QLabel *label_2;
    QTextEdit *textEditReferenceValue;
    QLabel *label_4;
    QTextBrowser *textBrowserMeasureValue_Angle;
    QLabel *label;
    QGroupBox *groupBox;
    QRadioButton *radioButton_femur;
    QRadioButton *radioButton_tibia;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLineEdit *lineEdit_B;
    QLabel *label_7;
    QLineEdit *lineEdit_ankle;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_Ry;
    QLabel *label_5;
    QLabel *label_Rz;
    QLabel *label_6;
    QLabel *label_Rx;
    QFrame *frame_Femur;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_4;
    QLabel *labelReferencePicture;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_3;
    QFrame *frame_Tibia;
    QRadioButton *radioButton_13;
    QRadioButton *radioButton_11;
    QRadioButton *radioButton_10;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_12;
    QLabel *labelReferencePicture_2;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_14;
    QRadioButton *radioButton_15;
    QPushButton *pushButtonRotatePic;

    void setupUi(QWidget *CArmWidget)
    {
        if (CArmWidget->objectName().isEmpty())
            CArmWidget->setObjectName(QStringLiteral("CArmWidget"));
        CArmWidget->resize(1280, 768);
        CArmWidget->setMaximumSize(QSize(1280, 768));
        CArmWidget->setStyleSheet(QStringLiteral(""));
        pushButtonOpenPicture = new QPushButton(CArmWidget);
        pushButtonOpenPicture->setObjectName(QStringLiteral("pushButtonOpenPicture"));
        pushButtonOpenPicture->setGeometry(QRect(1030, 110, 81, 31));
        pushButtonOpenPicture->setStyleSheet(QLatin1String("border-image: url(:/images/btn.png);\n"
"color: rgb(255, 255, 255);"));
        textBrowserMeasureValue = new QTextBrowser(CArmWidget);
        textBrowserMeasureValue->setObjectName(QStringLiteral("textBrowserMeasureValue"));
        textBrowserMeasureValue->setGeometry(QRect(1113, 210, 127, 32));
        label_2 = new QLabel(CArmWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1031, 171, 75, 16));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"\n"
"\n"
""));
        textEditReferenceValue = new QTextEdit(CArmWidget);
        textEditReferenceValue->setObjectName(QStringLiteral("textEditReferenceValue"));
        textEditReferenceValue->setGeometry(QRect(1113, 171, 127, 32));
        label_4 = new QLabel(CArmWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1031, 249, 75, 16));
        label_4->setStyleSheet(QLatin1String("color: rgb(235, 235, 235);\n"
""));
        textBrowserMeasureValue_Angle = new QTextBrowser(CArmWidget);
        textBrowserMeasureValue_Angle->setObjectName(QStringLiteral("textBrowserMeasureValue_Angle"));
        textBrowserMeasureValue_Angle->setGeometry(QRect(1113, 249, 127, 31));
        label = new QLabel(CArmWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1031, 210, 60, 16));
        label->setStyleSheet(QLatin1String("color: rgb(235, 235, 235);\n"
""));
        groupBox = new QGroupBox(CArmWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1010, 400, 261, 251));
        radioButton_femur = new QRadioButton(groupBox);
        radioButton_femur->setObjectName(QStringLiteral("radioButton_femur"));
        radioButton_femur->setGeometry(QRect(20, 30, 117, 21));
        radioButton_femur->setFocusPolicy(Qt::StrongFocus);
        radioButton_femur->setChecked(true);
        radioButton_tibia = new QRadioButton(groupBox);
        radioButton_tibia->setObjectName(QStringLiteral("radioButton_tibia"));
        radioButton_tibia->setGeometry(QRect(20, 60, 117, 21));
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 90, 231, 55));
        gridLayout_3 = new QGridLayout(layoutWidget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 0, 0, 1, 1);

        lineEdit_B = new QLineEdit(layoutWidget_2);
        lineEdit_B->setObjectName(QStringLiteral("lineEdit_B"));

        gridLayout_3->addWidget(lineEdit_B, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        lineEdit_ankle = new QLineEdit(layoutWidget_2);
        lineEdit_ankle->setObjectName(QStringLiteral("lineEdit_ankle"));

        gridLayout_3->addWidget(lineEdit_ankle, 1, 1, 1, 1);

        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 150, 231, 81));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_Ry = new QLabel(layoutWidget);
        label_Ry->setObjectName(QStringLiteral("label_Ry"));

        gridLayout_2->addWidget(label_Ry, 0, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        label_Rz = new QLabel(layoutWidget);
        label_Rz->setObjectName(QStringLiteral("label_Rz"));

        gridLayout_2->addWidget(label_Rz, 1, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_Rx = new QLabel(layoutWidget);
        label_Rx->setObjectName(QStringLiteral("label_Rx"));

        gridLayout_2->addWidget(label_Rx, 2, 1, 1, 1);

        frame_Femur = new QFrame(CArmWidget);
        frame_Femur->setObjectName(QStringLiteral("frame_Femur"));
        frame_Femur->setGeometry(QRect(720, 400, 280, 280));
        frame_Femur->setFrameShape(QFrame::StyledPanel);
        frame_Femur->setFrameShadow(QFrame::Raised);
        radioButton_6 = new QRadioButton(frame_Femur);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(160, 130, 71, 20));
        radioButton_6->setLayoutDirection(Qt::LeftToRight);
        radioButton_6->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        radioButton_1 = new QRadioButton(frame_Femur);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(10, 180, 61, 19));
        radioButton_1->setLayoutDirection(Qt::RightToLeft);
        radioButton_1->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_4 = new QRadioButton(frame_Femur);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(100, 190, 71, 19));
        radioButton_4->setLayoutDirection(Qt::LeftToRight);
        radioButton_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        labelReferencePicture = new QLabel(frame_Femur);
        labelReferencePicture->setObjectName(QStringLiteral("labelReferencePicture"));
        labelReferencePicture->setGeometry(QRect(0, 0, 280, 280));
        labelReferencePicture->setStyleSheet(QStringLiteral("border-image: url(:/images/sketch.png);"));
        radioButton_2 = new QRadioButton(frame_Femur);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(140, 70, 115, 19));
        radioButton_2->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_5 = new QRadioButton(frame_Femur);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(80, 130, 71, 20));
        radioButton_5->setLayoutDirection(Qt::RightToLeft);
        radioButton_5->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        radioButton_3 = new QRadioButton(frame_Femur);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(100, 220, 71, 20));
        radioButton_3->setLayoutDirection(Qt::LeftToRight);
        radioButton_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        labelReferencePicture->raise();
        radioButton_6->raise();
        radioButton_1->raise();
        radioButton_4->raise();
        radioButton_2->raise();
        radioButton_5->raise();
        radioButton_3->raise();
        frame_Tibia = new QFrame(CArmWidget);
        frame_Tibia->setObjectName(QStringLiteral("frame_Tibia"));
        frame_Tibia->setGeometry(QRect(420, 490, 281, 281));
        frame_Tibia->setFrameShape(QFrame::StyledPanel);
        frame_Tibia->setFrameShadow(QFrame::Raised);
        radioButton_13 = new QRadioButton(frame_Tibia);
        radioButton_13->setObjectName(QStringLiteral("radioButton_13"));
        radioButton_13->setGeometry(QRect(0, 190, 71, 20));
        radioButton_13->setLayoutDirection(Qt::RightToLeft);
        radioButton_13->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        radioButton_11 = new QRadioButton(frame_Tibia);
        radioButton_11->setObjectName(QStringLiteral("radioButton_11"));
        radioButton_11->setGeometry(QRect(160, 130, 71, 19));
        radioButton_11->setLayoutDirection(Qt::RightToLeft);
        radioButton_11->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_10 = new QRadioButton(frame_Tibia);
        radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
        radioButton_10->setGeometry(QRect(160, 30, 71, 20));
        radioButton_10->setLayoutDirection(Qt::RightToLeft);
        radioButton_10->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_9 = new QRadioButton(frame_Tibia);
        radioButton_9->setObjectName(QStringLiteral("radioButton_9"));
        radioButton_9->setGeometry(QRect(60, 80, 115, 19));
        radioButton_9->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_12 = new QRadioButton(frame_Tibia);
        radioButton_12->setObjectName(QStringLiteral("radioButton_12"));
        radioButton_12->setGeometry(QRect(80, 180, 71, 20));
        radioButton_12->setLayoutDirection(Qt::LeftToRight);
        radioButton_12->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        labelReferencePicture_2 = new QLabel(frame_Tibia);
        labelReferencePicture_2->setObjectName(QStringLiteral("labelReferencePicture_2"));
        labelReferencePicture_2->setGeometry(QRect(0, 0, 280, 280));
        labelReferencePicture_2->setStyleSheet(QLatin1String("border-image: url(:/images/sketch_2.png);\n"
""));
        radioButton_8 = new QRadioButton(frame_Tibia);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setGeometry(QRect(80, 240, 61, 19));
        radioButton_8->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_14 = new QRadioButton(frame_Tibia);
        radioButton_14->setObjectName(QStringLiteral("radioButton_14"));
        radioButton_14->setGeometry(QRect(150, 60, 71, 20));
        radioButton_14->setLayoutDirection(Qt::RightToLeft);
        radioButton_14->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        radioButton_15 = new QRadioButton(frame_Tibia);
        radioButton_15->setObjectName(QStringLiteral("radioButton_15"));
        radioButton_15->setGeometry(QRect(180, 110, 71, 20));
        radioButton_15->setLayoutDirection(Qt::RightToLeft);
        radioButton_15->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        labelReferencePicture_2->raise();
        radioButton_13->raise();
        radioButton_11->raise();
        radioButton_10->raise();
        radioButton_9->raise();
        radioButton_12->raise();
        radioButton_8->raise();
        radioButton_14->raise();
        radioButton_15->raise();
        pushButtonRotatePic = new QPushButton(CArmWidget);
        pushButtonRotatePic->setObjectName(QStringLiteral("pushButtonRotatePic"));
        pushButtonRotatePic->setGeometry(QRect(1140, 110, 81, 31));
        pushButtonRotatePic->setStyleSheet(QLatin1String("border-image: url(:/images/btn.png);\n"
"color: rgb(255, 255, 255);"));
        textBrowserMeasureValue->raise();
        label_2->raise();
        textEditReferenceValue->raise();
        label_4->raise();
        textBrowserMeasureValue_Angle->raise();
        label->raise();
        pushButtonOpenPicture->raise();
        groupBox->raise();
        frame_Femur->raise();
        frame_Tibia->raise();
        pushButtonRotatePic->raise();

        retranslateUi(CArmWidget);

        QMetaObject::connectSlotsByName(CArmWidget);
    } // setupUi

    void retranslateUi(QWidget *CArmWidget)
    {
        CArmWidget->setWindowTitle(QApplication::translate("CArmWidget", "Widget", 0));
        pushButtonOpenPicture->setText(QApplication::translate("CArmWidget", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        label_2->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\203\351\225\277\345\272\246\357\274\232", 0));
        label_4->setText(QApplication::translate("CArmWidget", "\347\233\264\347\272\277\345\244\271\350\247\222\357\274\232", 0));
        label->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\217\345\200\274\357\274\232", 0));
        groupBox->setTitle(QString());
        radioButton_femur->setText(QApplication::translate("CArmWidget", "\350\202\241\351\252\250", 0));
        radioButton_tibia->setText(QApplication::translate("CArmWidget", "\350\203\253\351\252\250", 0));
        label_8->setText(QApplication::translate("CArmWidget", "\345\270\203\346\213\211\351\227\250\350\265\233\347\211\271\347\272\277\357\274\232", 0));
        label_7->setText(QApplication::translate("CArmWidget", "\350\270\235\351\227\264\350\267\235\357\274\232", 0));
        label_3->setText(QApplication::translate("CArmWidget", "C\350\207\202\344\277\257\344\273\260\357\274\232", 0));
        label_Ry->setText(QString());
        label_5->setText(QApplication::translate("CArmWidget", "C\350\207\202\347\277\273\350\275\254\357\274\232", 0));
        label_Rz->setText(QString());
        label_6->setText(QApplication::translate("CArmWidget", "C\350\207\202\345\201\217\350\275\254\357\274\232", 0));
        label_Rx->setText(QString());
        radioButton_6->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2175", 0));
        radioButton_1->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2030", 0));
        radioButton_4->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2173", 0));
        labelReferencePicture->setText(QString());
        radioButton_2->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2031", 0));
        radioButton_5->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2174", 0));
        radioButton_3->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2172", 0));
        radioButton_13->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2175", 0));
        radioButton_11->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2033", 0));
        radioButton_10->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2032", 0));
        radioButton_9->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2031", 0));
        radioButton_12->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2174", 0));
        labelReferencePicture_2->setText(QString());
        radioButton_8->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2030", 0));
        radioButton_14->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2176", 0));
        radioButton_15->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2177", 0));
        pushButtonRotatePic->setText(QApplication::translate("CArmWidget", "\346\227\213\350\275\254\345\233\276\345\203\217", 0));
    } // retranslateUi

};

namespace Ui {
    class CArmWidget: public Ui_CArmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARMWIDGET_H
