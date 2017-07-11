/********************************************************************************
** Form generated from reading UI file 'getnormalx_ray.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETNORMALX_RAY_H
#define UI_GETNORMALX_RAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetGetNormalX_Ray
{
public:
    QLabel *label_Pic;
    QGroupBox *groupBox_4;
    QLabel *label_6;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_7;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QLineEdit *lineEdit_picth;
    QLabel *label_BlumensaatLinePic;
    QLineEdit *lineEdit_yaw;
    QLineEdit *lineEdit_2;
    QLabel *label_BlumensaatLine;
    QLineEdit *lineEdit_roll;
    QLabel *label_roll;
    QLabel *label_yaw;
    QLabel *label_BlumensaatLinePic_2;
    QLabel *label_1;
    QLineEdit *lineEdit_BlumensaatLine;
    QLabel *label_pitch;
    QPushButton *pushButton_loadPic;
    QPushButton *pushButton_rectify;
    QLabel *label;

    void setupUi(QWidget *WidgetGetNormalX_Ray)
    {
        if (WidgetGetNormalX_Ray->objectName().isEmpty())
            WidgetGetNormalX_Ray->setObjectName(QStringLiteral("WidgetGetNormalX_Ray"));
        WidgetGetNormalX_Ray->resize(1400, 1000);
        WidgetGetNormalX_Ray->setStyleSheet(QLatin1String("QWidget#getNormalX_Ray{border-image: url(:/images/bkg6.png);}\n"
"QPushButton{\n"
"    color: white;\n"
"	background-color: rgb(53, 63, 75);\n"
"}"));
        label_Pic = new QLabel(WidgetGetNormalX_Ray);
        label_Pic->setObjectName(QStringLiteral("label_Pic"));
        label_Pic->setGeometry(QRect(70, 20, 900, 900));
        label_Pic->setStyleSheet(QStringLiteral("border-image: url(:/images/bkg5.png);"));
        groupBox_4 = new QGroupBox(WidgetGetNormalX_Ray);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(990, 550, 311, 241));
        groupBox_4->setStyleSheet(QStringLiteral("QRadioButton{color: rgb(0, 170, 255);}"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(0, 30, 91, 16));
        radioButton = new QRadioButton(groupBox_4);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(120, 160, 41, 21));
        radioButton_2 = new QRadioButton(groupBox_4);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(110, 180, 41, 21));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(0, 50, 311, 191));
        label_7->setStyleSheet(QStringLiteral("border-image: url(:/images/lateralLabel.png);"));
        radioButton_3 = new QRadioButton(groupBox_4);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(120, 190, 41, 21));
        radioButton_4 = new QRadioButton(groupBox_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(180, 110, 41, 21));
        radioButton_5 = new QRadioButton(groupBox_4);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(150, 170, 41, 21));
        radioButton_6 = new QRadioButton(groupBox_4);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(170, 190, 41, 21));
        label_7->raise();
        label_6->raise();
        radioButton->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        radioButton_4->raise();
        radioButton_5->raise();
        radioButton_6->raise();
        lineEdit_picth = new QLineEdit(WidgetGetNormalX_Ray);
        lineEdit_picth->setObjectName(QStringLiteral("lineEdit_picth"));
        lineEdit_picth->setGeometry(QRect(1140, 820, 151, 25));
        label_BlumensaatLinePic = new QLabel(WidgetGetNormalX_Ray);
        label_BlumensaatLinePic->setObjectName(QStringLiteral("label_BlumensaatLinePic"));
        label_BlumensaatLinePic->setGeometry(QRect(1170, 460, 131, 101));
        label_BlumensaatLinePic->setStyleSheet(QStringLiteral("border-image: url(:/images/1.1.png);"));
        lineEdit_yaw = new QLineEdit(WidgetGetNormalX_Ray);
        lineEdit_yaw->setObjectName(QStringLiteral("lineEdit_yaw"));
        lineEdit_yaw->setGeometry(QRect(1140, 850, 151, 25));
        lineEdit_2 = new QLineEdit(WidgetGetNormalX_Ray);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(1190, 430, 113, 23));
        label_BlumensaatLine = new QLabel(WidgetGetNormalX_Ray);
        label_BlumensaatLine->setObjectName(QStringLiteral("label_BlumensaatLine"));
        label_BlumensaatLine->setGeometry(QRect(990, 400, 161, 20));
        lineEdit_roll = new QLineEdit(WidgetGetNormalX_Ray);
        lineEdit_roll->setObjectName(QStringLiteral("lineEdit_roll"));
        lineEdit_roll->setGeometry(QRect(1140, 880, 151, 25));
        label_roll = new QLabel(WidgetGetNormalX_Ray);
        label_roll->setObjectName(QStringLiteral("label_roll"));
        label_roll->setGeometry(QRect(1000, 880, 70, 25));
        label_yaw = new QLabel(WidgetGetNormalX_Ray);
        label_yaw->setObjectName(QStringLiteral("label_yaw"));
        label_yaw->setGeometry(QRect(1000, 850, 70, 25));
        label_BlumensaatLinePic_2 = new QLabel(WidgetGetNormalX_Ray);
        label_BlumensaatLinePic_2->setObjectName(QStringLiteral("label_BlumensaatLinePic_2"));
        label_BlumensaatLinePic_2->setGeometry(QRect(990, 460, 131, 101));
        label_BlumensaatLinePic_2->setStyleSheet(QStringLiteral("border-image: url(:/images/4.1.png);"));
        label_1 = new QLabel(WidgetGetNormalX_Ray);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(990, 430, 161, 20));
        lineEdit_BlumensaatLine = new QLineEdit(WidgetGetNormalX_Ray);
        lineEdit_BlumensaatLine->setObjectName(QStringLiteral("lineEdit_BlumensaatLine"));
        lineEdit_BlumensaatLine->setGeometry(QRect(1190, 400, 113, 23));
        label_pitch = new QLabel(WidgetGetNormalX_Ray);
        label_pitch->setObjectName(QStringLiteral("label_pitch"));
        label_pitch->setGeometry(QRect(1000, 820, 70, 25));
        pushButton_loadPic = new QPushButton(WidgetGetNormalX_Ray);
        pushButton_loadPic->setObjectName(QStringLiteral("pushButton_loadPic"));
        pushButton_loadPic->setGeometry(QRect(740, 930, 101, 41));
        pushButton_loadPic->setStyleSheet(QStringLiteral(""));
        pushButton_rectify = new QPushButton(WidgetGetNormalX_Ray);
        pushButton_rectify->setObjectName(QStringLiteral("pushButton_rectify"));
        pushButton_rectify->setGeometry(QRect(860, 930, 111, 41));
        label = new QLabel(WidgetGetNormalX_Ray);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1000, 50, 300, 300));
        label->setStyleSheet(QStringLiteral("border-image: url(:/images/bkg5.png);"));

        retranslateUi(WidgetGetNormalX_Ray);

        QMetaObject::connectSlotsByName(WidgetGetNormalX_Ray);
    } // setupUi

    void retranslateUi(QWidget *WidgetGetNormalX_Ray)
    {
        WidgetGetNormalX_Ray->setWindowTitle(QApplication::translate("WidgetGetNormalX_Ray", "Form", 0));
        label_Pic->setText(QString());
        groupBox_4->setTitle(QString());
        label_6->setText(QApplication::translate("WidgetGetNormalX_Ray", "\347\211\271\345\276\201\347\202\271\351\200\211\346\213\251\357\274\232", 0));
        radioButton->setText(QApplication::translate("WidgetGetNormalX_Ray", "1", 0));
        radioButton_2->setText(QApplication::translate("WidgetGetNormalX_Ray", "2", 0));
        label_7->setText(QString());
        radioButton_3->setText(QApplication::translate("WidgetGetNormalX_Ray", "3", 0));
        radioButton_4->setText(QApplication::translate("WidgetGetNormalX_Ray", "4", 0));
        radioButton_5->setText(QApplication::translate("WidgetGetNormalX_Ray", "5", 0));
        radioButton_6->setText(QApplication::translate("WidgetGetNormalX_Ray", "6", 0));
        label_BlumensaatLinePic->setText(QString());
        label_BlumensaatLine->setText(QApplication::translate("WidgetGetNormalX_Ray", "\345\270\203\346\213\211\351\227\250\350\265\233\347\211\271\347\272\277\351\225\277\345\272\246/mm\357\274\232", 0));
        lineEdit_roll->setText(QString());
        label_roll->setText(QApplication::translate("WidgetGetNormalX_Ray", "C\350\207\202\347\277\273\346\273\232\357\274\232", 0));
        label_yaw->setText(QApplication::translate("WidgetGetNormalX_Ray", "C\350\207\202\345\201\217\350\210\252\357\274\232", 0));
        label_BlumensaatLinePic_2->setText(QString());
        label_1->setText(QApplication::translate("WidgetGetNormalX_Ray", "\345\206\205\345\244\226\344\276\247\350\270\235\351\227\264\350\267\235/mm\357\274\232", 0));
        label_pitch->setText(QApplication::translate("WidgetGetNormalX_Ray", "C\350\207\202\344\277\257\344\273\260\357\274\232", 0));
        pushButton_loadPic->setText(QApplication::translate("WidgetGetNormalX_Ray", "\345\257\274\345\205\245\345\233\276\345\203\217", 0));
        pushButton_rectify->setText(QApplication::translate("WidgetGetNormalX_Ray", "\347\237\253\346\255\243", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WidgetGetNormalX_Ray: public Ui_WidgetGetNormalX_Ray {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETNORMALX_RAY_H
