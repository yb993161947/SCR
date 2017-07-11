/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget_getXRay
{
public:
    QRadioButton *radioButton_4;
    QTextBrowser *textBrowserMeasureValue;
    QLabel *labelReferencePicture;
    QRadioButton *radioButton_3;
    QLabel *label_3;
    QLabel *label;
    QPushButton *pushButtonOpenPicture;
    QLabel *label_2;
    QTextEdit *textEditReferenceValue;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QLabel *label_4;
    QTextBrowser *textBrowserMeasureValue_Angle;

    void setupUi(QWidget *Widget_getXRay)
    {
        if (Widget_getXRay->objectName().isEmpty())
            Widget_getXRay->setObjectName(QStringLiteral("Widget_getXRay"));
        Widget_getXRay->resize(1280, 768);
        Widget_getXRay->setMaximumSize(QSize(1280, 768));
        Widget_getXRay->setStyleSheet(QStringLiteral(""));
        radioButton_4 = new QRadioButton(Widget_getXRay);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(921, 523, 115, 19));
        radioButton_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        textBrowserMeasureValue = new QTextBrowser(Widget_getXRay);
        textBrowserMeasureValue->setObjectName(QStringLiteral("textBrowserMeasureValue"));
        textBrowserMeasureValue->setGeometry(QRect(1150, 200, 81, 31));
        labelReferencePicture = new QLabel(Widget_getXRay);
        labelReferencePicture->setObjectName(QStringLiteral("labelReferencePicture"));
        labelReferencePicture->setGeometry(QRect(720, 410, 280, 280));
        labelReferencePicture->setStyleSheet(QLatin1String("background-image: url(:/new/prefix1/images/bkg41.png);\n"
"border-image: url(:/new/prefix1/images/16_07_23-11_51_20-STD.XA._.12.1.2016.07.23.12.36.14.953125.8774122.BMP);\n"
""));
        radioButton_3 = new QRadioButton(Widget_getXRay);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(780, 540, 115, 19));
        radioButton_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        label_3 = new QLabel(Widget_getXRay);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1060, 260, 201, 221));
        label_3->setStyleSheet(QStringLiteral("color: rgb(244, 244, 244);"));
        label_3->setTextFormat(Qt::AutoText);
        label_3->setWordWrap(true);
        label = new QLabel(Widget_getXRay);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1050, 200, 81, 31));
        label->setStyleSheet(QLatin1String("color: rgb(235, 235, 235);\n"
""));
        pushButtonOpenPicture = new QPushButton(Widget_getXRay);
        pushButtonOpenPicture->setObjectName(QStringLiteral("pushButtonOpenPicture"));
        pushButtonOpenPicture->setGeometry(QRect(1060, 100, 101, 41));
        pushButtonOpenPicture->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/images/openImage.png);"));
        label_2 = new QLabel(Widget_getXRay);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1050, 160, 81, 31));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"\n"
"\n"
""));
        textEditReferenceValue = new QTextEdit(Widget_getXRay);
        textEditReferenceValue->setObjectName(QStringLiteral("textEditReferenceValue"));
        textEditReferenceValue->setGeometry(QRect(1149, 157, 81, 31));
        radioButton_1 = new QRadioButton(Widget_getXRay);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setGeometry(QRect(890, 580, 115, 19));
        radioButton_1->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        radioButton_2 = new QRadioButton(Widget_getXRay);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(890, 430, 115, 19));
        radioButton_2->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        label_4 = new QLabel(Widget_getXRay);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1040, 250, 81, 31));
        label_4->setStyleSheet(QLatin1String("color: rgb(235, 235, 235);\n"
""));
        textBrowserMeasureValue_Angle = new QTextBrowser(Widget_getXRay);
        textBrowserMeasureValue_Angle->setObjectName(QStringLiteral("textBrowserMeasureValue_Angle"));
        textBrowserMeasureValue_Angle->setGeometry(QRect(1150, 250, 81, 31));
        textBrowserMeasureValue->raise();
        labelReferencePicture->raise();
        radioButton_3->raise();
        label_3->raise();
        label->raise();
        pushButtonOpenPicture->raise();
        label_2->raise();
        textEditReferenceValue->raise();
        radioButton_1->raise();
        radioButton_2->raise();
        radioButton_4->raise();
        label_4->raise();
        textBrowserMeasureValue_Angle->raise();

        retranslateUi(Widget_getXRay);

        QMetaObject::connectSlotsByName(Widget_getXRay);
    } // setupUi

    void retranslateUi(QWidget *Widget_getXRay)
    {
        Widget_getXRay->setWindowTitle(QApplication::translate("Widget_getXRay", "Widget", 0));
        radioButton_4->setText(QApplication::translate("Widget_getXRay", "\346\265\213\351\207\2172", 0));
        labelReferencePicture->setText(QString());
        radioButton_3->setText(QApplication::translate("Widget_getXRay", "\346\265\213\351\207\2171", 0));
        label_3->setText(QApplication::translate("Widget_getXRay", "\345\212\237\350\203\2751 \346\265\213\347\233\270\345\257\271\351\225\277\345\272\246\357\274\232\n"
"1.\346\211\223\345\274\200\346\265\213\351\207\217\345\233\276\347\211\207\n"
"2.\351\200\211\346\213\251\345\217\202\350\200\203\347\202\271\344\270\216\346\265\213\351\207\217\347\202\271\n"
"3.\350\276\223\345\205\245\345\217\202\350\200\203\351\225\277\345\272\246\n"
"\345\212\237\350\203\2752 \346\265\213\347\233\264\347\272\277\345\244\271\350\247\222\357\274\232\n"
"\346\211\223\345\274\200\346\265\213\351\207\217\345\233\276\347\211\207\n"
"2.\351\200\211\346\213\251\345\217\202\350\200\203\347\202\271\344\270\216\346\265\213\351\207\217\347\202\271\n"
"", 0));
        label->setText(QApplication::translate("Widget_getXRay", "\346\265\213\351\207\217\345\200\274\357\274\232", 0));
        pushButtonOpenPicture->setText(QString());
        label_2->setText(QApplication::translate("Widget_getXRay", "\345\217\202\350\200\203\351\225\277\345\272\246\357\274\232", 0));
        radioButton_1->setText(QApplication::translate("Widget_getXRay", "\345\217\202\350\200\2031", 0));
        radioButton_2->setText(QApplication::translate("Widget_getXRay", "\345\217\202\350\200\2032", 0));
        label_4->setText(QApplication::translate("Widget_getXRay", "\347\233\264\347\272\277\345\244\271\350\247\222\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget_getXRay: public Ui_Widget_getXRay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
