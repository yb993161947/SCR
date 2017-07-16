#include "imagescene_Tibia_ap.h"
imageScene_Tibia_ap::imageScene_Tibia_ap(QObject * parent) : ImageScene(parent) {
    QPen pen;  
    pen.setColor(Qt::yellow);
    pen.setWidth(2);

    Line3_4 = new QGraphicsLineItem;//45直线
    addItem(Line3_4);
    Line3_4->setParentItem(&(pixImage));
    Line3_4->setPen(pen);
    Line3_4->hide();

    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::green);

    Line1_2 = new QGraphicsLineItem;//12直线
    addItem(Line1_2);
    Line1_2->setParentItem(&(pixImage));
    Line1_2->setPen(pen);
    Line1_2->hide();

    //Marker_Tip = new QGraphicsLineItem;//探针
    //addItem(Marker_Tip);
    //Marker_Tip->setParentItem(&(pixImage));
    //Marker_Tip->setPen(pen);
    //Marker_Tip->hide();

    pen.setColor(Qt::red);
    pen.setWidth(1);

    subline1 = new QGraphicsLineItem;//
    addItem(subline1);
    subline1->setParentItem(&(pixImage));
    subline1->setPen(pen);
    subline1->hide();
    radioB4toB3 = 0;



}

imageScene_Tibia_ap::~imageScene_Tibia_ap() {
	
}

void imageScene_Tibia_ap::show_otherItem()
{
    if (Piximage_point[0] != QPointF(-1, -1)
            && Piximage_point[1] != QPointF(-1, -1) )
    {
        Line1_2->setLine(Piximage_point[0].x(),Piximage_point[0].y(),Piximage_point[1].x(),Piximage_point[1].y());
        Line1_2->show();
    }

    if(Piximage_point[3] != QPointF(-1,-1) && Piximage_point[2] != QPointF(-1,-1))
    {
       Line3_4->setLine(Piximage_point[2].x(),Piximage_point[2].y(),Piximage_point[3].x(),Piximage_point[3].y());
       Line3_4->show();
    }	
          if (Piximage_point[0] != QPointF(-1, -1)
            && Piximage_point[1] != QPointF(-1, -1)
            && Piximage_point[2] != QPointF(-1, -1))
        {
			  float disB3toLine12 = distance_DotToLine(Piximage_point[1], Piximage_point[0], Piximage_point[2]);
			  float disB4toLine12 = disB3toLine12 * radioB4toB3;

			  subline1->setLine(offsetLine(Piximage_point[0], Piximage_point[1], disB4toLine12));
        }
}

float imageScene_Tibia_ap::distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot)
{
	float A = linePoint2.y() - linePoint1.y();
	float B = linePoint1.x() - linePoint2.x();
	float C = linePoint1.y() * linePoint2.x() - linePoint1.x() * linePoint2.y();
	float d = (A * dot.x() + B * dot.y() + C) /sqrt(A * A + B * B);
    return d;
}

QLineF imageScene_Tibia_ap::offsetLine(QPointF linePoint1, QPointF linePoint2, float distance)
{
    QPointF P1,P2;
    float sita = atan2f(linePoint2.y() - linePoint1.y(), linePoint2.x() - linePoint1.x())+PI/2;
    float move_x = distance *cosf(sita);
    float move_y = distance *sinf(sita);
    P1.setX(linePoint1.x() +  move_x);
    P1.setY(linePoint1.y() + move_y);
    P2.setX(linePoint2.x() +  move_x);
    P2.setY(linePoint2.y() + move_y);
    QLineF line(P1,P2);
    return line;
}

void imageScene_Tibia_ap::showsubline1(float radio)
{
         radioB4toB3 = radio;
          if (Piximage_point[0] != QPointF(-1, -1)
              && Piximage_point[1] != QPointF(-1, -1)
              && Piximage_point[2] != QPointF(-1, -1))
          {
              float disB3toLine12 = distance_DotToLine(Piximage_point[1], Piximage_point[0], Piximage_point[2]);
              float disB4toLine12 =  disB3toLine12 * radioB4toB3;

              subline1->setLine(offsetLine(Piximage_point[0],Piximage_point[1],disB4toLine12));

          }

          subline1->show();
          update();
}
