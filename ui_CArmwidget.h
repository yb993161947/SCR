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
    QRadioButton *radioButton_4;
    QLabel *labelReferencePicture;
    QRadioButton *radioButton_3;
    QPushButton *pushButtonOpenPicture;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_2;
    QLabel *label_line1_2;
    QLineEdit *lineEdit_line1;
    QLineEdit *lineEdit_line2;
    QLabel *label_line2;
    QLabel *label_result2;
    QLabel *label_result2_2;
    QPushButton *pushButton_calculate2;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_Ry;
    QLabel *label_5;
    QLabel *label_Rz;
    QLabel *label_6;
    QLabel *label_Rx;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLineEdit *lineEdit_B;
    QLabel *label_7;
    QLineEdit *lineEdit_ankle;
    QTextBrowser *textBrowserMeasureValue;
    QLabel *label_2;
    QTextEdit *textEditReferenceValue;
    QLabel *label_4;
    QTextBrowser *textBrowserMeasureValue_Angle;
    QLabel *label;

    void setupUi(QWidget *CArmWidget)
    {
        if (CArmWidget->objectName().isEmpty())
            CArmWidget->setObjectName(QStringLiteral("CArmWidget"));
        CArmWidget->resize(1280, 768);
        CArmWidget->setMaximumSize(QSize(1280, 768));
        CArmWidget->setStyleSheet(QStringLiteral(""));
        radioButton_4 = new QRadioButton(CArmWidget);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(710, 600, 71, 19));
        radioButton_4->setLayoutDirection(Qt::RightToLeft);
        radioButton_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        labelReferencePicture = new QLabel(CArmWidget);
        labelReferencePicture->setObjectName(QStringLiteral("labelReferencePicture"));
        labelReferencePicture->setGeometry(QRect(720, 410, 280, 280));
        labelReferencePicture->setStyleSheet(QLatin1String("border-image: url(:/images/sketch.png);\n"
""));
        radioButton_3 = new QRadioButton(CArmWidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(720, 580, 71, 20));
        radioButton_3->setLayoutDirection(Qt::RightToLeft);
        radioButton_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        pushButtonOpenPicture = new QPushButton(CArmWidget);
        pushButtonOpenPicture->setObjectName(QStringLiteral("pushButtonOpenPicture"));
        pushButtonOpenPicture->setGeometry(QRect(1030, 110, 81, 31));
        pushButtonOpenPicture->setStyleSheet(QLatin1String("border-image: url(:/images/btn.png);\n"
"color: rgb(255, 255, 255);"));
        radioButton_1 = new QRadioButton(CArmWidget);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(780, 610, 61, 19));
        radioButton_1->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_2 = new QRadioButton(CArmWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(870, 470, 115, 19));
        radioButton_2->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        groupBox_2 = new QGroupBox(CArmWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(1030, 290, 231, 161));
        label_line1_2 = new QLabel(groupBox_2);
        label_line1_2->setObjectName(QStringLiteral("label_line1_2"));
        label_line1_2->setGeometry(QRect(20, 40, 61, 21));
        lineEdit_line1 = new QLineEdit(groupBox_2);
        lineEdit_line1->setObjectName(QStringLiteral("lineEdit_line1"));
        lineEdit_line1->setGeometry(QRect(100, 40, 113, 23));
        lineEdit_line2 = new QLineEdit(groupBox_2);
        lineEdit_line2->setObjectName(QStringLiteral("lineEdit_line2"));
        lineEdit_line2->setGeometry(QRect(100, 70, 113, 23));
        label_line2 = new QLabel(groupBox_2);
        label_line2->setObjectName(QStringLiteral("label_line2"));
        label_line2->setGeometry(QRect(20, 70, 61, 21));
        label_result2 = new QLabel(groupBox_2);
        label_result2->setObjectName(QStringLiteral("label_result2"));
        label_result2->setGeometry(QRect(20, 110, 71, 21));
        label_result2_2 = new QLabel(groupBox_2);
        label_result2_2->setObjectName(QStringLiteral("label_result2_2"));
        label_result2_2->setGeometry(QRect(100, 100, 111, 51));
        pushButton_calculate2 = new QPushButton(CArmWidget);
        pushButton_calculate2->setObjectName(QStringLiteral("pushButton_calculate2"));
        pushButton_calculate2->setGeometry(QRect(1170, 480, 91, 31));
        pushButton_calculate2->setStyleSheet(QLatin1String("border-image: url(:/images/btn.png);\n"
"color: rgb(255, 255, 255);"));
        radioButton_5 = new QRadioButton(CArmWidget);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(840, 600, 71, 20));
        radioButton_5->setLayoutDirection(Qt::LeftToRight);
        radioButton_5->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        radioButton_6 = new QRadioButton(CArmWidget);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(860, 620, 71, 20));
        radioButton_6->setLayoutDirection(Qt::LeftToRight);
        radioButton_6->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        layoutWidget = new QWidget(CArmWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1030, 580, 231, 81));
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

        layoutWidget1 = new QWidget(CArmWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1030, 520, 231, 55));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 0, 0, 1, 1);

        lineEdit_B = new QLineEdit(layoutWidget1);
        lineEdit_B->setObjectName(QStringLiteral("lineEdit_B"));

        gridLayout_3->addWidget(lineEdit_B, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        lineEdit_ankle = new QLineEdit(layoutWidget1);
        lineEdit_ankle->setObjectName(QStringLiteral("lineEdit_ankle"));

        gridLayout_3->addWidget(lineEdit_ankle, 1, 1, 1, 1);

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
        labelReferencePicture->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        radioButton_3->raise();
        pushButtonOpenPicture->raise();
        radioButton_1->raise();
        radioButton_2->raise();
        radioButton_4->raise();
        groupBox_2->raise();
        pushButton_calculate2->raise();
        radioButton_5->raise();
        radioButton_6->raise();

        retranslateUi(CArmWidget);

        QMetaObject::connectSlotsByName(CArmWidget);
    } // setupUi

    void retranslateUi(QWidget *CArmWidget)
    {
        CArmWidget->setWindowTitle(QApplication::translate("CArmWidget", "Widget", 0));
        radioButton_4->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2173", 0));
        labelReferencePicture->setText(QString());
        radioButton_3->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2172", 0));
        pushButtonOpenPicture->setText(QApplication::translate("CArmWidget", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        radioButton_1->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2030", 0));
        radioButton_2->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\2031", 0));
        groupBox_2->setTitle(QApplication::translate("CArmWidget", "\350\256\241\347\256\227\350\247\222\345\272\246", 0));
        label_line1_2->setText(QApplication::translate("CArmWidget", "\347\233\264\350\247\222\350\276\2711\357\274\232", 0));
        label_line2->setText(QApplication::translate("CArmWidget", "\347\233\264\350\247\222\350\276\2712\357\274\232", 0));
        label_result2->setText(QApplication::translate("CArmWidget", "\350\256\241\347\256\227\347\273\223\346\236\234\357\274\232", 0));
        label_result2_2->setText(QString());
        pushButton_calculate2->setText(QApplication::translate("CArmWidget", "\350\256\241\347\256\227", 0));
        radioButton_5->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2174", 0));
        radioButton_6->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\2175", 0));
        label_3->setText(QApplication::translate("CArmWidget", "C\350\207\202\344\277\257\344\273\260\357\274\232", 0));
        label_Ry->setText(QString());
        label_5->setText(QApplication::translate("CArmWidget", "C\350\207\202\347\277\273\350\275\254\357\274\232", 0));
        label_Rz->setText(QString());
        label_6->setText(QApplication::translate("CArmWidget", "C\350\207\202\345\201\217\350\275\254\357\274\232", 0));
        label_Rx->setText(QString());
        label_8->setText(QApplication::translate("CArmWidget", "\345\270\203\346\213\211\351\227\250\350\265\233\347\211\271\347\272\277\357\274\232", 0));
        label_7->setText(QApplication::translate("CArmWidget", "\350\270\235\351\227\264\350\267\235\357\274\232", 0));
        label_2->setText(QApplication::translate("CArmWidget", "\345\217\202\350\200\203\351\225\277\345\272\246\357\274\232", 0));
        label_4->setText(QApplication::translate("CArmWidget", "\347\233\264\347\272\277\345\244\271\350\247\222\357\274\232", 0));
        label->setText(QApplication::translate("CArmWidget", "\346\265\213\351\207\217\345\200\274\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class CArmWidget: public Ui_CArmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARMWIDGET_H
