#include "navilabel.h"
#include "qdebug.h"
NaviLabel::NaviLabel(QWidget *parent):QLabel(parent)
{
    P1 = QPointF(-1,-1);
    P2 = QPointF(-1,-1);



}

NaviLabel::~NaviLabel()
{

}

void NaviLabel::Input_points(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4)
{

	Vector3d X_ = p1.cross(p2);
	X_ = X_ / X_.norm();
	Vector3d Z_ = p1 - p2;
	Z_ = Z_ / Z_.norm();
	cout << (p3 - p4) / (p3 - p4).norm();
	Vector3d Y_ = Z_.cross(X_);
	Matrix4d  O_;
	O_.col(0).head(3) = X_;
	O_.col(1).head(3) = Y_;
	O_.col(2).head(3) = Z_;
	O_.col(3).head(3) = p2;
	O_.row(3) << 0, 0, 0, 1;
	Vector4d Dir;
	Dir.head(3) = (p3-p4) /(p3-p4).norm() * 80 + p4;
	Dir(3) = 1;
	Matrix4d O_inverse = O_.inverse();
	Vector2d tp3 = (O_inverse * Dir).head(2);
	Dir.head(3) = p4;
	Vector2d tp4 = (O_inverse * Dir).head(2);

    P1.setX(tp3(0) / rad * siz / 12+ori);
    P1.setY(tp3(1) / rad * siz / 12+ori);
    P2.setX(tp4(0) / rad * siz / 12+ori);
    P2.setY(tp4(1) / rad * siz / 12+ori);

	if (pix.isNull())
		return;
	pix_temp = pix;
	if (P1 != QPointF(-1, -1) && P2 != QPointF(-1, -1))
	{
		QPainter painter(this);
		painter.begin(&pix_temp);
		if (((P1.x() - ori)*(P1.x() - ori) + (P1.y() - ori)*(P1.y() - ori) < rad*rad) 
			&& ((P2.x() - ori)*(P2.x() - ori) + (P2.y() - ori)*(P2.y() - ori) < rad*rad))
		{
			painter.setPen(QPen(Qt::green, 5));
			painter.drawLine(P1, P2);
			painter.drawEllipse(QRect(P2.x() - 5, P2.y() - 5, 10, 10));
		}
		else
		{
			painter.setPen(QPen(Qt::red, 5));
			painter.drawLine(P1, P2);
			painter.drawEllipse(QRect(P2.x() - 5, P2.y() - 5, 10, 10));
		}

		painter.setPen(QPen(Qt::magenta, 3, Qt::DashLine));
		painter.drawLine(QPoint(ori, ori), QPoint(((P1.x() + P2.x()) / 2), ((P1.y() + P2.y()) / 2)));

		painter.end();
	}
	setPixmap(pix_temp);
 }


double NaviLabel::Angle(Vector3d d1,Vector3d d2)
{
    double kousai=(d1(0)*d2(0)+d1(1)*d2(1)+d1(2)*d2(2))/sqrt(d1(0)*d1(0)+d1(1)*d1(1)+d1(2)*d1(2))/sqrt(d2(0)*d2(0)+d2(1)*d2(1)+d2(2)*d2(2));
    return (double) acos(kousai);
}
Vector3d NaviLabel::Project_line(Vector3d f1, Vector3d f2)
{

    Vector3d f3=f2/sqrt(f2(0)*f2(0)+f2(1)*f2(1)+f2(2)*f2(2))*(sqrt(f1(0)*f1(0)+f1(1)*f1(1)+f1(2)*f1(2))*(double) cos(Angle(f1,f2)));
    return f3;
}

void NaviLabel::setparameters(double size, double radius)
{
    siz=size;
    ori = size / 2;
    rad=radius;
    setGeometry(x(),y(),siz,siz);
}


void NaviLabel::setpicture(QPixmap &pix1)
{
    pix = pix1.scaled(siz,siz);
//	setPixmap(pix);
}

//void NaviLabel::paintEvent(QPaintEvent *event)
//{
//
//}	

