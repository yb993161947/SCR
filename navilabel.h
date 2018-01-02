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
    void Input_points(Vector3d pp1,Vector3d pp2,Vector3d pp3,Vector3d pp4);
    double Angle(Vector3d d1,Vector3d d2);
    Vector3d Project_line(Vector3d f1,Vector3d f2);
    void setparameters(double size, double radius);
    void setpicture(QPixmap &pix1);
    void setNaviState(bool isWork);
    bool getNavistate();

protected:
    void paintEvent(QPaintEvent *event);

private:
     bool isOpen = false;
     QPixmap pix;
	 QPixmap pix_temp;
     QPointF P1 = QPointF(0,0),P2 = QPointF(0,0);
	 Vector3d p1 = Vector3d(0, 0, 0), p2 = Vector3d(0, 0, 0), p3 = Vector3d(0, 0, 0), p4 = Vector3d(0, 0, 0);
};

#endif // NAVILABEL_H
