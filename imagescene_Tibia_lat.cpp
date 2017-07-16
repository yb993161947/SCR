#include "imagescene_Tibia_lat.h"
imageScene_Tibia_lat::imageScene_Tibia_lat(QObject * parent) : ImageScene(parent) {
    QPen pen;

    pen.setColor(Qt::yellow);
    pen.setWidth(2);


    Line5_6 = new QGraphicsLineItem;//56直线
    addItem(Line5_6);
    Line5_6->setParentItem(&(pixImage));
    Line5_6->setPen(pen);
    Line5_6->hide();

    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::green);

    Line1_2 = new QGraphicsLineItem();//12直线
    addItem(Line1_2);
    Line1_2->setParentItem(&(pixImage));
    Line1_2->setPen(pen);
    Line1_2->hide();

    pen.setStyle(Qt::SolidLine);//12交点提示
    pen.setColor(Qt::red);
    Line1_2cross= new QGraphicsLineItem();
    addItem(Line1_2cross);
    Line1_2cross->setPen(pen);
    Line1_2cross->setParentItem(&(pixImage));
    Line1_2cross->hide();

    pen.setColor(Qt::green);
    Line1_4 = new QGraphicsLineItem;//14直线
    Line1_4->setParentItem(&(pixImage));
    addItem(Line1_4);
    Line1_4->setPen(pen);
	Line1_4->hide();

    Line2_3 = new QGraphicsLineItem;//23直线
    addItem(Line2_3);
    Line2_3->setParentItem(&(pixImage));
    Line2_3->setPen(pen);
    Line2_3->hide();

    //Marker_Tip = new QGraphicsLineItem;//探针
    //addItem(Marker_Tip);
    //Marker_Tip->setParentItem(&(pixImage));
    //Marker_Tip->setPen(pen);
    //Marker_Tip->hide();

}

imageScene_Tibia_lat::~imageScene_Tibia_lat() {
	
}

void imageScene_Tibia_lat::show_otherItem()
{
    if (Piximage_point[0] != QPointF(-1, -1)
            && Piximage_point[1] != QPointF(-1, -1) )
    {
        Line1_2->setLine(Piximage_point[0].x(),Piximage_point[0].y(),Piximage_point[1].x(),Piximage_point[1].y());
        //画十字

        QPointF dir = QPointF((Piximage_point[1].x() - Piximage_point[0].x()) * 0.46,(Piximage_point[1].y()-  Piximage_point[0].y())* 0.46);
        QPointF dir_ver = QPointF((dir.y()) * 0.46, -(dir.x()) * 0.46);
        Line1_2cross->setLine(QLineF(dir+dir_ver+Piximage_point[0] , dir-dir_ver+Piximage_point[0]) );

        Line1_2->show();
        Line1_2cross->show();

    }

    if (Piximage_point[0] != QPointF(-1, -1)
            && Piximage_point[3] != QPointF(-1, -1) )
    {
        Line1_4->setLine(Piximage_point[0].x(),Piximage_point[0].y(),Piximage_point[3].x(),Piximage_point[3].y());
        Line1_4->show();
    }

    if (Piximage_point[1] != QPointF(-1, -1)
            && Piximage_point[2] != QPointF(-1, -1) )
    {
        Line2_3->setLine(Piximage_point[1].x(),Piximage_point[1].y(),Piximage_point[2].x(),Piximage_point[2].y());
        Line2_3->show();
    }

    if(Piximage_point[4] != QPointF(-1,-1) && Piximage_point[5] != QPointF(-1,-1))
    {
       Line5_6->setLine(Piximage_point[4].x(),Piximage_point[4].y(),Piximage_point[5].x(),Piximage_point[5].y());
       Line5_6->show();
    }
    if(Piximage_point[0] != QPointF(-1,-1) && Piximage_point[1] != QPointF(-1,-1)
            && Piximage_point[4] != QPointF(-1,-1) && Piximage_point[5] != QPointF(-1,-1))
    {
        float distance5to12 = distance_DotToLine(Piximage_point[0],Piximage_point[1],Piximage_point[4]);
        float distance6to12 = distance_DotToLine(Piximage_point[0],Piximage_point[1],Piximage_point[5]);
        float radio = distance6to12 / distance5to12 ;
        emit dotsHasSelected1(radio);
    }

	
}

float imageScene_Tibia_lat::distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot)
{
	float A = linePoint2.y() - linePoint1.y();
	float B = linePoint1.x() - linePoint2.x();
	float C = linePoint1.y() * linePoint2.x() - linePoint1.x() * linePoint2.y();
	float d = (A * dot.x() + B * dot.y() + C) /sqrt(A * A + B * B);
	return d;
}
