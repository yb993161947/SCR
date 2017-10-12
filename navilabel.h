#ifndef NAVILABEL_H
#define NAVILABEL_H
#include<vector>
#include<math.h>
#include<iostream>
#include"./Eigen/Eigen"
#include<qpixmap.h>
#include "QPainter"
#include "QLabel"
using namespace std;
using namespace Eigen;
using std::vector;
class NaviLabel : public QLabel
{
public:
    double ang1,ang2,ori,siz,rad;
    NaviLabel(QWidget *parent = 0);
    ~NaviLabel();
    void Input_points(Vector3d p1,Vector3d p2,Vector3d p3,Vector3d p4);
    double Angle(Vector3d d1,Vector3d d2);
    Vector3d Project_line(Vector3d f1,Vector3d f2);
    void setparameters(double size, double radius);
    void setpicture(QPixmap &pix1);

//
//protected:
//    void paintEvent(QPaintEvent *event);

private:

     QPixmap pix;
	 QPixmap pix_temp;
     QPointF P1,P2;
};

#endif // NAVILABEL_H
