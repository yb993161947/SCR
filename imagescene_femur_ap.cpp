#include "imagescene_femur_AP.h"
#include "qdebug.h"
#include "needle.h"
imageScene_Femur_AP::imageScene_Femur_AP(QObject * parent) : ImageScene(parent) {

    QPen pen;

    pen.setColor(Qt::yellow);
    pen.setWidth(2);

    Line4_5 = new QGraphicsLineItem;//45直线
    addItem(Line4_5);
    Line4_5->setParentItem(&(pixImage));
    Line4_5->setPen(pen);
    Line4_5->hide();

    pen.setColor(Qt::green);
    pen.setStyle(Qt::DashLine);

    Line1_2 = new QGraphicsLineItem;//12直线
    addItem(Line1_2);
    Line1_2->setParentItem(&(pixImage));
    Line1_2->setPen(pen);
    Line1_2->hide();

    Marker_Tip = new QGraphicsLineItem;//探针
    addItem(Marker_Tip);
    Marker_Tip->setParentItem(&(pixImage));
    Marker_Tip->setPen(pen);
    Marker_Tip->hide();

    pen.setColor(Qt::red);
    pen.setWidth(1);

    subline1 = new QGraphicsLineItem;//
    addItem(subline1);
    subline1->setParentItem(&(pixImage));
    subline1->setPen(pen);
    subline1->hide();
	radioA4toA3 = 0;

    subline2 = new QGraphicsLineItem;//
    addItem(subline2);
    subline2->setParentItem(&(pixImage));
    subline2->setPen(pen);
    subline2->hide();
    radioA5toA3 = 0;

}

imageScene_Femur_AP::~imageScene_Femur_AP() {
	
}

void imageScene_Femur_AP::show_otherItem()
{
    if (Piximage_point[0] != QPointF(-1, -1)
            && Piximage_point[1] != QPointF(-1, -1) )
    {
        Line1_2->setLine(Piximage_point[0].x(),Piximage_point[0].y(),Piximage_point[1].x(),Piximage_point[1].y());
        Line1_2->show();
    }

    if(Piximage_point[3] != QPointF(-1,-1)
            && Piximage_point[4] != QPointF(-1,-1))
    {
       Line4_5->setLine(Piximage_point[4].x(),Piximage_point[4].y(),Piximage_point[3].x(),Piximage_point[3].y());
       Line4_5->show();
    }
    if (Piximage_point[0] != QPointF(-1, -1)
        && Piximage_point[1] != QPointF(-1, -1)
        && Piximage_point[2] != QPointF(-1, -1))
    {
        float disA3toLine12 = distance_DotToLine(Piximage_point[0], Piximage_point[1], Piximage_point[2]);
        float disA4toLine12 =disA3toLine12 - disA3toLine12 * radioA4toA3;
        subline1->setLine(offsetLine(Piximage_point[0],Piximage_point[1],disA4toLine12));

        float disA5toLine12 = disA3toLine12 * radioA5toA3;
        subline2->setLine(offsetLine(Piximage_point[0], Piximage_point[1], -disA5toLine12 + disA3toLine12));
	}
	
}

float imageScene_Femur_AP::distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot)
{
	float A = linePoint2.y() - linePoint1.y();
	float B = linePoint1.x() - linePoint2.x();
	float C = linePoint1.y() * linePoint2.x() - linePoint1.x() * linePoint2.y();
	float d = (A * dot.x() + B * dot.y() + C) /sqrt(A * A + B * B);
    return d;
}

QLineF imageScene_Femur_AP::offsetLine(QPointF linePoint1, QPointF linePoint2, float distance)
{
    QPointF P1,P2;
    QPointF dir = (linePoint2 - linePoint1);
    float length = sqrtf(dir.x() * dir.x() + dir.y() * dir.y());
    dir = dir / length;
    QPointF dir_ver = QPointF(dir.y() , - dir.x());
    P1 = linePoint1 + distance * dir_ver;
    P2 = linePoint2 + distance * dir_ver;
    QLineF line(P1,P2);
    return line;
}

void imageScene_Femur_AP::showsubline1(float radio)
{

      radioA4toA3 = radio;
       if (Piximage_point[0] != QPointF(-1, -1)
           && Piximage_point[1] != QPointF(-1, -1)
           && Piximage_point[2] != QPointF(-1, -1))
       {
           float disA3toLine12 = distance_DotToLine(Piximage_point[0], Piximage_point[1], Piximage_point[2]);
           float disA4toLine12 =disA3toLine12 - disA3toLine12 * radioA4toA3;
           subline1->setLine(offsetLine(Piximage_point[0],Piximage_point[1],disA4toLine12));

       }

       subline1->show();
       update();

}

void imageScene_Femur_AP::showsubline2(float radio)
{
    radioA5toA3 = radio;
    if (Piximage_point[0] != QPointF(-1, -1)
        && Piximage_point[1] != QPointF(-1, -1)
        && Piximage_point[2] != QPointF(-1, -1))
    {
    float disA3toLine12 = distance_DotToLine(Piximage_point[0], Piximage_point[1], Piximage_point[2]);
    float disA5toLine12 = disA3toLine12 * radioA5toA3;
    subline2->setLine(offsetLine(Piximage_point[0], Piximage_point[1], -disA5toLine12 + disA3toLine12));
    }
    subline2->show();
    update();
}

