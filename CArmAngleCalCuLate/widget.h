#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include "Eigen/Eigen"
#define labelOpenPictureWidth  600;
#define labelOpenPictureHeight 600;

using namespace Eigen;
namespace Ui {
class  CArmWidget;
}

class CArmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CArmWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent * );

    ~CArmWidget();

    void axisangle_2_matrix(const double AxisAngle[3], Matrix3d &m);

    void matrix_2_axisangle(const Matrix3d &m, double AxisAngle[3]);

    void matrix_2_Rotate(const Matrix3d &m,double AxisAngle[3]);

private:
     void enlargePic(const QPoint originalImagePos1, int width, int height);

     void mouseReleaseEvent(QMouseEvent *event);

     double Distance_Point(QPointF StartPoint,QPointF EndPoint);//两直线距离
     double Angle_Point(QPointF Line1,QPointF Line2);
     int iRadioButtonIndex;
     double dx,dy;//相对于图像原点的标定点的实际位置

     QPoint originalImagePos,qPoint_MousePoint,enlargedImagePoint,qPoint_originalImagePoint[8];
     QButtonGroup btnGroupFruits,btnGroupFruits_2;
     QString qStr_ImageFilePath;
     QPixmap OpenPiture, EnlargedPicture, OpenPiture_temp,Bkg;
     QPointF qPoint_MousePoint1;

     void MeasureLength(QPoint qPoint[4]);
     void calculateAngle();

private slots:

    void on_pushButtonOpenPicture_clicked();

    void on_textEditReferenceValue_textChanged();

    void on_lineEdit_B_textChanged(const QString &arg1);

    void on_lineEdit_ankle_textChanged(const QString &arg1);

    void on_radioButton_femur_clicked();
    
    void on_radioButton_tibia_clicked();
    

private:
    Ui::CArmWidget *ui;
};

#endif // WIDGET_H
