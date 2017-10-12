#include "imagescene_femur_lat.h"

imageScene_Femur_Lat::imageScene_Femur_Lat(QObject * parent) : ImageScene(parent) {


    tablesketch = new TableSketch_Item;//四方格
	addItem(tablesketch);
	tablesketch->setParentItem(&(pixImage));
	tablesketch->setPos(0, 0);
	tablesketch->hide();

    QPen pen;

    pen.setColor(Qt::yellow);
    pen.setWidth(2);

    Line4_5 = new QGraphicsLineItem;//45直线
    addItem(Line4_5);
    Line4_5->setParentItem(&(pixImage));
    Line4_5->setPen(pen);
    Line4_5->hide();

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
	pen.setStyle(Qt::DashLine);
	pen.setColor(Qt::red);

    subline1 = new QGraphicsLineItem;//
    addItem(subline1);
    subline1->setParentItem(&(pixImage));
    subline1->setPen(pen);
    subline1->hide();

    subline2 = new QGraphicsLineItem;//
    addItem(subline2);
    subline2->setParentItem(&(pixImage));
    subline2->setPen(pen);
    subline2->hide();

}

imageScene_Femur_Lat::~imageScene_Femur_Lat() {
	
}

void imageScene_Femur_Lat::show_otherItem()
{
    if (Piximage_point[0] != QPointF(-1, -1)
            && Piximage_point[1] != QPointF(-1, -1) )
    {
        Line1_2->setLine(Piximage_point[0].x(),Piximage_point[0].y(),Piximage_point[1].x(),Piximage_point[1].y());
        Line1_2->show();
    }

    if (Piximage_point[0] != QPointF(-1, -1)
		&& Piximage_point[1] != QPointF(-1, -1) 
		&& Piximage_point[2] != QPointF(-1, -1))
	{
		tablesketch->setPos(Piximage_point[1]);
		float angle = cvFastArctan(Piximage_point[0].y() - Piximage_point[1].y(), Piximage_point[0].x() - Piximage_point[1].x());//旋转角
		float l_width = sqrt((Piximage_point[0].x() - Piximage_point[1].x())*(Piximage_point[0].x() - Piximage_point[1].x()) +
			(Piximage_point[0].y() - Piximage_point[1].y())*(Piximage_point[0].y() - Piximage_point[1].y()));//直线长度即宽
		float l_height = distance_DotToLine(Piximage_point[0], Piximage_point[1], Piximage_point[2]);//点到直线距离即高
		tablesketch->setTransform(QTransform().rotate(angle));
		tablesketch->setWidth(l_width);
		tablesketch->setHeight(l_height);
		tablesketch->show();
        if(Piximage_point[3] != QPointF(-1, -1))
        {
            float P3toLine12 = distance_DotToLine(Piximage_point[1],Piximage_point[0],Piximage_point[2]);
            float P4toLine12 = distance_DotToLine(Piximage_point[1],Piximage_point[0],Piximage_point[3]);
            float radioP4P3 = P4toLine12 / P3toLine12;
            emit dotsHasSelected1(radioP4P3);
        }
        if(Piximage_point[4] != QPointF(-1, -1))
        {
            float P3toLine12 = distance_DotToLine(Piximage_point[1],Piximage_point[0],Piximage_point[2]);
            float P5toLine12 = distance_DotToLine(Piximage_point[1],Piximage_point[0],Piximage_point[4]);
            float radioP5P3 = P5toLine12 / P3toLine12;
            emit dotsHasSelected2(radioP5P3);
        }
    }
    if(Piximage_point[3] != QPointF(-1,-1) &&
            Piximage_point[4] != QPointF(-1,-1))
    {
       Line4_5->setLine(Piximage_point[4].x(),Piximage_point[4].y(),Piximage_point[3].x(),Piximage_point[3].y());
       Line4_5->show();
    }
//	update();

	
}

float imageScene_Femur_Lat::distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot)
{
	float A = linePoint2.y() - linePoint1.y();
	float B = linePoint1.x() - linePoint2.x();
	float C = linePoint1.y() * linePoint2.x() - linePoint1.x() * linePoint2.y();
	float d = (A * dot.x() + B * dot.y() + C) /sqrt(A * A + B * B);
    return d;
}
